#ifndef MARIO_H
#define MARIO_H
#include <string>

class Mario{
    public:
        Mario();
        ~Mario();
        void collectCoin();
        void collectMushroom();
        void encounterEnemy();
        void encounterBoss(); 
        void encounterNothing();
        void enterWarpPipe();

    private:
        std::string m_PowLevel;
        int m_V;
        int m_coinCount;

}



#endif 