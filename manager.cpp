#include "manager.h"
#include <iostream>
#include <string>
using namespace std;

manager::manager(int ID, string name, int departmentID)
{
	this->workerID = ID;
	this->name = name;
	this->departmentID = departmentID;
}

void manager::showInfo()
{
	cout << "ID: " << this->workerID << endl << "Name: " << this->name << endl << "DepartmentID: " << this->departmentID <<
		endl <<
		"DepartmentName: " << this->getDepartmentName() << endl <<
		"Job responsibilities: Complete the tasks assigned by the boss and distribute the tasks to employees." << endl;
}

string manager::getDepartmentName()
{
	return "manager";
}
