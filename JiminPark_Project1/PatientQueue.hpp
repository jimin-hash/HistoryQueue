#pragma once
#include "Patient.hpp"
#include "PriorityMap.hpp"
#include "HistoryQueue.hpp"

class PatientQueue {
private:
	int size_;
public:
	PriorityMap* pm = new PriorityMap();
	//HistoryQueue* hq = new HistoryQueue();

	Patient* head_ = nullptr;
	Patient* tail_ = nullptr;

	PatientQueue();
	~PatientQueue();

	int getSize();
	bool addPatient(Patient* p);
	void dequeue();
	void clear();
	void printQueue();
};