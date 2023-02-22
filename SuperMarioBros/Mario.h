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
        

    private:
        void collectCoin();
        void collectMushroom();
        void encounterEnemy();
        void encounterBoss(); 
        void encounterNothing();
        void enterWarpPipe();
        bool attackGoomba();
        bool attackKoopa();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        int* m_MarioPosition;
        int m_PowLevel;
        int m_V;
        World* m_world;
        int m_coinCount;
        std::string m_direction;

};



#endif 