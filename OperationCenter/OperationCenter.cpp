#include "OperationCenter.h"

using namespace std;

const string OperationCenter::ADD_COMMAND = "add";
const string OperationCenter::DELETE_COMMAND = "delete";
const string OperationCenter::DISPLAY_COMMAND = "display";
const string OperationCenter::CLEAR_COMMAND = "clear";
const string OperationCenter::SORT_COMMAND = "sort";
const string OperationCenter::SEARCH_COMMAND = "search";
const string OperationCenter::EDIT_COMMAND = "edit";
const string OperationCenter::UNDO_COMMAND = "undo";
const string OperationCenter::EXIT_COMMAND = "exit";
const string OperationCenter::EMPTY_RESPONSE = "";
const string OperationCenter::IVALID_COMMAND_MESSAGE = "Invalid Command";

string Feedback::display;
string Feedback::response;

void OperationCenter::executeInput(string input){
	time_t t = time (0);   // get time now
    struct tm now;
	localtime_s (&now, &t);

	TimeMacro currentTime(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
	Parser parser;
	DataProcessor dataProcessor;
	
	parser.parseInput(input);
	string command = parser.getCommand();
	Data task = parser.getData();
	int taskNo = parser.getTaskNo();
	
	string returnResponse;
	string returnDisplay;
	
	
	if(command == "add") {
		returnResponse = dataProcessor.addTask(task);
	}else if(command == "display") {
		returnResponse = EMPTY_RESPONSE;
		returnDisplay = dataProcessor.displayTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());
		if(returnDisplay == ""){
			returnDisplay = "You have no task within the specified time period";
		}
	}else if(command == "delete"){
		returnResponse = dataProcessor.deleteTask(taskNo);
	}else if(command == "clear"){
		returnResponse = dataProcessor.clearTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());
	}else if(command == "sort"){
		returnResponse = "under construction";
	}else if(command == "search"){
		returnDisplay = dataProcessor.searchTask(task.getDesc());
		returnResponse = EMPTY_RESPONSE;
	}else if(command == "edit"){
		returnResponse = dataProcessor.editTask(taskNo, task);
	}else if(command == "undo"){
		returnResponse = dataProcessor.executeUndo();
	}else{
		returnResponse = IVALID_COMMAND_MESSAGE;
	}
	
	if(command != "display" && command != "search"){
		returnDisplay = dataProcessor.displayTask(currentTime, currentTime);
		if(returnDisplay == ""){
			returnDisplay = ":) You have no task for today";
		}
	}


	Feedback::updateDisplay(returnDisplay);
	Feedback::updateResponse(returnResponse);

}

void OperationCenter::saveData(){
	DataProcessor::saveData();
}

void OperationCenter::loadData(){
	DataProcessor::loadData();
}
