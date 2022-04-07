#pragma once
#include <string>
#include "worker.h"
using namespace std;

class employee : public worker
{
public:
	employee(int ID, string name, int departmentID);
	void showInfo() override;
	string getDepartmentName() override;
};
