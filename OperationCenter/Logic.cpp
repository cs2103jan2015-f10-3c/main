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

void Logic::executeInput(string input){
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
		try{
			returnDisplay = dataProcessor.searchTask(task.getDesc());
			returnResponse = EMPTY_RESPONSE;
		}
		catch (std::exception e){
			std::cout << e.what();
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
		returnResponse = IVALID_COMMAND_MESSAGE;
	}
	
	if(command != "display" && command != "search"){
		ostringstream out;
		out << "Today's Agenda:" << endl  
			<< dataProcessor.displayTask(currentTime, currentTime);
		returnDisplay = out.str();
		if(returnDisplay == ""){
			returnDisplay = ":) You have no task for today";
		}
	}


	Feedback::updateDisplay(returnDisplay);
	Feedback::updateResponse(returnResponse);

	saveData();

}