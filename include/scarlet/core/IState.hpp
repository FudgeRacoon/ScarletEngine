#ifndef ISTATE_HPP
#define ISTATE_HPP

class IState
{
public:
    virtual void OnEnter() = 0;
    virtual void OnUpdate() = 0;
    virtual void OnImGuiRender() = 0;
};

#endif