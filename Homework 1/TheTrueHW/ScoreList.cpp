
#ifndef SCORELIST
#define SCORELIST
#include "ScoreList.h"

ScoreList::ScoreList()
{
}

bool ScoreList:: add(unsigned long score)
{
    if (score <= 100 && m_sequence.insert(score))
        return true;
    return false;
}
bool ScoreList::remove(unsigned long score)
{
    if (m_sequence.erase(m_sequence.find(score)))
        return true;
    return false;
}


int ScoreList:: size() const
{
    return m_sequence.size();
}

unsigned long ScoreList::minimum() const // 0 does't work for some reason

{
    unsigned long value;
    int i = 0, p=-1;
    while (i <= 100)
    {
        if (m_sequence.find(i)!= -1)
        {
            p = m_sequence.find(i);
            break;
        }
        
        else
            i++;
    }
    if (p!= -1)
    {
        m_sequence.get(p, value);
        return value;
    }
    return NO_SCORE;
}


unsigned long ScoreList::maximum() const

{
    unsigned long value;
    int i = 100, p=-1;
    while (i >=0) // does >= 0 work?
    {
        if (m_sequence.find(i)!= -1)
        {
            p = m_sequence.find(i);
            break;
        }
        
        else
            i--;
    }
    
    if (p!= -1)
    {
        m_sequence.get(p, value);
        return value;
    }
    return NO_SCORE;
}


#endif /*SCORELIST */

