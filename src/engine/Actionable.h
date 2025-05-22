#ifndef ACTIONABLE_H
#define ACTIONABLE_H

class RunContext;

class Actionable
{
public:
    virtual ~Actionable();
    /// Azione da eseguire
    virtual void action(RunContext* ctx);
};

#endif
