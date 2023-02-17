#include "Level.h"
#include "World.h"
#include <iostream>
#include <cstdlib>

Level::Level(int N){
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
            int probability = rand(100);
            switch(probability){
                case 1 ... coinChance:              
                // coin placement 
                m_levelGrid[i][j] = 'c';
                break;
                case coinChance + 1 ... coinChance + emptyChance:
                // empty placement 
                m_levelGrid[i][j] = 'x';
                break;
                case coinChance + emptyChance + 1 ... coinChance + emptyChance + goombaChance:
                // goomba placement 
                m_levelGrid[i][j] = 'g';
                break;
                case coinChance + emptyChance + goombaChance + 1 ... coinChance + emptyChance + goombaChance + koopaChance:
                // koopa placement 
                m_levelGrid[i][j] = 'k';
                break;
                case coinChance + emptyChance + goombaChance + koopaChance + 1 ... 100:
                //mushroom placement 
                m_levelGrid[i][j] = 'm';
                break;
                default:
            }

            //parsing through grid we find first x
            //replace with b 
        }
    }
    return m_levelGrid;
}

void Level::displayGrid(){
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            std::cout << this->m_levelGrid[i][j];
        }
    }
}