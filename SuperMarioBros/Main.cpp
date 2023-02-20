#include <iostream>
#include <fstream>
#include "World.h"

using namespace std;
int main(){
    ifstream reader;
    reader.open("spec.txt");

    // while (reader){
    //     //getline(reader, line);              //# of levels
    //     int L = line;
    //     //getline(reader, line);              //grid dimension
    //     int N = line;
    //     //getline(reader, line);              //# of lives
    //     int V = line;
    //     //getline(reader, line);
    //     int coinChance = line;
    //     //getline(reader, line);
    //     int emptyChance = line;
    //     //getline(reader, line);
    //     int goombaChance = line;
    //     //getline(reader, line);
    //     int koopaChance = line;
    //     //getline(reader, line);
    //     int mushroomChance = line;
    // }

    int L = 2;
    int N = 5;
    int V = 3;
    int coinChance = 20;
    int emptyChance = 20;
    int goombaChance = 20;
    int koopaChance = 20;
    int mushroomChance = 20;


    World* world;
    world = new World(L, N, coinChance, emptyChance, goombaChance, koopaChance, mushroomChance);
    cout << "displaying grid" << endl;

    reader.close();

    //Game game;
    //game.play();
    

    return 0;

}