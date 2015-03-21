#include <iostream>
#include "OperationCenter.h"

int main(){

	OperationCenter::loadData();

	cout << "Welcome to BlinkList!" << endl;
	string userInput;
	getline(cin, userInput);

	while(userInput != "exit"){
		OperationCenter::executeInput(userInput);
		cout << Feedback::getResponse() << endl;
		cout << Feedback::getDisplay() << endl;
		
		getline(cin, userInput);
	}

	OperationCenter::saveData();

	return 0;
}