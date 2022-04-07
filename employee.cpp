#include "employee.h"
#include <iostream>
#include <string>
using namespace std;

employee::employee(int ID, string name, int departmentID)
{
	this->workerID = ID;
	this->name = name;
	this->departmentID = departmentID;
}

string employee::getDepartmentName()
{
	return "employee";
}

void employee::showInfo()
{
	cout << "ID: " << this->workerID << endl << "Name: " << this->name << endl <<
		"DepartmentID: " << this->departmentID << endl <<
		"DepartmentName:" << this->getDepartmentName() << endl <<
		"Job responsibilities: Complete the tasks assigned by the manager." << endl;
}
