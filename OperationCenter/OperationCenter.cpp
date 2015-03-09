#include "OperationCenter.h"

using namespace std;

OperationCenter::OperationCenter(){
	DataStorage dataStorage;
}

string OperationCenter::executeInput(string input){
	time_t now;
	struct tm *current;
	now = time(0);
	current = localtime(&now);
	TimeMacro currentTime(current->tm_mday, current->tm_mon, current->tm_year + 1900);
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
		returnString = dataProcessor.display(task.getTimeMacroBeg(), task.getTimeMacroEnd());	
	}
	else if(command == "delete"){
		returnString = dataProcessor.deleteTask(task);
	}
	else if(command == "clear"){
		returnString = dataProcessor.clearTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());
	}
	else if(command == "sort"){
		returnString = "under construction";
	}
	else if(command == "search"){
		returnString = dataProcessor.searchTask(task.getDesc());
	}
	else if(command == "edit"){
		returnString = dataProcessor.editTask(task.getTaskNo(), task);
	}
	else{
		cout<<"invalid command"<<endl;
	}
	if(command != "display"){
		dataProcessor.displayDaily(currentTime, currentTime);
	}
	return returnString;
}