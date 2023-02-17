#include "Level.h"
#include "World.h"
#include <iostream>
#include <cstdlib>

Level::Level(){
    std::cin >> N;
    this->m_levelGrid = new char*[N];
    for (int i = 0; i < N; ++i){
        m_levelGrid[i] = new char[N];
    }
    initializedGrid();
}

Level::~Level(){
    for (int i = 0; i < N; ++i){
        delete[] m_levelGrid[i];
    }
    delete[] m_levelGrid;
    m_levelGrid = nullptr;

}

char** Level::initializedGrid(){
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            //populate with coins by percentage
            //populate with Goombas by percentage
            //populate with Koopas by percentage
            //populate with mushroom by percentage
        }
    }
    return m_levelGrid;
}

void Level::displayGrid(){

}