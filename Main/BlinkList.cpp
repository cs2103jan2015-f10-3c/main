#include <iostream>
#include <Windows.h>
#include "OperationCenter.h"

void coutc(int color, string output);
enum Colors { dark=0, blue, green, cyan, red, purple, yellow, grey, dgrey, hblue, hgreen, hred, hpurple, hyellow, hwhite };


int main(){
	Logger log;
	log.deleteLogContent(); // delete previous log if any

	bool status = false;

	if(OperationCenter::findPath()){
		OperationCenter::loadData(status);
	}

	coutc (13, OperationCenter::getResponse()); 
	if(OperationCenter::getResponse() != ""){
		cout << endl << endl;
	}
	cout << OperationCenter::showWelcomeMessage(status);
		
	
	string userInput;
	getline(cin, userInput);

	while(userInput != "exit"){
		OperationCenter::clearScreen();
		OperationCenter::executeInput(userInput);
		
		coutc(13,OperationCenter::getResponse());
		
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




