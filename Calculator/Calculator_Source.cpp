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

	cout << "|		Калькулятор		|" << endl;


	//while (true)
	//{
		EnterTask();
	//	Calculations(stackValue, stackOperation, symbol);
	//	cout << "Ответ =>" << stackValue.top().value << endl;
	//}

	system("pause");

}