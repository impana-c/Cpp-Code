//
//  Set.cpp
//  Homework1
//
//  Created by Impana on 1/22/23.
//

#include "Set.h"

Set::Set(){
    m_size = 0;
}

bool Set::empty() const{
    return (m_size==0);
}

int Set::size() const{
    return m_size;
}

bool Set::contains(const ItemType& value) const {
    for (int i=0; i<size(); i++){
        if (value == m_set[i]){
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
        value = m_set[i];
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
        if (value == m_set[i]){
            pos = i;
            break;
        }
    }
    for (int i=pos; i<size()-1; i++){
        m_set[i] = m_set[i+1];
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
    if(size()==0){
        m_set[0] = value;
        m_size = 1;
        return true;
    }
    if ((size() != DEFAULT_MAX_ITEMS) && (!contains(value))){
        int i=0;
        while ((value>m_set[i]) && (i<size())){
            i++;
        }
        if (i<=DEFAULT_MAX_ITEMS){
            for (int j=size(); j>i; j--){
                m_set[j] = m_set[j-1];
            }
            m_set[i] = value;
            m_size++;
            return true;
        }

    }
    return false;
}

void Set::swap(Set& other){
  // Exchange the contents of this set with the other one.
    int sz;
    if (other.size() > size()){
        sz = other.size();
    } else{
        sz = size();
    }
    for(int i=0; i<other.size(); i++){
        ItemType temp = m_set[i];
        m_set[i] = other.m_set[i];
        other.m_set[i] = temp;
    }
    int temp = m_size;
    m_size = other.m_size;
    other.m_size = temp;

}

void Set::dump() const{
    for (int i = 0; i < size(); i++){
        std::cerr << m_set[i] << std::endl;
    }
}
