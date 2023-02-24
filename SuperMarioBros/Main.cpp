#include <iostream>
#include <fstream>
#include "World.h"
#include "Mario.h"

using namespace std;
int main(){
    ifstream reader;
    string line;
    reader.open("spec.txt");

    while (reader){
        getline(reader, line);              //# of levels
        int L = stoi(line);
        getline(reader, line);              //grid dimension
        int N = stoi(line);
        getline(reader, line);              //# of lives
        int V = stoi(line);
        getline(reader, line);
        int coinChance = stoi(line);
        getline(reader, line);
        int emptyChance = stoi(line);
        getline(reader, line);
        int goombaChance = stoi(line);
        getline(reader, line);
        int koopaChance = stoi(line);
        getline(reader, line);
        int mushroomChance = stoi(line);
    }

    cout << L << N << V << coinChance << emptyChance << endl;


    // World* world;
    // world = new World(L, N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    // Mario* mario;
    // mario = new Mario(V, world);

    // mario->play();
    

    reader.close();

    delete mario;
    delete world;

    return 0;

}