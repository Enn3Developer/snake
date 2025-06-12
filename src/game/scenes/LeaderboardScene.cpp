#include "LeaderboardScene.h"

#include <cstring>

#include "MainScene.h"
#include "../../engine/File.h"

MainScene main_scene;

void onMenu(RunContext *ctx) {
    // inizializza una nuova MainScene
    main_scene = *new MainScene();
    // e chiede all'engine di passare a quella scena
    ctx->queueScene(&main_scene);
}

LeaderboardScene::LeaderboardScene() {
    // inizializziamo la lista dei punteggi
    this->list_size = 0;
    this->head = nullptr;
    this->scrollable = new Scrollable(1, 27, 78);

    // apriamo l'handle per il file
    auto file = new File("leaderboard.txt");
    // inizializziamo il buffer per leggere riga per riga
    char line[257] = {};

    // finche' ci sta del contenuto da leggere
    while (!file->eof()) {
        // legge tutta la riga
        file->readLine(line);

        // se la riga e' vuota passiamo al prossimo ciclo
        if (strlen(line) == 0) continue;

        // creiamo l'oggetto che conterra' il punteggio
        Score score = *new Score();
        // convertiamo la stringa del punteggio a un punteggio vero e proprio
        score.fromString(line);
        // svuotiamo il buffer
        int line_len = strlen(line);
        for (int i = 0; i < line_len; i++) {
            line[i] = '\0';
        }

        // aggiungiamo il punteggio alla lista dei punteggi
        this->addScore(score);
    }

    // chiudiamo l'handle del file
    delete file;

    // creiamo la label legend da aggiungere all'inizio dello scrollable
    auto legendLabel = new Label();
    legendLabel->setColor(*new ColorPair(COLOR_GREEN));
    // spazi + "score" == 34 caratteri
    // sono i caratteri massimi del punteggio formattato
    legendLabel->setText("                             Score\tLevel");
    this->scrollable->add(legendLabel);

    // per ogni punteggio nella lista
    p_list l = this->head;
    while (l != nullptr) {
        // creiamo un buffer in memoria che lo conterra'
        char *score = new char[257]{};
        // convertiamo il punteggio in una stringa
        l->score.toFormattedString(score);

        // creiamo la label
        auto label = new Label();
        // impostiamo il testo della label a quella del punteggio convertito in stringa
        label->setText(score);
        // aggiungiamo la label allo scrollable
        this->scrollable->add(label);

        l = l->next;
    }

    // crea un pulsante per andare al menu principale
    this->menuBtn = new Button();
    this->menuBtn->setText("Main menu");
    this->menuBtn->setPosition(70, 28);
    this->menuBtn->setOnClick(onMenu);

    this->scrollable->setPosition(1, 1);

    this->add(this->scrollable);
    this->add(this->menuBtn);

    this->moveFocus(0);
}

void LeaderboardScene::addScore(Score score) {
    auto new_l = new list{score, nullptr};
    this->list_size += 1;

    // se la testa e' vuota
    if (this->head == nullptr) {
        // allora aggiungi lo score direttamente alla testa
        this->head = new_l;
        return;
    }

    // partiamo dalla testa e salvando l'elemento precedente
    p_list l = this->head;
    p_list prev_l = nullptr;

    // continuiamo fino alla fine della lista
    while (l != nullptr) {
        // controlliamo se lo score sia maggiore dello score dell'elemento attuale
        if (score > l->score) {
            // se lo e', allora questo punteggio va inserito prima dell'elemento attuale
            new_l->next = l;

            // ora controlliamo se abbiamo un elemento precedente
            if (prev_l == nullptr) {
                // se non c'e' significa che siamo ancora alla testa quindi salviamo il nuovo punteggio alla testa
                this->head = new_l;
            } else {
                // se c'e', allora salviamo il nuovo punteggio come elemento successivo all'elemento precedente
                prev_l->next = new_l;
            }

            // poiche' abbiamo gia' inserito lo score non e' necessario continuare oltre
            return;
        }

        // scorriamo avanti nella lista
        prev_l = l;
        l = l->next;
    }

    // se non ancora abbiamo inserito lo score allora significa che siamo arrivati in coda (prev_l) senza aggiungerlo e
    // l'elemento attuale e' NULL quindi aggiungiamo questo score alla coda
    prev_l->next = new_l;
}


const char *LeaderboardScene::getTitle() {
    return "Leaderboard";
}

bool LeaderboardScene::onEscape(RunContext *ctx) {
    onMenu(ctx);
    return true;
}
