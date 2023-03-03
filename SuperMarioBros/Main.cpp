/*
Arisa Trombley, Carina Chan
2375446, 2367721
trombley@chapman.edu, carchan@chapman.edu
CPSC 350-02, CPSC 350-03
Programming Assignment 2 - Not So Super Mario Bros.
*/

/* DESCRIPTION
Main method to play a game of Mario.
*/


#include <iostream>
#include <fstream>
#include "World.h"
#include "Mario.h"

using namespace std;
int main(){
    ifstream reader; //Reader for input from txt file.
    string line; //String for each line input.
    reader.open("spec.txt");
    int L; //# of levels.
    int N; //Grid dimension.
    int V; //# of lives.
    int coinChance;
    int emptyChance;
    int goombaChance;
    int mushroomChance;
    int koopaChance;

    //Reading input from txt file and assigning to respective variables.
    while (reader){
        getline(reader, line);
        L = stoi(line);
        getline(reader, line);
        N = stoi(line);
        getline(reader, line);
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

    //Creating World and Mario objects.
    World* world;
    world = new World(L, N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    Mario* mario;
    mario = new Mario(V, world);

    //Calling play method, playing the game.
    mario->play();
    
    //Closing the reader.
    reader.close();

    delete mario;
    delete world;

    return 0;
}