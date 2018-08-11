#include "Actor.h"
#include "GraphObject.h"
#include "StudentWorld.h"


Actor:: Actor(StudentWorld* world, int startX, int startY, Direction startDir, int imageID, int depth) : GraphObject(imageID, startX, startY, right), m_world(world)
{}

bool Actor::isDead() const //I'm assuming everything will be alive (i.e, on the field), unless
{ return false;}            //we're talking about an energy holder, in which case, it has it's own thing

bool Actor::blocksMovement() const {return false;}
StudentWorld* Actor::getWorld() const {return m_world;}


Pebble:: Pebble(StudentWorld* sw, int startX, int startY) : Actor(sw, startX, startY, right, IID_ROCK, 0)
{}
void Pebble::doSomething() {/*Pebbles don't do anything*/};
bool Pebble::blocksMovement() const {return true;}


BabyGrasshopper::BabyGrasshopper(StudentWorld* sw, int startX, int startY, Direction startDir, int imageID, int depth): Actor (sw, startX, startY, static_cast<GraphObject::Direction>(randInt(1,4)), IID_BABY_GRASSHOPPER, 2)
{   m_ticks =0;
    m_stun = 0;
    m_distance = randInt(2,10); //got to figure out how to do random directions
    
}

bool BabyGrasshopper:: check()
{
    if (getDirection()==up && getWorld()->pebbleExists(getX(), getY()-1))
        return true;
    else if (getDirection()==down && getWorld()->pebbleExists(getX(), getY()+1))
        return true;
    else if (getDirection()==left && getWorld()->pebbleExists(getX()-1, getY()))
        return true;
    else if (getDirection()==right && getWorld()->pebbleExists(getX()+1, getY()))
        return true;
    
    return false;
    
    
}

void BabyGrasshopper::doSomething()
{
    
    if (m_stun!=0)
    {
        m_stun--;
        m_ticks++;
        return;
    }
    
    
    if (m_distance==0|| check())
        
    {
        setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
        m_distance =randInt(2,10);
    }
    
    
    
    if (getDirection() == up)
        moveTo(getX(), getY()-1);
    else if (getDirection() == down)
        moveTo(getX(), getY()+1);
    else if (getDirection()==left)
        moveTo(getX()-1, getY());
    else if (getDirection()== right)
        moveTo(getX()+1, getY());
    m_distance--;
    
    
}

