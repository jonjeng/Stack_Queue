/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  Summer 2015
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

/**********************************************************
 * YOU MUST MODIFY THIS FUNCTION IF YOU DID NOT IMPLEMENT
 * Single_list.h IN PROJECT 1.  THIS REQUIRES YOU TO:
 *   1.  Change which header file is is included.   -------#include "Double_sentinel_list.h" and included Double_node.h in project files
 *   2.  Change the type of the member variable 'list'.
 *   3.  Update the ostream<< operator so that it prints
 *       out the entries in your implementation.
 **********************************************************/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"
#include "Double_sentinel_list.h"
#include "Exception.h"
#include <iostream>

template <typename Type>
class Linked_stack {
	private:
		static int const ARRAY_CAPACITY = 8;

		Double_sentinel_list<Type> list;
		int itop;
		int stack_size;

	public:
		Linked_stack();
		Linked_stack( Linked_stack & );
		~Linked_stack();

		bool empty() const;
		int size() const;
		int list_size() const;

		Type top() const;

		void swap( Linked_stack & );
		Linked_stack &operator=( Linked_stack );
		void push( Type const &obj );
		Type pop();

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Linked_stack<T> const & );
};

template <typename Type>
Linked_stack<Type>::Linked_stack():
stack_size( 0 ) {
	// Empty constructor
}

template <typename Type>
Linked_stack<Type>::Linked_stack( Linked_stack &stack ):
itop( stack.itop ),
stack_size( stack.stack_size ) {
	// enter your implementation here
    
    // Clear the original list
    for (int i = 0; i < stack_size; i++)
        list.pop_front();
    
    // Make a complete copy of the input linked stack. Each entry is pushed onto the new linked stack
    Type tempArray[stack_size];
    for (int i = 0; i < stack_size; i++) {
        tempArray[i] = stack.pop();
        push(tempArray[i]);
    }
    
    for (int i = 0; i < stack_size; i++)
        stack.push(tempArray[i]);
    
    // First, copy over the Double_sentinel_list
    /*
    int remainingItems = stack_size;
    for (Double_node<Type> *node = list.tail(); node != list.head(); node = node->previous()) {
        Type *array_to_be_copied = new Type[ARRAY_CAPACITY];
        array_to_be_copied = node->retrieve();
        Type *copied_array = new Type[ARRAY_CAPACITY];
        int remainingItemsOnStack = remainingItems % 8;
        if (remainingItemsOnStack == 0)
            remainingItemsOnStack = 8;
        for (int j = 0; j < remainingItemsOnStack; j++)
            copied_array[j] = array_to_be_copied[j];
        remainingItems -= remainingItemsOnStack;
        list.push_front(copied_array);
    }
    */
    
    //Feasibility?
}

template <typename Type>
Linked_stack<Type>::~Linked_stack() {
    // If the stack is empty, there is nothing to delete
    if (stack_size == 0)
        return;
    
    // Otherwise, traverse the list, deleting each node, including the head and tail sentinels, to deallocate the memory pointed to by the entries of the linked list
    Double_node<Type> *curr = list.head();
    Double_node<Type> *tmpPtr = list.head()->next();
    while (curr != nullptr) {
        delete curr;
        curr = tmpPtr;
        tmpPtr = tmpPtr->next();
    }
}

template <typename Type>
bool Linked_stack<Type>::empty() const {
	// enter your implementation here
    return (stack_size == 0);
}

template <typename Type>
int Linked_stack<Type>::size() const {
	// enter your implementation here
    return stack_size;
}

// Do not change this implementation

template <typename Type>
int Linked_stack<Type>::list_size() const {
	return list.size();
    //
    
    // Returns the number of nodes in the linked list data structure. This must be implemented as provided. (O(1))
    // We're told not to change the implementation but is this right? Shouldn't it be std::ceil(size/ARRAY_CAPACITY), for which we need #include <cmath>?
}

template <typename Type>
Type Linked_stack<Type>::top() const {
	// enter your implementation here
    
    // If the stack is empty, throw an underflow exception
    if (stack_size == 0)
        throw underflow();
    
    // Returns the object at the top of the stack (last entry in the front array)
    Type *tempArray = list.front();
    Type result = *(tempArray + itop);
    
	return result;
}

