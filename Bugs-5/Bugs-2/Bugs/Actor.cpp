#include "Actor.h"
#include "GraphObject.h"
#include "StudentWorld.h"


Actor:: Actor(int imageID, int startX, int startY, Direction dir, int depth, double size) : GraphObject(imageID, startX, startY, right, 0, .25)
{}



void Actor::doSomething()
{}



BabyGrasshopper::BabyGrasshopper(int imageID, int startX, int startY, Direction dir, int depth, double size) : Actor(IID_BABY_GRASSHOPPER, startX, startY, static_cast<GraphObject::Direction>(randInt(1,4)), 1, .25)
{
   
    m_distance = randInt(2,10); //got to figure out how to do random directions
    m_hitpoints = 500;
    m_stun = 0;
}



bool BabyGrasshopper::isYouPebble()
{
    return false;
}

bool Pebble::isYouPebble()
{
    return true;
}


BabyGrasshopper::~BabyGrasshopper()
{
   
    
}


void BabyGrasshopper::doSomething()
{
    m_hitpoints--;
    if (m_stun!=0){
        m_stun--;
        m_ticks++;
        return;
    }
   
    
    if (m_distance==0)
    {
        m_direction = static_cast<GraphObject::Direction>(randInt(1,4));
        m_distance =randInt(2,10);
    }
    
    
    //Hereee we go
    if (m_StudentWorld->pebbleExists(getX(), getY(), m_direction))
    {
        m_direction = static_cast<GraphObject::Direction>(randInt(1,4));
        m_distance =randInt(2,10);
    }
    /*
 
    else
    {
       if (m_direction == up)
           moveTo(getX(), getY()+1);
        else if (m_direction == down)
            moveTo(getX(), getY()-1);
        else if (m_direction==left)
            moveTo(getX()-1, getY());
        else //(m_direction== right)
            moveTo(getX()+1, getY());
        m_distance--;
        
    }
   */
    m_stun = 2;
    m_ticks++;
        
    

}
/*bool BabyGrasshopper::attemptMove( const StudentWorld& a, Direction dir, int& r, int& c)
{
    int rnew = r;
    int cnew = c;
    switch (dir)
    {
        case none: return true;
        case up:  if (r <= 1)        return false; else rnew--; break;
        case right:   if (c >= VIEW_WIDTH) return false; else cnew++; break;
        case down:  if (r >= VIEW_HEIGHT) return false; else rnew++; break;
        case left:   if (c <= 1)        return false; else cnew--; break;
    }
    r = rnew;
    c = cnew;
    return true;
}
*/


Pebble::Pebble(int imageID, int startX, int startY, Direction dir, int depth, double size) : Actor(IID_ROCK, startX, startY, right, 1, .25)
{
}


void Pebble::doSomething()
{}

Pebble::~Pebble()
{}




//game constants file
