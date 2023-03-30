//
//  newSet.cpp
//  Homework1
//
//  Created by Impana on 1/22/23.
//

#include "newSet.h"

Set::Set(){
    m_size = 0;
    m_max = DEFAULT_MAX_ITEMS;
    m_newSet = new ItemType[m_max];
}

Set::Set(int max){
    m_size = 0;
    m_max = max;
    m_newSet = new ItemType[m_max];
}

bool Set::empty() const{
    return (m_size==0);
}

int Set::size() const{
    return m_size;
}

Set::Set(const Set& old){
    m_max = old.m_max;
    m_size = old.m_size;
    m_newSet =  new ItemType[m_max];
    for (int i=0; i<size(); i++){
        m_newSet[i] = old.m_newSet[i];
    }
}

Set &Set::operator= (const Set &src){
    m_max = src.m_max;
    m_size = src.m_size;
    return *this;
}

bool Set::contains(const ItemType& value) const {
    for (int i=0; i<size(); i++){
        if (value == m_newSet[i]){
            return true;
        }
    }
    return false;
}

bool Set::get(int i, ItemType& value) const{
  // If 0 <= i < size(), copy into value the item in the set that is
  // strictly greater than exactly i items in the set and return true.
  // Otherwise, leave value unchanged and return false.
    if ((i>=0) && (i<size())){
        value = m_newSet[i];
        return true;
    }
    return false;
}

bool Set::erase(const ItemType& value){
      // Remove the value from the set if it is present.  Return true if the
      // value was removed; otherwise, leave the set unchanged and
      // return false.
    if (!contains(value)){
        return false;
    }

    int pos = -1;
    for (int i=0; i<size(); i++){
        if (value == m_newSet[i]){
            pos = i;
            break;
        }
    }
    for (int i=pos; i<size()-1; i++){
        m_newSet[i] = m_newSet[i+1];
    }
    m_size--;
    return true;
}

bool Set::insert(const ItemType& value){
  // Insert value into the set if it is not already present.  Return
  // true if the value is actually inserted.  Leave the set unchanged
  // and return false if value is not inserted (perhaps because it
  // was already in the set or because the set has a fixed capacity and
  // is full).=
    if(m_size >= m_max){
        return false;
    }

    if(size()==0){
        m_newSet[0] = value;
        m_size = 1;
        return true;
    }

    if ((size() != DEFAULT_MAX_ITEMS) && (!contains(value))){
        int i=0;
        while ((value>m_newSet[i]) && (i<size())){
            i++;
        }
        if (i<=DEFAULT_MAX_ITEMS){
            for (int j=size(); j>i; j--){
                m_newSet[j] = m_newSet[j-1];
            }
            m_newSet[i] = value;
            m_size++;
            return true;
        }

    }
    return false;
}

void Set::swap(Set& other){
  // Exchange the contents of this set with the other one.
    int temp_size = other.m_size;
    other.m_size = m_size;
    m_size = temp_size;

    int temp_max = other.m_max;
    other.m_max = m_max;
    m_max = temp_max;

    ItemType* tempSet = other.m_newSet;
    other.m_newSet = m_newSet;
    m_newSet = tempSet;
}

void Set::dump() const{
    for (int i = 0; i < size(); i++){
        std::cerr << m_newSet[i] << std::endl;
    }
}

Set:: ~Set(){
    delete [] m_newSet;
}
