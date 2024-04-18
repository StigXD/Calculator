#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <stack>
#include "Calculations.h"

using namespace std;

void EnterTask(stack <Symbol>& stackValue, stack <Symbol>& stackOperation, Symbol& symbol)
{
	char charSymbol;

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
			symbol.value = 0;
			stackOperation.push(symbol);
			cin.ignore();
			continue;
		}
	} while (charSymbol != '\n');

	return;
}