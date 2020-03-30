#pragma once
#include "PriorityElements.hpp"
#include "PriorityMapNode.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

using namespace std;

class PriorityMap {
private:
public:
	PriorityMapNode **table;
	
	size_t size_;

	PriorityMap();
	~PriorityMap();

	int hashFunc(string name);
	int compress(int hashval, int seed);
	int altHash(char* charr, int size);
	void pair_push(int key, PriorityElements* value);
	void readCSVFile();
	bool injuryExistCheck(string name);
	void calculateNewInjury(PriorityElements* pe);
	void newInjuryPush(PriorityElements* pe);
	void print();
	void writeCSVFile();
};