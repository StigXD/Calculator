#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

bool StartMenu()
{
	while(true)
	{
		cout << "_________________________________________________" << endl;
		cout << "|		  Калькулятор			|" << endl;
		cout << "|_______________________________________________|" << endl;
		cout << "|						|" << endl;
		cout << "| 1. Начать вычисления				|" << endl;
		cout << "| 2. Инфо					|" << endl;
		cout << "| 0. Выход					|" << endl;
		cout << "|_______________________________________________|" << endl << endl;

		int choice;
		cout << "Выберите пункт меню:" << endl << "=> ";
		cin >> choice;
		switch (choice)
		{
		case 0:
			return false;
		case 1:
			return true;
		case 2:
			cout << "*************************************************************************" << endl;
			cout << "* В калькуляторе реализовано:						*" << endl;
			cout << "* '+' - сложение;							*" << endl;
			cout << "* '-' - вычитание;							*" << endl;
			cout << "* '*' - умножение;							*" << endl;
			cout << "* '/' - деление;							*" << endl;
			cout << "* '()' - рассчет результатов происходит с учетом скобок и приоритетов.  *" << endl;
			cout << "*************************************************************************" << endl;
			break;
		default:
			cout << "Выберите один из пунктов меню" << endl;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		system("pause");
		system("cls");
	}
}