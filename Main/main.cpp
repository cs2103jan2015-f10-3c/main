#include <iostream>
#include "OperationCenter.h"

int main(){

	OperationCenter::loadData();

	cout << "Welcome to BlinkList!" << endl;
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