#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;

bool StartMenu()
{
	while(true)
	{
		cout << "_________________________________________________" << endl;
		cout << "|		  �����������			|" << endl;
		cout << "|_______________________________________________|" << endl;
		cout << "|						|" << endl;
		cout << "| 1. ������ ����������				|" << endl;
		cout << "| 2. ����					|" << endl;
		cout << "| 0. �����					|" << endl;
		cout << "|_______________________________________________|" << endl << endl;

		int choice;
		cout << "�������� ����� ����:" << endl << "=> ";
		cin >> choice;
		switch (choice)
		{
		case 0:
			return false;
		case 1:
			return true;
		case 2:
			cout << "*************************************************************************" << endl;
			cout << "* � ������������ �����������:						*" << endl;
			cout << "* '+' - ��������;							*" << endl;
			cout << "* '-' - ���������;							*" << endl;
			cout << "* '*' - ���������;							*" << endl;
			cout << "* '/' - �������;							*" << endl;
			cout << "* '()' - ������� ����������� ���������� � ������ ������ � �����������.  *" << endl;
			cout << "*************************************************************************" << endl;
			break;
		default:
			cout << "�������� ���� �� ������� ����" << endl;
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		system("pause");
		system("cls");
	}
}