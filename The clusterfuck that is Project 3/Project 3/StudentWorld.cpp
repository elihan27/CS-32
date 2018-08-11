#include "StudentWorld.h"
#include <string>
#include "Field.h"
#include "Actor.h"
#include "GraphObject.h"
using namespace std;


int StudentWorld::init()
{
    m_ticks = 0;
    Field m_field;
    string fieldFile = getFieldFilename();
    string error;
    if (m_field.loadField(fieldFile, error) != Field::LoadResult::load_success) {
        setError(fieldFile + " " + error);
        return GWSTATUS_LEVEL_ERROR; // something bad happened!
        
    }
    
    //m_field = f;
    
    for (int i =0; i!= VIEW_HEIGHT; i++)
    {
        for (int j=0; j!=VIEW_WIDTH; j++)
        {
           //std::list<Actor*> a;
           // a= m_actors[i][j];
            
            
           m_actors[i][j]= std::list<Actor*>();
            
            
            Actor* object;
            Field::FieldItem item = m_field.getContentsOf(j,i);
            if (item==Field::FieldItem::rock)
            {object = new Pebble(IID_ROCK, i, j, this);
             m_actors[i][j].push_back(object);
                //a.push_back(object);
            }
            else if (item==Field::FieldItem::grasshopper)
            { object = new BabyGrasshopper(IID_BABY_GRASSHOPPER, i, j, static_cast<GraphObject::Direction>(randInt(1,4)), this);
                m_actors[i][j].push_back(object);
                //a.push_back(object);
            }
          
           // a.push_back(object);
            

            
            
            
        }
        
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    m_ticks++;
    
    
    for (int i =0; i!= VIEW_HEIGHT; i++)
    {
        for (int j=0; j!=VIEW_WIDTH; j++)
        {
            for (list<Actor*>::iterator p = m_actors[i][j].begin(); p!= m_actors[i][j].end(); p++)
            {
               if (!m_actors[i][j].empty())
               {
                   int x = i,y=j;
                   (*p)->doSomething(); //Problem also here
                  /*int xNew =(*p)->getX(), yNew = (*p)->getY();
                   if (x!= xNew|| y!= yNew)
                   {
                       m_actors[xNew][yNew].push_back(*p);
                       p = m_actors[i][j].erase(p);
                   
                       
                   }
                    */
                   
                   
               }
                
            }
        }
        
    }
    
    string s = "Ticks " + to_string(m_ticks);
    setGameStatText(s);
    
    if (m_ticks<2000)
        return GWSTATUS_CONTINUE_GAME;
    
    return GWSTATUS_NO_WINNER;
    
}


bool StudentWorld::pebbleExists(int x, int y)
{
    
    for (list<Actor*>::iterator p = m_actors[x][y].begin(); p!= m_actors[x][y].end(); p++)
        if ((*p)->getIsPebble())
            return true;
    return false;
}


//bool StudentWorld::pebbleExists(int x, int y) //revised
//{
    
    //if (m_field.getContentsOf(x,y)==Field::FieldItem::rock)
     //   return true;
    //return false;
       
       
   /* Field::FieldItem item = m_field.getContentsOf(y, x);
    if (item==Field::FieldItem::rock)
        return true;
    return false;
    */

//}

 
/*

Actor* StudentWorld::first(int x, int y)
{
    list<Actor*>:: iterator p;
    p = m_actors[x][y].begin();
    return *p;
}
 */

/*bool StudentWorld::pebbleExists(int x, int y) //revised
{
    
    if (first(x,y))
    Field::FieldItem item = m_field.getContentsOf(x, y);
    if (item==Field::FieldItem::rock)
        return true;
    return false;
    
}
 
 */


    


/*bool StudentWorld::pebbleExists(int x, int y) //fix pebble Exists
{
    
  
    //there is also a problem here
    
   

if (m_actors[x][y].empty())
      return false;
    
 list<Actor*>::iterator p = m_actors[x][y].begin();

    if((*p)->isYouPebble()==true)
    return true;
 
 */
   
  /*  for (list<Actor*>::iterator p = m_actors[x][y].begin(); p!= m_actors[x][y].end(); p++)
    {
        if((*p)->isYouPebble()==true)
            return true;
    }
   */
    
    // return false;


 

    
  
     /*
    if (dir == BabyGrasshopper::none)
        return true;
    
    
   
    
    else if (dir==BabyGrasshopper::up)
    {
        for (list<Actor*>::iterator p = m_actors[x][y+1].begin(); p!= m_actors[x][y+1].end(); p++)
            if ((*p)->isYouPebble())
                return true;
        
    }
   
     
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
    
  // return false;
    
    
//}
//}

void StudentWorld::cleanUp()
{
    
    
    for (int i =0; i!= VIEW_HEIGHT; i++)
    {
        for (int j=0; j!=VIEW_WIDTH; j++)
        {
            for (list<Actor*>::iterator it = m_actors[i][j].begin(); it!= m_actors[i][j].end();)
            {
                delete *it;
                it = m_actors[i][j].erase(it);
            
            }
            
        }
        
    }

    
    
}



StudentWorld::~StudentWorld()
{
    cleanUp();
}





GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
