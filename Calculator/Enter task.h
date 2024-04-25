#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <stack>
#include "OperationPriority.h"
#include "Calculations.h"
using namespace std;

bool EnterTask(stack <Symbol>& stackValue, stack <Symbol>& stackOperation, Symbol& symbol)
{
	char charSymbol;
	bool isNegative = true;

	while (true)
	{
		charSymbol = cin.peek();
		if (charSymbol == '\n')
			break;
		if (charSymbol == ' ')
		{
			cin.ignore();
			continue;
		}
		if (charSymbol >= '0' && charSymbol <= '9'|| charSymbol == '-' && isNegative)
		{
			cin >> symbol.value;
			symbol.type = '0';
			stackValue.push(symbol);
			isNegative = false;
			continue;
		}
		if (charSymbol == '+' || charSymbol == '-' && !isNegative || charSymbol == '*' || charSymbol == '/')
		{
			if (stackOperation.size()==0)
			{
				symbol.type = charSymbol;
				symbol.value = 0;
				stackOperation.push(symbol);
				cin.ignore();
				continue;
			}
			if (stackValue.size() != 0 && stackOperation.size() != 0 && GetPriority(charSymbol)>GetPriority(stackOperation.top().type))
			{
				symbol.type = charSymbol;
				symbol.value = 0;
				stackOperation.push(symbol);
				cin.ignore();
				continue;
			}
			if (stackValue.size() != 0 && stackOperation.size() != 0 && GetPriority(charSymbol) <= GetPriority(stackOperation.top().type))
			{
				if (!Calculations(stackValue, stackOperation, symbol))
					break;
				continue;
			}
		}
		if (charSymbol == '(')
		{
			symbol.type = charSymbol;
			symbol.value = 0;
			stackOperation.push(symbol);
			cin.ignore();
			isNegative = true;
			continue;
		}
		if (charSymbol == ')')
		{
			while (stackOperation.top().type != '(')
			{
				if (!Calculations(stackValue, stackOperation, symbol))
					break;
				continue;
			}
			stackOperation.pop();
			cin.ignore();
			continue;
		}
		else
		{
			cout << "Неверное выражение!" << endl;
			return false;
		}
	}
	return true;
}