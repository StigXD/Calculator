#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <span>
#include <Windows.h>
#include <limits>
using namespace std;

struct Symbol
{
	char type;
	double value;
};

#include "Start menu.h"
#include "Enter task.h"
#include "Calculations.h"
#include "Output answer.h"

#undef max

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Symbol symbol;
	stack<Symbol>stackValue;
	stack<Symbol>stackOperation;

	while (StartMenu())
	{
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		cout << "Введите арифметическую операцию:" << endl
			<< "=> ";
		
		EnterTask(stackValue, stackOperation, symbol);
		
		while(stackOperation.size() !=0)
		{
			if (!Calculations(stackValue, stackOperation, symbol))
				break;
		}
		Answer(stackValue);

		char enterChoice;
		cout << "Выполнить следующую операцию?" << endl
			<< "Y/N =>";
		cin >> enterChoice;
		if (enterChoice == 'N' || enterChoice == 'n' || enterChoice == '0')
			return;

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		system("cls");
	}
	system("pause");
}
