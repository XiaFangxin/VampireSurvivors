#ifndef VAMPIREDEMON_H
#define VAMPIREDEMON_H

#include "vampire.h"
#include "config.h"

class VampireDemon:public Vampire
{
public:
    VampireDemon();
    void moveToTarget(int target_X, int target_Y);

public:
    Direction m_direct;
};

#endif // VAMPIREDEMON_H
