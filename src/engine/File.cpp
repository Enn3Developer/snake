#include "File.h"

#include <cstring>

File::File(const char *filename) {
    // apre il file
    this->file.open(filename);

    // imposta closed a false per segnalare che il file e' ancora aperto
    this->closed = false;
}

File::~File() {
    this->close();
}

void File::close() {
    // se il file non e' stato ancora chiuso
    if (!this->closed) {
        // segnala che e' chiuso
        this->closed = true;
        // e poi lo chiude
        this->file.close();
    }
}

void File::write(const char *content) {
    // non fare nulla se il file e' stato chiuso
    if (this->closed) return;

    // aggiunge il contenuto al file
    this->file << content;
}

void File::writeLine(const char *content) {
    // non fare nulla se il file e' stato chiuso
    if (this->closed) return;

    // aggiunge il contenuto al file aggiungendo il fine riga
    this->file << content << '\n';
}

bool File::eof() const {
    return this->file.eof();
}


char File::readChar() {
    // non fare nulla se il file e' stato chiuso
    if (this->closed) return '\0';

    // non fare nulla se il file non ha piu' contenuto che possiamo leggere
    if (this->eof()) return '\0';

    // inizializza il carattere
    char c;
    // legge il carattere
    this->file.get(c);

    // infine lo ritorna
    return c;
}

void File::readLine(char *str) {
    // partendo dal primo carattere
    char c = this->readChar();

    // controlliamo che il carattere non sia un carattere null o di nuova riga
    while (c != '\0' && c != '\n') {
        // se non lo e', lo concateniamo alla stringa
        strncat(str, &c, 1);

        // e passiamo al carattere successivo
        c = this->readChar();
    }
}

