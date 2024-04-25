#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <stack>

using namespace std;

bool Calculations(stack <Symbol> &stackValue, stack <Symbol>& stackOperation, Symbol& symbol)
{
	double x, y;
	x = stackValue.top().value;
	stackValue.pop();

	switch (stackOperation.top().type)
	{
	case '+':
		y = stackValue.top().value;
		stackValue.pop();
		symbol.value = x + y;
		symbol.type = '0';
		stackValue.push(symbol);
		stackOperation.pop();
		break;
	case '-':
		y = stackValue.top().value;
		stackValue.pop();
		symbol.value = y - x;
		symbol.type = '0';
		stackValue.push(symbol);
		stackOperation.pop();
		break;
	case '*':
		y = stackValue.top().value;
		stackValue.pop();
		symbol.value = x * y;
		symbol.type = '0';
		stackValue.push(symbol);
		stackOperation.pop();
		break;
	case '/':
		y = stackValue.top().value;
		if (x == 0)
		{
			cout << "На 0 делить нельзя!" << endl;
			return false;
		}
		else
		{
			stackValue.pop();
			symbol.value = y / x;
			symbol.type = '0';
			stackValue.push(symbol);
			stackOperation.pop();
			break;
		}
	default:
		cout << "Невозможно выполнить операцию" << endl;
		return false;
	}
	return true;
}