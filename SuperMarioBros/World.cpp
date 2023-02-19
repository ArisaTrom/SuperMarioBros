#include "World.h"
#include <iostream>


World::World(int L, int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    level = new Level(N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    this->m_levelAndGrids = new char**[L];
    for (int i = 1; i < L; ++i){
        m_levelAndGrids[i] = level->Level::initializedGrid(coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    }
}

World::~World(){
    delete level;
    delete[] m_levelAndGrids;
}

