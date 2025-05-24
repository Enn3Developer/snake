#include "Scene.h"
#include "Actionable.h"

Scene::Scene() {
    // inizializza tutto a 0 o NULL
    this->h_drawables = nullptr;
    this->t_drawables = nullptr;
    this->size = 0;
    this->focus = nullptr;
    this->startX = 0, this->startY = 0;
}

void Scene::add(Drawable *drawable) {
    // inizializza un elemento della lista
    const auto l = new list{drawable, nullptr, nullptr};

    // se la lista e' vuota
    if (this->h_drawables == nullptr) {
        // aggiungi l'elemento come unico elemento della lista (quindi sta sia in testa che in coda)
        this->h_drawables = l;
        this->t_drawables = l;
    }
    // altrimenti
    else {
        // assegna l'elemento come elemento successivo alla coda
        this->t_drawables->next = l;

        // assegna come elemento precedente di quello che si sta aggiungendo la coda
        l->prev = this->t_drawables;

        // assegna come coda della lista l'elemento
        this->t_drawables = l;
    }

    // incrementa il numero di elementi presenti nella lista
    this->size++;
}

Drawable *Scene::get(int idx) const {
    // partendo dalla testa della lista
    p_list l = this->h_drawables;

    // si continua finche' non si trova un elemento NULL oppure non arriviamo all'elemento che stiamo cercando
    while (idx > 0 && l != nullptr) {
        l = l->next;
        idx--;
    }

    // se l'elemento e' NULL, ritorna NULL
    if (l == nullptr) return nullptr;
    // altrimenti ritorna il drawable correlato a questo elemento
    return l->drawable;
}

void Scene::moveFocus(int idx) {
    // controlla se ci sta gia' un elemento in focus
    if (this->focus != nullptr) {
        // se ci sta, avvisa l'elemento che non e' piu' in focus
        this->focus->drawable->setHover(false);
        this->focus = nullptr;
    }

    // partendo dalla testa della lista
    p_list l = this->h_drawables;

    // va avanti fino a trovare l'elemento richiesto
    while (idx > 0 && l != nullptr) {
        l = l->next;
        idx--;
    }

    // se l'elemento richiesto esiste
    if (l != nullptr) {
        // allora imposta il nuovo focus
        l->drawable->setHover(true);
        this->focus = l;
    }
}


void Scene::focusUp() {
    // se un elemento e' gia' in focus
    if (this->focus != nullptr) {
        // avvisa l'elemento che non e' piu' in focus
        this->focus->drawable->setHover(false);
        // e assegna il nuovo focus all'elemento precedente (sopra == precedente)
        this->focus = this->focus->prev;
    }

    // se l'elemento in focus e' NULL (sia perche' non c'erano elementi in focus
    // o perche' l'elemento precedente di quello in focus e' NULL)
    if (this->focus == nullptr) {
        // assegna il focus all'elemento in coda
        // (si parte dalla coda perche' e' l'unico elemento di cui siamo quasi certi che ci sta sempre un elemento precedente)
        this->focus = this->t_drawables;
    }

    // variabile per determinare se abbiamo gia' fatto un giro totale di tutti gli elementi
    bool loop = false;
    // finche' il focus non e' NULL
    while (this->focus != nullptr) {
        // controlliamo se il focus attuale e' pure un Actionable e sia visibile all'utente
        if (dynamic_cast<Actionable *>(this->focus->drawable) != nullptr && this->focus->drawable->isVisible()) {
            // se lo e', avvisiamo che ora e' in hover
            this->focus->drawable->setHover(true);
            // e usciamo dal loop
            break;
        }

        // altrimenti, andiamo all'elemento precedente
        this->focus = this->focus->prev;

        // se ora l'elemento precedente e' null e non ancora abbiamo fatto un giro completo
        if (this->focus == nullptr && !loop) {
            // siamo sicuri che il giro completo l'abbiamo fatto
            loop = true;
            // quindi ora ripartiamo dalla coda
            this->focus = this->t_drawables;
        }
    }
}

void Scene::focusDown() {
    // se un elemento e' gia' in focus
    if (this->focus != nullptr) {
        // avvisa l'elemento che non e' piu' in focus
        this->focus->drawable->setHover(false);
        // e assegna il nuovo focus all'elemento successivo (sotto == successivo)
        this->focus = this->focus->next;
    }

    // se l'elemento in focus e' NULL (sia perche' non c'erano elementi in focus
    // o perche' l'elemento successivo di quello in focus e' NULL)
    if (this->focus == nullptr) {
        // assegna il focus all'elemento in testa
        // (si parte dalla testa perche' e' l'unico elemento di cui siamo quasi certi che ci sta sempre un elemento successivo)
        this->focus = this->h_drawables;
    }

    // variabile per determinare se abbiamo gia' fatto un giro totale di tutti gli elementi
    bool loop = false;
    // finche' il focus non e' NULL
    while (this->focus != nullptr) {
        // controlliamo se il focus attuale e' pure un Actionable e sia visibile all'utente
        if (dynamic_cast<Actionable *>(this->focus->drawable) != nullptr && this->focus->drawable->isVisible()) {
            // se lo e', avvisiamo che ora e' in hover
            this->focus->drawable->setHover(true);
            // e usciamo dal loop
            break;
        }

        // altrimenti, andiamo all'elemento successivo
        this->focus = this->focus->next;

        // se ora l'elemento successivo e' null e non ancora abbiamo fatto un giro completo
        if (this->focus == nullptr && !loop) {
            // siamo sicuri che il giro completo l'abbiamo fatto
            loop = true;
            // quindi ora ripartiamo dalla testa
            this->focus = this->h_drawables;
        }
    }
}

