#include "OperationCenter.h"

int main(){

	OperationCenter myOperationCenter;
	Parser myParser;

	string userInput; 
	getline(cin, userInput);
	vector<string> returnInput;
	returnInput = myParser.parseInput(userInput);
	string command = returnInput[0];
	string item = returnInput[1];
	myOperationCenter.executeCommand(command, item);
	

	return 0;
}

