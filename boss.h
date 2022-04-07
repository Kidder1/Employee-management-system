#pragma once
#include <string>
#include "worker.h"

class boss :public worker
{
public:
	boss(int ID, string name, int departmentID);
	void showInfo() override;
	string getDepartmentName() override;
	~boss();
};
