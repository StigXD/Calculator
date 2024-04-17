#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>

using namespace std;

void EnterTask(string &perform)
{
	cout << "Введите арифметическое выражение" << endl;
	cout << "Допустимый синтаксис выражения: (), +, -, *, /." << endl;

	getline(cin, perform);

	return;
}