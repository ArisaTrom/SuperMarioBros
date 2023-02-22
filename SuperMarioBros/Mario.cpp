#include "Mario.h"
#include <iostream>
#include <cstdlib>


Mario::Mario(int V, World* world){
    m_V = V;
    m_world = world;
    m_PowLevel = 0;
    m_coinCount = 0;
    m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
    m_direction = "";
    m_defeatedEnemyCount = 0;

}

Mario::~Mario(){

}

void Mario::play(){
    //while mario is alive
    while (m_V != 0){        

        std::string result = "";
        bool marioWon = false;

        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'H'){
            std::cout << "Mario is starting at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). " << std::endl;
            m_world->displayGrid(m_world->m_currentLevelForMario);
            m_MarioPosition = move();                                      // sets where mario will be 
            std::cout << m_MarioPosition[0] << m_MarioPosition[1] << std::endl;
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'm'){
            //collect mushroom and move Mario
            collectMushroom();
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario ate a mushroom. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);          
            m_MarioPosition = move();
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'c'){
            //collect coin and move mario
            collectCoin();
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario collected a coin. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_MarioPosition = move();

        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'g'){
            //encounter enemy and move mario
            marioWon = encounterEnemy('g');
            if (marioWon){
                result = "won";
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            } else {
                result = "lost";
            }
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a goomba and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_MarioPosition = move();
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'k'){
            //encounter enemy and move mario
            marioWon = encounterEnemy('k');
            if (marioWon){
                result = "won";
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            } else {
                result = "lost";
            }
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a koopa and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_MarioPosition = move();
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'x'){
            //encounter nothing and move mario
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario visited an empty space. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_MarioPosition = move();
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'w'){
            //encounter warp pipe move to next level
            enterWarpPipe();
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario visited an empty space. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_MarioPosition = move();
        }
        


    }
    
}



void Mario::collectCoin(){
    ++m_coinCount;
    if (m_coinCount == 20){
        m_coinCount = 0;
        ++m_V;
    }
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
                marioWin();
                enemyResult = true;
            } 
            else{
                //if lose
                marioLose();
                enemyResult = false;
            }
    }

    if (enemy == 'k'){
        srand(time(NULL));
        int probability = 1 + (rand() % 100);
            if (probability <= 65){
                // if win
                marioWin();
                enemyResult = true;
            } 
            else{
                //if lose
                marioLose();
                enemyResult = false;
            }
    }

    return enemyResult;
}

void Mario::marioWin(){
    //if mario win increase defeated enemy count
    //if he has defeated 7 enemies gain life
    m_defeatedEnemyCount++;
    if (m_defeatedEnemyCount == 7){
        m_V++;
    }
}

void Mario::marioLose(){
    //if mario lose power level decreases by 1 
    //if power level 0 mario loses life and defeated enemy count resets
    if (m_PowLevel = 0){
        m_V--;
        m_defeatedEnemyCount = 0;
    }
    else {
        m_PowLevel--;
    }

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


int* Mario::move(){
    int* newCoordinates = new int[2];

    int directions = 4;
    int pickedChoice = (int)(rand() * directions);
    switch (directions){
        case 1:         
        m_direction = "UP";
        moveUp();
        break;
        case 2:        
        m_direction = "DOWN";
        moveDown();
        break;
        case 3:         
        m_direction = "LEFT";
        moveLeft();
        break;
        case 4:         
        m_direction = "RIGHT";
        moveRight();
        break;
    }
    return newCoordinates;
}


void Mario::moveDown(){
    if (m_MarioPosition[1] == m_world->m_N){        // if at the bottom of grid move to top
        m_MarioPosition[1] = 0;
    }
    else{
        m_MarioPosition[1] = m_MarioPosition[1] + 1;
    }
    
}

void Mario::moveLeft(){
    if (m_MarioPosition[0] == 0){                   // if at the left of grid move to right edge
        m_MarioPosition[0] = m_world->m_N;
    }
    else{
        m_MarioPosition[0] = m_MarioPosition[0] - 1;
    }
    
}

void Mario::moveRight(){

    if (m_MarioPosition[0] == m_world->m_N){        // if at the right of grid move to left edge
        m_MarioPosition[0] = 0;
    }
    else{
        m_MarioPosition[0] = m_MarioPosition[0] + 1;
    }
    
}

void Mario::moveUp(){
    if (m_MarioPosition[1] == 0){                   // if at the top of the grid move to the bottom
        m_MarioPosition[1] = m_world->m_N;
    }
    else{
        m_MarioPosition[1] = m_MarioPosition[1] - 1;
    }
    
}

 
 




