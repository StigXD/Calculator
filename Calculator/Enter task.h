#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <stack>
//#include "Calculations.h"


using namespace std;

struct Symbol
{
	char type;
	double value;
};

void Calculations(stack <Symbol>& stackValue, stack <Symbol>& stackOperation, Symbol& symbol)
{
	double x, y;
	x = stackValue.top().value;
	stackValue.pop();

	switch (stackOperation.top().type)
	{
	case '+':
	{
		y = stackValue.top().value;
		stackValue.pop();
		symbol.value = x + y;
		symbol.type = '0';
		stackValue.push(symbol);
		break;
	}
	//case '-':
	//case '*':
	//case '/':
	}

}

void EnterTask()
{
	cout << "Введите арифметическое выражение" << endl;
	cout << "Допустимый синтаксис выражения: (), +, -, *, /." << endl;

	char charSymbol;

	Symbol symbol;
	stack<Symbol>stackValue;
	stack<Symbol>stackOperation;

	do
	{
		charSymbol = cin.peek();

		if (charSymbol >= '0' && charSymbol <= '9')
		{
			cin >> symbol.value;
			symbol.type = '0';
			stackValue.push(symbol);
			continue;
		}
		if (charSymbol == '+' || charSymbol == '-' || charSymbol == '*' || charSymbol == '/')
		{
			symbol.type = charSymbol;
			symbol.type = 0;
			stackOperation.push(symbol);
			cin.ignore();
			continue;
		}
	} while (charSymbol == '\n');

	Calculations(stackValue, stackOperation, symbol);

	cout << "Ответ =>" << stackValue.top().value << endl;

	return;
}