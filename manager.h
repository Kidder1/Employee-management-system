#pragma once
#include <string>
#include "worker.h"
using namespace std;

class manager : public worker
{
public:
	manager(int ID, string name, int departmentID);
	void showInfo() override;
	string getDepartmentName() override;
};
