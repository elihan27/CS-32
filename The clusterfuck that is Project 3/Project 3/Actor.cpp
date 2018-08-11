#include "Actor.h"
#include "GraphObject.h"
#include "StudentWorld.h"


//Actor implementation

Actor:: Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* sp) : GraphObject(imageID, startX, startY, right), m_StudentWorld(sp), m_isPebble(false)
{
    
}

bool Actor::getIsPebble()
{
    
    return m_isPebble;
}

void Actor::setIsPebble(bool isPebble)
{
    m_isPebble = isPebble;
}

void Actor::doSomething()
{}

//Pebble implementation
Pebble::Pebble(int imageID, int startX, int startY, StudentWorld* sp) : Actor(IID_ROCK, startX, startY, right, sp)
{
    setIsPebble();
}


void Pebble::doSomething()
{//pebbles do literally nothing
}



//BabyGrasshopper implementation

BabyGrasshopper::BabyGrasshopper(int imageID, int startX, int startY, Direction dir, StudentWorld* sp):Actor(IID_BABY_GRASSHOPPER, startX, startY, static_cast<GraphObject::Direction>(randInt(1,4)), sp)
{
    
    m_dead = false;
    m_hitpoints = 500;
    m_stun = 0;
    m_ticks =0;
    m_distance = randInt(2,10); //got to figure out how to do random directions
    
}


int BabyGrasshopper::ticks()
{
    return m_ticks;
}







void BabyGrasshopper::doSomething()
{
    
    m_hitpoints--;
    if (m_stun!=0)
    {
        m_stun--;
        m_ticks++;
        return;
    }
    
    
    if (m_distance==0)
    {
        setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
        m_distance =randInt(2,10);
    }
    
    
    /* if (
     (getDirection()==up && ( getY()>= VIEW_HEIGHT || m_StudentWorld->pebbleExists(getX(), getY()+1))
     )||
     (getDirection()==down && (getY()<=0 || m_StudentWorld->pebbleExists(getX(), getY()-1)))||
     (getDirection()==left && (getX()<=0 || m_StudentWorld->pebbleExists(getX()-1, getY())))||
     (getDirection()== right && (getX()>=VIEW_WIDTH || m_StudentWorld->pebbleExists(getX()+1, getY())))
     )
     {
     setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
     m_distance =randInt(2,10);
     }
     */
    if (
        (getDirection()==up && getY()>= VIEW_HEIGHT)||(getDirection()==down && getY()<=0) ||(getDirection()==left && getX()<=0)||(getDirection()== right && getX()>=VIEW_WIDTH))
    {
        setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
        m_distance =randInt(2,10);
    }
    
    
    
    else{
        
        
        if (getDirection() == up)
            moveTo(getX(), getY()+1);
        else if (getDirection() == down)
            moveTo(getX(), getY()-1);
        else if (getDirection()==left)
            moveTo(getX()-1, getY());
        else if (getDirection()== right)
            moveTo(getX()+1, getY());
        m_distance--;
        
    }
    
    
    m_stun = 2;
    m_ticks++;
    
    
    
    
}


/*   //Hereee we go
 if (m_StudentWorld->pebbleExists(getX(), getY())) //THERE IS SOME SORT OF PROBLEM HERE
 {
 setDirection(static_cast<GraphObject::Direction>(randInt(1,4)));
 m_distance =randInt(2,10);
 }
 */
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







//game constants file

