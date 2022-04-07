#pragma once//��ֹͷ�ļ������ظ�
#include<iostream>
#include "worker.h"
using namespace std;
// ���û��Ĺ�ͨ�˵�����
// ��ְ����ɾ�Ĳ�Ĳ���
// ���ļ��Ķ�д����


class WorkerManager
{
	
public:
	WorkerManager();
	void showMenu();
	void exitSystem();
	void addEmployee();
	void delEmployee();//����Ա����Ž���ɾ��
	void saveFile();
	void showWorker();
	void modifyEmployee();
	void findEmployee();
	void sortFile();
	void emptyFile();

	//����ְ������ж�ְ���Ƿ����,�����ڷ���ְ����������λ�ã������ڷ���-1
	int IsExist(int id);

	//ͳ���ļ������ڵ�����
	int getterEmployeeNum();
	void init_worker_pointsArray();

	~WorkerManager();
protected:
	//the number of employee
	int employeeNum;
	//��־�ļ��Ƿ�Ϊ��
	bool is_FileIsEmpty;
public:
	//manage the array of the worker's point
	worker ** worker_pointsArray;
};