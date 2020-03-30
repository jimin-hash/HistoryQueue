/**	@file PatientQueue.cpp
	@author Jimin Park
	@date 2019-10-20

	Implement for PatientQueue.hpp
*/
#include "PatientQueue.hpp"

PatientQueue::PatientQueue() {
	size_ = 0;
	pm->readCSVFile();
}

PatientQueue::~PatientQueue() {
	clear();

	delete pm;
}

/*!	 \fn getSize
	 \return int size
	 \param none

	 return the size of patientqueue */
int PatientQueue::getSize() {
	return this->size_;
}

/*!	 \fn addPatient
	 \return bool
	 \param Patient

	 enqueue paitent to patientqueue by priority score
	 For the queue threshold, any combined score below 4 is put into the regular queue*/
bool PatientQueue::addPatient(Patient* p) {
	p->priority_ = p->calcPriority(pm);

	if (this->head_ == nullptr) // first time
	{
		this->head_ = p;
		this->tail_ = this->head_;
		this->head_->prev_ = nullptr;
		this->head_->next_ = nullptr;
	}
	else if (p->priority_ < 4) { // below 4 is put into the regular queue
		this->tail_->next_ = p;
		p->prev_ = this->tail_;
		p->next_ = nullptr;
		this->tail_ = p;
	}
	else
	{
		Patient* it = this->head_;
		while (it != nullptr) {
			if (it->priority_ == p->priority_) { // same priority
				p->position_++;
			}

			if (it->priority_ < p->priority_) {
				break;
			}
			it = it->next_;
		}// while

		if (it == nullptr) {
			it = this->tail_;
			p->prev_ = it;
			this->tail_->next_ = p;
			this->tail_ = p;
		}
		else if (it == this->head_) { // head
			p->next_ = it;
			this->head_ = p;
			this->tail_->prev_ = p;
		}
		/*else if (it == this->tail_) {
			p->prev_ = it->prev_;
			p->next_ = it;
			it->prev_->next_ = p;
			it->prev_ = p;
		}*/
		else {
			p->prev_ = it->prev_;
			p->next_ = it;
			it->prev_->next_ = p;
			it->prev_ = p;
		}
	}

	this->size_++;
	return true;
}

/*!	 \fn dequeue
	 \return none
	 \param none

	 dequeue the patient who are in head_ */
void PatientQueue::dequeue() { // delete head_
	Patient* p  = this->head_;
	
	if (this->size_ > 1) { // last patient
		p->next_->prev_ = nullptr;
		this->head_ = p->next_;
	}

	this->size_--;

	delete p;

	if (size_ == 0) {
		this->head_ = nullptr;
	}

}

/*!	 \fn clear
	 \return string
	 \param none

	 clear all the patients who are in patientqueue */
void PatientQueue::clear() {
	if (this->head_ == nullptr) { return; }
	
	Patient* delptr = nullptr;
	Patient* next = nullptr;

	delptr = this->head_;
	next = delptr->next_;

	while (delptr != nullptr) {
		next = delptr->next_;
		delete delptr;
		delptr = next;
		this->size_--;
	}

	this->head_ = nullptr;
	this->tail_ = nullptr;
}

/*!	 \fn printQueue
	 \return none
	 \param none

	 print all the patients */
void PatientQueue::printQueue() {
	Patient* it = this->head_;
	while (it != nullptr) {
		cout << it->getPatientName() << "\t - priority " << it->priority_ << " - ";
		it->selectInjuryList();
		cout << endl;
		it = it->next_;
	}
}