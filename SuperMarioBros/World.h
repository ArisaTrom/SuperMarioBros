#ifndef WORLD_H
#define WORLD_H

class World{
    public:
        World(int L, int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance);
        ~World();
        void displayGrid(int level);
        void initializeLevels(int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance);
        void goNextLevel();
        int* getMario(int level);
        int m_currentLevelForMario;
        void moveMario(int level, int mario_x, int mario_y);
        char*** m_levelAndGrids;
        int m_N;

    private:
        int m_L;
        
        
};


#endif