//#pragma once
//#include <array>
//#include <iostream>
//#include <algorithm>
//#include <string>
//#include <Windows.h>
//#include <stack>
//
//
//using namespace std;
//
////void Calculations(stack <Symbol>& stackValue, stack <Symbol>& stackOperation, Symbol &symbol);
//
//
//void Calculations(stack <Symbol> &stackValue, stack <Symbol>& stackOperation, Symbol& symbol)
//{
//	double x, y;
//	x = stackValue.top().value;
//	stackValue.pop();
//
//	switch (stackOperation.top().type)
//	{
//	case '+':
//	{
//		y = stackValue.top().value;
//		stackValue.pop();
//		symbol.value = x + y;
//		stackValue.push(symbol);
//	}
//	//case '-':
//	//case '*':
//	//case '/':
//	}
//
//}