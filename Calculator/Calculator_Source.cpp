#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <span>
#include <Windows.h>
#include "Enter task.h"
#include "Calculations.h"
using namespace std;


void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "|		�����������		|" << endl;


	//while (true)
	//{
		EnterTask();
	//	Calculations(stackValue, stackOperation, symbol);
	//	cout << "����� =>" << stackValue.top().value << endl;
	//}

	system("pause");

}