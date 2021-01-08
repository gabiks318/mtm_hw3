#ifndef LIST_NODE_H
#define LIST_NODE_H

namespace mtm
{
template <typename T> 
class List;

template <typename T>
class Node //nodes to be contained with a list
{
    T node_data; //templatized data stored in node
	Node* next; //pointer to the next node in list
    friend class List<T>;

    public:
	Node(T node_data);
	T getData();
	
};

template <typename T>
Node<T>::Node(T data)
{
	node_data = data; //stores data in node
	next = NULL; //initializes point to next node to null
}

template <typename T>
T Node<T>::getData() //returns data stored in node
{
	return node_data;
}
}
#endif