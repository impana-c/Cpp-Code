//
//  Set.h
//  Project2
//
//  Created by Impana on 1/25/23.
//

#ifndef Set_h
#define Set_h
#include <iostream>
#include <string>

//const int DEFAULT_MAX_ITEMS = 160;

using ItemType = std::string;

class Set
{
    public:
        Set();
        ~Set(); //destructor
        Set(const Set& old); //copy constructor
        Set &operator= (const Set &src); //assignment operator
        bool empty() const;
        int size() const;
        bool insert(const ItemType& value);
        bool erase(const ItemType& value);
        bool contains(const ItemType& value) const;
        bool get(int pos, ItemType& value) const;
        void swap(Set& other);
        void dump() const;
    private:
        struct Node{
            ItemType m_data;
            Node *m_next;
            Node *m_prev;
        };
        Node *head;
        Node *tail;
        int m_size;
        ItemType* m_set;

};

//Non-member functions
void unite(const Set& s1, const Set& s2, Set& result);
void butNot(const Set& s1, const Set& s2, Set& result);

#endif /* Set_h */
