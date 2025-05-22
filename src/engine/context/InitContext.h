#ifndef INITCONTEXT_H
#define INITCONTEXT_H

class InitContext {
protected:
    /// Posizione della finestra rispetto al terminale
    int startX, startY;

public:
    InitContext();

    ~InitContext();

    /// Usato dall'engine per impostare la posizione della finestra rispetto al terminale
    void setStart(int x, int y);

    [[nodiscard]] int getStartX() const;

    [[nodiscard]] int getStartY() const;
};

#endif
