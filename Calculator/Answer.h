#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <stack>

using namespace std;

void Answer(stack <Symbol>& stackValue)
{
	cout << "����� =>" << stackValue.top().value << endl;
}
