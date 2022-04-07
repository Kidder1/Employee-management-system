#include <iostream>
#include "wokerManager.h"
#include "employee.h"
using namespace std;

int main()
{
	WorkerManager workerManager;
	int choice;
	cout << "The number of employees is: " << workerManager.getterEmployeeNum() << endl;
	while (1)
	{
		workerManager.showMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 0: //exit system
			workerManager.exitSystem();
			break;
		case 1: //add worker
			workerManager.addEmployee();
			break;
		case 2: //show worker info
			workerManager.showWorker();
			break;
		case 3: //delete worker
			workerManager.delEmployee();
			break;
		case 4: //modify worker
			workerManager.modifyEmployee();
			break;
		case 5: //find worker
			workerManager.findEmployee();
			break;
		case 6: //sort worker
			workerManager.sortFile();
			break;
		case 7: //empty file
			workerManager.emptyFile();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}
