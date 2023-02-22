#include "Mario.h"
#include <iostream>
#include <cstdlib>


Mario::Mario(int V, World* world){
    m_V = V;
    m_world = world;
    m_PowLevel = 0;
    m_coinCount = 0;
    m_MarioPosition = m_world->getMario(world->m_currentLevelForMario);

}

Mario::~Mario(){

}

// while (m_V != 0){            //while mario is alive
//     if (world->m_levelAndGrids[world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'H'){
//         move();
//     }
//     if (world->m_levelAndGrids[world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'm'){
//         //collect mushroom and move Mario
//         collectMushroom();
//         world->moveMario(world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
//         world->displayGrid(world->m_currentLevelForMario);
//     }

// }


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
    
    std::cout << "Mario ate a mushroom" << std::endl;
}

void Mario::encounterBoss(){
    //if win 
    std::cout << "Mario fought the level boss and won!" << std::endl;
    //if loss
    std::cout << "Mario fought the level boss and lost :(" << std::endl;
}

void Mario::encounterEnemy(){
    //if enemy is Goomba
        //if win
        //position is empty
        std::cout << "Mario fought a Goomba and won!" << std::endl;
        //if loss
        std::cout << "Mario fought a Goomba and lost :(" << std::endl;
    //if enemy is Koopa
        //if win 
        //position
        std::cout << "Mario fought a Koopa and won!" << std::endl;
        //if loss
        std::cout << "Mario fought a Koopa and lost :(" << std::endl;
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
        moveUp();
        break;
        //Move mario - int* getMario(); 
        case 2:         //down
        moveDown();
        break;
        case 3:         //left
        moveLeft();
        break;
        case 4:         //right
        moveRight();
        break;
        default:
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

 
 




