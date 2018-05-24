/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#ifndef DOUBLE_SENTINEL_LIST_H
#define DOUBLE_SENTINEL_LIST_H

#include <iostream>
#include "Exception.h"

template <typename Type>
class Double_sentinel_list {
	public:
		class Double_node {
			public:
				Double_node( Type const & = Type(), Double_node * = nullptr, Double_node * = nullptr );

				Type value() const;
				Double_node *previous() const;
				Double_node *next() const;

				Type         node_value;
				Double_node *previous_node;
				Double_node *next_node;
		};

		Double_sentinel_list();
		Double_sentinel_list( Double_sentinel_list const & );
		Double_sentinel_list( Double_sentinel_list && );
		~Double_sentinel_list();

		// Accessors

		int size() const;
		bool empty() const;

		Type front() const;
		Type back() const;
    
		Double_node *begin() const;
		Double_node *end() const;
		Double_node *rbegin() const;
		Double_node *rend() const;

		Double_node *find( Type const & ) const;
		int count( Type const & ) const;

		// Mutators

		void swap( Double_sentinel_list & );
		Double_sentinel_list &operator=( Double_sentinel_list );
		Double_sentinel_list &operator=( Double_sentinel_list && );

		void push_front( Type const & );
		void push_back( Type const & );

		void pop_front();
		void pop_back();

		int erase( Type const & );

	private:
		Double_node *list_head;
		Double_node *list_tail;
		int list_size;

		// List any additional private member functions you author here
	// Friends

	template <typename T>
	friend std::ostream &operator<<( std::ostream &, Double_sentinel_list<T> const & );
};

/////////////////////////////////////////////////////////////////////////
//                      Public member functions                        //
/////////////////////////////////////////////////////////////////////////

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list():
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    // Declare head and tail sentinel nodes
    Double_node* headSent = new Double_node;
    Double_node* tailSent = new Double_node;
    
    //Since list is initially empty, the sentinel nodes point to eachother
    headSent->next_node = tailSent;
    headSent->previous_node = nullptr;

    tailSent->next_node = nullptr;
    tailSent->previous_node = headSent;
    
    //Point list_head to head sentinel node and list_tail to list sentinel node
    list_tail = tailSent;
    list_head = headSent;
    list_size = 0;
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> const &list ): //Copy constructor
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    // Declare head and tail sentinel nodes for list that will be copied to
    Double_node* headSent = new Double_node;
    Double_node* tailSent = new Double_node;
 
    //Since list is initially empty, the sentinel nodes point to eachother
    headSent->next_node = tailSent;
    headSent->previous_node = nullptr;
    
    tailSent->next_node = nullptr;
    tailSent->previous_node = headSent;
    
    //Point list_head to head sentinel node and list_tail to list sentinel node
    list_tail = tailSent;
    list_head = headSent;
    list_size = 0;
    
    
    //Create pointer to the front of the list that is passed in.
    Double_node* traverse = list.begin();
    while(traverse->next_node != nullptr){
        push_back(traverse->node_value); //Push value to back of new list from the node traverse points to
        traverse = traverse->next_node;
    }
}

template <typename Type>
Double_sentinel_list<Type>::Double_sentinel_list( Double_sentinel_list<Type> &&list ): //Move constructor
// Updated the initialization list here
list_head( nullptr ),
list_tail( nullptr ),
list_size( 0 )
{
    // Declare head and tail sentinel nodes for list that will be copied to
    Double_node* headSent = new Double_node;
    Double_node* tailSent = new Double_node;
    
    //Since list is initially empty, the sentinel nodes point to eachother
    headSent->next_node = tailSent;
    headSent->previous_node = nullptr;
    
    tailSent->next_node = nullptr;
    tailSent->previous_node = headSent;
    
    //Point list_head to head sentinel node and list_tail to list sentinel node
    list_tail = tailSent;
    list_head = headSent;
    list_size = 0;
    
    //Swap the list_head, list_tail and list_size of the list being created and the lsit passsed in
    swap(list);
}

