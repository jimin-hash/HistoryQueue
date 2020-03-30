/**	@file Node.cpp
	@author Jimin Park
	@date 2019-10-20

	Implement for Node.hpp
*/
#include "Node.hpp"

Node::Node(string datain)
{
	this->injuryTitle_ = datain;
	this->next_ = nullptr;
}

Node::Node(const Node* n)
{
	this->injuryTitle_ = n->injuryTitle_;
}

Node::~Node()
{
}

// Desc:   sets the next Node pointer
// Parms:  value to set the next_ Node pointer
// Returns: n/a
void Node::setNext(Node* n)
{
	this->next_ = n;
}