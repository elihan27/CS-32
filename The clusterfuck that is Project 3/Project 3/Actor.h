#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"



class Actor: public GraphObject
{
public:
    
    Actor(int imageID, int startX, int startY, Direction dir, StudentWorld* sp);
    virtual void doSomething()=0; //this is because every actor does something differently
    
    
    bool getIsPebble();
    void setIsPebble(bool isPebble = true);
    
private:
    StudentWorld* m_StudentWorld;
    bool m_isPebble;
    
    
};




class BabyGrasshopper: public Actor
{
public:
    BabyGrasshopper(int imageID, int startX, int startY, Direction dir, StudentWorld* sp);
    virtual void doSomething();
    int ticks();
    //virtual bool isYouPebble();
    
private:
    
    StudentWorld* m_StudentWorld;
    bool m_dead;
    int m_distance;
    int m_hitpoints;
    int m_stun;
    int m_ticks;
    bool m_isPebble;
    
};


class Pebble: public Actor
{
public:
    Pebble(int imageID, int startX, int startY, StudentWorld* sp);
    virtual void doSomething();
   
   // virtual bool isYouPebble();
    
private:
    
    bool m_isPebble;
    
};


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp



#endif // ACTOR_H_
