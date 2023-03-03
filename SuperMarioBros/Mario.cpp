/*
Arisa Trombley, Carina Chan
2375446, 2367721
trombley@chapman.edu, carchan@chapman.edu
CPSC 350-02, CPSC 350-03
Programming Assignment 2 - Not So Super Mario Bros.
*/

/* DESCRIPTION
Contains constructor, destructor, and method implementations
for interacting with Mario.
*/


#include "Mario.h"
#include <iostream>
#include <cstdlib>

//-----------------------------DONE
//Mario constructor.
Mario::Mario(int V, World* world){
    //Member variables.
    m_V = V; //int - Mario's # of lives.
    m_world = world; //World object - World object to interact with World methods.
    m_PowLevel = 0; //int - Mario's power level.
    m_coinCount = 0; //int - Mario's coin count.
    m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario); //1D int array - Mario's position, obtained from World method, getMario.
    m_direction = ""; //string - Mario's next move.
    m_defeatedEnemyCount = 0; //int - Mario's # of defeated enemies.
    m_newPosition = new int[2]; //1D int array - Mario's new position [row, column].
    m_lastLifeCount = m_V; //int - Mario's most recent # of lives (before any changes).
    m_marioLostGoomba = false; //Boolean - shows if Mario won/lost encountering a goomba.
    m_marioLostKoopa = false; //Boolean - shows if Mario won/lost encountering a koopa.
    m_marioLostBoss = false;  //Boolean - shows if Mario won/lost encountering a boss.
}

//-----------------------------DONE
//Mario destructor.
Mario::~Mario(){
    delete m_newPosition; //Deletes 1D int array.
}


//-----------------------------DONE******
//play method - Simulates a game of Mario.
void Mario::play(){
    //While mario is alive.
    while (m_V != 0){        

        std::string result = ""; //Fighting result of encountering an enemy or boss.
        bool marioWon = false;
        
        //Places Mario into grid, prints grid.
        if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'H'){
            std::cout << "Mario is starting at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). " << std::endl;
            m_world->displayGrid(m_world->m_currentLevelForMario);
            firstMove();
        }

        //If Mario encounters a mushroom.
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'm'){
            collectMushroom();
            checkLoss();

            //Prints grid, prints statement.
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario ate a mushroom. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }

        //If Mario encounters a coin.
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'c'){
            collectCoin();
            checkLoss();

            //Prints grid, prints statement.
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario collected a coin. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move(); //Moves Mario to a new position.
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition; //Mario's current position is now the new position.
        }

        //If Mario encounters a goomba.
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'g'){
            checkLoss();

            marioWon = encounterEnemy('g');
            if (marioWon){
                result = "won";
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            } else {
                result = "lost";
                m_marioLostGoomba = true;
            }
            
            //Prints grid, prints statement.
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a goomba and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();    
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }

        //If Mario encounters a koopa.
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'k'){
            checkLoss();

            marioWon = encounterEnemy('k');
            if (marioWon){
                result = "won";
            } else {
                result = "lost";
                m_marioLostKoopa = true;
            }

            //Prints grid, prints statement.
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a koopa and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();    
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }

        //If Mario encounters an empty space.
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'x'){
            checkLoss();
            
            //Prints grid, prints statement.
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario visited an empty space. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }

        //If Mario encounters a warp pipe.
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'w'){
            enterWarpPipe();

            //Prints grid, prints statement.
            m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
            m_world->displayGrid(m_world->m_currentLevelForMario);
            std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
            std::cout << "Mario is at power level " << m_PowLevel << ". Mario warped to next level. Mario has " << m_lastLifeCount << " lives left. Mario has " << m_coinCount;
            m_newPosition = move();    
            std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
            m_MarioPosition = m_newPosition;
        }

        //If Mario encounters a boss.
        else if (m_world->m_levelAndGrids[m_world->m_currentLevelForMario][m_MarioPosition[0]][m_MarioPosition[1]] == 'b'){  
        std::cout << "ENCOUNTERED BOSS" << std::endl;                                                                        
            marioWon = encounterBoss();
            if (!marioWon){
                m_marioLostBoss = true;
                result = "lost";
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);  
                std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
                std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a boss and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
                m_newPosition = move();    
                std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
                m_MarioPosition = m_newPosition;
            } else {
                result = "won";
                m_newPosition = m_world->getMario(m_world->m_currentLevelForMario); //Gets marios starting position for next level grid.

                if (m_world->m_isLastLevel){ //If Mario wins boss on the last level, move him on the grid to the place of the boss.
                    m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]); //Move Mario to where boss is in new level.
                } else {
                    m_world->moveMario(m_world->m_currentLevelForMario - 1, m_MarioPosition[0], m_MarioPosition[1]); //If not last level move him on previous grid.
                }

                std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
                std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a boss and " << result << ". Mario has " << m_lastLifeCount << " lives left. Mario has " << m_coinCount;  
                std::cout << " coins. "<< std::endl;
                m_MarioPosition = m_newPosition; //Position in new level != old position.

                if (m_world->m_isLastLevel){ //If Mario wins boss for last level display.
                    std::cout << "========================" << std::endl;
                    std::cout << "Finished level grid" << std::endl;
                    m_world->displayGrid(m_world->m_currentLevelForMario); //Display last level grid with Hero where boss was.
                } else {
                    std::cout << "========================" << std::endl;
                    std::cout << "Finished level grid" << std::endl;
                    m_world->displayGrid(m_world->m_currentLevelForMario - 1); //If not display Hero where boss was in previous level.
                }
                m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]); //Moves mario to original position on next level grid.
            }
        }
    }

    //End the game.
    if (m_lastLifeCount != 0){ //If we end the game with lives.
        std::cout << "WE BEAT THE GAME! :)" << std::endl;
    } else { //If we end the game with 0 lives.
        std::cout << "GAME OVER :(" << std::endl;
    }
}

