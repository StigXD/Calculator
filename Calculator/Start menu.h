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
			system("pause");
			system("cls");
		}
		system("pause");
		system("cls");
	}
}