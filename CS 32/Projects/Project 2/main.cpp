//
//  main.cpp
//  Project2
//
//  Created by Impana on 1/25/23.
//

#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

int main() {
        // default constructor
    Set ss;
        // For an empty set:
    assert(ss.size() == 0);        // test size
    assert(ss.empty());            // test empty
    assert(!ss.erase("e"));     // nothing to remove
    
    ss.insert("to be erased");
    ss.erase("to be erased"); //testing erase at first element
    assert(ss.size() == 0); //checking if erase resulted in the empty set
    ss.insert("e"); //testing insert
    ss.insert("a");
    ss.insert("c");
    ss.insert("d");
    ss.insert("to be erased");
    ss.erase("to be erased"); //testing erase in the middle
    assert(ss.size() == 4);
    ss.insert("a"); //trying to insert duplicates
    ss.insert("b");
    ss.insert("d"); //trying to insert duplicate at end
    ss.insert("to be erased");
    ss.erase("to be erased"); //testing erase at last element
    assert(ss.size() == 5);  // duplicate "a" and "d" were not added
    
    assert(ss.contains("a")); //test contains
    assert(!ss.contains("x")); //test not containing
    assert(!ss.contains("")); //test empty string
    string x;
    ss.get(0, x); //test get at first element
    assert(x == "a");  // "a" is greater than exactly 0 items in ss
    ss.get(4, x); //test get at last element
    assert(x == "e");  // "e" is greater than exactly 4 items in ss
    ss.get(2, x); //test get at middle lement
    assert(x == "c");  // "c" is greater than exactly 2 items in ss
    
    Set ss1;
    ss1.insert("x");
    Set ss2;
    ss2.insert("y");
    ss2.insert("z");
    ss1.swap(ss2); //test swap
    assert(ss1.size() == 2  &&  ss1.contains("y")  &&  ss1.contains("z")  &&
               ss2.size() == 1  &&  ss2.contains("x"));
    
    Set ss3 = ss1; //test copy constructor
    Set ss4;
    ss4 = ss2; //test assignment operator
    
    Set ss5; //testing strings with multiple characters
    ss5.insert("ccc");
    ss5.insert("aaa");
    ss5.insert("bbb");
    ItemType y = "xxx";
    assert(!ss5.get(3, y)  &&  y == "xxx");  // x is unchanged
    assert(ss5.get(1, y)  &&  y == "bbb");   // "bbb" is greater than
                                            // exactly 1 item
    
    Set ss6;
    ss6.insert("x");
    ss6.insert("y");
    ss6.insert("z");
    ss6.insert("a"); //add "a": common element between ss and ss6
    Set result;
    unite(ss,ss6,result); //test unite: should print out abcdexyza
    Set result2;
    butNot(ss,ss6,result2); //test butNot: should print out bcde
    
    Set ss8; Set ss9;
    ss8.insert(""); //checking empty string
    ss9.insert("a");
    ss8.swap(ss9); //testing swap on empty string
    Set ss10 = ss9; //testing copy constructor on empty string
    Set ss11;
    ss11 = ss9; //testing assignment operator on empty string
    
    //Basic Testing on Unsigned Longs
//    Set uls;
//    assert(uls.insert(20));
//    assert(uls.insert(10));
//    assert(uls.size() == 2);
//    assert(uls.contains(10));
//    ItemType x = 30;
//    assert(uls.get(0, x)  &&  x == 10);
//    assert(uls.get(1, x)  &&  x == 20);
    
    cerr << "Passed all tests" << endl;

}
