#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>

using namespace std;

void EnterTask(string &perform)
{
	cout << "������� �������������� ���������" << endl;
	cout << "���������� ��������� ���������: (), +, -, *, /." << endl;

	getline(cin, perform);

	return;
}