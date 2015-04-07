#include "OperationCenter.h"

using namespace std;

const char Logic::COMMA[] = ",";
const char Logic::DASH[] = "-";
const char Logic::COLON[] = ":";
const char Logic::ADD_COMMAND[] = "add";
const char Logic::DELETE_COMMAND[] = "delete";
const char Logic::SHOW_COMMAND[] = "show";
const char Logic::CLEAR_COMMAND[] = "clear";
const char Logic::SORT_COMMAND[] = "sort";
const char Logic::SEARCH_COMMAND[] = "search";
const char Logic::EDIT_COMMAND[] = "edit";
const char Logic::UNDO_COMMAND[] = "undo";
const char Logic::UNDONE_COMMAND[] = "undone";
const char Logic::HELP_REQUEST[] = "help";
const char Logic::PATH_COMMAND[] = "path";
const char Logic::LOAD_COMMAND[] = "load";
const char Logic::EXIT_COMMAND[] = "exit";
const char Logic::EMPTY_RESPONSE[] = "";
const char Logic::IVALID_COMMAND_MESSAGE[] = "Invalid Command";
const char Logic::DONE_COMMAND[] = "done";
const char Logic::SHOW_COMMANDS[] = "show commands";
const char Logic::SHOW_FEATURES[] = "show features";
const char Logic::SHOW_DONE[] = "show done";
const char Logic::SHOW_FLOAT[] = "show float";
const char Logic::SHOW_TODAY[] = "show today";
const char Logic::FLOAT_NOT_FOUND_MESSAGE[] = "You have no floating task";
const char Logic::DONE_NOT_FOUND_MESSAGE[] = "You are lazy, you have done nothing at all";
const char Logic::SEARCH_NOT_FOUND_MESSAGE[] = "Oops, there is no matching task in your BlinkList\n";
const char Logic::HELP_MESSAGE[] = "Please type 'show commands' or 'show features'";
const char Logic::CANNOT_UNDO_MESSAGE[] = "You can only undo once";
const char Logic::WELCOME_MESSAGE[] = "Welcome to BlinkList!" ;
const char Logic::TODAY_MESSAGE[] = "Today's Agenda is as follows:";
const char Logic::NO_SAVED_DATA_MESSAGE[] = "There is no saved data";
const char Logic::NO_TASK_TO_SHOW_MESSAGE[] = "You have no task within the specified time period\n";
const char Logic::NO_TASK_TODAY_MESSAGE[] = ":) You have no task for today\n";
const char Logic::NO_TASK_ON_MESSAGE[] = "You have no task on ";
const char Logic::AGENDA_FOR_MESSAGE[] = "Your agenda for ";
const char Logic::NO_FLOAT_TASK_MESSAGE[] = "You have no task with unspecified date";
const char Logic::FLOAT_TASK_MESSAGE[] = "Your tasks with unspecified date are as follows: ";
const char Logic::PATH_MESSAGE[] = "New user path: ";
const char Logic::REINPUT_PATH[] = "Please reinput path ";
const char Logic::INPUT_PATH_MESSAGE[] = "Please input path by typing 'path *your directory*' ";

string Feedback::display;
string Feedback::response;
int Logic::undoCount;

void Logic::saveData(){
	DataProcessor::saveData();
}

void Logic::loadData(bool& status){
	DataProcessor::loadData(status);
}

string Logic::findPath(){
	try{
		DataProcessor::checkPathExistence();
		return EMPTY_RESPONSE;
	}		
	catch (string errorMessage){
		return errorMessage;
	}
}

string Logic::showWelcomeMessage(bool status){
	ostringstream out;
	out << WELCOME_MESSAGE << endl << endl;
	if(status == true){
		out << TODAY_MESSAGE << endl << endl;
		executeInput(SHOW_TODAY);
		out << Feedback::getDisplay() << endl;

	} else { 
		out << NO_SAVED_DATA_MESSAGE << endl;
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
		returnDisplay = NO_TASK_TO_SHOW_MESSAGE;
	} else {
		returnDisplay = NO_TASK_TODAY_MESSAGE;
	}
	return returnDisplay;
}