//-----------------------------DONE
//firstMove method - Looks at the element before Mario was placed.
void Mario::firstMove(){

    bool marioWon;
    std::string result;

    if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'm'){ //If the first element Mario encounters is a mushroom.
        collectMushroom();
        m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario ate a mushroom. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl; 
        m_MarioPosition = m_newPosition;

    }
    else if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'c'){ //If the first element Mario encounters is a coin.
        collectCoin();
        m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario collected a coin. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl; 
        m_MarioPosition = m_newPosition;

    }
    else if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'k'){ //If the first element Mario encounters is a koopa.
        marioWon = encounterEnemy('k');
        if (marioWon){
            result = "won";
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        } else {
            result = "lost";
            m_marioLostKoopa = true;
        }
        m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a koopa and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();    
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
        m_MarioPosition = m_newPosition;
    }
    else if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'g'){ //If the first element Mario encounters is a goomba.
        marioWon = encounterEnemy('g');
        if (marioWon){
            result = "won";
            m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        } else {
            result = "lost";
            m_marioLostGoomba = true;
        }
        m_MarioPosition = m_world->getMario(m_world->m_currentLevelForMario);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario encountered a goomba and " << result << ". Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();    
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
        m_MarioPosition = m_newPosition;
    }
    else if (m_world->m_firstGameElements[m_world->m_currentLevelForMario] == 'x'){  //If the first element Mario encounters is an empty space.
        m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
        std::cout << "Level: " << m_world->m_currentLevelForMario << ". Mario is at (" << m_MarioPosition[0] << ", " << m_MarioPosition[1] << "). ";
        std::cout << "Mario is at power level " << m_PowLevel << ". Mario visited an empty space. Mario has " << m_V << " lives left. Mario has " << m_coinCount;
        m_newPosition = move();    
        std::cout << " coins. Mario will move " << m_direction << "." << std::endl;
        m_MarioPosition = m_newPosition;
    }
}


//-----------------------------DONE
//checkLoss method - Checks if Mario lost against an enemy.
void Mario::checkLoss(){
    if (m_marioLostGoomba){ //If lost against a goomba.
        m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'g');
        m_marioLostGoomba = false;
    } else if (m_marioLostKoopa){ //If lost against a koopa.
        m_marioLostKoopa = false;
        m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'k');
    } else if (m_marioLostBoss){ //If lost against a boss.
        m_marioLostBoss = false;
        m_world->moveMarioAfterLoss(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1], 'b');
    } else if (!m_marioLostGoomba && !m_marioLostKoopa){ //If Mario won against goomba or koopa.
        m_world->moveMario(m_world->m_currentLevelForMario, m_MarioPosition[0], m_MarioPosition[1]);
    }
}

//-----------------------------DONE
//collectCoin method.
void Mario::collectCoin(){
    ++m_coinCount;

    //If coin count reaches 20, reset coin count to 0, increase Mario's lives by 1.
    if (m_coinCount == 20){
        m_coinCount = 0;
        ++m_V;
    }
}

//-----------------------------DONE
//collectMushroom method.
void Mario::collectMushroom(){
    
    //Increases power level only if current power level is 0 or 1.
    switch (m_PowLevel){
        case 0:
        case 1:
            ++m_PowLevel;
            break;
        default:
            break;
    }
}

//-----------------------------DONE
//encounterBoss method - Returns a boolean showing if Mario beat the boss.
bool Mario::encounterBoss(){

    bool bossResult;

    srand(time(NULL));
    int probability = 1 + (rand() % 100);
        if (probability <= 50){ //If Mario won against the boss.
            bossWin();
            bossResult = true;
            std::cout << "Mario fought the level boss and won!" << std::endl;
        } 
        else{ //If Mario lost against the boss.
            bossLose();
            bossResult = false;
            std::cout << "Mario fought the level boss and lost :(" << std::endl;
        }
    return bossResult;
}

