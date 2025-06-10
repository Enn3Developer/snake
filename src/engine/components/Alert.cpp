#include "Alert.h"

#include <cstring>

#include "../context/RunContext.h"

Alert::Alert() {
    this->color_id = -1;
    this->msg = nullptr;
    this->open = false;
}

void Alert::setMsg(const char *msg) {
    this->msg = msg;
}

bool Alert::isOpen() {
    return this->open;
}

void Alert::closeAlert() {
    this->open = false;
}

void Alert::openAlert() {
    this->open = true;
}

int Alert::height() {
    return 5;
}

int Alert::width() {
    // larghezza minima (lunghezza "ok")
    int min = 2;
    // larghezza del contenuto del messaggio
    int message_len = strlen(this->msg);

    // ritorna il valore piu' grande tra i due + il padding ai lati
    return (min > message_len ? min : message_len) + 2;
}

void Alert::draw(DrawContext *ctx) {
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
    ctx->coloredWriteAt(this->color_id, this->msg, this->x + 1, this->y + 1);

    ctx->coloredWriteAt(0, "Ok", this->x + width - 3, this->y + 3);
}

bool Alert::action(RunContext *ctx) {
    switch (ctx->getInput()) {
        // non fare nulla se l'input non e' di tipo conferma
        case UP:
        case DOWN:
        case LEFT:
        case RIGHT:
        case ESCAPE:
        case NONE:
            break;

        case CONFIRM:
            // chiude l'alert
            this->closeAlert();
            break;
        case CLICKED:
            // ottiene la posizione del mouse
            int *position = ctx->getMousePosition();
            int x = position[0];
            int y = position[1];

            // calcola la larghezza del modal
            int width = this->width();

            // controlliamo se sia stato premuto ok
            if (y == this->y + 3 && x >= this->x + width - 3 && x < this->x + width - 1) {
                // in quel caso chiudiamo l'alert
                this->closeAlert();
                break;
            }


            break;
    }

    return true;
}
