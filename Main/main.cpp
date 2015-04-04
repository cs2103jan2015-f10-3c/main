#include <iostream>
#include "OperationCenter.h"

void ClearScreen();
int main(){
	bool status = false;
	OperationCenter::loadData(status);
	
	cout<< OperationCenter::showWelcomeMessage(status);

	string userInput;
	getline(cin, userInput);

	while(userInput != "exit"){
		OperationCenter::clearScreen();
		OperationCenter::executeInput(userInput);
		cout << OperationCenter::getResponse() << endl;
		cout << OperationCenter::getDisplay() << endl;
		
		getline(cin, userInput);
	}

	return 0;
}



