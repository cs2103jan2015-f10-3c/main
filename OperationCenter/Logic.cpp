#include "OperationCenter.h"

using namespace std;

string Feedback::display;
string Feedback::response;

void Logic::saveData(){
	DataProcessor::saveData();
}

void Logic::loadData(bool& status){
	DataProcessor::loadData(status);
}

string Logic::displayIfEmpty(string returnDisplay, TimeMacro current, TimeMacro start, TimeMacro end){
	if(current.getDate() != start.getDate() || current.getDate() != end.getDate() || current.getMonth() != start.getMonth() || current.getMonth() != end.getMonth() || current.getYear() != start.getYear() || current.getYear() != end.getYear()){
		returnDisplay = "You have no task within the specified time period\n";
	} else {
		returnDisplay = ":) You have no task for today\n";
	}
	return returnDisplay;
}

string Logic::displayToday(string returnDisplay, TimeMacro current){
	DataProcessor dataProcessor;
	ostringstream out;
	returnDisplay = dataProcessor.displayTask(current, current);
	if(returnDisplay == ""){
		out << endl << ":) You have no task for today" << endl;
	}else{
		out<< "Today's Agenda:" << endl << endl << returnDisplay << endl;
	}
	returnDisplay = out.str();
	return returnDisplay;
}

void Logic::executeCommand(string& returnDisplay, string& returnResponse, string command, Data task, int taskNo, TimeMacro currentTime){
	
	DataProcessor dataProcessor;
	if(command == "add") {
		returnResponse = dataProcessor.addTask(task);
	}else if(command == "display") {
		returnResponse = EMPTY_RESPONSE;
		returnDisplay = dataProcessor.displayTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());
		if(returnDisplay == ""){
			returnDisplay = displayIfEmpty(returnDisplay, currentTime, task.getTimeMacroBeg(), task.getTimeMacroEnd());
		}
	}else if(command == "delete"){
		returnResponse = dataProcessor.deleteTask(taskNo);
	}else if(command == "clear"){
		returnResponse = dataProcessor.clearTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());
	}else if(command == "sort"){
		returnResponse = "under construction";
	}else if(command == "search"){
		try{
			returnDisplay = dataProcessor.searchTask(task.getDesc());
			returnResponse = EMPTY_RESPONSE;
		}
		catch (std::exception e){
			std::cout << e.what();
		}
		if(returnDisplay == ""){
			returnDisplay = "Oops, there is no matching task in your BlinkList\n";
		}
	}else if(command == "edit"){
		try{
			returnResponse = dataProcessor.editTask(taskNo, task);
		}
		catch (std::exception e){
			std::cout << e.what();
		}
	}else if(command == "undo"){
		returnResponse = dataProcessor.executeUndo();
	}else if(command == "done"){
		returnResponse = dataProcessor.markDone(taskNo);
	}else{	
	}

	if(command != "display" && command != "search"){
		returnDisplay = displayToday(returnDisplay, currentTime);
	}

}

void Logic::executeInput(string input){
	time_t t = time (0);   // get time now
    struct tm now;
	localtime_s (&now, &t);

	TimeMacro currentTime(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
	Parser parser;
	
	parser.parseInput(input);
	string command = parser.getCommand();
	Data task = parser.getData();
	int taskNo = parser.getTaskNo();
	string errorMessage = parser.getErrorMessage();
	
	string returnResponse;
	string returnDisplay;
	
	if(errorMessage == ""){
		executeCommand(returnDisplay, returnResponse, command, task, taskNo, currentTime);
	} else {
		returnResponse = errorMessage;
	}

	Feedback::updateDisplay(returnDisplay);
	Feedback::updateResponse(returnResponse);

	saveData();
}