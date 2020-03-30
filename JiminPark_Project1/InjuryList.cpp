/**	@file InjuryList.cpp
	@author Jimin Park
	@date 2019-10-20

	Implement for InjuryList.hpp
*/
#include "InjuryList.hpp"

InjuryList::InjuryList() {
	size_ = 0; 
}

InjuryList::InjuryList(const InjuryList* il)
{
	this->head_ = new Node(il->head_);
	this->size_ = il->size_;

	Node* newptr = this->head_;
	Node* orgptr = il->head_;

	// copy objects of Injury class by using a deep copy of the original object 
	while (orgptr->next_ != nullptr)
	{
		newptr->next_ = new Node(orgptr->next_);
		newptr = newptr->next_;
		orgptr = orgptr->next_;
	}

	this->tail_ = newptr;
}

InjuryList::~InjuryList() {
	clear();
}

/*!	 \fn clear
	 \return none
	 \param none

	 clear all the injuriLists which are patient belonging */
void InjuryList::clear() {
	Node* delptr = nullptr;
	Node* next = nullptr;

	delptr = this->head_;
	next = delptr->next_;

	if (this->head_ == nullptr) { return; }
	int cnt = 0;
	while (delptr != nullptr) {
		cnt++;
		next = delptr->next_;
		delete delptr;
		delptr = next;
	}
}

/*!	 \fn push_back
	 \return none
	 \param data -> injury

	 insert injury to list */
void InjuryList::push_back(string data){
	if (this->head_ == nullptr) // if the list is empty
	{
		this->head_ = new Node(data);
		this->tail_ = this->head_;
		this->head_->next_ = nullptr;
	}
	else // create a new node, set the tail to point to the new node
	{    // and the new tail next_ should be a nullptr
		Node* tmp = new Node(data);
		if (this->head_->next_ == nullptr)
		{
			this->head_->next_ = tmp;
		}
		this->tail_->next_ = tmp;
		this->tail_ = tmp;
		this->tail_->next_ = nullptr;
	}
	size_++;
}

/*!	 \fn print
	 \return none
	 \param none

	 print all the injury's list that belong to patient*/
void InjuryList::print() {
	Node* it = this->head_;
	while (it != nullptr)
	{
		if (it != head_)
			cout << ", ";
		cout << it->injuryTitle_;
		it = it->next_;
	}
}

