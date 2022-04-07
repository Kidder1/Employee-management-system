#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <fstream>
#define FILENAME "employeeFile.txt"
using namespace std;

class worker
{
public:
	virtual void showInfo() = 0;
	virtual string getDepartmentName() = 0;
public:
	int workerID;
	string name;
	int departmentID;
};

#endif
