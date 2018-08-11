//
//  testScoreList.cpp
//  HW 1.2
//
//  Created by Elizabeth Han on 1/24/17.
//  Copyright © 2017 Elizabeth Han. All rights reserved.
//

#include <iostream>
 #include <cassert>
#include "ScoreList.h"

 
 int main()
 {
 ScoreList s;
 s.add(50);
 assert (s.size() ==1);
 s.remove(50);
 assert (s.size()==0);
 s.add(20);
 s.add(50);
 s.add(100);
 assert (s.size() ==3);
 assert (s.minimum() ==20);
 assert (s.maximum()==100);
 s.remove(20);
 s.remove(50);
 s.remove(100);
 s.add(0);
 
 
 cout << s.maximum()<< endl;
 cout<< s.minimum() << endl;
 
 
 
 cout << "Passed all tests" << endl;


 }
