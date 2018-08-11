#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "StudentWorld.h"

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* world, int startX, int startY, Direction startDir, int imageID, int depth);
    
    virtual void doSomething() = 0;
    virtual bool isDead() const;
    virtual bool blocksMovement() const;
    
    StudentWorld* getWorld() const;
private:
    StudentWorld* m_world;
    int m_ticks;
    
};

class Pebble : public Actor
{
public:
    Pebble(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
    virtual bool blocksMovement() const;
};

class BabyGrasshopper : public Actor
{
public:
    BabyGrasshopper(StudentWorld* sw, int startX, int startY, Direction startDir, int imageID, int depth);
    virtual void doSomething();
    //virtual bool isDead() const;
    bool check();
    
private:
    int m_ticks;
    int m_stun;
    int m_distance;
};



#endif // ACTOR_H_