template <typename Type>
Double_sentinel_list<Type>::~Double_sentinel_list() {
    Double_node* traverse = list_head; //Create traverse pointer to move through each node in the list
    while(traverse != nullptr) // Iterate through entire list until nullptr is reached which will be the end
    {
            Double_node* del = traverse; //Create pointer to node that should be deleted
            traverse = traverse->next_node;
            delete del;
    }
    list_size = 0;
}

template <typename Type>
int Double_sentinel_list<Type>::size() const {
    //Create traverse node pointer to traverse entire list and add to counter
    Double_node *traverse = list_head;
    int count = 0;
    while(traverse != nullptr) // Iterate through entire list until nullptr is reached which will be the end
    {
        traverse = traverse->next_node;
        count++;
    }
	return count - 2; // Subtract two from total count to account for both sentinel nodes.
}

template <typename Type>
bool Double_sentinel_list<Type>::empty() const {
    if(list_size == 0)//Check list_size, if 0, the list must be empty
        return true;
    return false;
}

template <typename Type>
Type Double_sentinel_list<Type>::front() const {
    // Check to see if list is empty before getting front node value
    if(empty())
        throw underflow();
    else
        return list_head->next_node->value(); //list_head points to the head sentinel node so the next node after that will be the front node.
    
	return Type();
}

