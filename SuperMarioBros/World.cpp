#include "World.h"
#include "Level.h"
#include <iostream>


World::World(){
    std::cin >> L;
    this->m_levelAndGrids = new char**[L];
    for (int i = 0; i < L; ++i){
        m_levelAndGrids[i] = Level->initializedGrid();
    }
}

World::~World(){
    delete[] m_levelAndGrids;
}

