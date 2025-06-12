#include "GameScene.h"

#include <cstdlib>
#include <ctime>

#include "MainScene.h"
#include "../Score.h"
#include "../../engine/Engine.h"
#include "../../engine/File.h"
#include "../../engine/components/Label.h"

MainScene *main_menu_scene;

GameScene::GameScene(int length, int speed, int level) {
    // assicuriamoci che venga assegnato un seed iniziale ad ogni nuova partita basandoci sull'epoch attuale
    srand(time(nullptr));

    // inizializziamo la variabile che determina se il giocatore ha vinto o perso
    // lasciamo a false e se vince la impostiamo a true
    this->won = false;

    // usato quando andiamo a salvare il punteggio nel file per la visualizzazione nella classifica
    this->level = level;

    // inizializziamo le variabili del punteggio
    this->pointsStr = new char[50];
    this->points = 0;
    this->bonusPoints = 1;

    // inizializziamo le variabili del timer
    this->timerStr = new char[50];
    this->timer = ONE_MINUTE;

    this->rateStr = new char[50];

    // inizializziamo il serpente che gestira' anche il campo di gioco
    this->snake = new Snake(length, speed);
    this->snake->setPosition(1, 1);

    // inizializziamo il modal che viene usato quando l'utente mette in pausa il gioco
    this->modal = new Modal("Do you want to quit the game?");
    this->modal->setVisible(false);
    this->modal->setPosition(getCenteredX(this->modal), 12);

    // inizializziamo l'alert che viene usato per segnalare una vittoria o una sconfitta
    this->alert = new Alert();
    this->alert->setVisible(false);

    // inizializziamo le label del punteggio, del tempo e del rate
    this->pointsLabel = new Label;
    this->pointsLabel->setText(this->pointsStr);
    this->pointsLabel->setColor(ColorPair(COLOR_CYAN));
    this->pointsLabel->setPosition(55, 0);

    this->timerLabel = new Label;
    this->timerLabel->setText(this->timerStr);
    this->timerLabel->setColor(ColorPair(COLOR_YELLOW));
    this->timerLabel->setPosition(43, 0);

    this->rateLabel = new Label;
    this->rateLabel->setText(this->rateStr);
    this->rateLabel->setColor(ColorPair(COLOR_BLUE));
    this->rateLabel->setPosition(30, 0);

    // inizializziamo le stringhe delle label
    sprintf(this->pointsStr, "Points: 0");
    sprintf(this->timerStr, "Time: %d", this->timer / 1000);
    sprintf(this->rateStr, "");

    this->add(this->snake);
    this->add(this->modal);
    this->add(this->alert);
    this->add(this->pointsLabel);
    this->add(this->timerLabel);
    this->add(this->rateLabel);

    // spostiamo immediatamente il focus al drawable corrispondente al campo di gioco
    // 0 perche' this->snake e' il primo elemento
    this->moveFocus(0);
}

void GameScene::setBonusPoints(int bonusPoints) {
    this->bonusPoints = bonusPoints;
}

const char *GameScene::getTitle() {
    return "Snake";
}

