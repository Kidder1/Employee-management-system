#include <iostream>
#include <string>
#include "boss.h"
using namespace std;

boss::boss(int ID, string name, int departmentID)
{
	this->workerID = ID;
	this->name = name;
	this->departmentID = departmentID;
}

void boss::showInfo()
{
	cout << "ID: " << this->workerID << endl << "Name: " << this->name << endl << "DepartmentID: " << this->departmentID <<
		endl <<
		"DepartmentName: " << this->getDepartmentName() << endl <<
		"Job responsibilities : Manage all affairs of the company." << endl;
}


string boss::getDepartmentName()
{
	return "boss";
}
