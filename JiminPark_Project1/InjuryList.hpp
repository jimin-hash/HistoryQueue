#pragma once
#include "Node.hpp"
#include <iostream>
#include <string>

using namespace std;

class InjuryList {
private:
	//string injuryName;
public:
	size_t size_;
	Node* head_ = nullptr;
	Node* tail_ = nullptr;

	InjuryList();
	InjuryList(const InjuryList* il);
	~InjuryList();

	void push_back(string data);
	void print();
	void clear();
};