/*****************************************
 Project 1 - CIS 22C
 
 * Contributors:
 * Evan Finnigan
 * Forest Finnigan
 * Jonathan Jeng
 * Abhishek Rajbahndri
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_node.h"
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
private:
    Double_node<Type> *list_head;
    Double_node<Type> *list_tail;
    int list_size;
    
public:
    Double_sentinel_list();
    Double_sentinel_list( Double_sentinel_list const & );
    ~Double_sentinel_list();
    
    // Accessors
    
    int size() const;
    bool empty() const;
    
    Type* front() const;
    Type* back() const;
    
    Double_node<Type> *head() const;
    Double_node<Type> *tail() const;
    
    int count( Type const & ) const;
    
    // Mutators
    
    void swap( Double_sentinel_list & );
    Double_sentinel_list &operator=( Double_sentinel_list const & );
    
    void push_front( Type* & );
    void push_back( Type* & );
    
    Type* pop_front();
    Type* pop_back();
    
    int erase( Type* const & );
    
    // Friends
    
    template <typename T>
    friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
    // Cannot have sentinels with value -1 because -1 isn't of typename Type
    Type* default_parameter;
    list_head = new Double_node<Type>(default_parameter, nullptr, nullptr);
    list_tail = new Double_node<Type>(default_parameter, list_head, nullptr);
    
    list_head->next_node = list_tail;
    
    // list_size remains 0 as there are no items in this list
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ),
list_tail( nullptr ),
list_size( list.list_size ) {
    // Allocate two sentinels with corresponding next_node and previous_node assignments
    Type* default_parameter;
    list_head = new Double_node<Type>(default_parameter, nullptr, nullptr);
    list_tail = new Double_node<Type>(default_parameter, list_head, nullptr);
    
    list_head->next_node = list_tail;
    
    // The to-be-copied list shall be referred to as source, and the newly created list shall be referred to as copyList
    // If the list to be copied is empty, nothing is to be done
    if (list.empty()) return;
    
    // Copy the elements of source, including tail_sentinel (value -1), to copy_list
    for (Double_node<Type> *source = list.list_head->next(), *curr = list_head; (source != nullptr); source = source->next(), curr = curr->next_node)
    {
        curr->next_node = new Double_node<Type>(default_parameter, curr, list_tail);
        curr->next_node->element = source->retrieve();
        curr->next_node->previous_node = curr;
        curr->next_node->next_node = list_tail;
        list_tail->previous_node = (curr->next_node);
    }
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    while (!empty()) pop_front();
    delete list_head;
    delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    // If the list is empty, return 0
    if (empty()) return 0;
    
    // Otherwise, return the size of the list
    return list_size;
    
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    // Return true if size == 0
    if (list_size == 0) return true;
    
    // Otherwise, the list is not empty
    return false;
}

template <typename Type>
Type* Double_sentinel_list<Type>::front() const {
    try {
        // If the list is empty, throw an underflow exception
        if (list_size == 0)
            throw underflow();
        // Return the contents of the first node past the head
        return list_head->next()->retrieve();
    }
    catch(underflow & exception){
        // Inform the client of the underflow exception
        std::cout << "Error: there are no items in the list!\n" << std::endl;
        return nullptr;
    }
}

template <typename Type>
Type* Double_sentinel_list<Type>::back() const {
    try {
        // If the list is empty, throw an underflow exception
        if (list_size == 0)
            throw underflow();
        // Return the contents of the first node past the head
        return list_tail->previous_node->retrieve();
    }
    catch(underflow & exception){
        // Inform the client of the underflow exception
        std::cout << "Error: there are no items in the list!\n" << std::endl;
        return -1;
    }
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {
    return list_head;
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {
    return list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    // Returns the number of nodes in the linked list storing a value equal to the argument
    // If the list is empty, we already know there are 0 instances of the argument
    if (list_size == 0) return 0;
    
    // Otherwise, iterate through the list and count the number of matching instances
    int count = 0;
    for (Double_node<Type> *tmpPtr = list_head; tmpPtr != nullptr; tmpPtr = tmpPtr->next_node)
        if (tmpPtr->element == obj) count++;
    
    return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
    std::swap( list_head, list.list_head );
    std::swap( list_tail, list.list_tail );
    std::swap( list_size, list.list_size );
}

template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> const &rhs ) {
    // Makes a copy of the argument and then swaps the member variables of this node doubly linked sentinel list those of the copy. (O(nlhs + nrhs))
    Double_sentinel_list<Type> copy( rhs );
    
    this->swap( copy );
    
    return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type* &obj ) {
    Double_node<Type> *tmpPtr = list_head->next_node;
    Double_node<Type> *tmpPtr2 = nullptr;
    tmpPtr2 = new Double_node<Type>(obj, list_head, tmpPtr);
    list_head->next_node = tmpPtr2;
    tmpPtr->previous_node = tmpPtr2;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type* &obj ) {
    Double_node<Type> *tmpPtr = list_tail->previous_node;
    Double_node<Type> *tmpPtr2 = new Double_node<Type>(obj, tmpPtr, list_tail);
    list_tail->previous_node = tmpPtr2;
    tmpPtr->next_node = tmpPtr2;
    list_size++;
    
}

template <typename Type>
Type* Double_sentinel_list<Type>::pop_front() {
    try {
        // If the list is empty, throw an underflow exception
        if (empty())
            throw underflow();
        // Delete the front node and return its contents
        Double_node<Type> *tmpPtr;
        if (list_head->next_node != list_tail)
            tmpPtr = list_head->next_node->next_node;
        else
            tmpPtr = list_tail;
        Type* temp = list_head->next_node->retrieve();
        delete list_head->next_node;
        list_head->next_node = tmpPtr;
        tmpPtr->previous_node = list_head;
        list_size--;
        return temp;
    }
    catch(underflow & exception){
        // Inform the client of the underflow exception
        std::cout << "Error: there are no items in the list!\n" << std::endl;
        return nullptr;
    }
    
}

template <typename Type>
Type* Double_sentinel_list<Type>::pop_back() {
    
    try {
        // If the list is empty, throw an underflow exception
        if (list_size == 0)
            throw underflow();
        
        // Remove the back node and return its value
        Double_node<Type> *tmpPtr = list_tail->previous_node->previous_node;
        Type* temp = list_tail->previous_node->retrieve();
        delete list_tail->previous_node;
        list_tail->previous_node = tmpPtr;
        tmpPtr->next_node = list_tail;
        list_size--;
        return temp;
    }
    catch(underflow & exception){
        // Inform the client of the underflow exception
        std::cout << "Error: there are no items in the list!\n" << std::endl;
        return nullptr;
    }
    
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type* const &obj ) {
    // If the list is empty, there is nothing to erase and the client can be told that 0 items were erased
    if (empty()) return 0;
    
    // Otherwise, iterate through the list and erase all matching instances, while counting the number of erases
    int count = 0;
    for (Double_node<Type> *stepper = list_head->next(); stepper != nullptr; )
    {
        if (stepper->retrieve() == obj)
        {
            count++;
            Double_node<Type> *holder = stepper;
            Double_node<Type> *tmpPtr = stepper->previous();
            stepper = stepper->next();
            delete holder;
            stepper->previous_node = tmpPtr;
            tmpPtr->next_node = stepper;
        }
        else stepper = stepper->next();
    }
    return count;
}

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
    out << "head";
    
    for ( Double_node<T> *ptr = list.head(); ptr != nullptr; ptr = ptr->next() ) {
        if ( ptr == list.head() || ptr == list.tail() ) {
            out << "->S";
        } else {
            out << "->" << ptr->retrieve();
        }
    }
    
    out << "->0" << std::endl << "tail";
    
    for ( Double_node<T> *ptr = list.tail(); ptr != nullptr; ptr = ptr->previous() ) {
        if ( ptr == list.head() || ptr == list.tail() ) {
            out << "->S";
        } else {
            out << "->" << ptr->retrieve();
        }
    }
    
    out << "->0";
    
    return out;
}

#endif
