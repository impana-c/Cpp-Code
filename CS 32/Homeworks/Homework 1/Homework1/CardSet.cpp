//
//  CardSet.cpp
//  Homework1
//
//  Created by Impana on 1/22/23.
//

#include "CardSet.h"
#include <iostream>
using namespace std;
using ItemType = unsigned long;


CardSet::CardSet(){
    //no need to add anything here because Set's default constructor already initializes size to 0
}

bool CardSet::add(ItemType cardNumber){
    return (m_cardSet.insert(cardNumber));
}

int CardSet::size() const{
    return m_cardSet.size();
}

void CardSet::print() const{
    for (int i=0; i<m_cardSet.size(); i++){
        ItemType temp;
        m_cardSet.get(i,temp);
        cout << temp << endl;
    }
}


