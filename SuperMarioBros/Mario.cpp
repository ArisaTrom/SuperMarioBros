#include "Mario.h"
#include <iostream>
#include <cstdlib>


Mario::Mario(int V, World* world){
    m_V = V;
    m_world = world;
    m_PowLevel = 0;
    m_coinCount = 0;
    m_MarioPosition = m_world->getMario(world->m_currentLevelForMario);
    m_direction = "";

}

Mario::~Mario(){

}

void Mario::play(){
    //while mario is alive
    while (m_V != 0){            
        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'H'){
            m_MarioPosition = move();       // new position up down left right 
        }
        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'm'){
            //collect mushroom and move Mario
            collectMushroom();
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            m_MarioPosition = move();
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario ate a mushroom. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << "coins. Mario will move " << m_direction << "." << std::endl;
        }
        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'c'){
            //collect coin and move mario
            collectCoin();
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            m_MarioPosition = move();
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario collected a coin. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << "coins. Mario will move " << m_direction << "." << std::endl;

        }
        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'g'){
            //encounter enemy and move mario
            // std::string result = encounterEnemy('g');
            // if (win){
            //     m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            // }
            m_world->displayGrid(m_world->m_currentLevelForMario);
            m_MarioPosition = move();
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a goomba and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << "coins. Mario will move " << m_direction << "." << std::endl;
        }
        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'k'){
            //encounter enemy and move mario
            std::string result = encounterEnemy('k');
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a koopa and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << "coins. Mario will move " << m_direction << "." << std::endl;
        }
        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'x'){
            //encounter nothing and move mario
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario visited an empty space. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << "coins. Mario will move " << m_direction << "." << std::endl;
        }
        


    }
    
}



void Mario::collectCoin(){
    ++m_coinCount;
    if (m_coinCount == 20){
        m_coinCount = 0;
        ++m_V;
    }
    std::cout << "Mario collected a coin" << std::endl;
}


void Mario::collectMushroom(){
    
    switch (m_PowLevel){
        case 0:
        case 1:
        ++m_PowLevel;
        default:
        break;
    }
    
}

void Mario::encounterBoss(){
    //if win 
    std::cout << "Mario fought the level boss and won!" << std::endl;
    //if loss
    std::cout << "Mario fought the level boss and lost :(" << std::endl;
}

bool Mario::encounterEnemy(char enemy){
    //if enemy is Goomba - outside function if H lands on g or k, then call this function

    bool enemyResult;

    if (enemy == 'g'){
        srand(time(NULL));
        int probability = 1 + (rand() % 100);
            if (probability <= 80){
                // if win
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
                enemyResult = true;
            } 
            else{
                //if lose
                enemyResult = false;
            }
    }

    if (enemy == 'k'){
        srand(time(NULL));
        int probability = 1 + (rand() % 100);
            if (probability <= 65){
                // if win
                enemyResult = true;
            } 
            else{
                //if lose
                enemyResult = false;
            }
    }

    return enemyResult;
}

void Mario::marioWin(){
    //if mario win
    m_MarioPosition[]

}

void Mario::marioLose(){
    //if mario lose
}

void Mario::encounterNothing(){
    std::cout << "The position is empty" << std::endl;
}

void Mario::enterWarpPipe(){
    //Mario warps to random spot in next level
    m_world->goNextLevel();
    std::cout << "Mario warped" << std::endl;
    //FInd way to increase level index


}

bool Mario::attackGoomba(){
    //with probability
    return true;
}

bool Mario::attackKoopa(){

}

int* Mario::move(){
    int* newCoordinates = new int[2];

    int directions = 4;
    int pickedChoice = (int)(rand() * directions);
    switch (directions){
        case 1:         //up
        m_direction = "UP";
        moveUp();
        break;
        case 2:         //down
        m_direction = "DOWN";
        moveDown();
        break;
        case 3:         //left
        m_direction = "LEFT";
        moveLeft();
        break;
        case 4:         //right
        m_direction = "RIGHT";
        moveRight();
        break;
    }
    return newCoordinates;
}


void Mario::moveDown(){
    m_MarioPosition[1]--;
}

void Mario::moveLeft(){
    m_MarioPosition[0]--;
}

void Mario::moveRight(){
    m_MarioPosition[0]++;
}

void Mario::moveUp(){
    m_MarioPosition[1]++;
}

 
 




