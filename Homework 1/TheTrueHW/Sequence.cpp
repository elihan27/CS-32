

#ifndef SEQUENCE
#define SEQUENCE
#include "Sequence.h"

///////SEQUENCE IMPLEMENTATION
Sequence::Sequence()
{
    m_size = 0;
}

bool Sequence::empty() const
{
    if (size()==0)
        return true;
    else
        return false;
    
}

int Sequence::size() const
{
    
    return m_size;
}

bool Sequence:: insert(int pos, const ItemType& value) //go back and fix
{
    if (pos >= (size()+1) || pos <0 || size() >= DEFAULT_MAX_ITEMS)
    /*would this just be if 200?
     Return true if 0 <= pos <= size() and the value could be // inserted. */
        return false;
    else
    {
        m_size++;
        int i = size()-1;
        if (pos == i)
            m_array[pos] = value;
        else
        { while (i != pos-1)
        {
            m_array[i+1] = m_array[i];
            i--;
        }
            m_array[pos] = value;
        }
        
    }
    
    return true;
}


int Sequence::insert(const ItemType& value)
{
    
    int i = 0, p= size();
    while (i!=size())
    {
        if (m_array[i] <= value)
        {
            p = i;
            break;
        }
        else
            i++;
        
    }
    
    
    if (insert(p, value) == true)
        return p;
    return -1;
    
    
}

bool Sequence::erase(int pos)
{
    if (pos<0|| pos > size()) //change this maybee.....
        return false;
    else
    {
        int i = pos;
        while (i != size()-1)
        {
            m_array[i] = m_array[i+1];
            i++;
        }
        m_size--; /// what to do with that last bit
    }
    return true;
}
int Sequence::remove(const ItemType& value)
{
    int i =0, removedItem = 0;
    while (i<size()) //is this static, or not?
    {
        if (m_array[i]== value)
            erase(i);
        removedItem++;
    }
    
    return removedItem;
}

bool Sequence:: get(int pos, ItemType& value) const
{
    if (pos<0 || pos >= size())
        return false;
    else
        value = m_array[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos<0 || pos >= size())
        return false;
    else
    {
        m_array[pos] = value;
        return true;
    }
}
int Sequence::find (const ItemType& value) const
{
    int p = -1, i= 0;
    while (i != size())
    {
        if (m_array[i] == value)
        {
            p = i;
            break;
        }
        else
            i++;
    }
    return p;
    
}

void Sequence::swap(Sequence& other)
{
   if (m_array != other.m_array)
    {
        Sequence backup;
        int i =0;
        while (i != size())
        {
            backup.m_array[i] = m_array[i];
            i++;
        }
        
        int j = 0;
        while (j != other.size())
        {
            m_array[j] = other.m_array[j];
            j++;
        }
        int k = 0;
        while (k != size())
        {
            other.m_array[k] = backup.m_array[k];
            k++;
        }
        
        
        int backSize;
        backSize = m_size;
        m_size = other.m_size;
        other.m_size = backSize;
    }

   /*Sequence *ptr1, *ptr2, *temp;
    ptr1 = this;
    ptr2 = &other;
    *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = *temp;
    */
    
    
}


#endif /* SEQUENCE */
