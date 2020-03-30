/**	@file Patient.cpp
	@author Jimin Park
	@date 2019-10-20

	Implement for Patient.hpp
*/
#include "Patient.hpp"

Patient::Patient() {
}
Patient::~Patient() {
	delete list;
}

/*!	 \fn getPatientName
	 \return string
	 \param none

	 return the patient's name */
string Patient::getPatientName(){
	return this->patientName_;
}

/*!	 \fn setPatientName
	 \return none
	 \param string name

	 set patient's name */
void Patient::setPatientName(string name){
	this->patientName_ = name;
}

/*!	 \fn addtoList
	 \return none
	 \param injuryname

	 insert to patient's injury list */
void Patient::addtoList(string injuryName) {
	list->push_back(injuryName);
}

/*!	 \fn getInjuryList
	 \return InjuryList
	 \param none

	 return patient's injurylist */
InjuryList* Patient::getInjuryList() {
	return this->list;
}

/*!	 \fn setInjuryList
	 \return none
	 \param InjuryList

	 set patient's injurylist  */
void Patient::setInjuryList(InjuryList* i) {
	this->list  = i;
}

/*!	 \fn calcPriority
	 \return none
	 \param PriorityMap

	 calculate priority
	 For combined scores any individual score below a 3 is not added to the patients overall score.*/
int Patient::calcPriority(PriorityMap* pm) {
	int priority = 0;
	int maxPriority = 0;

	Node* it = list->head_;
	PriorityMapNode* table = pm->table[0];

	while (it != nullptr) {
		for (int i = 0; i < 20; i++) {
			table = pm->table[i];
			while (table != NULL) {
				if (it->injuryTitle_ == table->value_->name_) {
					if (list->size_ > 1) { // multiple issues
						if (table->value_->priority_ >= 3) {
							priority += table->value_->priority_;
						}
						else if (table->value_->priority_ < 3) { //below a 3, pick highest
							if (table->value_->priority_ > maxPriority) {
								maxPriority = table->value_->priority_;
							}
						}
					}
					else { // one aliment
						return table->value_->priority_;
					}
				}
				table = table->next_;
			}
		}
		it = it->next_;
	}


	if (priority > 0) {
		this->priority_ = priority;
		return priority;
	}
	else { // below a 3
		this->priority_ = maxPriority;
		return maxPriority;
	}
}

/*!	 \fn selectInjuryList
	 \return none
	 \param none

	 print patient's injurylist  */
void Patient::selectInjuryList() {
	this->list->print();
}