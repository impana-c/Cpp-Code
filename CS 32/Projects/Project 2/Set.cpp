//
//  Set.cpp
//  Project2
//
//  Created by Impana on 1/25/23.
//

#include "Set.h"

Set::Set(){ //initialize an empty set
    m_size = 0;
    head = nullptr;
    tail = nullptr;
    
}

bool Set::empty() const{
    return (m_size == 0); //checking whether size is 0
}

int Set::size() const{
    return m_size;
}

Set:: ~Set(){
    if (head==nullptr) //checking if set is already empty
        return; //do nothing
    Node *p = head;
    while (p!=nullptr){ //traverse through set
        Node *n = p->m_next;
        delete p; //delete each node
        p = n; //move to next node
    }
}
Set::Set(const Set& old){ //copy constructor to create a new object
    if (old.head == nullptr){ //if old set is empty
        head = nullptr; //leave head as empty
        return;
    }

    head = new Node;  //initializing the first element
    Node* old_p; //indexing node for old set
    old_p = old.head;
    head->m_data = old_p->m_data;
    head->m_next = nullptr;
    head->m_prev = nullptr;

    Node* p;  //initializing a new ptr
    p = head;
    old_p = old_p->m_next;  //moving to second element of old
    
    while (old_p != nullptr){
        Node* new_p = new Node;  //creating a new node object
        new_p->m_data = old_p->m_data;
        new_p->m_next = nullptr;
        new_p->m_prev = p; //p is currently pointing to the last added item

        p->m_next = new_p; //linking new node object to copy constructor list
        old_p = old_p->m_next; //incrementing old_p
        p = p->m_next; //incrementing p
    }
    tail = p; //setting the tail to the last element
    m_size = old.m_size;
}


Set &Set::operator= (const Set &rhs){ //assignment operator to copy into already initialized values
    if (this != &rhs){ //checks if the new set is not the same as the current set
        Set temp(rhs); //create new copy of rhs using copy constructor
        swap(temp); //swap the elements of the two sets
    }
    return *this;
}

bool Set::contains(const ItemType& value) const {
    Node *h = head;
    Node *t = tail;
    while ((h != nullptr) && (t != nullptr)){ //traverse the set from both sides
        if ((value == h->m_data) || (value == t->m_data)){
            return true;
        }
        h = h->m_next; //move to next element
        t = t->m_prev; //move to previous element
    }
    return false;
}

bool Set::get(int pos, ItemType& value) const{
    if ((pos>=0) && (pos<size())) {
        int i = 0;
        Node *p = head;
        while ((p != nullptr) && (i!=pos)){ //wait until counter reaches position
            i++;
            p = p->m_next;
        } //p points at node with value needed
        value = p->m_data;
        return true;
    }
    return false;    
}

bool Set::erase(const ItemType& value){
    if (!contains(value)) //check if the value to be deleted is even in the list in the first place
        return false;
    if (head==nullptr) //check if the list is empty
        return false;
    
    if (head->m_data == value){ //Case 1: deleting the first element
        Node *killMe = head; //create new node to be deleted later
        head = killMe->m_next;
        delete killMe;
        m_size--;
        return true;
    }
        
    Node *p = head; //Case 2: deleting a middle/end element
    while(p != nullptr){
        if((p->m_next != nullptr) && (p->m_next->m_data == value))
            break; //p points to node just before value
        p = p->m_next;
    }
    if (p!=nullptr){
        Node *killMe = p->m_next; //killMe points to node containing value
        p->m_next = killMe->m_next;
        if (p->m_next != nullptr){ //if not at last element
            p->m_next->m_prev = p; //update p's m_next
        } else{
            tail = tail->m_prev; //if at last element, tail is now element before tail
        }
        delete killMe;
    }
    m_size--;
    return true;
}

bool Set::insert(const ItemType& value) {
    if(size()==0){ //check if adding the first element to an empty list
        Node *new_p = new Node; //create new node, initialize with values and correct prev and next pointers
        new_p->m_data = value;
        new_p->m_prev = nullptr;
        new_p->m_next = nullptr;
        head = new_p;
        tail = new_p;
        m_size = 1; //update head, tail, and set size
        return true;
    }
    if (!contains(value)){
        if (value <= head->m_data){ //check if the element is added to the top
            Node *new_p = new Node; //create new node, initialize with values and correct prev and next pointers
            new_p->m_data = value;
            new_p->m_next = head;
            new_p->m_prev = nullptr;
            head->m_prev = new_p; //now head is the second element, so the second element's previous should point to new Node
            head = new_p;
            m_size++;
            return true;
        }
        if (value >= tail->m_data){ //check if the element is added to the rear
            Node *new_p = new Node; //create new node, initialize with values and correct prev and next pointers
            new_p->m_data = value;
            new_p->m_next = nullptr;
            new_p->m_prev = tail;
            tail->m_next = new_p; //now tail is the second-to-last element, so the second-to-last element's next node should point to the new node
            tail = new_p;
            m_size++;
            return true;
        }
        
        Node *p = head; //indexing node
        while ((value>p->m_data) && (p!=nullptr)){
            p = p->m_next;
        }
        //now p is pointing to element after where new element should be placed
        p = p->m_prev; //now p is pointing to element before where new element should be placed
        
        Node *new_p = new Node; //create new node, initialize with values and correct prev and next pointers
        new_p->m_data = value;
        new_p->m_prev = p;
        new_p->m_next = p->m_next; //update prev and next of the elements around newly-added element
        p->m_next->m_prev = new_p;
        p->m_next = new_p;
        m_size++;
        return true;
    }
    return false;
}

void Set::swap(Set& other){
    int temp_size = other.m_size; //swap set sizes
    other.m_size = m_size;
    m_size = temp_size;

    Node* temp_head = head; //swap head pointers
    head = other.head;
    other.head = temp_head;
    
    Node* temp_tail = tail; //swap tail pointers
    tail = other.tail;
    other.tail = temp_tail;
}

void unite(const Set& s1, const Set& s2, Set& result){
    for (int i = 0; i < s1.size(); i++){ //iterate over each element in s1
        ItemType x;
        s1.get(i,x); //get each element
        result.insert(x); //try insert into result
    }
    for (int i = 0; i < s2.size(); i++){ //iterate over each element in s2
        ItemType x;
        s2.get(i,x); //get each element
        result.insert(x); //try insert into result
    }
}

void butNot(const Set& s1, const Set& s2, Set& result){
    for (int i = 0; i < s1.size(); i++){ //iterate over each element in s1
        ItemType x;
        s1.get(i,x); //get each element
        if(!s2.contains(x)) //if element not contained in s2
            result.insert(x); //try insert into result
    }
}

void Set::dump() const{
    std::cerr << "--------DUMP---------" << std::endl;
    Node *p;
    p = head;
    while (p != nullptr){
        std::cerr << p->m_data << std::endl;
        p = p->m_next;
    }
    if (head==nullptr)
        std::cerr << " - Head: is nullptr" << std::endl;
    else
        std::cerr << " - Head: " << head->m_data << std::endl;
    if (tail==nullptr)
        std::cerr << " - Tail: is nullptr" << std::endl;
    else
        std::cerr << " - Tail: " << tail->m_data << std::endl;
    std::cerr << "--------------------" << std::endl;
}


