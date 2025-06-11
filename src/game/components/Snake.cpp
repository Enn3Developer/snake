#include "Snake.h"

#include <cstdlib>

#include "../../engine/context/RunContext.h"
#include "../scenes/GameScene.h"

Snake::Snake(int length, int speed) {
    // inizializza la griglia
    this->snakeGrid = new bool[SNAKE_HEIGHT][SNAKE_WIDTH]{false};

    // inizializza i valori di default per i colori, la lunghezza e la velocita' espressa in frame/tick
    this->snake_color_id = -1;
    this->apple_color_id = -1;
    this->length = length;
    this->speed = speed;
    this->remaining_ticks = 0;
    this->horizontalMovementTicks = HORIZONTAL_MOVEMENT_TICKS;
    this->bonusTicks = BONUS_TICKS;

    // inizializza il serpente nella grigla
    for (int x = 10; x < length + 10; x++) {
        this->snakeGrid[12][x] = true;
        auto pos = position{x, 12};
        this->addSnakePosition(pos);
    }

    // genera la posizione iniziale della mela
    this->generateApple();
    // direzione iniziale del serpente
    this->direction = D_UP;
}

void Snake::addSnakePosition(position pos) {
    auto new_pos = new list{pos, nullptr, nullptr};

    // se la lista e' vuota allora l'unico elemento della lista e' la posizione appena aggiunta
    if (this->h_snake == nullptr) {
        this->h_snake = new_pos;
        this->t_snake = new_pos;
        return;
    }

    // assegna come elemento successivo a questa posizione la posizione precedente (attualmente alla testa)
    new_pos->next = this->h_snake;
    // assegna alla testa come elemento precedente questa posizione
    this->h_snake->prev = new_pos;
    // infine assegna come testa della lista questa posizione
    this->h_snake = new_pos;
}

void Snake::generateApple() {
    // calcola la larghezza e l'altezza del campo di gioco
    int width = this->width();
    int height = this->height();

    // genera la posizione della mela finche' non si trova una posizione valida
    do {
        this->apple = {rand() % width, rand() % height};
    } while (isInSnake(this->apple));
}

bool Snake::isInSnake(position pos) {
    // controlla che la posizione sia interna al serpente o meno
    return this->snakeGrid[pos.y][pos.x];
}

