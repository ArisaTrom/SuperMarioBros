#include "World.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


World::World(int L, int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    this->m_L = L;
    this->m_levelAndGrids = new char**[m_L];
    Level* level0 = new Level(N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    Level* level1 = new Level(N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    Level* level2 = new Level(N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    

    // for (int i = 0; i <= m_L; ++i){
    //     this->m_level = new Level(N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    //     m_levelAndGrids[i] = this->m_level->Level::getGrid();
    //     std::cout << "Level " << i << std::endl;
    // }
}

World::~World(){
    for (int i = 0; i < m_L; ++i){
        delete m_level;
    }
    delete[] m_levelAndGrids;
}

