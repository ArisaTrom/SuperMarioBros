#include "World.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


World::World(int L, int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    m_L = L;
    m_N = N;
    m_levelAndGrids = new char**[m_L];
    m_currentLevelForMario = -1;            //Level 0 is first level

    for (int i = 0; i < m_L; ++i){
        m_levelAndGrids[i] = new char*[m_N];
        for (int j = 0; j < m_N; ++j){
            m_levelAndGrids[i][j] = new char[m_N];
        }
    }

    initializeLevels(coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);


}

World::~World(){
    for (int i = 0; i < m_L; ++i){
        for (int j = 0; j < m_N; ++j){
            delete[] m_levelAndGrids[i][j];
        }
        delete[] m_levelAndGrids[i];
    }

    delete[] m_levelAndGrids;
}

void World::initializeLevels(int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    srand(time(NULL));
    std::cout << m_L << m_N << std::endl;
    for (int i = 0; i < m_L; i++){
        std::cout << "initalizing level " << i << std::endl;
        m_currentLevelForMario++;
        std::cout << m_currentLevelForMario << std::endl;
        for (int j = 0; j < m_N; ++j){
            for (int k = 0; k < m_N; ++k){
                //std::cout << "second for loop" << i << j << k << std::endl;
                int probability = 1 + (rand() % 100);
                if (probability <= coinChance){
                    // coin placement
                    m_levelAndGrids[i][j][k] = 'c';
                } 
                else if (probability <= (coinChance + emptyChance)){
                    // empty placement 
                    m_levelAndGrids[i][j][k] = 'x';
                }
                else if (probability <= (coinChance + emptyChance + goombaChance)){
                    // goomba placement 
                    m_levelAndGrids[i][j][k] = 'g';
                }
                else if (probability <= (coinChance + emptyChance + goombaChance + koopaChance)){
                    //koopa placement
                    m_levelAndGrids[i][j][k] = 'k';
                }
                else if (probability <= 100){
                    //koopa placement
                    m_levelAndGrids[i][j][k] = 'k';
                }
                else {
                    std::cout << "Didnt work" << std::endl;
                }

            }

        }
        int iRand = (rand() % m_N);
        int jRand = (rand() % m_N);
        m_levelAndGrids[i][iRand][jRand] = 'b';

        while(true){
            iRand = (rand() % m_N);
            jRand = (rand() % m_N);
            if (m_levelAndGrids[i][iRand][jRand] != 'b'){
                m_levelAndGrids[i][iRand][jRand] = 'w';
                break;
            }
        }

        while (true){
                iRand = (rand() % m_N);
                jRand = (rand() % m_N);
                if (m_levelAndGrids[i][iRand][jRand] != 'b' && m_levelAndGrids[i][iRand][jRand] != 'w'){
                    m_levelAndGrids[i][iRand][jRand] = 'H';
                    break;
                }
        }
        displayGrid(i);
    }
    
}

void World::displayGrid(int level){
    std::cout << "display Grid function" << std::endl;
    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            std::cout << m_levelAndGrids[level][i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "========================" << std::endl;
}

int* World::getMario(int level){
    int* coordinates = new int[2];

    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            if (m_levelAndGrids[level][i][j] == 'H'){
                coordinates[0] = i;
                coordinates[1] = j;
                return coordinates; //Exits function
            }
        }
    }
}

void World::moveMario(int level, int mario_x, int mario_y){
    // makes old H position into an empty
    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            if (m_levelAndGrids[level][i][j] == 'H'){
                m_levelAndGrids[level][i][j] = 'x';
            }
        }
    }
    // makes new Mario position into H
    m_levelAndGrids[level][mario_x][mario_y] = 'H';
}

void World::goNextLevel(){
    if (m_currentLevelForMario >= m_L){
        //no more levels
    }
    else{
        m_currentLevelForMario++;
    }
    
}



