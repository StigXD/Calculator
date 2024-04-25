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

#undef max

#include "Start menu.h"
#include "Enter task.h"
#include "Calculations.h"
#include "Output answer.h"

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Symbol symbol;
	stack<Symbol>stackValue;
	stack<Symbol>stackOperation;

	char enterChoice;

	while (StartMenu())
	{
		while (true)
		{
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			stackValue = stack<Symbol>();
			stackOperation = stack<Symbol>();

			cout << "Введите арифметическую операцию:" << endl
				<< "=> ";

			if (!EnterTask(stackValue, stackOperation, symbol))
			{
				cout << endl << "Выполнить следующую операцию?" << endl
					<< "Y/N =>";
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin >> enterChoice;
				if (enterChoice == 'N' || enterChoice == 'n' || enterChoice == '0')
					break;
				else
				{
					system("cls");
					continue;
				}
			}

			while (stackOperation.size() != 0)
			{
				if (!Calculations(stackValue, stackOperation, symbol))
					break;
			}
			Answer(stackValue);

			cout << "Выполнить следующую операцию?" << endl
				<< "Y/N =>";
			cin >> enterChoice;
			if (enterChoice == 'N' || enterChoice == 'n' || enterChoice == '0')
				break;

			system("cls");
		}
	}

	system("pause");
}
