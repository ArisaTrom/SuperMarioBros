#ifndef LEVEL_H
#define LEVEL_H

class Level{
    public:
        Level(int N, int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance);
        ~Level();
        void displayGrid();
        void initializedGrid(int coinChance, int emptyChance, int goombaChance, int koopaChance, int mushroomChance);
        int* getMario();
        char** getGrid();

    private:
        int m_N;
        char** m_levelGrid;
};





#endif