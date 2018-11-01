#include "Actor.h"
#include "GraphObject.h"
#include "StudentWorld.h"
#include <cmath>

static const double PI = 4 * atan(1.0);

///ACTOR IMPLEMENTATION

Actor:: Actor(StudentWorld* world, int startX, int startY, Direction startDir, int imageID, int depth) : GraphObject(imageID, startX, startY, right), m_world(world)
{}

bool Actor::isDead() const //I'm assuming everything will be alive (i.e, on the field), unless
{ return false;}            //we're talking about an energy holder, in which case, it has it's own thing

bool Actor::blocksMovement() const {return false;}

void Actor::getBitten(int amt)//only energy holders get bitten, poisoned, stuned, and whatever
{}
void Actor::getPoisoned(){}
void Actor::getStunned(){}
bool Actor::isEdible() const {return false;} //only food is edible
bool Actor::isPheromone() const {return false;} //only pheromones return true

bool Actor::isEnemy(int colony) const {return false;} //go back to this
bool Actor::isDangerous() const{return false;}//go back to this too;
void Actor::increaseStrength(){}
bool Actor::isMyHill(int colony) const{return false;}
StudentWorld* Actor::getWorld() const {return m_world;}


///PEBBLE IMPLEMENTATION

Pebble:: Pebble(StudentWorld* sw, int startX, int startY) : Actor(sw, startX, startY, right, IID_ROCK, 0)
{}
void Pebble::doSomething() {/*Pebbles don't do anything*/};
bool Pebble::blocksMovement() const {return true;}

//ENERGYHOLDER IMPLEMENTATION

EnergyHolder:: EnergyHolder(StudentWorld* sw, int startX, int startY, Direction startDir, int energy, int imageID, int depth) : Actor(sw, startX, startY, startDir, imageID, depth), m_energy(energy), m_food(0)
{}

int EnergyHolder:: getEnergy() const
{return m_energy;}

bool EnergyHolder::isDead() const
{
    if (m_energy<=0)
        return true;
    return false;
}

void EnergyHolder::updateEnergy(int amt)
{ m_energy = amt;}





void EnergyHolder::addFood(int amt)
{
 
   Actor* food = getWorld()->getEdibleAt(getX(), getY()); //gonnna need to check this;
    if (food!= nullptr)
    {
        int amount = food->getEnergy();
        food->updateEnergy(amount + amt);
    }
    else
    {
    Food* ptr =new Food(getWorld(), getX(), getY(), amt);
    getWorld()->addActor(ptr);
    }
    
    
}

int EnergyHolder::pickupFood(int amt)
{
   int x = getX(), y = getY();
    Actor* food = getWorld()->getEdibleAt(x, y);
    if (food!= nullptr)
    {
        int amount = food->getEnergy();
        int k = amount -amt;
        if (k<=0)
        {
            food->updateEnergy(0); 
            m_food += amount;
        }
        else
        {
            food->updateEnergy(k);
            m_food += amt;
        }
        return 1;
    
    }
    
    return 0;
    

}


int EnergyHolder::antPickupFood(int amt)
{
    int x = getX(), y = getY();
    Actor* food = getWorld()->getEdibleAt(x, y);
    if (food!= nullptr)
    {
        int max = 1800;
        int amount = food->getEnergy(); //this is how much food is in the energything
        int k = amount - amt; //this would be how much after we take it out;
        if (k<=0)
        {
            if (m_food+amount<= max)
            {
                m_food += amount;
                food->updateEnergy(0);
            }
            else
            {
                m_food = max;
                food->updateEnergy(m_food+amount-max);
            }
        }
        else //this assumes that there is enough food in there
        {
            if(m_food+amt<= max)
            {
                m_food += amt;
                food->updateEnergy(k);
            }
            else
            {
                m_food = max;
                food->updateEnergy(m_food+amt-max);
            }
        }
        return 1;
    }
    return 0;
}


int EnergyHolder::pickupAndEatFood(int amt)

