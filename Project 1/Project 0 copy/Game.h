//
//  Game.h
//  Project 0
//
//  Created by Elizabeth Han on 1/16/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include <string> ///remove later.
using namespace std;

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nRats);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    string takePlayerTurn();
};



#endif /* GAME_INCLUDED */
