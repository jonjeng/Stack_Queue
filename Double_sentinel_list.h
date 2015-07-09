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
 * Calender Term of Submission: Summer 2015
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

		Type front() const;
		Type back() const;

		Double_node<Type> *head() const;
		Double_node<Type> *tail() const;

		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list const & );

		void push_front( Type const & );
		void push_back( Type const & );

		Type pop_front();
		Type pop_back();

		int erase( Type const & );

	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 ) {
	// fix assignments...
	// enter your implementation here
    
    // Allocate two sentinels with corresponding next_node and previous_node assignments (the sentinels - list_head and list_tail - are designated as having value -1
    list_head = new Double_node<Type>(-1, nullptr, nullptr);
    list_tail = new Double_node<Type>(-1, list_head, nullptr);
    
    list_head->next_node = list_tail;
    
    // list_size remains 0 as there are no items in this list
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ):
list_head( nullptr ), 
list_tail( nullptr ),
list_size( 0 ) {
	// enter your implementation here
    
    // The to-be-copied list shall be referred to as source, and the newly created list shall be referred to as copyList
    // If the list to be copied is empty, nothing is to be done
    if (list.empty()) return;
    
    // Copy the head_sentinel (value -1) of source to copyList
    push_front( list.front() );
    
    // Copy the elements of source, including tail_sentinel (value -1), to copy_list
    for (Double_node<Type> *source = list.list_head->next(), *copy = list.list_head; (source != nullptr); copy = copy->next(), source = source->next())
    {
        copy->next_node = new Double_node<Type>(source->retrieve(), copy, source);
    }
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
	// enter your implementation here
    while (!empty()) pop_front();
    delete list_head;
    delete list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
	// enter your implementation here
	// If the list is empty, return 0
    if (empty()) return 0;
    
    // Otherwise, find the size of the list
    // count is a variable to count the number of items in the list, excluding the two sentinels
    int count = 0;
    
    // counter is a pointer to list items. It must start at the element following the head_sentinel and end at the element immediately prior to the tail_sentinel (value -1
    Double_node<Type> *counter = list_head;
    
    while (counter->next_node->retrieve() != -1)
    {
        count++;
        counter = counter->next();
    }
    
    return count;
    
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
	// enter your implementation here
    
    // Return true if size == 0 and/or the head sentinel points to the tail sentinel (value 0)
    Double_node<Type> *check = list_head;
    if (list_size == 0 || check->next_node->retrieve() == -1) return true;
    
    // Otherwise, the list is not empty
    return false;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
	// enter your implementation here
    
    Double_node<Type> *tmpPtr = list_head->next();
    return tmpPtr->retrieve();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
	// enter your implementation here
    
    // If size == 0, the back is the tail sentinel (value -1)
    if (list_size == 0) return -1;
    
    // Move through the list to the node preceding the tail sentinel (value -1)
    Double_node<Type> *tmpPtr = list_head->next();
    while (tmpPtr->next() != nullptr)
        tmpPtr = tmpPtr->next_node;
    
    // Move one back to the node immediately preceding the tail sentinel
    tmpPtr = tmpPtr->previous();
    
	return tmpPtr->retrieve();
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::head() const {
	// enter your implementation here
	return list_head;
}

template <typename Type>
Double_node<Type> *Double_sentinel_list<Type>::tail() const {
	// enter your implementation here
	return list_tail;
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
	// enter your implementation here
    //    Returns the number of nodes in the linked list storing a value equal to the argument. (O(n))
    if (list_size == 0) return 0;
    
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
	Double_sentinel_list<Type> copy( rhs );

	swap( copy );
	
	return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
	// enter your implementation here
    
    Double_node<Type> *tmpPtr = list_head->next_node;
    Double_node<Type> *tmpPtr2 = nullptr;
    tmpPtr2 = new Double_node<Type>(obj, list_head, tmpPtr);
    list_head->next_node = tmpPtr2;
    tmpPtr->previous_node = tmpPtr2;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
	// enter your implementation here
    
    Double_node<Type> *tmpPtr = list_tail->previous_node;
    Double_node<Type> *tmpPtr2 = new Double_node<Type>(obj, tmpPtr, list_tail);
    list_tail->previous_node = tmpPtr2;
    tmpPtr->next_node = tmpPtr2;
    list_size++;

}

template <typename Type>
Type Double_sentinel_list<Type>::pop_front() {
	// enter your implementation here
    if (list_head->next_node == list_tail)
        return -1;
    Double_node<Type> *tmpPtr = list_head->next_node;
    Double_node<Type> *tmpPtr2 = tmpPtr->next_node;
    Type temp = tmpPtr->retrieve();
    delete tmpPtr;
    list_head->next_node = tmpPtr2;
    tmpPtr2->previous_node = list_head;
    list_size--;
	return temp;
}

template <typename Type>
Type Double_sentinel_list<Type>::pop_back() {
	// enter your implementation here
    if (list_tail->previous_node == list_head)
        return -1;
    Double_node<Type> *tmpPtr = list_tail->previous_node;
    Double_node<Type> *tmpPtr2 = tmpPtr->previous_node;
    Type temp = tmpPtr->retrieve();
    delete tmpPtr;
    list_tail->previous_node = tmpPtr2;
    tmpPtr2->next_node = list_tail;
    list_size--;
    return temp;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
	// enter your implementation here
    // Instructions: Delete the first node (from the front and other than the sentinals) in the linked list that contains the object equal to the argument (use == to to test for equality with the retrieved element). Update the previous and next pointers of any other node (including possibly the sentinels) within the list. Return the number of nodes that were deleted.
            // Does this mean that we delete only the first match, or all matches?
    if (empty()) return 0;
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

// You can modify this function however you want:  it will not be tested

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

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