{
    if (pickupFood(amt)==1)
    {
        int k = m_food - amt;
        if (k<=0)
        {
            m_energy += m_food;
            m_food =0;
        }
        else
        {
            m_food -= amt;
            m_energy+= amt;
        }

        return 1;
    }
    
    return 0;


}
int EnergyHolder::getFood()
{return m_food;}
void EnergyHolder::updateFood(int amt)
{m_food=amt;}

int EnergyHolder::eatFood(int amt)
{
    int k = m_food - amt;
    if (k<=0)
    {
        m_energy += m_food;
        m_food =0;
        return 1;
    }
    
    else
    {
        m_food -= amt;
        m_energy+= amt;
         return 0;
    }

   
}




bool EnergyHolder::becomesFoodUponDeath() const {return false;}


//FOOD IMPLEMENTATION

Food::Food(StudentWorld* sw, int startX, int startY, int energy): EnergyHolder(sw, startX, startY, right, energy, IID_FOOD, 2)
{}

void Food::doSomething(){} //food does nothing
bool Food::isEdible() const {return true;}



//ANTHILL IMPLEMENTATION

AntHill::AntHill(StudentWorld* sw, int startX, int startY, int colony, Compiler* program): EnergyHolder(sw, startX, startY, right, 8999, IID_ANT_HILL, 2), m_colony(colony), m_program(program)
{}
void AntHill::doSomething()
{
    
    int k = getEnergy();
    k--;
    if (k<=0)
    {
        updateEnergy(k);
        return;
    }
    pickupAndEatFood(10000);
    int j = getEnergy();
    int trueID =0;
    if (j>=2000)
    {
        j-=1500;
        updateEnergy(j);
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
        
        Ant* birth = new Ant(getWorld(), getX(), getY(), m_colony, m_program, trueID);
        getWorld()->addActor(birth);
        getWorld()->increaseScore(m_colony);
        return;
    }

}
bool AntHill::isMyHill(int colony) const
{
    if (colony==m_colony)
        return true;
    return false;
}


//PHEROMONE IMPLEMENTATION

Pheromone::Pheromone(StudentWorld* sw, int startX, int startY, int colony): EnergyHolder(sw, startX, startY, right, 256, which(), 2)
{}

void Pheromone::doSomething()
{
    int strength = getEnergy();
    strength--;
    updateEnergy(strength); //isDead function should activate, then.
}

bool Pheromone::isPheromone() const
{
    return true;
    
}
bool Pheromone::isMyPheromone(int colony) const
{
    if (m_colony == colony)
        return true;
    return false;
     
}



void Pheromone::increaseStrength()
{
    int strength = getEnergy();
    if (strength==768)
        return;
    strength += 256;
    if (strength>768)
        updateEnergy(768);
    else updateEnergy(strength);


}



//TRIGGERABLE ACTOR IMPLEMENTATION

TriggerableActor::TriggerableActor(StudentWorld* sw, int x, int y, int imageID): Actor(sw, x, y, right, imageID, 2)
{}

bool TriggerableActor::isDangerous() const
{return true;}

//WATERPOOL IMPLEMENTATION
WaterPool:: WaterPool(StudentWorld* sw, int x, int y): TriggerableActor(sw, x, y, IID_WATER_POOL)
{}

void WaterPool::doSomething()
{
    getWorld()->stunAllStunnableAt(getX(), getY());
}

//POISON IMPLEMENTATION

Poison:: Poison(StudentWorld* sw, int x, int y): TriggerableActor(sw, x, y, IID_POISON)
{}
void Poison::doSomething()
{
    getWorld()->poisonAllPoisonableAt(getX(), getY());
}

 
//INSECT IMPLEMENTATION

Insect:: Insect(StudentWorld* world, int startX, int startY, int energy, int imageID): EnergyHolder(world, startX, startY, static_cast<GraphObject::Direction>(randInt(1,4)), energy, imageID, 1)
{}

