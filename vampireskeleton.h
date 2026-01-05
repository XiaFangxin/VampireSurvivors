#ifndef VAMPIRESKELETON_H
#define VAMPIRESKELETON_H

#include "vlightning.h"
#include "vampire.h"

class VampireSkeleton:public Vampire
{
public:
    VampireSkeleton();
    void changeImage();
    void changePosition();

public:
    Direction m_direct;
    int countDuration;
};

#endif // VAMPIRESKELETON_H
