#pragma once
#include <string>
using namespace std;

// Node class used in the linked list
// Each node contains an int data value and a pointer to the next
//		node in the Linked List
class Node{
public:
	string injuryTitle_;
	Node* next_ = nullptr;

	Node(string datain);
	Node(const Node* n);
	~Node();
	void setNext(Node * n);
};

