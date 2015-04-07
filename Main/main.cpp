#include <iostream>
#include <Windows.h>
#include "OperationCenter.h"

void coutc(int color, string output);
enum Colors { dark=0, blue, green, cyan, red, purple, yellow, grey, dgrey, hblue, hgreen, hred, hpurple, hyellow, hwhite };


int main(){
	Logger log;
	log.deleteLogContent(); // delete previous log if any

	bool status = false;

	cout << OperationCenter::findPath() << endl; //is it correct if I put here?

	OperationCenter::loadData(status);

	cout << OperationCenter::showWelcomeMessage(status);
	//coutc(6, OperationCenter::showWelcomeMessage(status));	
	
	string userInput;
	getline(cin, userInput);

	while(userInput != "exit"){
		OperationCenter::clearScreen();
		OperationCenter::executeInput(userInput);
		//cout << OperationCenter::getResponse() << endl;
		coutc(13,OperationCenter::getResponse());
		//cout << OperationCenter::getDisplay() << endl;
		coutc(15, OperationCenter::getDisplay());
		getline(cin, userInput);
	}

	return 0;
}


void coutc(int color, string output)
{
   HANDLE handle= GetStdHandle(STD_OUTPUT_HANDLE);
   SetConsoleTextAttribute( handle, color);
   cout << output << endl;
   SetConsoleTextAttribute(handle, 15);
}




