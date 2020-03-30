#pragma once
#include "InjuryList.hpp"
#include "PriorityMap.hpp"
#include <iostream>
#include <string>

class Patient {
private:
	string patientName_;
public:
	InjuryList* list = new InjuryList();
	int priority_ = 0;
	int position_ = 1;
	Patient* prev_ = nullptr;
	Patient* next_ = nullptr;

	Patient();
	~Patient();

	string getPatientName();
	void setPatientName(string name);
	void addtoList(string injuryName);
	InjuryList* getInjuryList();
	void setInjuryList(InjuryList* i);
	int calcPriority(PriorityMap* pm);
	void selectInjuryList();
};