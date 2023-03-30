//
//  testCardSet.cpp
//  Homework1
//
//  Created by Impana on 1/22/23.


#include "CardSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    CardSet cs;
    cs.add(12345);
    cs.add(67890);
    assert(cs.add(67890) == false);
    cs.add(123);
    cs.add(12345); //should not work
    cs.add(99000);
    cs.add(12345); //should not work
    cs.add(324679238758247);
    assert(cs.size() == 5);
    cs.print();

    cout << "Passed all tests" << endl;
}
