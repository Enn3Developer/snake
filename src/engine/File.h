#ifndef FILE_H
#define FILE_H
#include <fstream>

class File {
private:
    bool closed;
    std::fstream file;

public:
    /// Apre un file
    explicit File(const char *filename);

    /// Chiude in automatico il file
    ~File();

    /// Chiude il file
    void close();

    /// Scrive del contenuto nel file
    void write(const char *content);

    /// Scrive del contenuto nel file e ci aggiunge un fine riga alla fine
    void writeLine(const char *content);

    /// Controlla se e' stata raggiunta la fine del file
    bool eof() const;

    /// Legge un singolo carattere dal file
    char readChar();
};

#endif
