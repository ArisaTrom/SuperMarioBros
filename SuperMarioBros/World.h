#ifndef WORLD_H
#define WORLD_H

class World{
    public:
        World(int L, int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance);
        ~World();
        void displayGrid(int level);
        void initializeLevels(int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance);
        int* getMario(int level);
        int m_currentLevelForMario;
        void moveMario(int level, int mario_x, int mario_y);
        void moveMarioAfterLoss(int level, int mario_x, int mario_y, char e);
        char*** m_levelAndGrids;
        int m_N;
        int m_L;
        char* m_firstGameElements;

    private:
        
        
};


#endif