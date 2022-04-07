#include "wokerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//file not exits
	if (!ifs.is_open())
	{
		cout << "ERROR! EmployeeFile not exits!" << endl;
		this->employeeNum = 0;
		this->worker_pointsArray = NULL;
		this->is_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//file exits but is empty
	char x;
	ifs >> x;
	if (ifs.eof())
	{
		cout << "EmployeeFile  exits but is empty" << endl;
		this->employeeNum = 0;
		this->worker_pointsArray = NULL;
		this->is_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//初始化的时候将文件的人存入文件,并且初始化相应数据
	int num = this->getterEmployeeNum();
	this->employeeNum = num;

	//根据职工数创建数组
	this->worker_pointsArray = new worker*[this->employeeNum]; //不创建数组的话,二重指针没有实际意义
	//初始化职工
	this->init_worker_pointsArray();
}

void WorkerManager::showMenu()
{
	cout << "****************************************************************" << endl;
	cout << "*********  Welcome to the employee management system! **********" << endl;
	cout << "*************  0. Exit the management program.        **********" << endl;
	cout << "*************  1. Add employee information.           **********" << endl;
	cout << "*************  2. Display employee information.       **********" << endl;
	cout << "*************  3. Delete resigned employees.          **********" << endl;
	cout << "*************  4. Modify employee information.        **********" << endl;
	cout << "*************  5. Find employee information.          **********" << endl;
	cout << "*************  6. Sort by number.                     **********" << endl;
	cout << "*************  7. Empty all documents.                **********" << endl;
	cout << "****************************************************************" << endl;
	cout << endl;
}

void WorkerManager::exitSystem()
{
	cout << "Welcome to use next time!" << endl;
}

void WorkerManager::addEmployee()
{
	int addnum; //添加的人数
	cout << "How many memangers do you want to add ?: ";
	cin >> addnum;
	if (addnum > 0)
	{
		int newSpace = this->employeeNum + addnum;
		worker** new_worker_points_array = new worker*[newSpace]; //new的数组接受所有不同类型员工对象的地址

		//迁移原有数据到新的里面,保持数据的连续性
		if (worker_pointsArray != NULL)
		{
			for (int i = 0; i < this->employeeNum; i++)
			{
				new_worker_points_array[i] = this->worker_pointsArray[i];
			}
		}

		//创建新的员工
		for (int i = 0; i < addnum; i++)
		{
			int workerID;
			string name;
			int departmentID;

			cout << "Enter the information of the new employee according to the prompt." << endl;

			cout << "Name: ";
			cin >> name;
			// cin.sync();

			cout << "Current employee ID:" << this->employeeNum;
			cout << " New ID: ";
			// cin.sync();
			cin >> workerID;

			cout << "DepartmentID: ";
			// cin.sync();
			cin >> departmentID;

			//创建员工对象
			worker* worker = NULL; //存储新员工的地址
			switch (departmentID)
			{
			case 1:
				worker = new employee(workerID, name, 1);
				break;
			case 2:
				worker = new manager(workerID, name, 2);
				break;
			case 3:
				worker = new boss(workerID, name, 3);
				break;
			default:
				break;
			}
			new_worker_points_array[this->employeeNum] = worker;

			//更新元素个数
			this->employeeNum++;
		}

		//释放原来旧的空间
		delete[] this->worker_pointsArray;

		//更改新的指针指向
		this->worker_pointsArray = new_worker_points_array;

		//更新文件为空标志
		this->is_FileIsEmpty = false;

		cout << "成功添加" << addnum << "名新职工！" << endl;

		//test codes
		// cout << this->worker_pointsArray[0]->workerID << this->worker_pointsArray[0]->name;
		// cout << this->worker_pointsArray[1]->workerID << this->worker_pointsArray[1]->name;

		//save employee in file
		this->saveFile();
	}
	else
	{
		cout << "Wrong input!" << endl;
	}
}

void WorkerManager::delEmployee()
{
	int position{};
	//判断文件是否为空
	if (this->is_FileIsEmpty)
	{
		cout << "The file not exits." << endl;
	}
	else
	{
		int id;
		cout << "Enter the id that you want to delete: ";
		cin >> id;
		position = this->IsExist(id);
		if (position != 0)
		{
			for (int i = 0; i < position; i++)
			{
				this->worker_pointsArray[i] = this->worker_pointsArray[i + 1];
			}
			this->saveFile();
			this->employeeNum--;
			cout << "Delete successfully." << endl;
		}
		else
			return;
	}
}

void WorkerManager::modifyEmployee()
{
	if (this->is_FileIsEmpty)
	{
		cout << "The file is empty!" << endl;
	}
	else
	{
		int position;
		int id;
		cout << "Enter the id of employee modified: ";
		cin >> id;
		position = this->IsExist(id);

		int workerID;
		string name;
		int departmentID;
		cout << "Enter the new information according to the prompt." << endl;

		cout << "Name: ";
		cin >> name;
		// cin.sync();

		cout << "New ID: ";
		// cin.sync();
		cin >> workerID;

		cout << "DepartmentID: ";
		// cin.sync();
		cin >> departmentID;

		//创建员工对象
		worker* worker = NULL; //存储新员工的地址
		switch (departmentID)
		{
		case 1:
			worker = new employee(workerID, name, 1);
			break;
		case 2:
			worker = new manager(workerID, name, 2);
			break;
		case 3:
			worker = new boss(workerID, name, 3);
			break;
		default:
			break;
		}
		this->worker_pointsArray[position - 1] = worker;
		this->saveFile();
	}
}

int WorkerManager::IsExist(int id)
{
	int index{};
	while (1)
	{
		if (this->worker_pointsArray[index]->workerID == id)
		{
			//cout << "This employee's position is " << index + 1 << " ." << endl;
			return index + 1;
		}
		else
		{
			if (index + 1 == this->employeeNum) //比较人数,如果遍历完的话,则这个人不存在
			{
				cout << "ERROR! this employee not exits" << endl;
				return 0;
			}
			else
			{
				index++;
			}
		}
	}
}

void WorkerManager::saveFile()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->employeeNum; i++)
	{
		ofs << "ID:" << this->worker_pointsArray[i]->workerID << endl
			<< "Name:" << this->worker_pointsArray[i]->name << endl
			<< "DepartmentID:" << this->worker_pointsArray[i]->departmentID << endl
			<< "DepartmentName:" << this->worker_pointsArray[i]->getDepartmentName() << endl << endl;
	}
	ofs.close();
}

