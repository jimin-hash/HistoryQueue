/**	@file TrigeMain.cpp
	@author Jimin Park
	@date 2019-10-20

	Create a hospital triage system using a Priority 
*/
#include "PriorityMap.hpp"
#include "Patient.hpp"
#include "PatientQueue.hpp"
#include "HistoryQueue.hpp"
#include <iostream>
#include <locale>
#include <iomanip>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace std;
void addPatient(PatientQueue* pq, HistoryQueue* hq);
void menuPrint(PatientQueue* pq, HistoryQueue* hq);
bool patientNameCheck(PatientQueue* pq, string name);
void proceNextPatient(PatientQueue* pq, HistoryQueue* hq);
void reviewCurrentQueue(PatientQueue* pq, HistoryQueue* hq);
void historyQueue(PatientQueue* pq, HistoryQueue* hq);
void writeCSVPriorityMap(PatientQueue* pq, HistoryQueue* hq);
void clearPatients(PatientQueue* pq, HistoryQueue* hq);

/*!	 \fn clearPatients
	 \return none
	 \param PatientQueue* pq, HistoryQueue* hq

	'C': Clear the Patient Priority Queue  */
void clearPatients(PatientQueue* pq, HistoryQueue* hq){
	cin.ignore();
	pq->clear();
	menuPrint(pq, hq);
}

/*!	 \fn writeCSVPriorityMap
	 \return none
	 \param PatientQueue* pq, HistoryQueue* hq

	'S': Save priorityMap to csv file  */
void writeCSVPriorityMap(PatientQueue* pq, HistoryQueue* hq) {
	cin.ignore();

	pq->pm->writeCSVFile();
	
	menuPrint(pq,hq);
}

/*!	 \fn historyQueue
	 \return none
	 \param PatientQueue* pq, HistoryQueue* hq

	'H': Print the history of the Queue (Oldest first)  
	when user process patient, that patient enqueue to historyqueue*/
void historyQueue(PatientQueue* pq, HistoryQueue* hq) {
	cin.ignore();

	hq->historyQueuePrint();

	menuPrint(pq, hq);
}

/*!	 \fn reviewCurrentQueue
	 \return none
	 \param PatientQueue* pq, HistoryQueue* hq

	'R': Review the current queue */
void reviewCurrentQueue(PatientQueue* pq, HistoryQueue* hq) {
	cin.ignore();

	if (pq->getSize() == 0) {
		cout << "We don't have patients in Patient Queue." << endl;
	}
	else {
		pq->printQueue();
	}

	menuPrint(pq, hq);
}

/*!	 \fn proceNextPatient
	 \return none
	 \param PatientQueue* pq, HistoryQueue* hq

	'P': Process the next patient in the queue
	delete patient on head_ which has highest priority*/
void proceNextPatient(PatientQueue* pq, HistoryQueue* hq) {
	cin.ignore();
	
	Patient* ph = new Patient(*pq->head_);
	ph->prev_ = nullptr;
	ph->next_ = nullptr;
	
	InjuryList* il = new InjuryList(pq->head_->getInjuryList());
	ph->setInjuryList(il);
	
	hq->enqueue(ph);

	cout << "Patient: " << pq->head_->getPatientName() << " moved to patient room" << endl;
	pq->dequeue();

	if (pq->getSize() > 0)
		cout << "Next patient in queue : " << pq->head_->getPatientName() << " with Priority " << pq->head_->priority_ << endl;
	else
		cout << "Doesn't have patients in queue any more" << endl;
	menuPrint(pq, hq);
}

/*!	 \fn patientNameCheck
	 \return none
	 \param PatientQueue* pq, string name

	check user input name is already in queue or not*/
bool patientNameCheck(PatientQueue* pq, string name){
	locale loc;
	string nameInQueue = "";

	//for (size_t i = 0; i < name.length(); ++i)
	//	cout << toupper(name[i], loc);

	Patient* it = pq->head_;
	while (it != nullptr)
	{
		nameInQueue = it->getPatientName();
		for (size_t i = 0; i < nameInQueue.length(); ++i)
			cout << toupper(nameInQueue[i], loc);

		if (name == nameInQueue) {
			cout << endl;
			cout << it->getPatientName() << "patient already existed. ";
			return true;
		}
		it = it->next_;
	}

	return false;
}

/*!	 \fn addPatient
	 \return none
	 \param PatientQueue* pq, HistoryQueue* hq

	'A' : Add a new patient to the queue*/
