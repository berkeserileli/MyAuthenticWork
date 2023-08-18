#include <iostream>
using std::string;
#include<vector>


class Person {
protected:
	string personName, personSurname;
	int personID;
public:
	Person(string name, string surname,int ID) {
		personName = name;
		personSurname = surname;
		personID = ID;
	}
	void printInfo() {
		std::cout << "Name: " << personName << std::endl;
		std::cout << "Surname: " << personSurname << std::endl;
		std::cout << "ID: " << personID << std::endl;
	}
	string getPersonName() { return personName; };
	string getPersonSurname() { return personSurname; };
	int getPersonID() { return personID; };
};



class Patient:public Person{
private:
	int patientSituation;
public:
	Patient(string name, string surname, int ID,int situation) :Person(name, surname,ID) {
		patientSituation = situation;
	};
	void setSituation(int situation) { patientSituation = situation;};
	int getSituation(){return patientSituation; };
	void printInfo(){
		Person::printInfo();
		std::cout << "Situation: " <<getSituation() << std::endl;
	}
	int getPatientSituation() { return patientSituation; };
	
};

class Nurse:public Person{
private:
	int cntDiagnosed;
public:
	Nurse(string name, string surname, int ID,int diagnosed):Person(name,surname,ID){
		cntDiagnosed = diagnosed;
	};
	int getCntDiagnosed() { return cntDiagnosed; };
	void diagnose(Patient* p) {
		
		if (p->getPatientSituation() >= 2) {
			std::cout << "Doctor needed" << std::endl;
		}
		else {
			std::cout << "Assisted." << std::endl;
			cntDiagnosed++;
		}
	}
		void printInfo(){
			Person::printInfo();
			std::cout << "Diagnose: " << getCntDiagnosed()<<std::endl;
		}
};

class Doctor :public Person {
private:
	int cntServed;
	public:
		Doctor(string name, string surname, int ID,int served):Person(name,surname,ID){
			cntServed = served;
		};
		int getServed() { return cntServed; };
		int dead_count = 0;
		int rescued_count = 0;
	
		void result(Patient*p) {
			if (p->getPatientSituation() > 3) {
				std::cout << "Dead!" << std::endl;
				dead_count += 1;
			}
			else {
				std::cout << "Patient was rescued!" << std::endl;
				rescued_count += 1;
				cntServed++;
			}
		}
			void printInfo() {
				Person::printInfo();
				std::cout << "Served: " <<cntServed<< std::endl;
				std::cout << "Rescued patients: " << rescued_count << std::endl;
				std::cout << "Dead patients: " << dead_count << std::endl;
		}
};

void addPatient() {
	string name1;
	string surname1;
	int ID1;
	int situation1;
	std::cout << "Enter the name of new patient:  " << std::endl;
	std::cin >> name1;
	std::cout << "Enter the surname of new patient" << std::endl;
	std::cin >> surname1;
	std::cout << "Enter the ID of new patient: " << std::endl;
	std::cin >> ID1;
	std::cout << "Enter the situation of new patient: " << std::endl;
	std::cin >> situation1;
	Patient* newPatient = new Patient(name1, surname1, ID1, situation1);
	std::cout << "New patient has been added on the list!" << std::endl;
	delete[]&ID1;
	delete[]&situation1;

}


