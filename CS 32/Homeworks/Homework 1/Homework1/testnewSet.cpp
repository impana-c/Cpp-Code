//
//  testnewSet.cpp
//  Homework1
//
//  Created by Impana on 1/22/23.
//
#include "newSet.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(){
//    Set ss;
//    ss.insert("lavash");
//    ss.insert("roti");
//    ss.insert("chapati");
//    ss.insert("injera");
//    ss.insert("roti");
//    ss.insert("matzo");
//    ss.insert("injera");
//    assert(ss.size() == 5);  // duplicate "roti" and "injera" were not added
//    string x;
//    ss.get(0, x);
//    assert(x == "chapati");  // "chapati" is greater than exactly 0 items in ss
//    ss.get(4, x);
//    assert(x == "roti");  // "roti" is greater than exactly 4 items in ss
//    ss.get(2, x);
//    assert(x == "lavash");  // "lavash" is greater than exactly 2 items in ss
//
//    Set ss1;
//    ss1.insert("laobing");
//    Set ss2;
//    ss2.insert("matzo");
//    ss2.insert("pita");
//    ss1.swap(ss2);
//    assert(ss1.size() == 2  &&  ss1.contains("matzo")  &&  ss1.contains("pita")  &&
//           ss2.size() == 1  &&  ss2.contains("laobing"));
//
//    Set ss3;
//    ss3.insert("dosa");
//    assert(!ss.contains(""));
//    ss3.insert("tortilla");
//    ss3.insert("");
//    ss3.insert("focaccia");
//    assert(ss3.contains(""));
//    ss3.erase("dosa");
//    assert(ss3.size() == 3  &&  ss3.contains("focaccia")  &&  ss3.contains("tortilla")  &&
//                ss3.contains(""));
//    string v;
//    assert(ss3.get(1, v)  &&  v == "focaccia");
//    assert(ss3.get(0, v)  &&  v == "");
//
//    Set s5;
//    assert(s5.empty());
//    ItemType x1 = "arepa";
//    assert( !s5.get(42, x1)  &&  x1 == "arepa"); // x unchanged by get failure
//    s5.insert("chapati");
//    assert(s5.size() == 1);
//    assert(s5.get(0, x1)  &&  x1 == "chapati");
//
//    Set a(1000);   // a can hold at most 1000 distinct items
//    Set b(5);      // b can hold at most 5 distinct items
//    Set c;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
//    ItemType list[6] = {"ab", "bc", "cd", "de", "ef", "fg"};
//      // No failures inserting 5 distinct items into b
//    for (int k = 0; k < 5; k++)
//        assert(b.insert(list[k]));
//      // Failure if we try to insert a sixth distinct item into b
//    assert(!b.insert(list[5]));
//      // When two Sets' contents are swapped, their capacities are swapped
//      // as well:
//    a.swap(b);
//    assert(!a.insert(list[5])  &&  b.insert(list[5]));
//    cout << "Passed all tests" << endl;
    
//    //Use with unsigned long
//    Set s;
//    assert(s.empty());
//    ItemType x = 9876543;
//    assert( !s.get(42, x)  &&  x == 9876543); // x unchanged by get failure
//    s.insert(123456789);
//    assert(s.size() == 1);
//    assert(s.get(0, x)  &&  x == 123456789);
//    Set a1(1000);   // a can hold at most 1000 distinct items
//    Set b1(5);      // b can hold at most 5 distinct items
//    Set c1;         // c can hold at most DEFAULT_MAX_ITEMS distinct items
//    ItemType list1[6] = {1000, 2000, 30000, 4000, 4578493, 34732078};
//      // No failures inserting 5 distinct items into b
//    for (int k = 0; k < 5; k++)
//        assert(b1.insert(list1[k]));
//      // Failure if we try to insert a sixth distinct item into b
//    assert(!b1.insert(list1[5]));
//      // When two Sets' contents are swapped, their capacities are swapped
//      // as well:
//    a1.swap(b1);
//    assert(!a1.insert(list1[5])  &&  b1.insert(list1[5]));
//    cout << "Passed all tests" << endl;
}
