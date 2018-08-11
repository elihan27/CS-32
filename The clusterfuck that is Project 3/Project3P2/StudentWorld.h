#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
#include "Field.h"


class Actor;
class Compiler;
class AntHill;

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir)
    : GameWorld(assetDir), m_colony0(0), m_colony1(1), m_colony2(2), m_colony3(3)
    {}
    
    //StudentWorld(std::string assetDir);
    virtual ~StudentWorld();
    
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    
    // Can an insect move to x,y?
    bool canMoveTo(int x, int y) const;
    
    // Add an actor to the world
    void addActor(Actor* a);
    
    
    // If an item that can be picked up to be eaten is at x,y, return a
    // pointer to it; otherwise, return a null pointer.  (Edible items are
    // only ever going be food.)
    Actor* getEdibleAt(int x, int y) const;
    
    bool isTherePheromone(int x, int y) const;
    // If a pheromone of the indicated colony is at x,y, return a pointer
    // to it; otherwise, return a null pointer.
    Actor* getPheromoneAt(int x, int y, int colony) const;
    
    // Is an enemy of an ant of the indicated colony at x,y?
    bool isEnemyAt(int x, int y, int colony) const;
    
    // Is something dangerous to an ant of the indicated colony at x,y?
    bool isDangerAt(int x, int y, int colony) const;
    
    // Is the anthill of the indicated colony at x,y?
    bool isAntHillAt(int x, int y, int colony) const;
    
    // Bite an enemy of an ant of the indicated colony at me's location
    // (other than me; insects don't bite themselves).  Return true if an
    // enemy was bitten.
    bool biteEnemyAt(Actor* me, int colony, int biteDamage);
    
    // Poison all poisonable actors at x,y.
    bool poisonAllPoisonableAt(int x, int y);
    
    // Stun all stunnable actors at x,y.
    bool stunAllStunnableAt(int x, int y);
    
    // Record another ant birth for the indicated colony.
    void increaseScore(int colony);
    
    
    
private:
    int m_ticks;
    Field m_field;
    std::vector<Actor*> m_actors[VIEW_WIDTH][VIEW_HEIGHT];
    std::vector<std::string> compilerProgram;
    int m_colony0;
    int m_colony1;
    int m_colony2;
    int m_colony3;
    
    
    
};

#endif // STUDENTWORLD_H_
