#include "Engine.h"
#include "Scene.h"
#include <ctime>

Engine::Engine(const int height, const int width, const int startX, const int startY) {
    // inizializzazione di ncurses
    initscr();
    noecho();
    nodelay(stdscr, true);
    cbreak();
    set_escdelay(0);
    mouseinterval(0);
    keypad(stdscr, true);
    curs_set(0);
    mousemask(
        BUTTON1_CLICKED | BUTTON1_PRESSED | BUTTON1_RELEASED | BUTTON3_CLICKED | BUTTON4_PRESSED | BUTTON5_PRESSED |
        REPORT_MOUSE_POSITION, nullptr);
    printf("\033[?1003h");
    fflush(stdout);
    start_color();
    const auto win = newwin(height, width, startY, startX);
    refresh();
    box(win, 0, 0);
    wrefresh(win);

    // imposta la scena attuale a NULL
    this->scene = nullptr;

    // inizializza il DrawContext
    this->drawContext = DrawContext();

    // imposta la finestra per il DrawContext alla finestra attuale
    this->drawContext.setWindow(win);

    // imposta le coordinate iniziali della finestra
    this->startX = startX, this->startY = startY;

    this->runTicks = 0;
}

Engine::~Engine() {
    // pulisce la finestra
    clear();
    // aggiorna la finestra
    refresh();
    // elimina la finestra
    endwin();
}

void Engine::setTitle(const char *title) {
    // imposta il titolo della finestra tramite il DrawContext
    this->drawContext.setTitle(title);
}

void Engine::start(Scene *scene) {
    // inizializza la scena
    this->initScene(scene);
    // ed esegue il main loop
    this->run();
}

void Engine::initScene(Scene *scene) {
    // imposta la scena attuale alla scena richiesta
    this->scene = scene;
    // prende il titolo dalla scena e lo imposta tramite il DrawContext
    this->drawContext.setTitle(this->scene->getTitle());
    // inizializza il contesto di inizializzazione della scena
    auto ctx = InitContext();
    ctx.setStart(this->startX, this->startY);

    // avvisa la scena di fare l'inizializzazione
    this->scene->init(ctx);
}


void Engine::input(RunContext *ctx) {
    // legge l'input dell'utente
    const auto c = getch();

    // inizializza l'input a NONE
    InputKind input = NONE;

    // inizializza i dati per un possibile click con il mouse
    int x = 0, y = 0;
    MEVENT mouseEvent;

    switch (c) {
        case KEY_UP:
            input = UP;
            break;
        case KEY_DOWN:
            input = DOWN;
            break;
        case KEY_LEFT:
            input = LEFT;
            break;
        case KEY_RIGHT:
            input = RIGHT;
            break;
        case '\n':
        case ' ':
            input = CONFIRM;
            break;
        case 27: // ESCAPE
            input = ESCAPE;
            break;
        case KEY_MOUSE:
            // in caso di click del mouse prendiamo i dati rilevanti e controlliamo che non ci siano stati errori
            if (getmouse(&mouseEvent) == OK) {
                // se il pulsante premuto e' il sinistro
                if (mouseEvent.bstate & BUTTON1_CLICKED) {
                    // impostiamo l'evento a CLICKED
                    input = CLICKED;
                    // e impostiamo anche la posizione del mouse
                    x = mouseEvent.x, y = mouseEvent.y;
                } else if (mouseEvent.bstate & BUTTON1_PRESSED) {
                    input = CLICKED;
                    x = mouseEvent.x, y = mouseEvent.y;
                } else if (mouseEvent.bstate & BUTTON4_PRESSED) {
                    input = SCROLL_UP;
                } else if (mouseEvent.bstate & BUTTON5_PRESSED) {
                    input = SCROLL_DOWN;
                } else if (mouseEvent.bstate & BUTTON3_CLICKED) {
                    input = ESCAPE;
                } else if (mouseEvent.bstate & BUTTON1_RELEASED) {
                    input = RELEASED;
                }
                // altrimenti non e' stato premuto nessun pulsante quindi e' stato solo mosso il mouse
                else {
                    // impostiamo l'evento a MOVEMENT
                    input = MOVEMENT;
                    // e impostiamo anche la posizione del mouse
                    x = mouseEvent.x, y = mouseEvent.y;
                }
            }
            break;
        default:
            input = NONE;
            break;
    }

    // impostiamo l'input che abbiamo letto attraverso il RunContext
    ctx->setInput(input);
    // e pure la posizione del mouse (in caso non ci siano stati click, la posizione e' a (0,0))
    ctx->setMousePosition(x, y);
}


void Engine::run() {
    // main loop del gioco
    while (true) {
        // otteniamo l'epoch attuale
        const int64_t start = micros();

        // inizializziamo il RunContext
        auto ctx = RunContext();

        // leggiamo l'input dell'utente
        input(&ctx);

        // eseguiamo il codice della scena
        this->scene->run(&ctx);

        this->runTicks += 1;

        // se e' arrivata una richiesta di cambio scena
        if (ctx.sceneQueued()) {
            // inizializziamo la nuova scena
            this->initScene(ctx.newScene());
            // e passiamo al prossimo loop per disegnare il prima possibile la nuova scena
            continue;
        }

        // se e' arrivata una richiesta di uscire dal gioco
        if (ctx.exitQueued()) {
            // usciamo dal loop
            break;
        }

        if (this->runTicks >= MILLIS_PER_FRAME) {
            // disegniamo la nuova scena
            this->draw(&ctx);
            this->runTicks = 0;
        }

        // e, se ci avanza tempo, fermiamo l'esecuzione in modo da ottenere un framerate fisso
        // per aumentare la fluidita' del gioco
        if (const int64_t end = micros();
            end - start <= RUN_MICROS_PER_FRAME) {
            int64_t sleep_time = RUN_MICROS_PER_FRAME - (end - start);
            sleepMicros(sleep_time);
        }
    }
}

void Engine::draw(RunContext *ctx) {
    // se una scena ha fatto richiesta di un colore custom per la box
    // allora registra il colore e abilitalo
    int color = 0;
    if (ctx->getBoxColor() != DEFAULT_COLOR_PAIR) {
        color = this->drawContext.registerColorPair(ctx->getBoxColor());
        this->drawContext.enableColor(color);
    }

    // prepariamo la fase del draw
    this->drawContext.prepare(ctx->redrawForced());

    // se una scena ha fatto richiesta di un colore custom per la box, allora color e' diverso da 0
    // quindi ora possiamo disattivarlo
    if (color != 0) {
        this->drawContext.disableColor(color);
    }

    // avvisiamo la scena che ora puo' fare il draw
    this->scene->draw(&this->drawContext);

    // e aggiorniamo la finestra
    this->drawContext.refresh();
}

void Engine::sleepMicros(unsigned int micros) {
    int64_t start = Engine::micros();
    int64_t now = Engine::micros();

    while (now - start < micros) {
        now = Engine::micros();
    }
}

int64_t Engine::millis() {
    // otteniamo l'epoch attuale
    timespec now{};
    timespec_get(&now, TIME_UTC);

    // e lo convertiamo in millisecondi
    return now.tv_sec * 1000 + now.tv_nsec / 1000000;
}

int64_t Engine::micros() {
    // otteniamo l'epoch attuale
    timespec now{};
    timespec_get(&now, TIME_UTC);

    // e lo convertiamo in millisecondi
    return now.tv_sec * 1000000 + now.tv_nsec / 1000;
}