string Logic::displayToday(string returnDisplay, TimeMacro current){
	DataProcessor dataProcessor;
	ostringstream out;
	returnDisplay = dataProcessor.displayTask(current, current);
	if(returnDisplay == EMPTY_RESPONSE){
		out << endl << NO_TASK_TODAY_MESSAGE << endl;
	}else{
		out<< TODAY_MESSAGE << endl << endl << returnDisplay << endl;
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

	if(returnDisplay == EMPTY_RESPONSE && latestData.getTimeMacroBeg().getDate() != 0){
		out << NO_TASK_ON_MESSAGE << latestData.getTimeMacroBeg().getDay() << COMMA  
			<< latestData.getTimeMacroBeg().getDate() << DASH 
			<< latestData.getTimeMacroBeg().getMonth() << DASH
			<< latestData.getTimeMacroBeg().getYear() << endl;
	} else if(latestData.getTimeMacroBeg().getDate() != 0){
		out << AGENDA_FOR_MESSAGE << latestData.getTimeMacroBeg().getDay() << COMMA  
			<< latestData.getTimeMacroBeg().getDate() << DASH 
			<< latestData.getTimeMacroBeg().getMonth() << DASH
			<< latestData.getTimeMacroBeg().getYear() << COLON << endl;
	} else if(returnDisplay == EMPTY_RESPONSE && latestData.getTimeMacroBeg().getDate() == 0){
		out<< NO_FLOAT_TASK_MESSAGE<< endl;
	} else if(latestData.getTimeMacroBeg().getDate() == 0){
		out << FLOAT_TASK_MESSAGE << endl;
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
		if(returnDisplay == EMPTY_RESPONSE){
			returnDisplay = displayIfEmpty(returnDisplay, currentTime, task.getTimeMacroBeg(), task.getTimeMacroEnd());
		}
	}else if(command == DELETE_COMMAND){
		try{
			returnResponse = dataProcessor.deleteTask(taskNo);
			dataProcessor.clearDisplayList();
			returnDisplay = displaySpecificDay(dataProcessor, currentTime);
		}		
		catch (string errorMessage){
			returnResponse = errorMessage;
		}
		}else if(command == CLEAR_COMMAND){
		dataProcessor.clearDisplayList();
		returnResponse = dataProcessor.clearTask();
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
		catch (string errorMessage){
			returnResponse = errorMessage;
		}
	}else if(command == UNDO_COMMAND){
			dataProcessor.clearDisplayList();
			returnResponse = dataProcessor.executeUndo();
			returnDisplay = displaySpecificDay(dataProcessor, currentTime);
	}else if(command == DONE_COMMAND){
		try{
			returnResponse = dataProcessor.markDone(taskNo);
			dataProcessor.clearDisplayList();
			returnDisplay = displaySpecificDay(dataProcessor, currentTime);
		}
		catch (string errorMessage) {
			returnResponse = errorMessage;
		}
	}else if(command == UNDONE_COMMAND){
		try {
			returnResponse = dataProcessor.unDone(taskNo);
			dataProcessor.clearDisplayList();
			returnDisplay = displaySpecificDay(dataProcessor, currentTime);
		}
		catch (string errorMessage){
			returnResponse = errorMessage;
		}
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
	}else if(command == HELP_REQUEST){
		returnResponse = HELP_MESSAGE;
	}else if(command == PATH_COMMAND){
		if(dataProcessor.savePath(directory)){
			ostringstream out;
			out << PATH_MESSAGE << directory <<endl ;
			returnResponse = out.str();
		} else{
			returnResponse = REINPUT_PATH;
		}
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
	if(command != ADD_COMMAND && command != DELETE_COMMAND && command != EDIT_COMMAND && command != CLEAR_COMMAND && command != DONE_COMMAND && command != UNDONE_COMMAND){
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
			returnResponse = CANNOT_UNDO_MESSAGE;
		} else {
			executeCommand(returnDisplay, returnResponse, command, directory, task, taskNo, currentTime);
		}

		checkCommand(command);

	} else {
		returnResponse = errorMessage;
	}

	Feedback::updateDisplay(returnDisplay);
	Feedback::updateResponse(returnResponse);

	saveData();
}

void Logic::clearScreen(){

	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
	if (hStdOut == INVALID_HANDLE_VALUE){
		return;
	}
	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )){
		return;
	}
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(hStdOut,(TCHAR) ' ', cellCount, homeCoords, &count)){
		return;
	}

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)){
		  return;
	}
	/* Move the cursor home */
	SetConsoleCursorPosition( hStdOut, homeCoords );
  }