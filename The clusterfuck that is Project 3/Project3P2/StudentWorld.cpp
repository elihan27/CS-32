#include "StudentWorld.h"
#include "Compiler.h"
#include <string>
#include <vector>
#include "Actor.h"
#include <iostream>
#include <sstream>

using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
    return new StudentWorld(assetDir);
}

int StudentWorld::init()
{
    m_ticks = 0;
    
    std::string error;
    
    Compiler *compilerForEntrant0 = new Compiler, *compilerForEntrant1 = new Compiler, *compilerForEntrant2= new Compiler, *compilerForEntrant3= new Compiler;
    
    
    compilerProgram =getFilenamesOfAntPrograms();
    
    std::vector<std::string> fileNames = getFilenamesOfAntPrograms();
    
    
    if ( ! compilerForEntrant0->compile(fileNames[0], error) )
    {
        setError(fileNames[0] + " " + error);
        return GWSTATUS_LEVEL_ERROR;
    }
    
    if ( ! compilerForEntrant1->compile(fileNames[1], error) )
    {
        setError(fileNames[1] + " " + error);
        return GWSTATUS_LEVEL_ERROR;
    }
    if ( ! compilerForEntrant2->compile(fileNames[2], error) )
    {
        setError(fileNames[2] + " " + error);
        return GWSTATUS_LEVEL_ERROR;
    }
    if ( ! compilerForEntrant0->compile(fileNames[3], error) )
    {
        setError(fileNames[3] + " " + error);
        return GWSTATUS_LEVEL_ERROR;
    }
    
    
    
    
    Field m_field;
    string fieldFile = getFieldFilename();
    if (m_field.loadField(fieldFile, error) != Field::LoadResult::load_success) {
        setError(fieldFile + " " + error);
        return GWSTATUS_LEVEL_ERROR; // something bad happened!
        
        
    }
    
    
    //m_field = f;
    
    for (int i =0; i!= VIEW_HEIGHT; i++)
    {
        for (int j=0; j!=VIEW_WIDTH; j++)
        {
            
            Actor* object;
            Field::FieldItem item = m_field.getContentsOf(i, j);
            
            
            switch (item)
            {
                case Field::FieldItem::anthill0:
                    object = new AntHill(this, i, j, 0, compilerForEntrant0);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::anthill1:
                    object = new AntHill(this, i, j, 1, compilerForEntrant1);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::anthill2:
                    object = new AntHill(this, i, j, 2, compilerForEntrant2);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem:: anthill3:
                    object = new AntHill(this, i, j, 3, compilerForEntrant3);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::rock:
                    object = new Pebble(this, i, j);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::grasshopper:
                    object = new BabyGrasshopper(this, i, j);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::food:
                    object= new Food(this, i, j, 6000);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::water:
                    object = new WaterPool(this, i, j);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::poison:
                    object = new Poison(this, i, j);
                    m_actors[i][j].push_back(object);
                    break;
                case Field::FieldItem::empty: //check this later
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
                
            {
                if (m_actors[i][j][w]->isDead())
                {
                    delete m_actors[i][j][w];
                    m_actors[i][j].erase(m_actors[i][j].begin()+w);
                    w--;
                }
            }
            for (int w =0; w!= m_actors[i][j].size(); w++)
                
            {
                int x = i,y=j;
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
    
    /*string s = "Ticks " + to_string(m_ticks);
     setGameStatText(s);
     
     */
    ostringstream display;
    display << "Ticks: " << 2000 - m_ticks << "  " << compilerProgram[0] << ": " << m_colony0 << "  " << compilerProgram[1] << ": " << m_colony1 << "  " << compilerProgram[2] << ": " << m_colony2 << "  " << compilerProgram[3] << ": " << m_colony3;
    string gameStart = display.str();
    setGameStatText(gameStart);
    
    
    
    
    if (m_ticks<2000)
        return GWSTATUS_CONTINUE_GAME;
    
    return GWSTATUS_NO_WINNER;
    
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

bool StudentWorld::canMoveTo(int x, int y) const
{
    if (m_actors[x][y].size()!=0)
    {if (m_actors[x][y][0]->blocksMovement())
        return false;
    }
    return true;
    
}



void StudentWorld::addActor(Actor* a)
{
    int x = a->getX(), y = a->getY();
    // Actor* temp = getEdibleAt(x, y);
    //if (a->isEdible() && temp!=nullptr )
    //{
    //    int i = a->getEnergy();
    
    //}
    m_actors[x][y].push_back(a);
}

Actor* StudentWorld::getEdibleAt(int x, int y) const
{
    for (int w =0; w!= m_actors[x][y].size(); w++)
    {
        if (m_actors[x][y][w]->isEdible())
            return m_actors[x][y][w];
    }
    
    
    return nullptr;
}


bool StudentWorld::isTherePheromone(int x, int y) const
{
    for (int w =0; w!= m_actors[x][y].size(); w++)
    {
        if (m_actors[x][y][w]->isPheromone())
            return true;
    }
    return false;
}


Actor* StudentWorld::getPheromoneAt(int x, int y, int colony) const
{
    for (int w =0; w!= m_actors[x][y].size(); w++)
    {
        if (m_actors[x][y][w]->isMyPheromone(colony))
            return m_actors[x][y][w];
    }
    
    return nullptr;
}

bool StudentWorld::isEnemyAt(int x, int y, int colony) const
{
    for (int w = 0; w!= m_actors[x][y].size();w++ )
    {
        if (m_actors[x][y][w]->isEnemy(colony))
            return true;
    }
    
    return false;
}//not right but probably a good assumption to make;

bool StudentWorld::isDangerAt(int x, int y, int colony) const
{
    for (int w = 0; w!= m_actors[x][y].size();w++ )
    {
        if (m_actors[x][y][w]->isEnemy(colony)||m_actors[x][y][w]->isDangerous())
            return true;
    }
    
    return false;
}

// Is the anthill of the indicated colony at x,y?
bool StudentWorld::isAntHillAt(int x, int y, int colony) const
{
    for (int w = 0; w!= m_actors[x][y].size();w++ )
    {
        if (m_actors[x][y][w]->isMyHill(colony))
            return true;
    }
    return false;
}

// Bite an enemy of an ant of the indicated colony at me's location
// (other than me; insects don't bite themselves).  Return true if an
// enemy was bitten.
bool StudentWorld::biteEnemyAt(Actor* me, int colony, int biteDamage)
{
    int x = me->getX(), y = me->getY();
    for (int w = 0; w!= m_actors[x][y].size();w++ )
    {
        if (isEnemyAt(x, y, colony) && m_actors[x][y][w]!=me)
            m_actors[x][y][w]->getBitten(biteDamage);
    }
    
    return true;
};

// Poison all poisonable actors at x,y.
bool StudentWorld::poisonAllPoisonableAt(int x, int y)
{
    for (int w=0; w!= m_actors[x][y].size(); w++)
    {
        m_actors[x][y][w]->getPoisoned();
    }
    
    return false;}


// Stun all stunnable actors at x,y.
bool StudentWorld::stunAllStunnableAt(int x, int y)
{
    
    for (int w=0; w!= m_actors[x][y].size(); w++)
    {
        m_actors[x][y][w]->getStunned();
    }
    return true;
}

// Record another ant birth for the indicated colony.
void StudentWorld::increaseScore(int colony)
{
    switch(colony)
    {
        case 0:
            m_colony0++;
            break;
        case 1:
            m_colony1++;
            break;
        case 2:
            m_colony2++;
            break;
        case 3:
            m_colony3++;
            break;
            
    }
    
}









// Students:  Add code to this file (if you wish), StudentWorld.h, Actor.h and Actor.cpp
