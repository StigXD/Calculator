#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <span>
#include <Windows.h>
using namespace std;

struct Symbol
{
	char type;
	double value;
};

#include "Enter task.h"
#include "Calculations.h"
#include "Answer.h"

inline void CinFlush()
{
	while (cin.get() != '\n') 
		cin.ignore();
	return;
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Symbol symbol;
	stack<Symbol>stackValue;
	stack<Symbol>stackOperation;

	while (true)
	{
		cout << "|		Калькулятор		|" << endl;
		cout << "Введите арифметическое выражение" << endl;
		cout << "Допустимый синтаксис выражения: (), +, -, *, /." << endl;

		EnterTask(stackValue, stackOperation, symbol);
		Calculations(stackValue, stackOperation, symbol);
		Answer(stackValue);

		char enterChoice;
		cout << "Выполнить следующую операцию?" << endl
			<< "Y/N =>";
		cin >> enterChoice;
		if (enterChoice == 'N' || enterChoice == 'n')
			return;

		//cin.sync();
		//cin.ignore();
		CinFlush();
		system("cls");
	}
	system("pause");
}