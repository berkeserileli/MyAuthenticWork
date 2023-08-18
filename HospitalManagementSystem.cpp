#include "HospitalManagementSystem.h"
#include <time.h>



int main() {
	srand(time(NULL));
	Patient *patient1 = new Patient("Fatih", "Dursun", 1469,rand()%5);
	patient1->printInfo();
	Nurse *nurse1= new Nurse("Nursema", "Sumbul", 2742,rand()%5);
	nurse1->diagnose(patient1);
	nurse1->printInfo();
	Doctor* doctor1 = new Doctor("Mustafa", "Keser", 3366,rand()%3);
	doctor1->result(patient1);
	doctor1->printInfo();
	addPatient();






}