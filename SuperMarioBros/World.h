#ifndef WORLD_H
#define WORLD_H

class World{
    public:
        World(int L, int N);
        ~World();

    private:
        Level* level;
        char*** m_levelAndGrids;
};


#endif