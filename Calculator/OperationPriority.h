#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <stack>

using namespace std;

int GetPriority(char charSymbol)
{
	if (charSymbol == '+' || charSymbol == '-')
		return 1;
	if (charSymbol == '*' || charSymbol == '/')
		return 2;
	return 0;
}