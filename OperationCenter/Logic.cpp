#include "OperationCenter.h"

using namespace std;

const char Logic::ADD_COMMAND[] = "add";
const char Logic::DELETE_COMMAND[] = "delete";
const char Logic::SHOW_COMMAND[] = "show";
const char Logic::CLEAR_COMMAND[] = "clear";
const char Logic::SORT_COMMAND[] = "sort";
const char Logic::SEARCH_COMMAND[] = "search";
const char Logic::EDIT_COMMAND[] = "edit";
const char Logic::UNDO_COMMAND[] = "undo";
const char Logic::EXIT_COMMAND[] = "exit";
const char Logic::EMPTY_RESPONSE[] = "";
const char Logic::IVALID_COMMAND_MESSAGE[] = "Invalid Command";
const char Logic::DONE_COMMAND[] = "done";
const char Logic::SHOW_COMMANDS[] = "show commands";
const char Logic::SHOW_FEATURES[] = "show features";
const char Logic::SHOW_DONE[] = "show done";
const char Logic::SHOW_FLOAT[] = "show float";
const char Logic::FLOAT_NOT_FOUND_MESSAGE[] = "You have no floating task";
const char Logic::DONE_NOT_FOUND_MESSAGE[] = "You are lazy, you have done nothing at all";
const char Logic::SEARCH_NOT_FOUND_MESSAGE[] = "Oops, there is no matching task in your BlinkList\n";
string Feedback::display;
string Feedback::response;
int Logic::undoCount;

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
		out << "You have no task on " << latestData.getTimeMacroBeg().getDay() << ", "  
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

void Logic::executeCommand(string& returnDisplay, string& returnResponse, string command, string directory, Data task, int taskNo, TimeMacro currentTime){
	
	DataProcessor dataProcessor;

	if(command == ADD_COMMAND) {
		dataProcessor.clearDisplayList();
		returnResponse = dataProcessor.addTask(task);
		returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == SHOW_COMMAND) {
		dataProcessor.clearDisplayList();
		returnResponse = EMPTY_RESPONSE;
		returnDisplay = dataProcessor.displayTask(task.getTimeMacroBeg(), task.getTimeMacroEnd());
		if(returnDisplay == ""){
			returnDisplay = displayIfEmpty(returnDisplay, currentTime, task.getTimeMacroBeg(), task.getTimeMacroEnd());
		}
	}else if(command == DELETE_COMMAND){
		returnResponse = dataProcessor.deleteTask(taskNo);
		dataProcessor.clearDisplayList();
		returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == CLEAR_COMMAND){
		dataProcessor.clearDisplayList();
		returnResponse = dataProcessor.clearTask();
	}else if(command == SORT_COMMAND){
		returnResponse = "under construction";
	}else if(command == SEARCH_COMMAND){
		try{
			dataProcessor.clearDisplayList();
			returnDisplay = dataProcessor.searchTask(task.getDesc());
			returnResponse = EMPTY_RESPONSE;
		}
		catch (std::exception e){
			//std::cout << e.what();
			returnResponse = e.what();
		}
		if(returnDisplay == EMPTY_RESPONSE){
			returnResponse = SEARCH_NOT_FOUND_MESSAGE;
		}
	}else if(command == EDIT_COMMAND){
		try{
			returnResponse = dataProcessor.editTask(taskNo, task);
			dataProcessor.clearDisplayList();
			returnDisplay = displaySpecificDay(dataProcessor, currentTime);
		}
		catch (std::exception e){
			//std::cout << e.what();
			returnResponse = e.what();
		}
	}else if(command == UNDO_COMMAND){
			dataProcessor.clearDisplayList();
			returnResponse = dataProcessor.executeUndo();
			returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == DONE_COMMAND){
		returnResponse = dataProcessor.markDone(taskNo);
		dataProcessor.clearDisplayList();
		returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == SHOW_COMMANDS){
		dataProcessor.clearDisplayList();
		returnDisplay = dataProcessor.showCommands();
	}else if(command == SHOW_DONE){
		dataProcessor.clearDisplayList();
		returnDisplay = dataProcessor.showDone();
		if(returnDisplay == EMPTY_RESPONSE){
			returnResponse = DONE_NOT_FOUND_MESSAGE;
		}
	}else if(command == SHOW_FLOAT){
		dataProcessor.clearDisplayList();
		returnDisplay = dataProcessor.showFloat();
		if(returnDisplay == EMPTY_RESPONSE){
			returnResponse = FLOAT_NOT_FOUND_MESSAGE;
		}
	}else if(command == SHOW_FEATURES){
		dataProcessor.clearDisplayList();
		returnDisplay = dataProcessor.showFeatures();
	}else if(command == "save"){
		dataProcessor.saveData();//directory should be added, waiting for support from DataProcessor
	}

}

void Logic::updateUndoCount(string command){
	if(command == UNDO_COMMAND){
		++undoCount;
	}

	if(command != UNDO_COMMAND){
		undoCount = 0;
	}
}

void Logic::checkCommand(string command){
	if(command != ADD_COMMAND && command != DELETE_COMMAND && command != EDIT_COMMAND && command != CLEAR_COMMAND && command != DONE_COMMAND){
		++undoCount;
	}
}

void Logic::executeInput(string input){
	TimeMacro currentTime = setCurrentTime();

	Parser parser;
	
	parser.parseInput(input);
	string command = parser.getCommand();
	Data task = parser.getData();
	int taskNo = parser.getTaskNo();
	string errorMessage = parser.getErrorMessage();
	string directory = parser.getDirectory();
	
	string returnResponse;
	string returnDisplay;
	
	if(errorMessage == EMPTY_RESPONSE){		
		updateUndoCount(command);
		if(undoCount > 1){
			returnResponse = "You can only undo once";
		} else {
			executeCommand(returnDisplay, returnResponse, command, directory, task, taskNo, currentTime);
		}
		checkCommand(command);

		if(command == "show" || command == "show commands" || command == "show done" || command == "show float" || command == "show features" || command == "search"){
			++undoCount;
		}

	} else {
		returnResponse = errorMessage;
	}

	Feedback::updateDisplay(returnDisplay);
	Feedback::updateResponse(returnResponse);

	saveData();
}