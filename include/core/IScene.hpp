#ifndef ISCENE_H
#define ISCENE_H

class IScene
{
public:
    virtual void OnEnter() = 0;
    virtual void Update() = 0;
    virtual void OnExit() = 0;
};

#endif