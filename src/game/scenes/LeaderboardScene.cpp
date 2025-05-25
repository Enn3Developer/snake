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

// inizializza la scrollbar; per qualche motivo al compilatore non gli piace che la inizializzo dentro al costruttore
LeaderboardScene::LeaderboardScene(): scrollable(1, 27, 79) {
    this->list_size = 0;
    this->head = nullptr;

    auto file = new File("leaderboard.txt");
    char line[257] = {};

    while (!file->eof()) {
        file->readLine(line);

        if (strlen(line) == 0) continue;

        Score score = *new Score();
        score.fromString(line);
        int line_len = strlen(line);
        for (int i = 0; i < line_len; i++) {
            line[i] = '\0';
        }

        this->addScore(score);
    }

    delete file;

    // inizializzazione dei drawable

    p_list l = this->head;

    while (l != nullptr) {
        char *score = new char[257]{};
        l->score.toString(score);
        auto label = new Label();
        label->setText(score);
        scrollable.add(label);
        l = l->next;
    }

    this->menuBtn = *new Button();
    this->menuBtn.setText("Main menu");
    this->menuBtn.setPosition(70, 28);
    this->menuBtn.setOnClick(onMenu);

    this->scrollable.setPosition(1, 1);

    this->add(&this->scrollable);
    this->add(&this->menuBtn);
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
