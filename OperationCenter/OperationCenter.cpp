#include "OperationCenter.h"

void OperationCenter::executeCommand(string command, string item){
	
	DataStorage myDataStorage;
	Parser myParser;
	string userInput;

	while(command != "exit") {
		if(command == "add") {
			myDataStorage.addItem(item);
		}
		else if(command == "display") {
			myDataStorage.displayList();	

		}
		else if(command == "undo"){
			myDataStorage.executeUndo();
		}
		else{
			cout<<"invalid command"<<endl;
		}
		
		getline(cin, userInput);
		vector<string> newReturnInput;
		newReturnInput = myParser.parseInput(userInput);
		command = newReturnInput[0];
		item = newReturnInput[1];
	}

}