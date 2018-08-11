#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "StudentWorld.h"
#include "Field.h"
#include <string>
#include <list>


class Actor;


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir)
    {
        
    }
    
    
     ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    bool pebbleExists(int x, int y);
    Actor* first(int x, int y);
    
    
private:
    int m_ticks; //comments
    Field m_field;
    std::list<Actor*> m_actors[VIEW_WIDTH][VIEW_HEIGHT];
    
    //keep track of pebbles and baby grasshoppers
    //constructor and destructor
    
};

#endif // STUDENTWORLD_H_
