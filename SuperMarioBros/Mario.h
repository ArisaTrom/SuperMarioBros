#ifndef MARIO_H
#define MARIO_H
#include <string>
#include "World.h"

class Mario{
    public:
        Mario(int V, World* world);
        ~Mario();
        int* move();
        void play();
        int m_V;
        

    private:
        void firstMove();
        void collectCoin();
        void collectMushroom();
        bool encounterEnemy(char enemy);
        void marioWin();
        void marioLose();
        bool encounterBoss();
        void bossWin();
        void bossLose(); 
        void enterWarpPipe();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void goNextLevel();
        bool m_marioLostKoopa;
        bool m_marioLostGoomba;
        int m_lastLifeCount;
        int* m_MarioPosition;
        int m_PowLevel;
        int m_defeatedEnemyCount;
        World* m_world;
        int m_coinCount;
        std::string m_direction;
        int* m_newPosition;

};



#endif 