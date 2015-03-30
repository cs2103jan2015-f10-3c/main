#include <iostream>
#include "OperationCenter.h"

int main(){
	bool status = false;
	OperationCenter::loadData(status);
	
	cout<< OperationCenter::showWelcomeMessage(status);

	string userInput;
	getline(cin, userInput);

	while(userInput != "exit"){
		OperationCenter::executeInput(userInput);
		cout << OperationCenter::getResponse() << endl;
		cout << OperationCenter::getDisplay() << endl;
		
		getline(cin, userInput);
	}

	return 0;
}