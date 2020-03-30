/**	@file HistoryQueue.cpp
	@author Jimin Park
	@date 2019-10-20

	Implement for HistoryQueue.hpp
*/
#include "HistoryQueue.hpp"

HistoryQueue::HistoryQueue() {
}

HistoryQueue::~HistoryQueue() {
	if (this->head_ == nullptr) { return; }

	Patient* delptr = nullptr;
	Patient* next = nullptr;
	delptr = this->head_;
	next = delptr->next_;

	while (delptr != nullptr) {
		next = delptr->next_;
		delete delptr;
		delptr = next;
	}
}

/*!	 \fn enqueue
	 \return none
	 \param Patient

	 enqueue patient's information to historyqueue
	 when user process patient, that patient enqueue to historyqueue */
void HistoryQueue::enqueue(Patient* p){

	if (this->head_ == nullptr) // first time
	{
		this->head_ = p;
		this->tail_ = this->head_;
		this->head_->prev_ = nullptr;
		this->head_->next_ = nullptr;
	}
	else {
		if (this->head_->next_ == nullptr) {
			this->head_->next_ = p;
		}
		p->prev_ = this->tail_;
		this->tail_->next_ = p;
		this->tail_ = p;
		this->tail_->next_ = nullptr;
	}
}

/*!	 \fn historyQueuePrint
	 \return none
	 \param none

	 print all the patients which are in historyqueue */
void HistoryQueue::historyQueuePrint(){
	cout << endl <<  " History of inserted Patients on Triage System" << endl;

	Patient* it = this->head_;
	while (it != nullptr) {
		cout << it->getPatientName() << "\t - priority " << it->priority_ << " - ";
		it->selectInjuryList();	
		cout << endl;
		it = it->next_;
	}
}