#pragma once//防止头文件包含重复
#include<iostream>
#include "worker.h"
using namespace std;
// 与用户的沟通菜单界面
// 对职工增删改查的操作
// 与文件的读写交互


class WorkerManager
{
	
public:
	WorkerManager();
	void showMenu();
	void exitSystem();
	void addEmployee();
	void delEmployee();//根据员工编号进行删除
	void saveFile();
	void showWorker();
	void modifyEmployee();
	void findEmployee();
	void sortFile();
	void emptyFile();

	//按照职工编号判断职工是否存在,若存在返回职工在数组中位置，不存在返回-1
	int IsExist(int id);

	//统计文件中现在的人数
	int getterEmployeeNum();
	void init_worker_pointsArray();

	~WorkerManager();
protected:
	//the number of employee
	int employeeNum;
	//标志文件是否为空
	bool is_FileIsEmpty;
public:
	//manage the array of the worker's point
	worker ** worker_pointsArray;
};