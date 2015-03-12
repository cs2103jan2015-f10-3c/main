#include "OperationCenter.h"

using namespace std;

const string OperationCenter::ADD_COMMAND = "add";
const string OperationCenter::DELETE_COMMAND = "delete";
const string OperationCenter::DISPLAY_COMMAND = "display";
const string OperationCenter::CLEAR_COMMAND = "clear";
const string OperationCenter::SORT_COMMAND = "sort";
const string OperationCenter::SEARCH_COMMAND = "search";
const string OperationCenter::EDIT_COMMAND = "edit";
const string OperationCenter::EXIT_COMMAND = "exit";
const string OperationCenter::EMPTY_RESPONSE = "";
const string OperationCenter::IVALID_COMMAND_MESSAGE = "Invalid Command";

OperationCenter::OperationCenter(){
}

vector<string> OperationCenter::executeInput(string input){
	time_t now;
	struct tm *current;
	now = time(0);
	current = localtime(&now);

	vector<string> returnVector;
	Parser parser;
	DataProcessor dataProcessor;
	TimeMacro currentTime(current->tm_mday, current->tm_mon, current->tm_year + 1900);
	
	parser.parseInput(input);
	string command = parser.getCommand();
	Data task = parser.getData();
	int taskNo = parser.getTaskNo();
	
	string returnResponse;
	string returnDisplay;
	
	
	if(command == ADD_COMMAND) {
		returnResponse = dataProcessor.addTask(task);
	}else if(command == DISPLAY_COMMAND) {
		returnResponse = EMPTY_RESPONSE;
		returnDisplay = dataProcessor.displayTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());	
	}else if(command == DELETE_COMMAND){
		returnResponse = dataProcessor.deleteTask(taskNo);
	}else if(command == CLEAR_COMMAND){
		returnResponse = dataProcessor.clearTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());
	}else if(command == SORT_COMMAND){
		returnResponse = "under construction";
	}else if(command == SEARCH_COMMAND){
		returnDisplay = dataProcessor.searchTask(task.getDesc());
		returnResponse = EMPTY_RESPONSE;
	}else if(command == EDIT_COMMAND){
		returnResponse = dataProcessor.editTask(task.getTaskNo(), task);
	}else{
		returnResponse = IVALID_COMMAND_MESSAGE;
	}
	
	if(command != DISPLAY_COMMAND && command != SEARCH_COMMAND){
		returnDisplay = dataProcessor.displayTask(currentTime, currentTime);
	}

	returnVector.push_back(returnDisplay);
	returnVector.push_back(returnResponse);

	return returnVector;
}