void GameScene::run(RunContext *ctx) {
    // esegue la logica base della scena
    Scene::run(ctx);

    // se e' ancora aperto il modal, non fare nulla
    if (this->modal->isOpen()) return;

    // se l'alert e' ancora aperto, non fare nulla
    if (this->alert->isOpen()) return;
    // altrimenti, se e' stato chiuso ma e' ancora visibile
    if (this->alert->isVisible()) {
        // salva il punteggio solo in caso di vittoria
        if (this->won) {
            // apre l'handle del file
            auto file = new File("leaderboard.txt");

            // crea il punteggio e assegna i valori giusti
            auto score = new Score();
            score->score = this->points;
            score->level = (long) level;

            // crea il buffer
            char *line = new char[257]{};
            // scrive il punteggio sul buffer
            score->toString(line);

            // aggiunge alla fine del file il punteggio in stringa
            file->writeLine(line);
            // chiude l'handle del file
            delete file;
        }

        // allora ritorna al menu principale
        main_menu_scene = new MainScene();
        ctx->queueScene(main_menu_scene);
    }

    int combo = 0;

    // muove il serpente e calcola i punti per questo tick
    ScoreType score_type = this->snake->tick(&combo);

    if (combo == 0) {
        sprintf(this->rateStr, "");
    }

    // rimuove dal timer il tempo passato dall'ultimo frame (delta)
    this->timer -= RUN_MILLIS_PER_FRAME;

    // se il timer termina
    if (this->timer <= 0) {
        // allora il giocatore ha vinto
        this->won = true;

        // mostriamo l'alert per segnalare la vittoria
        this->alert->setMsg("Game over!");
        this->alert->setVisible(true);
        this->alert->openAlert();
        this->alert->setPosition(getCenteredX(this->alert), 12);
        this->moveFocus(2);
    }

    // aggiorniamo il timer
    sprintf(this->timerStr, "Time: %d", this->timer / 1000);

    // quando mancano 10 secondi al termine della partita (sono 11 nel check per via dell'arrotondamento)
    // cambia colore ogni secondo tra rosso e bianco per segnalare al giocatore che la partita sta per terminare
    if (this->timer / 1000 % 2 == 0 && this->timer <= 11000) {
        ctx->setBoxColor(ColorPair(COLOR_RED));
    }

    // se la combo e' abbastanza alta, cambia il colore del box ogni secondo per avvisare il giocatore che sta giocando bene
    if (combo >= ON_FIRE_COMBO && this->timer / 1000 % 2 == 1) {
        // inoltre se sta facendo una combo "godlike" anziche' del giallo usa il magenta (caso speciale se la difficolta' e' "god")
        if (combo >= GOD_COMBO) {
            // difficolta' == "god"
            if (this->level == 5) ctx->setBoxColor(ColorPair(COLOR_BLACK, COLOR_RED));
            else ctx->setBoxColor(ColorPair(COLOR_MAGENTA));
        } else ctx->setBoxColor(ColorPair(COLOR_YELLOW));
    }

    // se il tick del serpente e' risultato in un'evento di sconfitta
    if (score_type == S_LOSE) {
        // mostriamo l'alert per segnalare la sconfitta
        this->alert->setMsg("You lost");
        this->alert->setVisible(true);
        this->alert->openAlert();
        this->alert->setPosition(getCenteredX(this->alert), 12);
        this->moveFocus(2);
    } else {
        int points;

        // calcola il punteggio in base alla valutazione dell'azione
        switch (score_type) {
            // ha mangiato la mela ma ci ha messo tanto tempo, quindi punti base (e non viene calcolata la combo che rimane fissa a 1)
            case S_OK:
                points = BASE_POINTS;
                sprintf(this->rateStr, "%s: x%d", "OK", combo);
                break;
            // ha mangiato la mela nel tempo prestabilito, quindi punti base * punti bonus (combo calcolata)
            case S_GOOD:
                points = BASE_POINTS * BONUS_POINTS;
                sprintf(this->rateStr, "%s: x%d", "GOOD", combo);
                break;
            // ha mangiato la mela in un lasso di tempo molto basso, quindi punti base * punti bonus ^ 2 (combo calcolata)
            case S_GREAT:
                points = BASE_POINTS * BONUS_POINTS * BONUS_POINTS;
                sprintf(this->rateStr, "%s: x%d", "GREAT", combo);
                break;
            // il resto delle azioni non sono utili per calcolare il punteggio
            default:
                points = 0;
                break;
        }

        // altrimenti aggiungiamo i punti al punteggio moltiplicati per il punteggio bonus del livello moltiplicati ancora per la combo
        // se la combo e' a 0 allora usiamo 1 come combo
        // aggiunto il case speciale della god combo
        this->points += points * (long) (this->bonusPoints * (combo > 0 ? combo : 1)) * (combo >= GOD_COMBO ? 10 : 1);
        sprintf(this->pointsStr, "Points: %ld", this->points);
    }

    // se il modal non e' visibile, non fare nulla
    if (!this->modal->isVisible()) return;

    // altrimenti (se deve essere chiuso perche' l'utente ha compiuto un'azione) allora rendilo invisibile
    this->modal->setVisible(false);
    // e, se l'utente ha confermato l'azione
    if (this->modal->isConfirmed()) {
        // allora ritorna al menu principale
        main_menu_scene = new MainScene();
        ctx->queueScene(main_menu_scene);
    }
    this->moveFocus(0);
}

bool GameScene::onEscape(RunContext *ctx) {
    // se il modal non e' ancora stato aperto e l'alert non e' aperto
    if (!this->modal->isOpen() && !this->alert->isVisible()) {
        // allora rendilo visibile
        this->modal->setVisible(true);
        // avvisa il modal che e' stato aperto
        this->modal->openModal();
        // e sposta il focus li'
        this->moveFocus(1);
    }

    // infine, annulla l'uscita dal gioco
    return true;
}
