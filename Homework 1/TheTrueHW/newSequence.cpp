

#ifndef NEW_SEQUENCE
#define NEW_SEQUENCE

#include "newSequence.h"
//
//  Sequence.h



///////SEQUENCE IMPLEMENTATION

Sequence::Sequence() //default constructor
{
    
    m_size = 0;
    m_arraysize =DEFAULT_MAX_ITEMS;
    m_array = new ItemType[m_arraysize];
}

Sequence::Sequence(int value) //not so default constructor
{
    
    m_size = 0;
    m_arraysize = value;
    m_array = new ItemType[m_arraysize];
}

Sequence::~Sequence() //destructor
{
    delete [] m_array;
    
};

Sequence::Sequence(const Sequence &other) //copy constructor
{
    m_size = other.m_size;
    m_arraysize = other.m_arraysize;
    m_array = new ItemType[m_arraysize];
}

Sequence& Sequence::operator =(const Sequence& rhs) //assignment

{
    if (this != &rhs)
    {
        Sequence temp(rhs);
        swap(temp);
    }
    return *this;
    
};



/*String (const String & other) //other is a term for t
 {
 m_len = other.m_len;
 m_text = new char {m_len+1}
 }
 */



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
    
    if (pos >= (size()+1)|| pos <0|| size() >= m_arraysize)
    /*would this just be if 200?
     Return true if 0 <= pos <= size() and the value could be // inserted. */
        return false;
    else
    {
        m_size++;
        int i = size()-1;
        if (pos == i)
        {
            m_array[pos] = value;
        }
        else
        {
            
            while (i != pos-1)
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
    
    if (m_array!= other.m_array)
    {
        ItemType* temp = other.m_array;
        other.m_array = m_array;
        m_array = temp;
        
        int tmp = other.m_size;
        other.m_size = m_size;
        m_size = tmp;
        
        int arraysize = other.m_arraysize;
        other.m_arraysize = m_arraysize;
        m_arraysize = arraysize;
    }
    
    
    
}




#endif /* NEW_SEQUENCE*/

