#include "Mario.h"
#include <iostream>
#include <cstdlib>


Mario::Mario(){
    std::cin >> m_V;
    m_PowLevel = "PL0";
    m_coinCount = 0;

}

Mario::~Mario(){

}

void Mario::collectCoin(){
    ++m_coinCount;
    if (m_coinCount == 20){
        m_coinCount = 0;
        ++m_V;
    }
    std::cout << "Mario collected a coin" << std::endl;
}


void Mario::collectMushroom(){
    switch(m_PowLevel){
        case "PL0":
        m_PowLevel = "PL1";
        break;
        case "PL1":
        m_PowLevel = "PL2";
        break;
        case "PL2":
        m_PowLevel = "PL2";
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
        //position is empty
        std::cout << "Mario fought a Goomba and won!" << std::endl;
        //if loss
        std::cout << "Mario fought a Goomba and lost :(" << std::endl;
    //if enemy is Koopa
        //if win 
        //position
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

bool Mario::attackGoomba(){
    //with probability
    return true
}

bool Mario::attackKoopa(){

}

void Mario::move(){
    int directions = 4;
    int pickedChoice = (int)(rand() * directions);
    switch (directions){
        case 1:         //up
        //Move mario 
        case 2:         //down
        case 3:         //left
        case 4:         //right
    }
 }

 
 




