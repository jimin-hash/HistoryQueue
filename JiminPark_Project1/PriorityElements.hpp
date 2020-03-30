#pragma once
#include <iostream>
#include <string>

using namespace std;

class PriorityElements {
public:
	string name_;
	int type_ = 0; // Ailment-1/Injury-2
	int severity_ = 0; // severity 1 to 5
	int timeCritical_ = 0; // time criticality 1 - 10
	int contagious_ = 0; // Contagious Highly - 4 - yes-1 No-0
	int priority_ = 0;

	PriorityElements* next_ = nullptr;
};