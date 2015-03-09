#include "OperationCenter.h"
#include "OperationCenter.h"

using namespace std;

OperationCenter::OperationCenter(){
	DataStorage dataStorage;
}

string OperationCenter::executeInput(string input){
	Parser parser;
	parser.parseInput(input);
	string command = parser.getCommand();
	Data task = parser.getTask();
	string returnString;
	DataProcessor dataProcessor;
	if(command == "add") {
		returnString = dataProcessor.addTask(task);
	}
	else if(command == "display") {
		returnString = dataProcessor.display(task.getTimeMacro, task.getTimeMicro);	
	}
	else if(command == "delete"){
		returnString = dataProcessor.deleteTask(task);
	}
	else if(command == "clear"){
		returnString = dataProcessor.clearTask(task.getTimeMacro, task.getTimeMicro);
	}
	else if(command == "sort"){
		returnString = "under construction";
	}
	else if(command == "search"){
		returnString = dataProcessor.searchTask(task.getDesc);
	}
	else if(command == "edit"){
		returnString = "under construction";
	}
	else{
		cout<<"invalid command"<<endl;
	}
	cout<<"command: ";
	cin >> command;
}