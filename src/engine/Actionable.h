#ifndef ACTIONABLE_H
#define ACTIONABLE_H

class RunContext;

class Actionable {
public:
    virtual ~Actionable();

    /// Azione da eseguire; se il valore di ritorno e' true allora la scena che ha chiamato quest'azione non deve proseguire con l'azione di default
    virtual bool action(RunContext *ctx);
};

#endif
