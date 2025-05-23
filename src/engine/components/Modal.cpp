#include "Modal.h"

#include <cstring>

Modal::Modal(const char *message, bool *open, bool *confirm) {
    this->message = message;
    this->open = open;
    this->confirm = confirm;
}

int Modal::height() {
    return 5;
}

int Modal::width() {
    // larghezza minima (cancel + ok + spacing)
    int min = 6 + 2 + 1;
    // larghezza del contenuto del messaggio
    int message_len = strlen(this->message);

    // ritorna il valore piu' grande tra i due + il padding ai lati
    return (min > message_len ? min : message_len) + 2;
}