template <typename Type>
Type Double_sentinel_list<Type>::back() const {
    // Check to see if list is empty before getting back node value
    if(empty())
        throw underflow();
    else
        return list_tail->previous_node->value(); //list_tail points to the tail sentinel node so the previous node before that will be the back node.
	return Type(); // This returns a default value of Type
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::begin() const {
    // list_head points to head sentinel node, next node after sentinel node will the first node in the list
	return list_head->next_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::end() const {
    // list_tail point to the tail sentinel node
	return list_tail;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rbegin() const {
    // previous_node of list_tail is the last node in the list
	return list_tail->previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::rend() const {
    // list_head point to the head sentinel node
	return list_head;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::find( Type const &obj ) const {
    //Create traverse node pointer to iterate through each node in the list
    Double_node *traverse = list_head->next_node;
    while(traverse != nullptr)
    {
        if(traverse->node_value == obj) //If the node that traverse is pointing to has the same value as obj, return traverse pointer
            return traverse;
        else
            traverse = traverse->next_node; //If the values dont match, point traverse to the next node in the list
    }
	return end();
}

template <typename Type>
int Double_sentinel_list<Type>::count( Type const &obj ) const {
    //Create traverse node pointer to iterate through each node in the list
    Double_node *traverse = list_head->next_node;
    int count = 0;
    while(traverse != nullptr)
    {
        if(traverse->node_value == obj) //If the node that traverse is pointing to has the same value as obj, increment count
            count++;

        traverse = traverse->next_node;  //Always move the traverse pointer to the next node in the list
    }
    return count;
}

template <typename Type>
void Double_sentinel_list<Type>::swap( Double_sentinel_list<Type> &list ) {
	// This is done for you
	std::swap( list_head, list.list_head );
	std::swap( list_tail, list.list_tail );
	std::swap( list_size, list.list_size );
}

// The assignment operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> rhs ) {
	// This is done for you
	swap( rhs );

	return *this;
}

// The move operator
template <typename Type>
Double_sentinel_list<Type> &Double_sentinel_list<Type>::operator=( Double_sentinel_list<Type> &&rhs ) {
    // This is done for you
    swap( rhs );

    return *this;
}

template <typename Type>
void Double_sentinel_list<Type>::push_front( Type const &obj ) {
// Create new node to add to list holding the value passed in
    Double_node *n = new Double_node;
    
//Re-arrange next an dprevious poinbters to add new node to list
    n->node_value = obj;
    n->next_node = list_head->next_node;
    n->previous_node = list_head;
    
    list_head->next_node->previous_node = n;
    list_head ->next_node = n;
    list_size++;
}

template <typename Type>
void Double_sentinel_list<Type>::push_back( Type const &obj ) {
// Create new node to add to list holding the value passed in
    Double_node *n = new Double_node;
    
//Re-arrange next an dprevious poinbters to add new node to list
    n->node_value = obj;
    n->next_node = list_tail;
    n->previous_node = list_tail->previous_node;
    
    list_tail->previous_node->next_node = n;
    list_tail->previous_node = n;
    list_size++;
    
}

template <typename Type>
void Double_sentinel_list<Type>::pop_front() {
	// Check to see if list is empty before attempting to remove first node
    if(empty())
        throw underflow();
    Double_node* nodePop = list_head->next_node; //Assign temporary pointer to the last node in the list (besides sentinel)
    
    //Move pointers around first node in list to establish a new first node
    list_head->next_node = nodePop->next_node;
    list_head->next_node->previous_node = list_head;
    
    //Delete node after pointers have been allocated correctly
    delete nodePop;
    list_size--;
}

template <typename Type>
void Double_sentinel_list<Type>::pop_back() {
	// Check to see if list is empty before attempting to remove first node
    if(empty())
        throw underflow();
    Double_node* nodePop = list_tail->previous_node; //Assign temporary pointer to the first node in the list (besides sentinel)
    
    //Move pointers around first node in list to establish a new first node
    list_tail->previous_node = nodePop->previous_node;
    list_tail->previous_node->next_node = list_tail;
    
    //Delete node after pointers have been allocated correctly
    delete nodePop;
    list_size--;
}

template <typename Type>
int Double_sentinel_list<Type>::erase( Type const &obj ) {
    //Create counter to count how mamny nodes are erased
    int numDelete = 0;
    //Create traverse pointer to navigate list
    Double_node* traverse = list_head->next_node;
    while(traverse->next_node != nullptr)
    {
        if(traverse->node_value == obj){ //If the node value matches the value passed in,
            Double_node* del = traverse; //Create temporary pointer to node that is to be deleted
            del->previous_node->next_node = traverse->next_node; // Re-arrange pointers to avoid the node to be deleted
            del->next_node->previous_node = traverse->previous_node;
            traverse = traverse->next_node; // Move traverse to next node to ensure it is not lost
            
            delete del; // Delete desired node
            numDelete++;
            list_size--;
        }
        else
            traverse = traverse->next_node; //If the node value does not match the value passed in, move traverse to next node in list
    }
    return numDelete;
}

template <typename Type>
Double_sentinel_list<Type>::Double_node::Double_node(
	Type const &nv,
	typename Double_sentinel_list<Type>::Double_node *pn,
	typename Double_sentinel_list<Type>::Double_node *nn ):
// Updated the initialization list here
node_value( Type() ), // This assigns 'node_value' the default value of Type
previous_node( nullptr ),
next_node( nullptr )
{
	// Enter your implementation here
}

template <typename Type>
Type Double_sentinel_list<Type>::Double_node::value() const {
	return node_value; // This returns the value of the node
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::previous() const {
    // Return previous_node pointer
	return previous_node;
}

template <typename Type>
typename Double_sentinel_list<Type>::Double_node *Double_sentinel_list<Type>::Double_node::next() const {
	//Return next_node pointer
	return next_node;
}


/////////////////////////////////////////////////////////////////////////
//                      Private member functions                       //
/////////////////////////////////////////////////////////////////////////

// If you author any additional private member functions, include them here

/////////////////////////////////////////////////////////////////////////
//                               Friends                               //
/////////////////////////////////////////////////////////////////////////

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator<<( std::ostream &out, Double_sentinel_list<T> const &list ) {
	out << "head";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.rend(); ptr != nullptr; ptr = ptr->next() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0" << std::endl << "tail";

	for ( typename Double_sentinel_list<T>::Double_node *ptr = list.end(); ptr != nullptr; ptr = ptr->previous() ) {
		if ( ptr == list.rend() || ptr == list.end() ) {
			out << "->S";
		} else {
			out << "->" << ptr->value();
		}
	}

	out << "->0";

	return out;
}

#endif