void Insect::doSomething()
{
   int amount = getEnergy(); //adjust hitpoints
    amount--;
    updateEnergy(amount);
    if (isDead())
    {   addFood(100);
        return;
    }
    
    
   
}

void Insect::getBitten(int amt)
{
   int amount = getEnergy();
    int k = amount-amt;
    if (k<=0)
    {
        updateEnergy(0);
        addFood(100);
        return;
    }
    else updateEnergy(k);
    
}
void Insect::getPoisoned(){
    int amount = getEnergy();
    int k = amount-150;
    if (k<=0)
    {
        updateEnergy(0);
        addFood(100);
        return;
    }
    else updateEnergy(k);
    
}
void Insect::getStunned()
{
    m_stun = 2;

}
int Insect::returnStun()
{return m_stun;}
void Insect::lessStun()
{m_stun--;}

bool Insect::isEnemy(int colony) {return true;} //figure this is good to assume 

bool Insect::becomesFoodUponDeath() const {return true;}

void Insect::getXYInFrontOfMe(int& x, int& y) const
{
    x = getX(), y = getY();
    switch(getDirection())
    {
        case up:
            y -=1;
            break;
        case down:
            y+=1;
            break;
        case left:
            x-=1;
            break;
        case right:
             x+=1;
            break;
        default:
            break;
    }
}

bool Insect::moveForwardIfPossible()
{
    Direction dir = getDirection();
    switch(dir)
    {
        case up:
            if (getWorld()->canMoveTo(getX(), getY()-1))
            {   moveTo(getX(), getY()-1);
                return true;
            }
            break;
        case down:
            if (getWorld()->canMoveTo(getX(), getY()+1))
            {   moveTo(getX(), getY()+1);
                return true;
            }
            break;
        case left:
            if (getWorld()->canMoveTo(getX()-1, getY()))
            {   moveTo(getX()-1, getY());
                return true;
            }
            break;
        case right:
            if (getWorld()->canMoveTo(getX()+1, getY()))
            {   moveTo(getX()+1, getY());
                return true;
            }
            break;
        default:
            return false;
            
    }
    return false;
    
}

void Insect::increaseSleepTicks(int amt)
{m_stun+=amt;}


//ANT IMPLEMENTATION


Ant::Ant(StudentWorld* sw, int startX, int startY, int colony, Compiler* program, int imageID): Insect(sw, startX, startY, 1500, imageID), m_bitten(0), m_block(0), m_random(0), m_instruction(0), m_program(program)
{}

void Ant::doSomething()
{
   Insect::doSomething();
    if(isDead())
        return;
    if (returnStun()!=0)
    {
        lessStun();
        return;
    }
   
    simpleInterpreter(m_program);
    
    
    
}

void Ant::getBitten(int amt)
{
    int amount = getEnergy();
    int k = amount-amt;
    if (k<=0)
    {
        updateEnergy(0);
        addFood(100);
        return;
    }
    else updateEnergy(k);
    m_bitten = 1;

}

bool Ant::isEnemy(int colony) const
{
    if (colony ==m_colony)
        return false;
    return true;

}
bool Ant::moveForwardIfPossible()
{
    return true;}

