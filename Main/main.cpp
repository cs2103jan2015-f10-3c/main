#include <iostream>
#include "OperationCenter.h"

int main(){
	bool status = false;
	OperationCenter::loadData(status);

	cout << "Welcome to BlinkList!" << endl;
	if(status == true){
		cout << "Today's Agenda is as follows: \n";
		OperationCenter::executeInput("display today");
		cout << Feedback::getDisplay() << endl;

	}

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