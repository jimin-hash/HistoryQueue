/**	@file PriorityMap.cpp
	@author Jimin Park
	@date 2019-10-20

	Implement for PriorityMap.hpp
*/
#include "PriorityMap.hpp"

PriorityMap::PriorityMap() {
	size_ = 0;

	table = new PriorityMapNode * [20];
	for (int i = 0; i < 20; i++) {
		table[i] = nullptr;
	}
}

PriorityMap::~PriorityMap() {
	for (int i = 0; i < 20; ++i) {
		PriorityMapNode* entry = table[i];
		while (entry != NULL) {
			PriorityMapNode* prev = entry;
			entry = entry->next_;
			delete prev->value_;
			delete prev;
		}
		table[i] = nullptr;
	}
	// destroy the hash table
	delete[] table;
}

/*!	 \fn hashFunc
	 \return int
	 \param name

	 return the hash value*/
int PriorityMap::hashFunc(string name) {
	size_t length = name.length();
	char chars[20];
	strcpy_s(chars, name.c_str());
	if (length < 20) {
		for (size_t i = length; i < 20; i++) {
			chars[i] = '?';
		}
	}

	int hashval = this->altHash(chars, 20);
	int hashvalcompress = this->compress(hashval, 20);
	//cout << endl << "The final compressed alternate  value is -> " << hashvalcompress << endl;

	return hashvalcompress;
}

/*!	 \fn compress
	 \return int size
	 \param none

	 compress value is get from altHash()*/
int PriorityMap::compress(int hashval, int seed)
{
	int finalval = hashval % seed;
	return finalval;
}

/*!	 \fn altHash
	 \return int
	 \param char* charr, int size

	 calculate all the alphbets which are contain charr */
int PriorityMap::altHash(char* charr, int size)
{
	int ascii = 0;
	int final = 0;
	for (int cnt = 0; cnt < size; cnt++) {
		ascii = *(charr + cnt);
		ascii *= cnt;
		final += ascii;
		//cout << *(charr + cnt) << " = " << ascii << endl;
	}
	return final;
}

/*!	 \fn pair_push
	 \return none
	 \param int k, PriorityElements* v

	 push injury by key which was calculated by hachFunc() */
void PriorityMap::pair_push(int k, PriorityElements* v) {
	PriorityMapNode* prev = NULL;
	PriorityMapNode* curr = table[k];

	while (curr != NULL ){
		prev = curr;
		curr = curr->next_;
	}

	if (curr == NULL) {
		curr = new PriorityMapNode(k, v);
		if (prev == NULL) {
			// insert as first bucket
			table[k] = curr;
		}
		else {
			prev->next_ = curr;
		}
	}
}

/*!	 \fn readCSVFile
	 \return none
	 \param none

	  read csv file, then push to prioritymap*/
void PriorityMap::readCSVFile() {
	
	ifstream ip("project 1 priorities scores.csv");

	if (!ip.is_open()) cout << "Error: File Open" << endl;

	string name;
	string type;
	string severity;
	string timeCritical; 
	string contagious; 
	string priority;
	string line;

	while (getline(ip, name, ',')) {
		//getline(ip, name,',');
		getline(ip, type,',');
		getline(ip, severity,',');
		getline(ip, timeCritical,',');
		getline(ip, contagious,',');
		ip.ignore(1);
		getline(ip, priority, '\n');

		PriorityElements* add = new PriorityElements();

		add->name_ = name;
		add->type_ = stoi(type);
		add->severity_ = stoi(severity);
		add->timeCritical_ = stoi(timeCritical);
		add->contagious_ = stoi(contagious);
		add->priority_ = stoi(priority);

		int h = hashFunc(name);
		this->pair_push(h, add);
		
		size_++;
	}
	ip.close();
	
}

/*!	 \fn calculateNewInjury
	 \return void
	 \param PriorityElements

	 calculate priorty score */
void PriorityMap::calculateNewInjury(PriorityElements* pe) {
	int priority = (int)round((((double)pe->type_ + (double)pe->severity_) / (double)pe->timeCritical_) + pe->contagious_);
	pe->priority_ = priority;
}

/*!	 \fn newInjuryPush
	 \return none
	 \param PriorityElements

	 insert new injury to prioritymap */
void PriorityMap::newInjuryPush(PriorityElements* pe) {
	int h = hashFunc(pe->name_);
	this->pair_push(h, pe);
}

/*!	 \fn injuryExistCheck
	 \return bool
	 \param string name

	 check user insert injury is in prioritymap or not */
bool PriorityMap::injuryExistCheck(string name) {
	int h = hashFunc(name);
	PriorityMapNode* it = table[h];

	while (it != NULL) {
		if (name == it->value_->name_)
			return true;
		it = it->next_;
	}

	return false;
}

/*!	 \fn print
	 \return none
	 \param none

	 print all the injury list */
void PriorityMap::print() {
	PriorityMapNode* entry = table[0];
	for (int i = 0; i < 20; i++) {
		entry = table[i];
		cout << i;
		while (entry != NULL) {
			cout << " --> " << entry->value_->name_ << " " ;
			entry = entry->next_;
		}
		cout << endl;
	}
}

/*!	 \fn writeCSVFile
	 \return none
	 \param none

	 write new csv file */
void PriorityMap::writeCSVFile() {
	ofstream op;
	op.open("priorities scores_new version.csv");

	if (!op.is_open()) cout << "Error: File Open" << endl;

	PriorityMapNode* entry = table[0];
	for (int i = 0; i < 20; i++) {
		entry = table[i];
		while (entry != NULL) {
			op << entry->value_->name_ << "," << entry->value_->type_ << "," << entry->value_->severity_ << ","
				<< entry->value_->timeCritical_ << "," << entry->value_->contagious_ << ",," << entry->value_->priority_
				<< "\n";
			entry = entry->next_;
		}
	}

	op.close();
}