bool Ant::simpleInterpreter(Compiler* c)
{
    Compiler::Command cmd;
    int command = 0;
    if (!(c->getCommand(m_instruction, cmd)))
    {
        updateEnergy(0); //this should set to dead
        return false;
    }
    //while (command!=10)
    //{
    switch(cmd.opcode)
    {
    
        case Compiler::moveForward:
        {
            if(Insect::moveForwardIfPossible())
            {
                m_block=0;
                m_bitten =0;
    
            }
        
            else
               m_block=1;
            command++;
            m_instruction++;
            return true;
            break;
        }
        case Compiler:: eatFood:
        {
            eatFood(100);
            command++;
            m_instruction++;
            return true;
            break;
        }
        case Compiler::dropFood:
        {
            int k = getFood();
            updateFood(0);
            addFood(k);
            command++;
            m_instruction++;
            return true;
            break;
        }
        case Compiler::bite:
        {
            getWorld()->biteEnemyAt(this, m_colony, 15);
            command++;
            m_instruction++;
            return true;
            break;
            
        }
        case Compiler::pickupFood:
        {
            antPickupFood(400);
            command++;
            m_instruction++;
            return true;
            break;
        }
        case Compiler::emitPheromone:
        {
            Actor* pheromone = getWorld()->getPheromoneAt(getX(), getY(), m_colony);
            if (pheromone == nullptr)
            {
                pheromone = new Pheromone(getWorld(), getX(), getY(), m_colony);
                getWorld()->addActor(pheromone);
            }
            else
                pheromone->increaseStrength();
            command++;
            m_instruction++;
            return true;
            break;
        }
        case Compiler::faceRandomDirection:
        {
            setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
            command++;
            m_instruction++;
            return true;
            break;
            
        }
        case Compiler::rotateClockwise:
        {
            switch(getDirection())
            {
                case up:
                    setDirection(right);
                    break;
                case right:
                    setDirection(down);
                    break;
                case down:
                    setDirection(left);
                    break;
                case left:
                    setDirection(up);
                    break;
                default:
                    break;
            }
            command++;
            m_instruction++;
            return true;
            break;
        }
        case Compiler::rotateCounterClockwise:
        {
            switch(getDirection())
            {
                case up:
                    setDirection(left);
                    break;
                case right:
                    setDirection(up);
                    break;
                case down:
                    setDirection(right);
                    break;
                case left:
                    setDirection(down);
                    break;
                default:
                    break;
                
            }
            
            command++;
            return true;
            break;
        
        }
        case Compiler::generateRandomNumber:
        {
            if (stoi(cmd.operand1)==0)
                m_random=0;
            else
                m_random = randInt(0, stoi(cmd.operand1)-1);
            m_instruction++;
            
            break;
        }
        case Compiler::goto_command:
        {
            m_instruction = stoi(cmd.operand1);
            
            break;

        }
        case Compiler::if_command:
        {
            switch(stoi(cmd.operand1))
            {
                case static_cast<int>(Compiler::last_random_number_was_zero):
                {
                    if (m_random==0)
                        m_instruction = stoi(cmd.operand2);
                    break;
                }
                case static_cast<int>(Compiler::i_am_carrying_food):
                {
                    if (getFood()!=0)
                        m_instruction = stoi(cmd.operand2);
                    break;
                }
                case static_cast<int>(Compiler::i_am_hungry):
                {
                    if (getFood()<=25)
                        m_instruction = stoi(cmd.operand2);

                    break;
                }
                case static_cast<int>(Compiler::i_am_standing_with_an_enemy):
                {
                    if (getWorld()->isEnemyAt(getX(), getY(), m_colony))
                         m_instruction = stoi(cmd.operand2);
                    break;
                }
                case static_cast<int>(Compiler::i_am_standing_on_food):
                {
                    if (getWorld()->getEdibleAt(getX(), getY())!=nullptr)
                        m_instruction = stoi(cmd.operand2);
                    break;
                }
                case static_cast<int>(Compiler::i_am_standing_on_my_anthill):
                {
                    if (getWorld()->isAntHillAt(getX(), getY(), m_colony))
                        m_instruction = stoi(cmd.operand2);
                    break;
                }
                case static_cast<int>(Compiler::i_smell_pheromone_in_front_of_me):
                {
                    int x, y;
                    getXYInFrontOfMe(x, y);
                    if (getWorld()->isTherePheromone(x,y))
                        m_instruction = stoi(cmd.operand2);

                    break;
                }
                case static_cast<int>(Compiler::i_smell_danger_in_front_of_me):
                {
                    int x, y;
                    getXYInFrontOfMe(x, y);
                    if (getWorld()->isDangerAt(x,y,m_colony))
                        m_instruction = stoi(cmd.operand2);
                    break;
                }
                case static_cast<int>(Compiler::i_was_bit):
                {
                    if (m_bitten==1)
                        m_instruction = stoi(cmd.operand2);
                    break;

                }
                case static_cast<int>(Compiler::i_was_blocked_from_moving):
                {
                    if (m_block==1)
                        m_instruction = stoi(cmd.operand2);
                    break;
                    
                }
            }
            break;
        }
    }

  //  }
    
    return true;
    
}

