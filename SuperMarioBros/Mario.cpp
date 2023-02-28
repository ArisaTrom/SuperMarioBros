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
    m_newPosition = new int[2];
    m_lastLifeCount = m_V;
    m_marioLostGoomba = false;
    m_marioLostKoopa = false;
    m_marioLostBoss = false;

}

Mario::~Mario(){
    delete m_newPosition;
}

void Mario::play(){
    //while mario is alive
    while (m_V != 0){        

        std::string result = "";
        bool marioWon = false;
        

        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'H'){
            if (m_marioLostBoss){
                m_marioLostBoss = false;
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
                std::cout << "Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). " << std::endl;
                m_MarioPosition = move();
                std::cout << "Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). " << std::endl;
                continue;
            }
            std::cout << "Mario is starting at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). " << std::endl;
            m_world->displayGrid(m_world->m_currentLevelForMario);
            firstMove();
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'm'){
            //collect mushroom and move Mario
            collectMushroom();

            if (m_marioLostGoomba){
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'g');
                m_marioLostGoomba = false;
            } else if (m_marioLostKoopa){
                m_marioLostKoopa = false;
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'k');
            } else if (!m_marioLostGoomba && !m_marioLostKoopa){
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            }

            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario ate a mushroom. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();    
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'c'){
            //collect coin and move mario
            collectCoin();

            if (m_marioLostGoomba){
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'g');
                m_marioLostGoomba = false;
            } else if (m_marioLostKoopa){
                m_marioLostKoopa = false;
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'k');
            } else if (!m_marioLostGoomba && !m_marioLostKoopa){
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            }

            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario collected a coin. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;

        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'g'){
            //encounter enemy and move mario

            if (m_marioLostGoomba){
                m_marioLostGoomba = false;
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'g');
                
            } else if (m_marioLostKoopa){
                m_marioLostKoopa = false;
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'k');
            } else if (!m_marioLostGoomba && !m_marioLostKoopa){
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            }

            marioWon = encounterEnemy('g');
            if (marioWon){
                result = "won";
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            } else {
                result = "lost";
                m_marioLostGoomba = true;
            }
            
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a goomba and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();    
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'k'){
            //encounter enemy and move mario

            if (m_marioLostGoomba){
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'g');
                m_marioLostGoomba = false;
            } else if (m_marioLostKoopa){
                m_marioLostKoopa = false;
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'k');
            } else if (!m_marioLostGoomba && !m_marioLostKoopa){
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            }

            marioWon = encounterEnemy('k');
            if (marioWon){
                result = "won";
            } else {
                result = "lost";
                m_marioLostKoopa = true;
            }
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a koopa and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();    
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'x'){
            //encounter nothing and move mario

            if (m_marioLostGoomba){
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'g');
                m_marioLostGoomba = false;
            } else if (m_marioLostKoopa){
                m_marioLostKoopa = false;
                m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'k');
            } else if (!m_marioLostGoomba && !m_marioLostKoopa){
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            }
            

            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario visited an empty space. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'w'){
            //encounter warp pipe move to next level
            enterWarpPipe();
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario warped to next level. Mario has " << m_lastLifeCount << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();    
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'b'){
        std::cout << "ENCOUNTERED BOSS" << std::endl;
            marioWon = encounterBoss();
            if (!marioWon){
                result = "lost";
                std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
                std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a boss and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
                m_newPosition = move();    
                std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
                m_MarioPosition = m_newPosition;
            } else {
                result = "won";
                std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
                std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a boss and " << result << ". Mario has " << m_lastLifeCount << " lives left. Mario has " << m_coinCount;  
                std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            }
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            
        }
        


    }

    if (m_lastLifeCount != 0){
        std::cout << "WE BEAT THE GAME! :)" << std::endl;
    } else {
        std::cout << "GAME OVER :(" << std::endl;
    }
    
}

