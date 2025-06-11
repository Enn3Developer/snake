#include "Modal.h"

#include <cstring>

#include "../context/RunContext.h"

Modal::Modal(const char *message) {
    this->message = message;
    this->open = false;
    this->confirm = false;
    this->confirm_focused = true;
    this->color_id = -1;
}

int Modal::height() {
    return 5;
}

int Modal::width() {
    // larghezza minima (cancel + ok + spacing)
    int min = 6 + 2 + 1;
    // larghezza del contenuto del messaggio
    int message_len = this->message != nullptr ? strlen(this->message) : 0;

    // ritorna il valore piu' grande tra i due + il padding ai lati
    return (min > message_len ? min : message_len) + 2;
}

void Modal::openModal() {
    this->open = true;
    this->confirm = false;
    this->confirm_focused = true;
}

void Modal::closeModal() {
    this->open = false;
}

bool Modal::isOpen() {
    return this->open;
}

bool Modal::isConfirmed() {
    return this->confirm;
}

bool Modal::action(RunContext *ctx) {
    // calcola la larghezza del modal
    int width = this->width();
    int x, y;

    switch (ctx->getInput()) {
        case ESCAPE:
        case NONE:
            break;
        case DOWN:
        case UP:
        case LEFT:
        case RIGHT:
            // sposta il focus tra i pulsanti (cancel e ok)
            this->confirm_focused = !this->confirm_focused;
            break;
        case CONFIRM:
            // conferma l'azione del pulsante selezionato
            this->confirm = this->confirm_focused;
            // e chiudi il modal
            this->closeModal();
            break;
        case MOVEMENT:
            // ottiene la posizione del mouse
            x = ctx->getMouseX();
            y = ctx->getMouseY();

            // se il movimento e' avvenuto sulla riga dei pulsanti
            if (y == this->y + 3) {
                // se l'hover e' su cancel
                if (x >= this->x + 1 && x < this->x + 1 + 6) {
                    // allora impostiamo l'hover su cancel
                    this->confirm_focused = false;
                    break;
                }

                // altrimenti, controlliamo se l'hover sia su ok
                if (x >= this->x + width - 3 && x < this->x + width - 1) {
                    // in quel caso impostiamo l'hover su ok
                    this->confirm_focused = true;
                    break;
                }
            }

            break;
        case CLICKED:
            // ottiene la posizione del mouse
            x = ctx->getMouseX();
            y = ctx->getMouseY();

            // se il click e' avvenuto sulla riga dei pulsanti
            if (y == this->y + 3) {
                // se e' stato premuto cancel
                if (x >= this->x + 1 && x < this->x + 1 + 6) {
                    // allora annulliamo l'azione e chiudiamo il modal
                    this->confirm_focused = false;
                    this->confirm = false;
                    this->closeModal();
                    break;
                }

                // altrimenti, controlliamo se sia stato premuto ok
                if (x >= this->x + width - 3 && x < this->x + width - 1) {
                    // in quel caso confermiamo l'azione e chiudiamo il modal
                    this->confirm_focused = true;
                    this->confirm = true;
                    this->closeModal();
                    break;
                }
            }
            break;
        default: break;
    }
    return true;
}

void Modal::draw(DrawContext *ctx) {
    // registra il colore se non ancora e' stato registrato
    if (this->color_id == -1) {
        this->color_id = ctx->registerColorPair(*new ColorPair(COLOR_BLACK, COLOR_WHITE));
    }

    // ottiene le dimensioni del modal
    int width = this->width();
    int height = this->height();

    // disegna il background del modal
    ctx->drawBackground(this->color_id, this->x, this->y, width, height);

    // disegna il box che contiene tutto il modal
    ctx->drawBox(this->color_id, this->x, this->y, width, height);

    // scrive il messaggio del modal
    ctx->coloredWriteAt(this->color_id, this->message, this->x + 1, this->y + 1);

    // scrive i pulsanti del modal e cambia colore in base a se sono in focus o meno
    // colore 0 -> colore default (white, black)
    // colore color_id -> colore del modal (black, white)
    // le posizioni dei pulsanti sono Cancel tutto a sinistra e Ok tutto a destra
    ctx->coloredWriteAt(this->confirm_focused ? this->color_id : 0, "Cancel", this->x + 1, this->y + 3);
    ctx->coloredWriteAt(this->confirm_focused ? 0 : this->color_id, "Ok", this->x + width - 3, this->y + 3);
}
