/*****************************************
 Project 1 - CIS 22C
 
 * Contributors:
 * Evan Finnigan
 * Forest Finnigan
 * Jonathan Jeng
 * Abhishek Rajbahndri
 *****************************************/

#ifndef DOUBLE_NODE_H
#define DOUBLE_NODE_H

#ifndef nullptr
#define nullptr 0
#endif

#include "ece250.h"

template <typename Type>
class Double_list;

template <typename Type>
class Cyclic_double_list;

template <typename Type>
class Double_sentinel_list;

template <typename Type>
class Cyclic_double_sentinel_list;

template <typename Type>
class Double_node {
private:
    Type*       element;
    Double_node *previous_node;
    Double_node *next_node;
    
public:
    Double_node( Type *& = Type(), Double_node * = nullptr, Double_node * = nullptr );
    
    Type* retrieve() const;
    Double_node *previous() const;
    Double_node *next() const;
    
    friend class Double_list<Type>;
    friend class Cyclic_double_list<Type>;
    friend class Double_sentinel_list<Type>;
    friend class Cyclic_double_sentinel_list<Type>;
    
};

template <typename Type>
Double_node<Type>::Double_node( Type *&e, Double_node<Type> *p, Double_node<Type> *n ):
element( e ),
previous_node( p ),
next_node( n ) {
    // empty constructor
}

template <typename Type>
Type* Double_node<Type>::retrieve() const {
    return element;
}

template <typename Type>
Double_node<Type> *Double_node<Type>::previous() const {
    return previous_node;
}

template <typename Type>
Double_node<Type> *Double_node<Type>::next() const {
    return next_node;
}

#endif
