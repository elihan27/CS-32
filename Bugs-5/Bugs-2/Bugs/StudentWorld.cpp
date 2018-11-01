#include "StudentWorld.h"
#include <string>
#include "Field.h"
#include "Actor.h"
#include "GraphObject.h"
using namespace std;


int StudentWorld::init()
{
    m_ticks = 0;
    Field f;
    string fieldFile = getFieldFilename();
    string error;
    if (f.loadField(fieldFile, error) != Field::LoadResult::load_success) {
        setError(fieldFile + " " + error);
        return GWSTATUS_LEVEL_ERROR; // something bad happened!
    
    }
    
    for (int i =0; i!= VIEW_WIDTH; i++)
    {
        for (int j=0; j!=VIEW_HEIGHT; j++)
        {
            Actor* object;
            Field::FieldItem item = f.getContentsOf(i,j);
            if (item==Field::FieldItem::rock)
                object = new Pebble(IID_ROCK, i, j, GraphObject::Direction::right, 1, 0.25);
            else if (item==Field::FieldItem::grasshopper)
                object = new BabyGrasshopper(IID_BABY_GRASSHOPPER, i, j, GraphObject::Direction::right, 1, .25);
            m_actors[i][j].push_back(object);
            
        }
            
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_ticks++;
    
    
  
     for (int i =0; i!= VIEW_WIDTH; i++)
     {
         for (int j=0; j!=VIEW_HEIGHT; j++)
         {
             for (list<Actor*>::iterator p = m_actors[i][j].begin(); p!= m_actors[i][j].end(); p++)
                 (*p)->doSomething();
         }
     
     }
   
    
    if (m_ticks<2000)
        return GWSTATUS_CONTINUE_GAME;
    
    return GWSTATUS_NO_WINNER;
}



// This code is here merely to allow the game to build, run, and terminate after you hit enter.
// Notice that the return value GWSTATUS_NO_WINNER will cause our framework to end the simulation.

bool StudentWorld::pebbleExists(int x, int y, GraphObject::Direction dir) //fix pebble Exists
{
    if (dir == BabyGrasshopper::none)
        return true;
   
    
    else if (dir==BabyGrasshopper::up)
        {
            for (list<Actor*>::iterator p = m_actors[x][y+1].begin(); p!= m_actors[x][y+1].end(); p++)
               if ((*p)->isYouPebble())
                    return true;
        
        }
    /*

    else if (dir==BabyGrasshopper::down)
    {
        for (list<Actor*>::iterator p = m_actors[x][y-1].begin(); p!= m_actors[x][y-1].end(); p++)
            if ((*p)->isYouPebble())
                return true;
        
    }
    else if (dir==BabyGrasshopper::left)
    {
        for (list<Actor*>::iterator p = m_actors[x+1][y].begin(); p!= m_actors[x+1][y].end(); p++)
            if ((*p)->isYouPebble())
                return true;
    }
    
    else if (dir==BabyGrasshopper::left)
    {
        for (list<Actor*>::iterator p = m_actors[x+1][y].begin(); p!= m_actors[x+1][y].end(); p++)
            if ((*p)->isYouPebble())
                return true;
    }
    
    else if (dir==BabyGrasshopper::left)
    {
        for (list<Actor*>::iterator p = m_actors[x-1][y].begin(); p!= m_actors[x-1][y].end(); p++)
            if ((*p)->isYouPebble())
                return true;
    }
*/
    
    return false;

    
}


GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
