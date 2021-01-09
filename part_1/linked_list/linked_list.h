#ifndef LIST_H
#define LIST_H

#include <iostream>
#include "../exceptions.h"

using std::cout;
using std::endl;
using mtm::OutOfBoundaries;
#include "node.h"
namespace mtm
{
template <typename T>
class List //linked list of Node objects
{
    Node<T> *start_node; //stores the pointer of first object in the linked list
	Node<T> *end_node; //stored the pointer of the last object in the linked list
	void insertStart(T); //inserts new node before the first node in the list
	void insertEnd(T); //inserts new node after the last node in the list
    void removeStart();
    void removeEnd();
    

    public:
	List();
    List(const List<T>& copy_list);
    List<T>& operator=(const List<T>& copy_list);
	~List();
	void insert(T data); //fucntion used to insert new node in order in the list
    void remove(T data);
    
    int getSize();
    bool isEmpty(); //utility functions used to see if the list contains no elements
	void print(); //prints the contents of the linked list
	bool exists(T data); //searches for a value in the linked list and returns the point to object that contains that value
    T operator[](int index);	
};



template <typename T>
List<T>::List(const List<T>& copy_list)
{
    start_node = NULL;
    end_node = NULL;
    Node<T>* copy_node = copy_list.start_node;
    while(copy_node != NULL){
        insert(copy_node->node_data);
        copy_node = copy_node->next;
    }
}

template <typename T>
List<T>::List() //creates list with start_node and end_node as NULL
{
	start_node = NULL;
	end_node = NULL;
}

template <typename T>
List<T>& List<T>::operator=(const List& copy_list){
    if(!isEmpty()){
        Node<T>* current = start_node;
        Node<T>* temp;
        while (current != NULL ) // delete remaining nodes
        {  
            temp = current;
            current = current->next;
            delete temp;
        }
    }

    start_node = NULL;
    end_node = NULL;
    Node<T>* copy_node = copy_list.start_node;
    while(copy_node != NULL){
        insert(copy_node->node_data);
        copy_node = copy_node->next;
    }

    return *this;
}

template <typename T>
List<T>::~List()
{
	if (!isEmpty()) // List is not empty
   {    
      Node<T>* current = start_node;
      Node<T>* temp;

      while (current != NULL ) // delete remaining nodes
      {  
         temp = current;
         current = current->next;
         delete temp;
      }
   }
}

template <typename T>
bool List<T>::isEmpty()
{
	if(start_node == NULL && end_node == NULL){   //if the start_node pointer and end_node pointer are NULL then the list is empty
        return true;
    } else {
		return false;
    }
}

template <typename T>
void List<T>::insertStart(T data)
{
	if(isEmpty()) //if the list is empty create first element of the list
	{
		Node<T>* new_node = new Node<T>(data); //creates new node
		start_node = new_node; //start_node and end_node pointer are same becuase there is only one object in list
		end_node = new_node;
	}
    else //if node(s) exist in list insert additional object before the first
	{
		Node<T>* new_node = new Node<T>(data);
		new_node->next = start_node; //the next pointer of the new node points to the node that was previously first
		start_node = new_node; //the pointer for the new node is now the starting node
	}
}

template <typename T>
void List<T>::insertEnd(T data)
{
	if(isEmpty()) //if the list is empty create first element of the list (same as first case in insert at begin)
	{
		Node<T>* new_node = new Node<T>(data);
		start_node = new_node;
		end_node = new_node;
	} else //if node(s) exist in the list then insert new node at the end_node of the list
	{
		Node<T>* new_node = new Node<T>(data);
		end_node->next = new_node; //the current last node's next pointer points to the new node
		end_node = new_node; //the new node is now the last node in the list
	}
}

template <typename T>
void List<T>::insert(T data) //general funtionn to insert new node the proper order in the list
{
	if(isEmpty()) //if there is no nodes in the list simply insert at beginning
	{
		insertStart(data);
        return;
	}

	if(data < start_node->node_data) //if the data of the new object is less than than the data of first node in list insert at beginning
	{
		insertStart(data);
        return;
	}
	if(data >= end_node->node_data) //if the data of the new object is greater than than the data of last node in list insert at end_node
	{
		insertEnd(data);
        return;
	}
		
	Node<T>* current = start_node;
	Node<T>* new_node = new Node<T>(data); //creates new node
	while(current != end_node) //runs until the end_node of the list is reached
	{
		if((new_node->node_data < current->next->node_data) && (new_node->node_data >= current->node_data)) //if the data of the new node is less the data in the next node and greater than the data in the current node, insert after current node 
		{
			Node<T>* next = current->next; 
			current->next = new_node; //current nodes next pointer now points to the new node
			new_node->next = next; //the new nodes next pointer now points the node previously after the current node
			break;
		}
		current = current->next; //moves to the next node in the list
		
	}
	
}

template <typename T>
int List<T>::getSize(){
    if(isEmpty()){
        return 0;
    }
    int count = 0;
    Node<T>* temp = start_node;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }

    return count;
}

template <typename T>
void List<T>::removeStart(){
    Node<T>* temp = start_node;
    start_node = temp->next;
    delete temp;
}

template <typename T>
void List<T>::removeEnd(){
    Node<T>* temp = end_node;
    Node<T>* node_iterator = start_node;
    while(node_iterator != NULL){
        if(node_iterator->next == end_node){
            break;
        }
        node_iterator = node_iterator->next;
    }

    end_node = node_iterator;
    end_node->next = NULL;
    delete temp;
}



template <typename T>
void List<T>::remove(T key)
{
    if(isEmpty() || !exists(key)){
        return;
    }
    if(start_node->node_data == key){
        removeStart();
        return;
    }
    if(end_node->node_data == key){
        removeEnd();
        return;
    }
    
    Node<T>* node_ptr, *node_temp;
	node_ptr = start_node;
    node_temp = NULL;
    while(node_ptr->next !=NULL)
    {
        if(node_ptr->node_data == key){
            break;
        }
        node_temp = node_ptr;
        node_ptr = node_ptr->next;
    }

    node_temp->next =node_ptr->next;
    delete node_ptr;
}

template <typename T>
void List<T>::print()
{
	if(isEmpty())
	{
		cout << "The list is empty" << endl;
	
	}else
	{
		Node<T> * current = start_node;

		cout << "The contents of the list is: ";
		while(current != NULL) //prints until the end_node of the list is reached
		{
			cout << current->node_data << ' ';
			current = current->next; //moves to next node in list
		}
		cout << endl;
	}
}

template <typename T>
bool List<T>::exists(T key) //exists functions that searches for node that contains data equal to the key
{
	Node<T>* node_ptr;
	node_ptr = start_node;

	while(node_ptr != NULL) //runs through list until data is found within a node or end_node of list is reached
	{
		if(node_ptr->node_data == key){
            return true;
		} else {
            node_ptr = node_ptr->next; //moves to next node in list 
        }	
	}
	return false; //returns pointer to the node that contains data equal to key (NULL if not found)
}

template <typename T>
T List<T>::operator[](int index){
    int size = getSize();
    /*if(index < 0 || index >= size){
        throw OutOfBoundaries();
    }*/
    if(index == 0){
        return start_node->node_data;
    }
    if(index == size - 1){
        return end_node->node_data;
    }
    Node<T>* temp = start_node;
    for(int i = 0; i < index; i++){
        temp = temp->next;
    }

    return temp->node_data;
}
}
#endif 