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

    // inizializziamo le label del punteggio e del tempo
    this->pointsLabel = new Label;
    this->pointsLabel->setText(this->pointsStr);
    this->pointsLabel->setColor(*new ColorPair(COLOR_CYAN, COLOR_BLACK));
    this->pointsLabel->setPosition(60, 0);

    this->timerLabel = new Label;
    this->timerLabel->setText(this->timerStr);
    this->timerLabel->setColor(*new ColorPair(COLOR_YELLOW, COLOR_BLACK));
    this->timerLabel->setPosition(48, 0);

    // inizializziamo le stringhe delle label
    sprintf(this->pointsStr, "Points: 0");
    sprintf(this->timerStr, "Time: %d", this->timer / 1000);

    this->add(this->snake);
    this->add(this->modal);
    this->add(this->alert);
    this->add(this->pointsLabel);
    this->add(this->timerLabel);

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
            score->level = level;

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

    // muove il serpente e calcola i punti per questo tick
    int points = this->snake->tick();
    // rimuove dal timer il tempo passato dall'ultimo frame (delta)
    this->timer -= MILLIS_PER_FRAME;

    // se il timer termina
    if (this->timer <= 0) {
        // allora il giocatore ha vinto
        this->won = true;

        // mostriamo l'alert per segnalare la vittoria
        this->alert->setMsg("You won");
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

    // se il tick del serpente e' risultato in un'evento di sconfitta
    if (points == -1) {
        // mostriamo l'alert per segnalare la sconfitta
        this->alert->setMsg("You lost");
        this->alert->setVisible(true);
        this->alert->openAlert();
        this->alert->setPosition(getCenteredX(this->alert), 12);
        this->moveFocus(2);
    } else {
        // altrimenti aggiungiamo i punti al punteggio moltiplicati per il punteggio bonus del livello
        this->points += points * this->bonusPoints;
        sprintf(this->pointsStr, "Points: %d", this->points);
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
    // se il modal non e' ancora stato aperto
    if (!this->modal->isOpen()) {
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