void Mario::firstMove(){

    bool marioWon;
    std::string result;
    
    // looking at the element before Mario was placed
    if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'm'){
        collectMushroom();
        m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario ate a mushroom. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl; 
        m_MarioPosition = m_newPosition;

    }
    else if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'c'){
        collectCoin();
        m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario collected a coin. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl; 
        m_MarioPosition = m_newPosition;

    }
    else if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'k'){
        marioWon = encounterEnemy('k');
        if (marioWon){
            result = "won";
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        } else {
            result = "lost";
        }
        m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a koopa and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();    
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
        m_MarioPosition = m_newPosition;
    }
    else if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'g'){
        marioWon = encounterEnemy('g');
        if (marioWon){
            result = "won";
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        } else {
            result = "lost";
        }
        m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a goomba and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();    
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
        m_MarioPosition = m_newPosition;
    }
    else if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'x'){
        m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario visited an empty space. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();    
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
        m_MarioPosition = m_newPosition;
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
            break;
        default:
            break;
    }
    
}

bool Mario::encounterBoss(){
    //if win 

    bool bossResult;

     srand(time(NULL));
        int probability = 1 + (rand() % 100);
            if (probability <= 50){
                // if win
                bossWin();
                bossResult = true;
                std::cout << "Mario fought the level boss and won!" << std::endl;
            } 
            else{
                //if lose
                bossLose();
                bossResult = false;
                std::cout << "Mario fought the level boss and lost :(" << std::endl;
            }

    return bossResult;
}

void Mario::bossWin(){
    goNextLevel();
}

void Mario::bossLose(){
    m_marioLostBoss = true;
    switch (m_PowLevel){
        case 0:
        case 1:
            m_V--;
            m_lastLifeCount = m_V;
            break;
        case 2:
            m_PowLevel -= 2;
            encounterBoss();
            break;
        default:
            break;
    }
}



bool Mario::encounterEnemy(char enemy){
    //if enemy is Goomba or Koopa - outside function if H lands on g or k, then call this function

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

    else if (enemy == 'k'){
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
    if (m_PowLevel == 0){
        m_V--;
        m_lastLifeCount = m_V;
        m_defeatedEnemyCount = 0;
        m_PowLevel = 0;
    }
    else {
        m_PowLevel--;
    }

}


void Mario::enterWarpPipe(){
    //Mario warps to random spot in next level
    goNextLevel();
    //FInd way to increase level index
}


int* Mario::move(){

    int directions = 4;
    int randDirection = 1 + (rand() % directions);
    switch (randDirection){
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
    return m_MarioPosition;
}


void Mario::moveDown(){
    if (m_MarioPosition[0] == m_world->m_N - 1){        // if at the bottom of grid move to top (0,1) (1,1)
        m_MarioPosition[0] = 0;
    }
    else{
        m_MarioPosition[0] = m_MarioPosition[0] + 1;
    }
    
}

void Mario::moveLeft(){
    if (m_MarioPosition[1] == 0){                   // if at the left of grid move to right edge (4,4) (4,3)
        m_MarioPosition[1] = m_world->m_N - 1;
    }
    else{
        m_MarioPosition[1] = m_MarioPosition[1] - 1;
    }
    
}

void Mario::moveRight(){

    if (m_MarioPosition[1] == m_world->m_N - 1){        // if at the right of grid move to left edge (0,1) (0,2)
        m_MarioPosition[1] = 0;
    }
    else{
        m_MarioPosition[1] = m_MarioPosition[1] + 1;
    }
    
}

void Mario::moveUp(){
    if (m_MarioPosition[0] == 0){                   // if at the top of the grid move to the bottom  (4,4) (3,4)
        m_MarioPosition[0] = m_world->m_N - 1;
    }
    else{
        m_MarioPosition[0] = m_MarioPosition[0] - 1;
    }
    
}

void Mario::goNextLevel(){
    if (m_world->m_currentLevelForMario >= m_world->m_L - 1){
        m_lastLifeCount = m_V;
        m_V = 0;
    }
    else{
        m_world->m_currentLevelForMario++;
    }
    
}
 