Scene::~Scene() = default;

void Scene::draw(DrawContext *ctx) {
    // partendo dalla lista
    p_list l = this->h_drawables;

    // andiamo per iterazione per ogni elemento nella lista
    while (l != nullptr) {
        // se l'elemento e' visibile
        if (l->drawable->isVisible()) {
            // mandiamo il comando draw all'elemento
            l->drawable->draw(ctx);
        }

        // passiamo all'elemento successivo
        l = l->next;
    }
}

void Scene::init(InitContext &ctx) {
    // impostiamo le coordinate iniziali della scena
    this->startX = ctx.getStartX(), this->startY = ctx.getStartY();
}

void Scene::run(RunContext *ctx) {
    // controlliamo l'input che manda l'utente
    switch (ctx->getInput()) {
        // FRECCIA SU/SINISTRA
        case LEFT:
        case UP:
            // controlliamo se ci sta un elemento in focus
            if (this->focus != nullptr) {
                // se ci sta, controlliamo se sia un Actionable
                if (const auto actionable = dynamic_cast<Actionable *>(this->focus->drawable);
                    actionable != nullptr) {
                    // se lo e', avvisiamolo dell'azione e controlliamo se dobbiamo fare anche l'azione di default
                    if (actionable->action(ctx)) {
                        break;
                    }
                }
            }
            // di default mandiamo il focus verso l'alto
            this->focusUp();
            break;
        // FRECCIA GIU'/DESTRA
        case RIGHT:
        case DOWN:
            // controlliamo se ci sta un elemento in focus
            if (this->focus != nullptr) {
                // se ci sta, controlliamo se sia un Actionable
                if (const auto actionable = dynamic_cast<Actionable *>(this->focus->drawable);
                    actionable != nullptr) {
                    // se lo e', avvisiamolo dell'azione e controlliamo se dobbiamo fare anche l'azione di default
                    if (actionable->action(ctx)) {
                        break;
                    }
                }
            }
            // di default mandiamo il focus verso il basso
            this->focusDown();
            break;
        // TASTO INVIO
        case CONFIRM:
            // di default controlliamo se ci sta un elemento in focus
            if (this->focus != nullptr) {
                // facciamo il cast a un Actionable e controlliamo se sia valido
                if (const auto actionable = dynamic_cast<Actionable *>(this->focus->drawable);
                    actionable != nullptr) {
                    // se lo e', avvisiamo l'elemento che l'utente l'ha attivato
                    actionable->action(ctx);
                }
            }
            break;
        // TASTO ESCAPE
        case ESCAPE:
            // se la scena non annulla l'azione
            if (!this->onEscape(ctx)) {
                // allora chiediamo l'uscita dal gioco all'engine
                ctx->queueExit();
            }
            break;
        // NESSUN TASTO
        case NONE:
            break;
        // CLICK SINISTRO DEL MOUSE
        case CLICKED:
            // prendiamo la posizione del mouse al momento del click
            const int *position = ctx->getMousePosition();
            // e chiamiamo la funzione che gestisce i click normalizzando la posizione
            this->click(ctx, position[0] - this->startX, position[1] - this->startY);
            break;
    }
}

void Scene::click(RunContext *ctx, const int x, const int y) {
    // se ci sta gia' un elemento in focus
    if (this->focus != nullptr) {
        // avvisiamo l'elemento che non e' piu' in focus
        this->focus->drawable->setHover(false);
        // e impostiamo il focus a NULL
        this->focus = nullptr;
    }

    // partendo dalla testa della lista
    p_list l = this->h_drawables;

    // controlliamo ogni elemento
    while (l != nullptr) {
        // prendiamo direttamente il puntatore al drawable per semplificare la scrittura
        Drawable *drawable = l->drawable;

        // prendiamo la posizione del drawable
        const int *position = drawable->getPosition();
        const int drawX = position[0];
        const int drawY = position[1];

        // controlliamo se il click e' stato fatto all'interno di questo drawable
        if (x >= drawX && x < drawX + drawable->width()
            && (y >= drawY && y < drawY + drawable->height())) {
            // controlliamo che il drawable sia anche un Actionable
            if (auto *actionable = dynamic_cast<Actionable *>(drawable);
                actionable != nullptr) {
                // aggiorna la posizione del mouse
                ctx->setMousePosition(x, y);
                // avvisiamo il drawable che ora e' in focus
                drawable->setHover(true);
                // impostiamo il focus a quell'elemento
                this->focus = l;
                // avvisiamo il drawable/actionable dell'azione dell'utente
                actionable->action(ctx);
                // e usciamo dalla funzione
                return;
            }
        }

        // passiamo al prossimo elemento
        l = l->next;
    }
}

const char *Scene::getTitle() {
    // Titolo default di una scena
    return "Scene";
}

int Scene::getCenteredX(Drawable *drawable) {
    // calcoliamo la posizione centrale nell'asse X per un drawable
    const auto x = 80 - drawable->width();
    return x % 2 ? x / 2 : (x - 1) / 2;
}

bool Scene::onEscape(RunContext *ctx) {
    return false;
}