//-----------------------------DONE
//bossWin method.
void Mario::bossWin(){
    goNextLevel(); //Advances the game to the next level.
}

//-----------------------------DONE
//bossLose method.
void Mario::bossLose(){
    switch (m_PowLevel){
        case 0:
        case 1: //If power level is 1.
            m_V--; //Decreases life count by 1.
            m_lastLifeCount = m_V; //Stores previous life count so it can be accessed.
            break;
        case 2: //If power level is 2.
            m_PowLevel -= 2; //Decreases power level by 2.
            encounterBoss(); //Fights boss again.
            break;
        default:
            break;
    }
}

//-----------------------------DONE
//encounterEnemy method - Returns a boolean showing if Mario beat the enemy.
//Parameters: char - the enemy that Mario encounters.
bool Mario::encounterEnemy(char enemy){

    bool enemyResult;

    //If Mario encounters a goomba.
    if (enemy == 'g'){
        srand(time(NULL));
        int probability = 1 + (rand() % 100);
            if (probability <= 80){ //If Mario won against the goomba.
                marioWin();
                enemyResult = true;
            } 
            else{ //If Mario lost against the goomba.
                marioLose();
                enemyResult = false;
            }
    }
    //If Mario encounters a koopa.
    else if (enemy == 'k'){
        srand(time(NULL));
        int probability = 1 + (rand() % 100);
            if (probability <= 65){ //If Mario won against the koopa.
                marioWin();
                enemyResult = true;
            } 
            else{ //If Mario lost against the goomba.
                marioLose();
                enemyResult = false;
            }
    }
    return enemyResult;
}

//-----------------------------DONE
//marioWin method.
void Mario::marioWin(){
    m_defeatedEnemyCount++; //Increases count for number of defeated enemies.
    if (m_defeatedEnemyCount == 7){ //If Mario defeats 7 enemies, increase # of lives by 1.
        m_V++;
    }
}

//-----------------------------DONE
//marioLose method.
void Mario::marioLose(){
    if (m_PowLevel == 0){ //If power level 0, Mario loses life and defeated enemy count resets to 0.
        m_V--;
        m_lastLifeCount = m_V;
        m_defeatedEnemyCount = 0;
        m_PowLevel = 0;
    }
    else { //Decreases power level by 1.
        m_PowLevel--;
    }
}

//-----------------------------DONE
//enterWarpPipe method.
void Mario::enterWarpPipe(){
    goNextLevel(); //Advances the game to the next level.
}

//-----------------------------DONE
//move method  - Returns a 1D int array of Mario's movement [up/down, left/right].
int* Mario::move(){
    int directions = 4;
    int randDirection = 1 + (rand() % directions); //Random number generator, range: 1-4.
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

//-----------------------------DONE
//moveDown method.
void Mario::moveDown(){
    if (m_MarioPosition[0] == m_world->m_N - 1){ //If at the bottom of grid move to top (0,1) --> (1,1).
        m_MarioPosition[0] = 0;
    }
    else{
        m_MarioPosition[0] = m_MarioPosition[0] + 1; //Move down one position.
    }
}

//-----------------------------DONE
//moveLeft method.
void Mario::moveLeft(){
    if (m_MarioPosition[1] == 0){ // If at the left of grid move to right edge (4,4) --> (4,3).
        m_MarioPosition[1] = m_world->m_N - 1;
    }
    else{
        m_MarioPosition[1] = m_MarioPosition[1] - 1; //Move left one position.
    }
}

//-----------------------------DONE
//moveRight method.
void Mario::moveRight(){
    if (m_MarioPosition[1] == m_world->m_N - 1){//If at the right of grid move to left edge (0,1) --> (0,2)
        m_MarioPosition[1] = 0;
    }
    else{
        m_MarioPosition[1] = m_MarioPosition[1] + 1; //Move right one position.
    }
}

//-----------------------------DONE
//moveUp method.
void Mario::moveUp(){
    if (m_MarioPosition[0] == 0){ //If at the top of the grid move to the bottom (4,4) --> (3,4)
        m_MarioPosition[0] = m_world->m_N - 1;
    }
    else{
        m_MarioPosition[0] = m_MarioPosition[0] - 1; //Move up one position.
    }
}

//-----------------------------DONE
//goNextLevel method.
void Mario::goNextLevel(){
    if (m_world->m_currentLevelForMario >= m_world->m_L - 1){ //If Mario is on the last level.
        m_world->m_isLastLevel = true;
        m_lastLifeCount = m_V; //Stores previous life count so it can be accessed.
        m_V = 0; //Sets # of lives to 0, breaks out of while loop in play() method to end game.
    }
    else{
        m_world->m_currentLevelForMario++; //Advances to the next level.
    }
}