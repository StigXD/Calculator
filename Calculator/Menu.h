#pragma once
#include <array>
#include <iostream>
#include <algorithm>
#include <string>
#include <Windows.h>
#include "Enter task.h"
#include "String to double.h"

using namespace std;

void Menu()
{
	string perform;
	while (true)
	{
		EnterTask(perform);
		StringToDouble(perform);
	}

}