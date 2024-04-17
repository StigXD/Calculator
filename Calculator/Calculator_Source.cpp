#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <span>
#include <Windows.h>
#include "Menu.h"
using namespace std;

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "|		Калькулятор		|" << endl;

	Menu();

	system("pause");

}