void WorkerManager::findEmployee()
{
	int position{};
	if (is_FileIsEmpty)
	{
		cout << "The file is empty!" << endl;
	}
	else
	{
		cout << "1. Use id to find." << endl;
		cout << "2. Use name to find." << endl;
		cout << "Please input the mean which you want to use to find: ";

		int choice;
		cin >> choice;
		if (choice == 1)
		{
			int id;
			while (1)
			{
				cout << "Input the id: ";
				cin >> id;
				if (id <= 0)//正则表达式检测输入
				{
					cout << "Error input! Please input again." << endl;
					continue;
				}
				else
				{
					break;
				}
			}

			position = IsExist(id);
			if(position)
			{
				cout << "ID: " << this->worker_pointsArray[position - 1]->workerID << endl << "Name: " << this->
					worker_pointsArray[position - 1]->name
					<< endl
					<< "DepartmentID: " << this->worker_pointsArray[position - 1]->departmentID << endl
					<< "DepartmentName:" << this->worker_pointsArray[position - 1]->getDepartmentName() << endl << endl;
			}
			else
			{
				return;
			}
			
		}
		if (choice == 2)
		{
			int index{};
			string name;
			cout << "Input the name: ";
			cin >> name;
			for (int i = 0; i < this->employeeNum; i++)
			{
				if (this->worker_pointsArray[i]->name == name)
				{
					cout << "ID: " << this->worker_pointsArray[index]->workerID << endl << "Name: " << this->
						worker_pointsArray[index]->name
						<< endl
						<< "DepartmentID: " << this->worker_pointsArray[index]->departmentID << endl
						<< "DepartmentName:" << this->worker_pointsArray[index]->getDepartmentName() << endl << endl;
					break;
				}
				else
				{
					if(index+1 == this->employeeNum)
					{
						cout << "No one was found." << endl;
						break;
					}
					else 
						index++;
				}
			}
		}
	}
}