void addPatient(PatientQueue* pq, HistoryQueue* hq) {
	cin.ignore();

	string name, injuryName;
	Patient* p = new Patient();

	bool existAilmentYN = true;
	bool existNameYN = true;

	while (existNameYN) {
		cout << "Enter the Patient Name: ";
		getline(cin, name);

		existNameYN = patientNameCheck(pq, name);
	}
	p->setPatientName(name);

	while (1) { 
		cout << "\nEnter the Injury or Illness name." <<endl << "If you want to stop to insert injury, enter the 'Q'" <<endl;
		getline(cin, injuryName);

		if (injuryName == "q" || injuryName == "Q")
			break;

		existAilmentYN = pq->pm->injuryExistCheck(injuryName);

		if (existAilmentYN == false) { // not exist in priorityMap
			int type = 0; // Ailment-1/Injury-2
			int severity = 0; // severity 1 to 5
			int timeCritical = 0; // time criticality 1 - 10
			int contagious = 0; // Contagious Highly - 4 - yes-1 No-0

			cout << "------ Insert new Ailment/Injury ------" << endl;
			do {
				cout << "Enter the type(Ailment - 1 / Injury - 2)" << endl;
				cin >> type;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			} while (!(type == 1 || type == 2));

			do {
				cout << "Enter the severity(1 to 5)" << endl;
				cin >> severity;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			} while (!(severity > 0 || severity < 6));

			do {
				cout << "Enter the timeCritical(1 to 10)" << endl;
				cin >> timeCritical;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			} while (!(timeCritical > 0 || timeCritical < 11));

			do {
				cout << "Enter the contagious(Highly - 4, yes - 1, No - 0)" << endl;
				cin >> contagious;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
			} while (!(contagious == 0 || contagious == 1 || contagious == 4));

			PriorityElements* pe = new PriorityElements();
			pe->name_ = injuryName;
			pe->type_ = type;
			pe->severity_ = severity;
			pe->timeCritical_ = timeCritical;
			pe->contagious_ = contagious;

			pq->pm->calculateNewInjury(pe); // calculate proprity
			pq->pm->newInjuryPush(pe);
			cin.ignore();
		}
		existAilmentYN = true;

		p->addtoList(injuryName);
	}

	pq->addPatient(p);

	cout << "Patient: " << p->getPatientName() << " add to queue with priority " << p->priority_ << " in position " << p->position_ << endl;

	menuPrint(pq, hq);
}

/*!	 \fn menuPrint
	 \return none
	 \param PatientQueue* pq, HistoryQueue* hq

	print menu for insert a selection*/
void menuPrint(PatientQueue* pq, HistoryQueue* hq) {
	cin.clear();

	cout << endl << endl;
	cout << "************************************************" <<endl;
	cout << "A Add a new patient to the queue" << endl;
	cout << "P Process the next patient in the queue" << endl;
	cout << "R Review the current queue " << endl;
	cout << "H Print the history of the Queue (Oldest first) " << endl;
	cout << "C Clear the Patient Priority Queue " << endl;
	cout << "S Save prioritiMap to csv file " << endl;
	cout << "X Exit the system" << endl;
	cout << "************************************************" << endl;


	int ch = 0;
	while (!(toupper(ch) == 'X' || toupper(ch) == 'S' || toupper(ch) == 'C' || toupper(ch) == 'H' || toupper(ch) == 'R' || toupper(ch) == 'P' || toupper(ch) == 'A'))
	{
		cout << "Please make a selection : ";

		if ((ch = getchar()) != EOF) {
			if (toupper(ch) == 'A')
			{
				addPatient(pq, hq);
			}
			else if (toupper(ch) == 'P')
			{
				proceNextPatient(pq, hq);
			}
			else if (toupper(ch) == 'R')
			{
				reviewCurrentQueue(pq, hq);
			}
			else if (toupper(ch) == 'H')
			{
				historyQueue(pq, hq);
			}
			else if (toupper(ch) == 'C')
			{
				clearPatients(pq, hq);
			}
			else if (toupper(ch) == 'S')
			{
				writeCSVPriorityMap(pq, hq);
			}
			else if (toupper(ch) == 'X')
			{
				cout << "Thank you for using Triage system." << endl;
			}
			else {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
	} 
}

int main() {
	cout << "Welcome to the Fanshawe EMERG Triage System\n" << endl;

#if defined(_DEBUG)
	// gets the state of the debug flags
	int dbgFlags = ::_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	// bitwise or - check block integrity on every memory call
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	// don't always remove the blocks on delete
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	// check for memory leaks at process termination
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	// modifies the state of the debug flags
	_CrtSetDbgFlag(dbgFlags);
#endif

	PatientQueue* pq = new PatientQueue();
	HistoryQueue* hq = new HistoryQueue();

	menuPrint(pq, hq);
	delete pq;
	delete hq;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	return 0;
}