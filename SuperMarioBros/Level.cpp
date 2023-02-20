#include "Level.h"
#include "World.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Level::Level(int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    this->m_N = N;
    this->m_levelGrid = new char*[m_N];
    for (int i = 0; i < m_N; ++i){
        m_levelGrid[i] = new char[N];
    }
    initializedGrid(coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
}

Level::~Level(){
    for (int i = 0; i < m_N; ++i){
        delete[] m_levelGrid[i];
    }
    delete[] m_levelGrid;
    m_levelGrid = nullptr;

}

void Level::initializedGrid(int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    std::cout << "initalizing grid" << std::endl;
    srand(time(0));
    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            int probability = 1 + (rand() % 100);
            if (probability > 0 && probability <= coinChance){
                // coin placement
                this->m_levelGrid[i][j] = 'c';
            } 
            else if (probability > coinChance && probability <= (coinChance + emptyChance)){
                // empty placement 
                this->m_levelGrid[i][j] = 'x';
            }
            else if (probability > (coinChance + emptyChance) && probability <= (coinChance + emptyChance + goombaChance)){
                // goomba placement 
                this->m_levelGrid[i][j] = 'g';
            }
            else if (probability > (coinChance + emptyChance + goombaChance) && probability <= (coinChance + emptyChance + goombaChance + koopaChance)){
                //koopa placement
                this->m_levelGrid[i][j] = 'k';
            }
            else if (probability > (coinChance + emptyChance + goombaChance + koopaChance) && probability <= 100){
                //koopa placement
                this->m_levelGrid[i][j] = 'k';
            }
            else {}

        }
    }

    int iRand = (rand() % m_N);
    int jRand = (rand() % m_N);
    this->m_levelGrid[iRand][jRand] = 'b';

    iRand = (rand() % m_N);
    jRand = (rand() % m_N);
    if (this->m_levelGrid[iRand][jRand] != 'b'){
        this->m_levelGrid[iRand][jRand] = 'w';
    }
    displayGrid();
    
    iRand = (rand() % m_N);
    jRand = (rand() % m_N);
    if (this->m_levelGrid[iRand][jRand] != 'b' && this->m_levelGrid[iRand][jRand] != 'w'){
        this->m_levelGrid[iRand][jRand] = 'H';
    }

}

void Level::displayGrid(){
    std::cout << "display Grid function" << std::endl;
    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            std::cout << this->m_levelGrid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "========================" << std::endl;
}

int* Level::getMario(){
    int* coordinates = new int[2];

    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            if (m_levelGrid[i][j] == 'H'){
                coordinates[0] = i;
                coordinates[1] = j;
                return coordinates; //Exits function
            }
        }
    }
}

char** Level::getGrid(){
    return this->m_levelGrid;
}