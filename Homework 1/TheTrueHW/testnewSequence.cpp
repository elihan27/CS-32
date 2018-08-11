
#include <iostream>
#include <cassert>
#include "newSequence.h"
using namespace std;

int main()
{
    
    
    Sequence s1;
    assert(s1.size()==0);
    s1.insert(0, 10);
    assert(s1.size()==1);
    assert(s1.find(10) == 0);
    s1.insert(0, 20);
    assert(s1.find(10) == 1);
    
    assert(s1.size() == 2);
    Sequence s2;
    s2.insert(0, 30);
    s1.swap(s2);
    assert(s1.size() == 1  &&  s1.find(30) == 0);
    assert(s2.size() == 2);
    assert(s2.find(20) == 0);
    assert(s2.find(10) == 1);
    
    cout << "Pass all tests. "<< endl;
    
}