template <typename Type>
void Linked_stack<Type>::swap( Linked_stack<Type> &stack ) {
	std::swap( list, stack.list );
	std::swap( stack_size, stack.stack_size );
	std::swap( itop, stack.itop );
}

template <typename Type>
Linked_stack<Type> &Linked_stack<Type>::operator=( Linked_stack<Type> rhs ) {
	//The assignment operator makes a copy of the argument and then swaps the member variables of this node with those of the copy. (O(nlhs + nrhs))
    
    // To avoid losing the argument (referred to as rhs), the following must be done
    list = rhs.list;
    stack_size = rhs.stack_size;
    itop = rhs.itop;
    
	return *this;
}

template <typename Type>
void Linked_stack<Type>::push( Type const &obj ) {
	// enter your implementation here

    
    // Check to see if stack is empty or if the topmost array constituting the stack is full. If so, allocate memory for a new array, put the argument in it and push it onto the list
    if (stack_size == 0 || itop == 7) {
        Type *topArray = new Type[ARRAY_CAPACITY];
        itop = 0;
        topArray[itop] = obj;
        list.push_front(*topArray);
        // Looks diff from the instructions - problem? Instructions: If the stack is empty, allocate memory for a new array with the required capacity, push the address of that array onto the linked list, set both indices to zero and place the new argument at that location. The size of the stack is now one.
    }
    // If the topmost array constituting the stack isn't full, push the argument into it
    //////////////////////////
    else {
        itop++;
        Double_node<Type> *curr = list.head()->next();
        Type *topArray = curr->retrieve();
        topArray[itop] = obj;
    }
    
    // Increment the stack size
    stack_size++;
}

template <typename Type>
Type Linked_stack<Type>::pop() {
	// enter your implementation here
    
    // If the stack is empty, throw an underflow exception
    if (stack_size == 0) throw underflow();
    
    // Otherwise, decrement itop and pop the top of the stack
    itop--;
    Double_node<Type> *curr = list.head()->next();
    Type *tmpArray = curr->retrieve();
    Type result = tmpArray[(itop+1)];
    tmpArray[(itop+1)] = NULL;
    
    // if itop is an invalid value, reset it accordingly and delete the now-extraneous array and node
    if (itop == -1) {
        itop = ARRAY_CAPACITY - 1;
        list.pop_front();
    }
    
    // Decrement the stack size
    stack_size--;
    
    // If the stack is now empty, also pop the front of the linked list and deallocate the memory allocated to the array in that node
    if (stack_size == 0) {
        /* necessary? If the stack is now empty, itop = -1 (previous conditional)
         Double_node<Type> temp = list.head()->next();
         Type *tempArray = temp->retrieve();
         delete [] tempArray;
         list.pop_front();
         */
    }    
    
    // Decrement the stack size
    stack_size--;
    
	return result;
}

// You will be required to modify this function in order to accomodate
// your implementation of a singly linked list in Project 1.

// values are in arrays, not values singly attached to nodes
// first arrays occur on list.tail()->previous(); not on list.head()
template <typename T>
std::ostream &operator<<( std::ostream &out, Linked_stack<T> const &stack ) {
	if ( stack.list.size() == 0 ) {
		out << "0->0";
	} else if ( stack.list.size() == 1 ) {
		out << "0->[ ";
        
        Double_node<T> *node = stack.list.head()->next();
        T* val = node->retrieve();
		for ( int i = 0; i <= stack.itop; ++i ) {
			out << val[i] << " ";
		}
        node = node->next();
        
		out << "]->0";
	} else {
		out << "0->";

		for ( Double_node<T> *ptr = stack.list.head()->next(); ptr != stack.list.tail(); ptr = ptr->next() ) {
			out << "[ ";
            T* array = ptr->retrieve();
            
			if ( ptr == stack.list.head()->next() ) {
				for ( int i = 0; i <= stack.itop; ++i ) {
					out << array[i] << " ";
                }
			} else {
				for ( int i = 0; i <= Linked_stack<T>::ARRAY_CAPACITY - 1; ++i ) {
					out << array[i] << " ";
                }
			}

			out << "]->";
		}

		out << "0";
	}

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
