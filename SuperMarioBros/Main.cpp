#include <iostream>
#include <fstream>

using namespace std;
int main(){
    ifstream reader;
    reader.open("spec.txt");

    while (reader){
        int L = getline(reader, line);
        int N = getline(reader, line);
        int V = getline(reader, line);
        int coinChance = getline(reader, line);
        int emptyChance = getline(reader, line);
        int goombaChance = getline(reader, line);
        int koopaChance = getline(reader, line);
        int mushroomChance = getline(reader, line);
    }

    

    reader.close();
    

    

    return 0;

}