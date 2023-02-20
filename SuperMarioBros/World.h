#ifndef WORLD_H
#define WORLD_H
#include "Level.h"

class World{
    public:
        World(int L, int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance);
        ~World();

    private:
        int m_L;
        Level* m_level;
        char*** m_levelAndGrids;
};


#endif