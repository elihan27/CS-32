//
//  Player.h
//  Project 0
//
//  Created by Elizabeth Han on 1/16/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//

#ifndef PLAYER_INCLUDED
#define PLAYER_INCLUDED

using namespace std;

class Arena;

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string dropPoisonPellet();
    string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif /* PLAYER_INCLUDED */
