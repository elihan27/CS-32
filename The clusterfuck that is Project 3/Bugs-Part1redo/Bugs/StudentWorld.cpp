#include "StudentWorld.h"
#include "Actor.h"
#include <string>


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
    
    
    for (int i =0; i!= VIEW_HEIGHT; i++)
    {
        for (int j=0; j!=VIEW_WIDTH; j++)
        {
            
            Actor* object;
            Field::FieldItem item = m_field.getContentsOf(i, j);
            
            switch (item)
            {
                case Field::FieldItem::rock:
                    object = new Pebble(this, i, j);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::grasshopper:
                    object = new BabyGrasshopper(this, i, j, static_cast<GraphObject::Direction>(randInt(1,4)), IID_BABY_GRASSHOPPER, 2);
                    m_actors[i][j].push_back(object);
                    break;
                default: //check this later
                    break;
            }
            
            
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
        
            for (int w =0; w!= m_actors[i][j].size(); w++)
            
            {  int x = i,y=j;
                ( m_actors[i][j][w])->doSomething(); //Problem also here
            
                int xNew =m_actors[i][j][w]->getX(), yNew = m_actors[i][j][w]->getY();
                if (x!= xNew|| y!= yNew)
                {
                    m_actors[xNew][yNew].push_back(m_actors[i][j][w]);
                    m_actors[i][j].erase(m_actors[i][j].begin()+w);
                    w--;
                    
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
    if (m_actors[x][y].size()!=0)
    {if (m_actors[x][y][0]->blocksMovement())
        return true;
    }
    return false;
}

void StudentWorld::cleanUp()
{
    
    
    for (int i =0; i!= VIEW_HEIGHT; i++)
    {
        for (int j=0; j!=VIEW_WIDTH; j++)
        {
            
            for (int w =0; w!= m_actors[i][j].size(); w++)
            {
                delete m_actors[i][j][w];
               m_actors[i][j].erase(m_actors[i][j].begin()+w);
                w--;

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
