#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <stack>

using namespace std;

void Calculations(stack <Symbol> &stackValue, stack <Symbol>& stackOperation, Symbol& symbol)
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
		break;
	case '-':
		y = stackValue.top().value;
		stackValue.pop();
		symbol.value = y - x;
		symbol.type = '0';
		stackValue.push(symbol);
		break;
	case '*':
		y = stackValue.top().value;
		stackValue.pop();
		symbol.value = x * y;
		symbol.type = '0';
		stackValue.push(symbol);
		break;
	case '/':
		y = stackValue.top().value;
		stackValue.pop();
		symbol.value = y / x;
		symbol.type = '0';
		stackValue.push(symbol);
		break;
	}

}