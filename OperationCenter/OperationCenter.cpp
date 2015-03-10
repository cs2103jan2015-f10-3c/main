#include "OperationCenter.h"

using namespace std;

OperationCenter::OperationCenter(){
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
	Data task = parser.getData();
	int taskNo = parser.getTaskNo();
	string returnString;
	ostringstream out;
	DataProcessor dataProcessor;
	if(command == "add") {
		returnString = dataProcessor.addTask(task);
	}
	else if(command == "display") {
		returnString = dataProcessor.displayTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());	
	}
	else if(command == "delete"){
		returnString = dataProcessor.deleteTask(taskNo);
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
	string returnMessage;
	if(command != "display"){
		out << returnString << endl << dataProcessor.displayTask(currentTime, currentTime);
	}
	else {
		out << returnString;
	}
	returnMessage = out.str();
	return returnMessage;
}