void WorkerManager::sortFile()
{
	if(this->is_FileIsEmpty)
	{
		cout << "The file is empty." << endl;
	}
	else
	{
		cout << "1. Ascending by ID." << endl;
		cout << "2. Descending by ID." << endl;
		cout << "Please input the mean which you want to use to sort:";

		int choice{};
		cin >> choice;

		for (int i = 0; i < this->employeeNum; i++)
		{
			int minOrMax = i;
			for (int j = i + 1; j < employeeNum; j++)
			{
				if (choice == 1) //升序
				{
					if (this->worker_pointsArray[minOrMax]->workerID > this->worker_pointsArray[j]->workerID)
					{
						minOrMax = j;
					}
				}
				else  //降序
				{
					if (this->worker_pointsArray[minOrMax]->workerID < this->worker_pointsArray[j]->workerID)
					{
						minOrMax = j;
					}
				}
			}

			if (i != minOrMax)
			{
				worker* temp = worker_pointsArray[i];
				worker_pointsArray[i] = worker_pointsArray[minOrMax];
				worker_pointsArray[minOrMax] = temp;
			}

			cout << "Sorting succeeded. The result after sorting is：" << endl;
			this->saveFile();
			this->showWorker();
		}

	}
}


void WorkerManager::emptyFile()
{
	int choice;
	cout << "1. Confirm" << endl;
	cout << "2. Cancel" << endl;
	cout << "Confirm emptying?: ";
	cin >> choice;
	if(choice == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
	}
	else if(choice == 2)
	{
		return;
	}
	if(this->worker_pointsArray != NULL)
	{
		//释放堆区空间和还原指针指向空
		for(int i = 0; i < this->employeeNum; i++)
		{
			delete[] this->worker_pointsArray[i];
		}
		this->employeeNum = 0;
		this->worker_pointsArray = NULL;
		this->is_FileIsEmpty = true;
	}
	cout << "Cleared successfully!" << endl;

}

int WorkerManager::getterEmployeeNum()
{
	int num{};
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string ID;
	string name;
	string departmentID;
	string departmentName;

	while (ifs >> ID >> name >> departmentID >> departmentName)
	{
		num++;
	}
	ifs.close();
	return num;
}

void WorkerManager::init_worker_pointsArray()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	string ID;
	string name;
	string departmentID;
	string departmentName;
	stringstream sstream;
	int index{}; //数组的下标
	while (ifs >> ID >> name >> departmentID >> departmentName)
	{
		int tempID{}; //临时存储departmentID值的
		int temp_departmentID;
		string tempName;

		//获取参数的具体名称
		//ID
		sstream << ID.substr(3);
		sstream >> tempID;
		//sstream的清除操作
		sstream.str(" "); //将sstream中的值清空
		sstream.clear(); //将sstream中的错误标志位清空

		//name
		tempName = name.substr(5);

		//departmentID
		sstream << departmentID.substr(13);
		sstream >> temp_departmentID;
		//sstream的清除操作
		sstream.str(" "); //将sstream中的值清空
		sstream.clear(); //将sstream中的错误标志位清空

		//store the employee from file to arrays
		worker* worker = NULL;
		if (temp_departmentID == 1)
		{
			worker = new employee(tempID, tempName, temp_departmentID);
		}
		if (temp_departmentID == 2)
		{
			worker = new manager(tempID, tempName, temp_departmentID);
		}
		if (temp_departmentID == 3)
		{
			worker = new boss(tempID, tempName, temp_departmentID);
		}

		//将对象的地址存入数组
		this->worker_pointsArray[index] = worker;
		// //testcode
		// cout << index;
		// cout << "ID: " << this->worker_pointsArray[index]->workerID << endl << "Name: " << this->worker_pointsArray[index]->name << endl <<
		// 	"DepartmentID: " << this->worker_pointsArray[index]->departmentID << endl <<
		// 	"DepartmentName: " << this->worker_pointsArray[index]->getDepartmentName() << endl;
		index++;
	}
}

void WorkerManager::showWorker()
{
	int num = this->getterEmployeeNum();
	this->init_worker_pointsArray();
	for (int i = 0; i < num; i++)
	{
		cout << "ID: " << this->worker_pointsArray[i]->workerID << endl << "Name: " << this->worker_pointsArray[i]->name
			<< endl
			<< "DepartmentID: " << this->worker_pointsArray[i]->departmentID << endl
			<< "DepartmentName:" << this->worker_pointsArray[i]->getDepartmentName() << endl << endl;
	}
}

WorkerManager::~WorkerManager()
{
	if (worker_pointsArray != NULL)
	{
		delete worker_pointsArray;
	}
}
