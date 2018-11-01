#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"
#include "Compiler.h"


class Actor: public GraphObject
{
public:
   
    Actor(int imageID, int startX, int startY, Direction dir = right, int depth=0, double size =.25);
    virtual void doSomething(); //this is because every actor does something differently
    virtual bool isYouPebble()=0;
    
    
private:
   StudentWorld* m_StudentWorld;
    
};




class BabyGrasshopper: public Actor
{
public:
    BabyGrasshopper(int imageID, int startX, int startY, Direction dir, int depth = 1, double size = 0.25);
    virtual void doSomething();
    int ticks();
    //bool attemptMove(const StudentWorld& a, Direction dir, int& r, int& c);
    virtual bool isYouPebble();

private:
   
    StudentWorld* m_StudentWorld;
    bool m_dead;
    int m_distance;
    int m_hitpoints;
    int m_stun;
    int m_ticks;
    
    };


class Pebble: public Actor
{
public:
    Pebble(int imageID, int startX, int startY, Direction dir = right, int depth = 1, double size = .25);
    virtual void doSomething();
    virtual bool isYouPebble();

private:
    
    

};


// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
 


#endif // ACTOR_H_
