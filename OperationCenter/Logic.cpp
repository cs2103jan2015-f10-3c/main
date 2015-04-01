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

string Logic::showWelcomeMessage(bool status){
	ostringstream out;
	out << "Welcome to BlinkList!" << endl << endl;
	if(status == true){
		out << "Today's Agenda is as follows:" << endl << endl;
		executeInput("show today");
		out << Feedback::getDisplay() << endl;

	} else { 
		out << "There is no saved data" << endl;
	}
	string welcomeMessage = out.str();
	return welcomeMessage;
}

TimeMacro Logic::setCurrentTime(){
	
	time_t t = time (0);   // get time now
    struct tm now;
	localtime_s (&now, &t);

	TimeMacro currentTime(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);

	return currentTime;
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

//display the list of task for a specific day, depending on the date of the object being
//added, edited, deleted or done. 
string Logic::displaySpecificDay(DataProcessor dataProcessor, TimeMacro current){
	Data latestData = dataProcessor.getLatestData();
	string returnDisplay;
	ostringstream out;
	
	//check if the date is today
	if(latestData.getTimeMacroBeg().getDate() == current.getDate() && latestData.getTimeMacroBeg().getMonth() == current.getMonth() && latestData.getTimeMacroBeg().getYear() == current.getYear()){
		returnDisplay = displayToday(returnDisplay, current);
		return returnDisplay;
	}

	returnDisplay = dataProcessor.displayTask(latestData.getTimeMacroBeg(), latestData.getTimeMacroBeg());

	if(returnDisplay == "" && latestData.getTimeMacroBeg().getDate() != 0){
		out << "Your have no task on " << latestData.getTimeMacroBeg().getDay() << ", "  
			<< latestData.getTimeMacroBeg().getDate() << "-" 
			<< latestData.getTimeMacroBeg().getMonth() << "-"
			<< latestData.getTimeMacroBeg().getYear() << endl;
	} else if(latestData.getTimeMacroBeg().getDate() != 0){
		out << "Your agenda for " << latestData.getTimeMacroBeg().getDay() << ", "  
			<< latestData.getTimeMacroBeg().getDate() << "-" 
			<< latestData.getTimeMacroBeg().getMonth() << "-"
			<< latestData.getTimeMacroBeg().getYear() << ":" << endl;
	} else if(returnDisplay == "" && latestData.getTimeMacroBeg().getDate() == 0){
		out<< "You have no task with unspecified date"<< endl;
	} else if(latestData.getTimeMacroBeg().getDate() == 0){
		out << "Your tasks with unspecified date are as follows: " << endl;
	}

	out << returnDisplay;
	returnDisplay = out.str();
	
	return returnDisplay;
}

void Logic::executeCommand(string& returnDisplay, string& returnResponse, string command, Data task, int taskNo, TimeMacro currentTime){
	
	DataProcessor dataProcessor;

	if(command == "add") {
		dataProcessor.clearDisplayList();
		returnResponse = dataProcessor.addTask(task);
		returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == "show") {
		dataProcessor.clearDisplayList();
		returnResponse = EMPTY_RESPONSE;
		returnDisplay = dataProcessor.displayTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());
		if(returnDisplay == ""){
			returnDisplay = displayIfEmpty(returnDisplay, currentTime, task.getTimeMacroBeg(), task.getTimeMacroEnd());
		}
	}else if(command == "delete"){
		returnResponse = dataProcessor.deleteTask(taskNo);
		dataProcessor.clearDisplayList();
		returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == "clear"){
		dataProcessor.clearDisplayList();
		returnResponse = dataProcessor.clearTask();
	}else if(command == "sort"){
		returnResponse = "under construction";
	}else if(command == "search"){
		try{
			dataProcessor.clearDisplayList();
			returnDisplay = dataProcessor.searchTask(task.getDesc());
			returnResponse = EMPTY_RESPONSE;
		}
		catch (std::exception e){
			//std::cout << e.what();
			returnResponse = e.what();
		}
		if(returnDisplay == ""){
			returnResponse = "Oops, there is no matching task in your BlinkList\n";
		}
	}else if(command == "edit"){
		try{
			returnResponse = dataProcessor.editTask(taskNo, task);
			dataProcessor.clearDisplayList();
			returnDisplay = displaySpecificDay(dataProcessor, currentTime);
		}
		catch (std::exception e){
			//std::cout << e.what();
			returnResponse = e.what();
		}
	}else if(command == "undo"){
		dataProcessor.clearDisplayList();
		returnResponse = dataProcessor.executeUndo();
		returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == "done"){
		returnResponse = dataProcessor.markDone(taskNo);
		dataProcessor.clearDisplayList();
		returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == "show commands"){
		dataProcessor.clearDisplayList();
		dataProcessor.showCommands();
	}else if(command == "show done"){
		returnDisplay = dataProcessor.showDone();
	}

	/*if(command != "show" && command != "search" && command != "show commands"){
		dataProcessor.clearDisplayList();
		returnDisplay = displayToday(returnDisplay, currentTime);
	}*/

}

void Logic::executeInput(string input){
	TimeMacro currentTime = setCurrentTime();

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