/*
Arisa Trombley, Carina Chan
2375446, 2367721
trombley@chapman.edu, carchan@chapman.edu
CPSC 350-02, CPSC 350-03
Programming Assignment 2 - Not So Super Mario Bros.
*/

/* DESCRIPTION
Contains constructor, destructor, and method implementations
for interacting with the world and its levels.
*/


#include "World.h"
#include "Mario.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

//World constructor.
World::World(int L, int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    //Member variables.
    m_L = L; //# of levels.
    m_N = N; //Grid dimension.
    m_levelAndGrids = new char**[m_L]; //2D array for the levels and grids.
    m_currentLevelForMario = 0; //Level 0 is first level.
    m_firstGameElements = new char[m_L]; //Array of the first game elements that Mario will encounter for each level.
    m_isLastLevel = false; //Checks if Mario is on the last level.

    //Dynamically allocates 2D Array.
    for (int i = 0; i < m_L; ++i){
        m_levelAndGrids[i] = new char*[m_N];
        for (int j = 0; j < m_N; ++j){
            m_levelAndGrids[i][j] = new char[m_N];
        }
    }
    initializeLevels(coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
}


//World destructor.
World::~World(){
    for (int i = 0; i < m_L; ++i){
        for (int j = 0; j < m_N; ++j){
            delete[] m_levelAndGrids[i][j];
        }
        delete[] m_levelAndGrids[i];
    }
    delete[] m_levelAndGrids;
}


//initializeLevels method.
//Parameters: int coinChance - chance that the space will hold a coin, int emptyChance - chance that the space will be empty,
//int goombaChance - chance that the space will hold a goomba, int koopaChance - chance that the space will hold a koopa,
//int mushroomChance - chance that the space will hold a mushroom.
void World::initializeLevels(int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance){
    srand(time(NULL));
    for (int i = 0; i < m_L; i++){
        for (int j = 0; j < m_N; ++j){
            for (int k = 0; k < m_N; ++k){
                int probability = 1 + (rand() % 100);
                if (probability <= coinChance){ //Coin placement.
                    m_levelAndGrids[i][j][k] = 'c';
                } 
                else if (probability <= (coinChance + emptyChance)){ //Empty placement.
                    m_levelAndGrids[i][j][k] = 'x';
                }
                else if (probability <= (coinChance + emptyChance + goombaChance)){ //Goomba placement.
                    m_levelAndGrids[i][j][k] = 'g';
                }
                else if (probability <= (coinChance + emptyChance + goombaChance + koopaChance)){ //Koopa placement.
                    m_levelAndGrids[i][j][k] = 'k';
                }
                else if (probability <= 100){ //Mushroom placement.
                    m_levelAndGrids[i][j][k] = 'm';
                }
                else { //Error statement.
                    std::cout << "Didnt work" << std::endl;
                }
            }
        }

        //Places boss on a random spot on the grid.
        int iRand = (rand() % m_N);
        int jRand = (rand() % m_N);
        m_levelAndGrids[i][iRand][jRand] = 'b';

        //Places warp pipe on a random spot on the grid excluding the boss spot.
        if (i != m_L - 1){
            while(true){
                iRand = (rand() % m_N);
                jRand = (rand() % m_N);
                if (m_levelAndGrids[i][iRand][jRand] != 'b'){
                    m_levelAndGrids[i][iRand][jRand] = 'w';
                    break;
                }
            }
        }

        //Displays grid before Mario is placed
        displayGrid(i);

        //Places Mario on a random spot on the grid excluding the boss and waro spot.
        while (true){
                iRand = (rand() % m_N);
                jRand = (rand() % m_N);
                if (m_levelAndGrids[i][iRand][jRand] != 'b' && m_levelAndGrids[i][iRand][jRand] != 'w'){
                    m_firstGameElements[i] = m_levelAndGrids[i][iRand][jRand];
                    m_levelAndGrids[i][iRand][jRand] = 'H';
                    break;
                }
        }
    }
}


//displayGrid method.
//Parameters: int - level that Mario is on.
void World::displayGrid(int level){
    std::cout << "========================" << std::endl;
    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            std::cout << m_levelAndGrids[level][i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "========================" << std::endl;
}


//getMario method - Returns a 1D int array of Mario's coordinates [row, column].
//Parameters: int - level that Mario is currently on.
int* World::getMario(int level){
    int* coordinates = new int[2];

    //Iterate through grid to find Mario 'H'.
    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            if (m_levelAndGrids[level][i][j] == 'H'){
                coordinates[0] = i;
                coordinates[1] = j;
                return coordinates; //Exits function.
            }
        }
    }
}


//moveMario method.
//Parameters: int level - the level that Mario is on, int mario_x - new x-coord, int mario_y - new y-coord.
void World::moveMario(int level, int mario_x, int mario_y){
    //Makes Mario's old position into an empty space.
    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            if (m_levelAndGrids[level][i][j] == 'H'){
                m_levelAndGrids[level][i][j] = 'x';
            }
        }
    }
    //Makes Mario's new position into an H.
    m_levelAndGrids[level][mario_x][mario_y] = 'H';
}



//moveMarioAfterLoss method.
//Parameters: int level - the level that Mario is on, int mario_x - new x-coord, int mario_y - new y-coord, char e - char that Mario encounters.
void World::moveMarioAfterLoss(int level, int mario_x, int mario_y, char e){
    //Make Mario's old position the original char because Mario lost.
    for (int i = 0; i < m_N; ++i){
        for (int j = 0; j < m_N; ++j){
            if (m_levelAndGrids[level][i][j] == 'H'){
                m_levelAndGrids[level][i][j] = e;
            }
        }
    }
    //Makes Mario's new position into H.
    m_levelAndGrids[level][mario_x][mario_y] = 'H';
}