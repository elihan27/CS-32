#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "GameConstants.h"
#include "GraphObject.h"
#include "StudentWorld.h"
#include <string>
#include <list>


class Actor;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetDir) //I have no idea what this does.
	 : GameWorld(assetDir)
	{
        
	}

    ~StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    bool pebbleExists(int x, int y);
    
    
    

private:
   int m_ticks; //comments
    std::list<Actor*> m_actors[VIEW_WIDTH][VIEW_HEIGHT]; //this is the grid we need.
    
    
};

#endif // STUDENTWORLD_H_
