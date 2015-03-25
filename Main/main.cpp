#include <iostream>
#include "OperationCenter.h"

int main(){
	bool status = false;
	OperationCenter::loadData(status);

	cout << "Welcome to BlinkList!" << endl << endl;
	if(status == true){
		cout << "Today's Agenda is as follows:" << endl << endl;
		OperationCenter::executeInput("display today");
		cout << OperationCenter::getDisplay() << endl;

	}

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