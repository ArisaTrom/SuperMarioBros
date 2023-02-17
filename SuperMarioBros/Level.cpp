#include "Level.h"
#include "World.h"
#include <iostream>
#include <cstdlib>

Level::Level(){
    std::cin >> N;
    this->levelGrid = new char*[N];
    for (int i = 0; i < N; ++i){
        levelGrid[i] = new char[N];
    }
    initializedGrid();
}

Level::~Level(){
    for (int i = 0; i < N; ++i){
        delete[] levelGrid[i];
    }
    delete[] levelGrid;
    levelGrid = nullptr;

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
    return levelGrid;
}

void Level::displayGrid(){

}