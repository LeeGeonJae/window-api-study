#pragma once
#include "CObject.h"

class CPlayer :
    public CObject
{
public:
    virtual void update();
    virtual void render();

private:
    void CreateMissile();
};