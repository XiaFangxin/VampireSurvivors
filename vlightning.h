#ifndef VLIGHTNING_H
#define VLIGHTNING_H

#include "vampire.h"
#include "config.h"

class VLightning:public Vampire
{
public:
    VLightning(int m, int n, Direction m_direct);
    void changeImage();
    void changePosition();

public:
    Direction m_direct;
    int countDuration;
};

#endif // VLIGHTNING_H