//GRASSHOPPER IMPLEMENTATION

Grasshopper::Grasshopper(StudentWorld* sw, int startX, int startY, int energy, int imageID): Insect(sw, startX, startY, energy, imageID), m_distance(randInt(2,10)), m_direction(getDirection())
{}

int Grasshopper::distance(){return m_distance;}
void Grasshopper::setDistance(int dis){m_distance = dis;}

void Grasshopper::doSomething()
{
   
    /*int amount = getEnergy(); //adjust hitpoints
    amount--;
    updateEnergy(amount);*/
    Insect::doSomething();
    if(isDead())
        return;
    if (returnStun()!=0)
    {
        lessStun();
        return;
    }
   if (getEnergy()>=1600)
    {
        updateEnergy(0);
        addFood(100);
        AdultGrasshopper* reborn = new AdultGrasshopper(getWorld(), getX(), getY());
        getWorld()->addActor(reborn);
        return;
    
   }

    pickupAndEatFood(200);
    if(randInt(0,1)==1)
    {
        getStunned();
        return;
    }
    if (m_distance==0)
        
    {
        setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
        m_distance =randInt(2,10);
    }
    if (!moveForwardIfPossible())
    {
        setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
        m_distance =0;
    }
    else
        m_distance--;
    
    getStunned();
        

}

//BABYGRASSHOPPER IMPLEMENTATION

BabyGrasshopper::BabyGrasshopper(StudentWorld* sw, int startX, int startY): Grasshopper(sw, startX, startY, 500, IID_BABY_GRASSHOPPER)
{}

bool BabyGrasshopper::isEnemy(int colony) const
{return true;}


//ADULTGRASSHOPPER IMPLEMENTATION
AdultGrasshopper:: AdultGrasshopper(StudentWorld* sw, int startX, int startY): Grasshopper(sw, startX, startY, 1600, IID_ADULT_GRASSHOPPER)
{}

void AdultGrasshopper::doSomething()
{
    Insect::doSomething();
    if(isDead())
        return;
    if (returnStun()!=0)
    {
        lessStun();
        return;
    }
    if (randInt(0,2)==0)
    { getWorld()->biteEnemyAt(this, 4, 50);
        getStunned();
        return;
    }
    
     if(randInt(1,10)==10)
     {
         int t = randInt(0, 2*PI);
         int r = randInt(1, 10);
         int x = r*cos(t)+getX();
         int y = r*sin(t)+getY();
         if ((x <VIEW_WIDTH&& x> 0) && (y<VIEW_HEIGHT && y>0) && getWorld()->canMoveTo(x, y))
         {  moveTo(x, y);
            getStunned();
             return;
         }
         
     }
    
    
    pickupAndEatFood(200);
    if(randInt(0,1)==1)
    {
        getStunned();
        return;
    }
    if (distance()==0)
        
    {
        setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
        setDistance(randInt(2,10));
    }
    if (!moveForwardIfPossible())
    {
        setDirection(static_cast<GraphObject::Direction>(randInt(1, 4)));
        setDistance(0);
    }
    else
    {   int k = distance()-1;
       setDistance(k);
    }
    
    getStunned();
    
    
}




void AdultGrasshopper::getBitten(int amt)
{
    Insect::getBitten(amt);
    if (!isDead())
    {
        if(randInt(0,1)==1)
        {
            getWorld()->biteEnemyAt(this, 4, 50);
            return;
        }
    }
    
};
void AdultGrasshopper::getPoisoned()
{}




