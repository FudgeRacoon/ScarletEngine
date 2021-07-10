#ifndef ISTATE_HPP
#define ISTATE_HPP

class IState
{
public:
    virtual void OnEnter() = 0;
    virtual void Update() = 0;
    virtual void OnExit() = 0;
};

#endif