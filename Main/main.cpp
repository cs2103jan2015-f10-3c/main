#include <iostream>
#include "OperationCenter.h"

int main(){
	bool status = false;
	OperationCenter::loadData(status);
	cout << endl;
//Comment @kevin, might be better to store this in O/C
	cout << "Welcome to BlinkList!" << endl << endl;
	if(status == true){
		cout << "Today's Agenda is as follows:" << endl << endl;
		OperationCenter::executeInput("show today");
		cout << OperationCenter::getDisplay() << endl;

	} else { 
		cout << "There is no saved data" << endl;
	}
//End of comment @Kevin
	


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