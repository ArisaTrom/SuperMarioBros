#include "Level.h"
#include "World.h"
#include <iostream>
#include <cstdlib>

Level::Level(int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    this->m_levelGrid = new char*[N];
    for (int i = 0; i < N; ++i){
        m_levelGrid[i] = new char[N];
    }
    initializedGrid(coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
}

Level::~Level(){
    for (int i = 0; i < N; ++i){
        delete[] m_levelGrid[i];
    }
    delete[] m_levelGrid;
    m_levelGrid = nullptr;

}

char** Level::initializedGrid(int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            int probability = 1 + (rand() % 100);
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
        }
    }

    //parsing through grid we find first x
    //replace with b 
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (m_levelGrid[i][j] == 'x'){
                m_levelGrid[i][j] = 'b';
                break;
            }
        }
    }

    //parsing through grid we find first c
    //replace with w
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (m_levelGrid[i][j] == 'c'){
                m_levelGrid[i][j] = 'w';
                break;
            }
        }
    }

    //parsing through grid we find first k
    //replace with H
    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (m_levelGrid[i][j] == 'k'){
                m_levelGrid[i][j] = 'H';
                break;
            }
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

int* Level::getMario(){
    int* coordinates = new int[2];

    for (int i = 0; i < N; ++i){
        for (int j = 0; j < N; ++j){
            if (m_levelGrid[i][j] == 'H'){
                coordinates[0] = i;
                coordinates[1] = j;
                return coordinates; //Exits function
            }
        }
    }
}