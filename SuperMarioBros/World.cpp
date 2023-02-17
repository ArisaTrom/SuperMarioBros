#include "World.h"
#include "Level.h"
#include <iostream>


World::World(){
    std::cin >> L;
    this->levelAndGrids = new char**[L];
    for (int i = 0; i < L; ++i){
        levelAndGrids[i] = Level->initializedGrid();
    }
}

World::~World(){
    delete[] levelAndGrids;
}

