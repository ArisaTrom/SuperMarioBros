#include "Mario.h"
#include <iostream>

Mario::Mario(){
    std::cin >> V;
    PowLevel = "PL0";
    coinCount = 0;

}

Mario::~Mario(){

}

void Mario::collectCoin(){
    ++coinCount;
    if (coinCount == 20){
        coinCount = 0;
        ++V;
    }
    std::cout << "Mario collected a coin" << std::endl;
}


void Mario::collectMushroom(){
    switch(PowLevel){
        case "PL0":
        PowLevel = "PL1";
        break;
        case "PL1":
        PowLevel = "PL2";
        break;
        case "PL2":
        PowLevel = "PL2";
        break;
        default:
    }
    std::cout << "Mario ate a mushroom" << std::endl;
}

void Mario::encounterBoss(){
    //if win 
    std::cout << "Mario fought the level boss and won!" << std::endl;
    //if loss
    std::cout << "Mario fought the level boss and lost :(" << std::endl;
}

void Mario::encounterEnemy(){
    //if enemy is Goomba
        //if win
        std::cout << "Mario fought a Goomba and won!" << std::endl;
        //if loss
        std::cout << "Mario fought a Goomba and lost :(" << std::endl;
    //if enemy is Koopa
        //if win 
        std::cout << "Mario fought a Koopa and won!" << std::endl;
        //if loss
        std::cout << "Mario fought a Koopa and lost :(" << std::endl;
}

void Mario::encounterNothing(){
    std::cout << "The position is empty" << std::endl;
}

void Mario::enterWarpPipe(){
    //Mario warps to random spot in next level 
    std::cout << "Mario warped" << std::endl;
}






