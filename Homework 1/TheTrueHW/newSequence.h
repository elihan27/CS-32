//
//  newSequence.h
//  HW 1.2
//
//  Created by Elizabeth Han on 1/24/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//

#ifndef newSequence_h
#define newSequence_h




#include <iostream>

using namespace std;

typedef unsigned long ItemType;

const int DEFAULT_MAX_ITEMS = 200;

class Sequence
{
    
public:
    Sequence(); // Default constructor
    Sequence (int size); //constructor
    ~Sequence(); /// destructor
    Sequence (const Sequence &other); //S // copy constructor
    Sequence& operator=(const Sequence& rhs);//assignment operator
    bool empty() const;
    int size() const;
    bool insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
private:
    ItemType* m_array;
    int m_size;
    int m_arraysize;
    
    
};


#endif /* newSequence_h */