int Snake::tick() {
    // decrementiamo i tick rimanenti alla prossima azione
    this->remaining_ticks -= 1;

    // se mancano ancora dei tick, usciamo dalla funzione
    if (this->remaining_ticks > 0) return 0;

    this->bonusTicks -= 1;

    // altrimenti impostiamo come tick rimanenti la velocita'
    this->remaining_ticks = speed;

    // inizializziamo il vettore movimento del serpente
    int dir_x = 0;
    int dir_y = 0;

    // calcoliamo il movimento del serpente in base alla direzione
    switch (this->direction) {
        case D_UP:
            dir_y -= 1;
            break;
        case D_DOWN:
            dir_y += 1;
            break;
        case D_LEFT:
            dir_x -= 1;
            this->horizontalMovementTicks -= 1;
            if (this->horizontalMovementTicks == 0) {
                this->horizontalMovementTicks = HORIZONTAL_MOVEMENT_TICKS;
            } else {
                this->remaining_ticks = 0;
            }
            break;
        case D_RIGHT:
            dir_x += 1;
            this->horizontalMovementTicks -= 1;
            if (this->horizontalMovementTicks == 0) {
                this->horizontalMovementTicks = HORIZONTAL_MOVEMENT_TICKS;
            } else {
                this->remaining_ticks = 0;
            }
            break;
    }
    this->currentDirection = this->direction;

    // ora creiamo la posizione partendo dalla testa del serpente
    auto pos = position{this->h_snake->pos.x + dir_x, this->h_snake->pos.y + dir_y};

    // se il serpente tocca il bordo del campo da gioco allora lo trasportiamo dall'altra parte
    if (pos.x < 0) pos.x = this->width() - 1;
    if (pos.y < 0) pos.y = this->height() - 1;

    if (pos.x >= this->width()) pos.x = 0;
    if (pos.y >= this->height()) pos.y = 0;

    // controlliamo che il serpente non si sia toccato,
    if (this->isInSnake(pos)) {
        // se si e' toccato, allora e' persa la partita
        return -1;
    }

    // rimuoviamo l'elemento alla coda del serpente
    this->snakeGrid[this->t_snake->pos.y][this->t_snake->pos.x] = false;
    this->t_snake->prev->next = nullptr;
    this->t_snake = this->t_snake->prev;

    // aggiungiamo alla testa del serpente la nuova posizione
    this->addSnakePosition(pos);
    this->snakeGrid[this->h_snake->pos.y][this->h_snake->pos.x] = true;

    // se il serpente ha mangiato la mela
    if (pos.x == apple.x && pos.y == apple.y) {
        // generiamo una nuova mela
        this->generateApple();
        // calcoliamo il punteggio base (moltiplicato in caso dal bonus velocita')
        // se il giocatore ci mette piu' di BONUS_TICKS tick per mangiare la mela, allora ritorna solo BASE_POINTS
        // se il giocatore ci mette meno di BONUS_TICKS tick per mangiare la mela, allora ritorna BASE_POINTS * BONUS_POINTS
        // se il giocatore ci mette meno della meta' di BONUS_TICKS tick per mangiare la mela, allora ritorna BASE_POINTS * BONUS_POINTS * BONUS_POINTS
        int points = BASE_POINTS * (this->bonusTicks > 0
                                        ? this->bonusTicks > BONUS_TICKS / 2
                                              ? BONUS_POINTS * BONUS_POINTS
                                              : BONUS_POINTS
                                        : 1);

        // resettiamo i tick per il bonus
        this->bonusTicks = BONUS_TICKS;

        return points;
    }

    return 0;
}

int Snake::height() {
    return SNAKE_HEIGHT;
}

int Snake::width() {
    return SNAKE_WIDTH;
}

void Snake::draw(DrawContext *ctx) {
    // registra i colori
    if (this->snake_color_id == -1) {
        this->snake_color_id = ctx->registerColorPair(*new ColorPair(COLOR_GREEN, COLOR_BLACK));
    }

    if (this->apple_color_id == -1) {
        this->apple_color_id = ctx->registerColorPair(*new ColorPair(COLOR_RED, COLOR_BLACK));
    }

    // disegniamo la testa del serpente
    auto pos = this->h_snake;
    ctx->coloredWriteAt(this->snake_color_id, "@", this->x + pos->pos.x, this->y + pos->pos.y);
    pos = pos->next;

    // disegniamo il resto del corpo del serpente
    while (pos != nullptr) {
        ctx->coloredWriteAt(this->snake_color_id, "o", this->x + pos->pos.x, this->y + pos->pos.y);
        pos = pos->next;
    }

    // infine, disegniamo la mela
    ctx->coloredWriteAt(this->apple_color_id, "$", this->x + this->apple.x, this->y + this->apple.y);
}

bool Snake::action(RunContext *ctx) {
    switch (ctx->getInput()) {
        // FRECCIA SU
        case UP:
            // se la direzione attuale e' opposta, annulla questo input
            if (this->currentDirection == D_DOWN) break;
            this->direction = D_UP;
            return true;
        // FRECCIA GIU'
        case DOWN:
            // se la direzione attuale e' opposta, annulla questo input
            if (this->currentDirection == D_UP) break;
            this->direction = D_DOWN;
            return true;
        // FRECCIA SINISTRA
        case LEFT:
            // se la direzione attuale e' opposta, annulla questo input
            if (this->currentDirection == D_RIGHT) break;
            this->direction = D_LEFT;
            return true;
        // FRECCIA DESTRA
        case RIGHT:
            // se la direzione attuale e' opposta, annulla questo input
            if (this->currentDirection == D_LEFT) break;
            this->direction = D_RIGHT;
            return true;
    }

    return false;
}

