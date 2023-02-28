/*
Arisa Trombley, Carina Chan
2375446, 2367721
trombley@chapman.edu, carchan@chapman.edu
CPSC 350-02, CPSC 350-03
Programming Assignment 2 - Not So Super Mario Bros.
*/


#include <iostream>
#include <fstream>
#include "World.h"
#include "Mario.h"

using namespace std;
int main(){
    ifstream reader;
    string line;
    reader.open("spec.txt");
    int L;
    int N;
    int V;
    int coinChance;
    int emptyChance;
    int goombaChance;
    int mushroomChance;
    int koopaChance;

    while (reader){
        getline(reader, line);              //# of levels
        L = stoi(line);
        getline(reader, line);              //grid dimension
        N = stoi(line);
        getline(reader, line);              //# of lives
        V = stoi(line);
        getline(reader, line);
        coinChance = stoi(line);
        getline(reader, line);
        emptyChance = stoi(line);
        getline(reader, line);
        goombaChance = stoi(line);
        getline(reader, line);
        koopaChance = stoi(line);
        getline(reader, line);
        mushroomChance = stoi(line);
        break;
    }


    World* world;
    world = new World(L, N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    Mario* mario;
    mario = new Mario(V, world);

    mario->play();
    

    reader.close();

    delete mario;
    delete world;

    return 0;

}