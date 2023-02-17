#ifndef LEVEL_H
#define LEVEL_H

class Level{
    public:
        Level(int N);
        ~Level();
        void displayGrid();

    private:
        int N;
        char** m_levelGrid = nullptr;
        const char population[8] = {x, m, c, g, k, b, w, H};
        void initializedGrid();
};





#endif