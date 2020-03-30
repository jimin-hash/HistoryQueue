#pragma once
#include "Patient.hpp"

class HistoryQueue {
public:
	HistoryQueue();
	~HistoryQueue();

	Patient* head_ = nullptr;
	Patient* tail_ = nullptr;

	void enqueue(Patient* p);
	void historyQueuePrint();
};