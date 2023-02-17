#include <iostream>
#include <fstream>
#include "Level.h"

using namespace std;
int main(){
    ifstream reader;
    reader.open("spec.txt");

    while (reader){
        int L = getline(reader, line);              //# of levels
        int N = getline(reader, line);              //grid dimension
        int V = getline(reader, line);              //# of lives
        int coinChance = getline(reader, line);
        int emptyChance = getline(reader, line);
        int goombaChance = getline(reader, line);
        int koopaChance = getline(reader, line);
        int mushroomChance = getline(reader, line);
    }

    reader.close();

    //Game game;
    //game.play();
    

    return 0;

}