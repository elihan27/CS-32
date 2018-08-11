#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "Compiler.h"

class StudentWorld;

class Actor : public GraphObject
{
public:
    Actor(StudentWorld* world, int startX, int startY, Direction startDir, int imageID, int depth);
    
    virtual void doSomething() = 0;
    virtual int updateEnergy(int amt) const {return 0;}
    virtual int getEnergy() const {return 0;}
    virtual bool isDead() const;
    virtual bool blocksMovement() const;
    virtual void getBitten(int amt);
    virtual void getPoisoned();
    virtual void getStunned();
    virtual bool isEdible() const;
    virtual bool isPheromone() const;
    virtual bool isMyPheromone(int colony) const {return false;}
    virtual bool isEnemy(int colony) const;
    virtual bool isDangerous() const;
    virtual void increaseStrength();
    
    // Is this actor the anthill of the indicated colony?
    virtual bool isMyHill(int colony) const;
    
    // Get this actor's world.
    StudentWorld* getWorld() const;
private:
    StudentWorld* m_world;
    bool m_isPheromone;
    bool m_isEnemy;
    bool m_isDangerous;
    bool m_isAnthill;
    int m_ticks;
    
    
};

class Pebble : public Actor
{
public:
    Pebble(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
    virtual bool blocksMovement() const;
};

class EnergyHolder : public Actor
{
public:
    EnergyHolder(StudentWorld* sw, int startX, int startY, Direction startDir, int energy, int imageID, int depth);
    
    virtual bool isDead() const;
    
    // Get this actor's amount of energy (for a Pheromone, same as strength).
    virtual int getEnergy() const;
    
    int getFood();
    void updateFood(int amt);
    
    // Adjust this actor's amount of energy upward or downward.
    virtual void updateEnergy(int amt);
    
    // Add an amount of food to this actor's location.
    void addFood(int amt);
    
    // Have this actor pick up an amount of food.
    int pickupFood(int amt);
    int antPickupFood(int amt);
    // Have this actor pick up an amount of food and eat it.
    int pickupAndEatFood(int amt);
    
    int eatFood(int amt);
    
    // Does this actor become food when it dies?
    virtual bool becomesFoodUponDeath() const;
private:
    int m_food;
    int m_energy;
    int m_isDead;
};

class Food : public EnergyHolder
{
public:
    Food(StudentWorld* sw, int startX, int startY, int energy);
    virtual void doSomething();
    virtual bool isEdible() const;
    
};

class AntHill : public EnergyHolder
{
public:
    AntHill(StudentWorld* sw, int startX, int startY, int colony, Compiler* program);
    virtual void doSomething();
    virtual bool isMyHill(int colony) const;
    
private:
    Compiler* m_program;
    int m_colony;
};

class Pheromone : public EnergyHolder
{
public:
    Pheromone(StudentWorld* sw, int startX, int startY, int colony);
    virtual void doSomething();
    virtual bool isPheromone() const;
    virtual bool isMyPheromone(int colony) const;
    
    
    // Increase the strength (i.e., energy) of this pheromone.
    virtual void increaseStrength();
private:
    int m_colony;
    int which()
    {
        int trueID =0;
        switch(m_colony)
        {
                
            case 0:
                trueID =IID_ANT_TYPE0;
                break;
            case 1:
                trueID =IID_ANT_TYPE1;
                break;
            case 2:
                trueID =IID_ANT_TYPE2;
                break;
            case 3:
                trueID =IID_ANT_TYPE3;
                break;
                
        }
        return trueID;
    }
};

class TriggerableActor : public Actor
{
public:
    TriggerableActor(StudentWorld* sw, int x, int y, int imageID);
    virtual bool isDangerous() const;
};

class WaterPool : public TriggerableActor
{
public:
    WaterPool(StudentWorld* sw, int x, int y);
    virtual void doSomething();
};

class Poison : public TriggerableActor
{
public:
    Poison(StudentWorld* sw, int x, int y);
    virtual void doSomething();
};


class Insect : public EnergyHolder
{
public:
    Insect(StudentWorld* world, int startX, int startY, int energy, int imageID);
    virtual void doSomething();
    virtual void getBitten(int amt);
    virtual void getPoisoned();
    virtual void getStunned();
    int returnStun();
    void lessStun();
    virtual bool isEnemy(int colony);
    virtual bool becomesFoodUponDeath() const;
    
    // Set x,y to the coordinates of the spot one step in front of this insect.
    void getXYInFrontOfMe(int& x, int& y) const;
    
    // Move this insect one step forward if possible, and return true;
    // otherwise, return false without moving.
    virtual bool moveForwardIfPossible();
    
    // Increase the number of ticks this insect will sleep by the indicated amount.
    void increaseSleepTicks(int amt);
    
private:
    int m_ticks;
    int m_stun;
    int m_food;
    
};

class Ant : public Insect
{
public:
    Ant(StudentWorld* sw, int startX, int startY, int colony, Compiler* program, int imageID);
    virtual void doSomething();
    virtual void getBitten(int amt);
    virtual bool isEnemy(int colony) const;
    virtual bool moveForwardIfPossible();
    bool simpleInterpreter(Compiler* c);
private:
    int m_colony;
    int m_bitten;
    int m_block;
    int m_random;
    int m_instruction;
    Compiler* m_program;
};


class Grasshopper : public Insect
{
public:
    Grasshopper(StudentWorld* sw, int startX, int startY, int energy, int imageID);
    virtual void doSomething();
    int distance();
    void setDistance(int dis);
private:
    int m_distance;
    Direction m_direction;
};

class BabyGrasshopper : public Grasshopper
{
public:
    BabyGrasshopper(StudentWorld* sw, int startX, int startY);
    virtual bool isEnemy(int colony) const;
};

class AdultGrasshopper : public Grasshopper
{
public:
    AdultGrasshopper(StudentWorld* sw, int startX, int startY);
    virtual void doSomething();
    virtual void getBitten(int amt);
    virtual void getPoisoned();
};

#endif // ACTOR_H_
