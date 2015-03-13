#include <iostream>
#include "OperationCenter.h"

int main(){

	string userInput;
	getline(cin, userInput);
	while(userInput != "exit"){
		OperationCenter::executeInput(userInput);
		cout << Feedback::getResponse << endl;
		cout << Feedback::getDisplay << endl;
		
		getline(cin, userInput);
	}



	return 0;
}