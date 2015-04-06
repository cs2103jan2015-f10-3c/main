#include <assert.h>
#include <exception>
#include <iomanip>
#include "DataProcessor.h"


const char DataProcessor::ADD_MESSAGE[] = " is added";
const char DataProcessor::DELETE_MESSAGE[] = " is deleted from BlinkList";
const char DataProcessor::CLEAR_MESSAGE[] = "all contents are cleared";
const char DataProcessor::EDIT_MESSAGE[] = " is edited";
const char DataProcessor::UNDO_MESSAGE[] = "You have undone your operation";
const char DataProcessor::DONE_MESSAGE[] = " is done";
const char DataProcessor::UNDONE_MESSAGE[] = " is reopened";
const char DataProcessor::ADD_COMMAND[] = "add";
const char DataProcessor::DELETE_COMMAND[] = "delete";
const char DataProcessor::SHOW_COMMAND[] = "show";
const char DataProcessor::CLEAR_COMMAND[] = "clear";
const char DataProcessor::EDIT_COMMAND[] = "edit";
const char DataProcessor::NO_DATE[] = "undefined";

const unsigned int DataProcessor::TIME_WIDTH	= 16;
const unsigned int DataProcessor::TIME_10		= 10;
const unsigned int DataProcessor::NO_TIME		= -1;
const unsigned int DataProcessor::DATE_WIDTH	= 40;
const unsigned int DataProcessor::DAY_WIDTH		= 13;
const unsigned int DataProcessor::WINDOW_WIDTH	= 81;

const char DataProcessor::EXCEPTION_INVALID_TASKNUMBER[] = "Exception:invalid tasknumber";
const char DataProcessor::EXCEPTION_EMPTY_KEYWORD[] = "Exception:empty keyword entere";

//This function reads in the Data object to be added,
//then return the string reporting the adding which contains the descripiton of the data added
string DataProcessor::addTask(Data task){
	Storing storing;
	storing.addData(task); 
	ostringstream out;
	out << convertDataObjectToLine(task) << ADD_MESSAGE << endl;
	string addMessage;
	addMessage = out.str();
	setLatestData(task);
	return addMessage;
}

//This function reads in the number of the task to be deleted,
//then return the string reporting the deletion which contains the description of the data deleted
string DataProcessor::deleteTask(int number){
	ostringstream out;
	Storing storing;
	try{
	out << convertDataObjectToLine(storing.deleteData(number)) << DELETE_MESSAGE << endl;
	}
	catch(string errorMessage){
		throw errorMessage;
	}
	string deleteMessage;
	deleteMessage = out.str();
	return deleteMessage;
}

//This function reads in two TimeMacro objects,
//then return the string which contains the list of task belonging to the desired time frame
string DataProcessor::displayTask(TimeMacro startTime, TimeMacro endTime){
	string taskString;
	Storing storing;
	storing.clearDisplayList();

	taskString = convertTaskListToString(storing.display(startTime, endTime));
	return taskString;
}

void DataProcessor::saveData(){
	Storing storing;
	storing.saveData();
}

void DataProcessor::loadData(bool& status){
	Storing storing;
	storing.loadData(status);
}

Data DataProcessor::getLatestData(){
	return _latestData;
}

void DataProcessor::setLatestData(Data data){
	_latestData = data;
}


//@Yang Xiaozhou A0113538J

//This function reads in the taskNumber of the task that is
//currently in display and the Data object which contains
//the updated information about the task.
//The return string is the successfuly message after edit operation
string DataProcessor::editTask(int taskNumber, Data task){
	ofstream outData;
	Storing  storing;
	outData.open("log.txt");
	if(taskNumber <= 0){
		outData << EXCEPTION_INVALID_TASKNUMBER;
		throw std::exception(EXCEPTION_INVALID_TASKNUMBER);
	}
	Data	 uneditedTask;
	outData << "start editing data";
	try{
		uneditedTask = storing.changeData(taskNumber, task);
	}
	catch (string errorMessage){
		throw errorMessage;
	}
	string	 editMessage = getEditMessage(uneditedTask);
	
	outData << "edit data is done";
	setLatestData(uneditedTask);
	
	return	 editMessage;
}

string DataProcessor::getEditMessage(Data uneditedTask){
	assert (uneditedTask.getDesc() != "\0");
	string editMessage = convertDataObjectToLine(uneditedTask) + EDIT_MESSAGE + "\n";;	
	return editMessage;
}

//This function clears the current display list
void DataProcessor::clearDisplayList(){
	Storing storing;
	storing.clearDisplayList();
}

//This function clears all the tasks inside storage
string DataProcessor::clearTask(){
	Storing storing;
	storing.clearDataList();

	return  CLEAR_MESSAGE;
}


string DataProcessor::executeUndo(){
	Data latestData;
	string latestCommand;
	vector<Data> latestVector;
	Storing storing; 

	latestVector = storing.getLatestVector();
	latestCommand = storing.getLatestCommand();
	latestData = storing.getLatestData();

	if (latestCommand == ADD_COMMAND){
		storing.undoAdd();
	}
	else if (latestCommand == DELETE_COMMAND){
		storing.addData(latestData);
	}
	else if (latestCommand == EDIT_COMMAND || latestCommand == CLEAR_COMMAND){
		undoEditOrClear(storing, latestVector);
	}

	setLatestData(latestData);
	return UNDO_MESSAGE;
}

//This function is the undo helper function
//it performs the undo action whenever
//the latest command is edit or clear
void DataProcessor::undoEditOrClear(Storing & storing, vector<Data> & latestVector){
		storing.clearDataList();
		for(int i = 0; i != latestVector.size(); i++){
			storing.addData(latestVector[i]);
		}
}



//This function reads in the desired keyword to be searched in the current
//task list, all tasks with description containing the keyword will be returned
string DataProcessor::searchTask(string keyword){
	ofstream	 outData;
	outData.open("log.txt");
	if(keyword.size() == 0){
		outData << EXCEPTION_EMPTY_KEYWORD;
		throw std::exception(EXCEPTION_EMPTY_KEYWORD);
	}
	
	Storing		 storing;
	storing.clearDisplayList();
	
	//logging
	outData << "update current displayList to display matched tasks";
	vector<Data> returnTaskList = storing.displaySearch(keyword);

	string		 returnTaskListString = convertTaskListToString(returnTaskList);
	return		 returnTaskListString;

}


//this function reads in the task number 
//and update the status of the corresponding
//task to done
string DataProcessor::markDone(int taskNo){
	Storing storing;
	Data targetData;
	try{
 	targetData = storing.getData(taskNo);		 	
	}
	catch (string errorMessage){
		throw errorMessage;
	}
			targetData.updateCompleteStatus(true);
			storing.changeData(taskNo, targetData);
	string	doneMessage = getDoneMessage(targetData);

	return doneMessage;
}

string DataProcessor::getDoneMessage(Data targetData){
	string doneMessage = convertDataObjectToLine(targetData) + DONE_MESSAGE;
	return doneMessage;
}

//this function reads in the task number 
//and update the status of the corresponding
//task to ongoing
string DataProcessor::unDone(int taskNo){
	Storing storing;

	Data	targetData = storing.getData(taskNo);
			targetData.updateCompleteStatus(false);
			storing.changeData(taskNo, targetData);
	string	undoneMessage = getUndoneMessage(targetData);
	setLatestData(targetData);
	return	undoneMessage;
}

string DataProcessor::getUndoneMessage(Data targetData){
	string undoneMessage = convertDataObjectToLine(targetData) + UNDONE_MESSAGE;
	return undoneMessage;
}

//This function gets a list of floating tasks
//and return it to Operation Center for displaying
string DataProcessor::showFloat(){
	Storing			storing;
	vector<Data>	floatingTaskList = storing.displayfloat();
	string			floatingTaskListString = convertTaskListToString(floatingTaskList);
	return			floatingTaskListString;
}

//This function get a list of completed tasks
//and return it to Operation Center for displaying
string DataProcessor::showDone(){
	Storing			storing;
	vector<Data>	completedTaskList = storing.displayDone();
	string			completedTaskListString = convertTaskListToString(completedTaskList);
	return			completedTaskListString;
}

//This function calls up a list of commands 
//available at BlinkList
string DataProcessor::showCommands(){
	Storing		storing;
	string		commandList = storing.retrieveCommandList();
	return		commandList;
}

//This function calls up a list of features
//features will be more elaborated than command file
string DataProcessor::showFeatures(){
	Storing		storing;
	string		featureList = storing.retrieveFeatureList();
	return		featureList;
}

//This function reads in a Data object and convert it into a string
//that contains all the information of that data and ready to be displayed
string DataProcessor::convertDataObjectToString(Data task){
	assert ( task.getDesc() != "\0");
	TimeMacro timeMacroBeg;
	TimeMicro timeMicroBeg, timeMicroEnd;
	getTimeObject(timeMacroBeg, timeMicroBeg, timeMicroEnd, task);	
	
	string descriptionLine = getDescriptionLine(task);
	string dayLine		   = getDayLine(timeMacroBeg);
	string timeLine		   = getTimeLine(timeMicroBeg, timeMicroEnd);
	string dateLine		   = getDateLine(timeMacroBeg);

	string taskString = descriptionLine + dayLine + timeLine + dateLine;
	return taskString;

}

//This function receives a Data object
//and converts it into one line of string
//that is ready to be put into response string
string DataProcessor::convertDataObjectToLine(Data task){
	assert ( task.getDesc() != "\0");
	setLatestData(task);
	ostringstream outData;
	TimeMacro timeMacroBeg;
	TimeMicro timeMicroBeg, timeMicroEnd;
	getTimeObject(timeMacroBeg, timeMicroBeg, timeMicroEnd, task);	
	
	outData << task.getDesc();
	//If there is deadline date associated with the task
	if(timeMacroBeg.getDate() != 0){
		outData << " on " 
				<< timeMacroBeg.getDay() << ", "
				<< timeMacroBeg.getDate() << "-"
				<< timeMacroBeg.getMonth() << "-"
				<< timeMacroBeg.getYear() << " ";
	}

	//Check if there is deadline time associated with the task
	if(timeMicroBeg.getHour() != -1){
		outData << "at ";
		if (timeMicroBeg.getHour() < 10) {
			outData << "0";
		}
		outData << timeMicroBeg.getHour() << ":";
		if (timeMicroBeg.getMin() < 10) {
			outData << "0";
		}
		outData << timeMicroBeg.getMin();

	}
	if(timeMicroEnd.getHour() != -1){
		outData << "-";
		if (timeMicroEnd.getHour() < 10) {
			outData << "0";
		}
		outData << timeMicroEnd.getHour() << ":";
		if (timeMicroEnd.getMin() < 10) {
			outData << "0";
		}
		outData << timeMicroEnd.getMin();
	}

	return outData.str();

}

//This function reads in a vector of Data object and subsequently converts
//them into a string that contains all datas in the vector
//The string will be ready for display by UI
string DataProcessor::convertTaskListToString(vector<Data>& taskList){
	ostringstream outList;
	int numberOfTask = 1;
	for(int i = 0; i != taskList.size(); i++){
		outList << numberOfTask << ". "
				<< convertDataObjectToString(taskList[i]) << endl
				<< setfill('*') << setw(WINDOW_WIDTH) << "\n";
		numberOfTask++;
	}
	assert (numberOfTask >= 1);

	string taskListString = outList.str();
	return taskListString;

}


//This function gets and returns all the
//time associated with the target task
void DataProcessor::getTimeObject(TimeMacro & timeMacroBeg, TimeMicro & timeMicroBeg,
								  TimeMicro & timeMicroEnd, Data task){
	timeMacroBeg = task.getTimeMacroBeg();
	timeMicroBeg = task.getTimeMicroBeg();
	timeMicroEnd = task.getTimeMicroEnd();
}

//This function converts the description
//of the target task into a formated string
string DataProcessor::getDescriptionLine(Data task){
	ostringstream outData;
	int descriptionWidth = task.getDesc().length();
	outData << setw(descriptionWidth) << left 
			<< task.getDesc() << endl << "   ";
	return outData.str();
}

//This function converts the day value
//of the target task into a formated string
string DataProcessor::getDayLine(TimeMacro timeMacroBeg){
	ostringstream outData;
	if(timeMacroBeg.getDay() != NO_DATE){
		outData << setfill(' ') << setw(DAY_WIDTH) << left << timeMacroBeg.getDay();
	}
	else{
		outData << setfill(' ') << setw(DAY_WIDTH) << left;
	}
	return outData.str();
}

//This function converts the time value
//of the target task into a formated string
string DataProcessor::getTimeLine(TimeMicro timeMicroBeg, TimeMicro timeMicroEnd){
	ostringstream outData;
	string timeMicroString = "   ";
	//Check if there is deadline time associated with the task
	if(timeMicroBeg.getHour() != NO_TIME){
		if (timeMicroBeg.getHour() < TIME_10) {
			timeMicroString += "0";
		}
		timeMicroString += to_string(timeMicroBeg.getHour()) + ":";
		if (timeMicroBeg.getMin() < TIME_10) {
			timeMicroString += "0";
		}
		timeMicroString += to_string(timeMicroBeg.getMin());

	}
	if(timeMicroEnd.getHour() != NO_TIME){
		timeMicroString += "-";
		if (timeMicroEnd.getHour() < TIME_10) {
			timeMicroString += "0";
		}
		timeMicroString += to_string(timeMicroEnd.getHour()) + ":";
		if (timeMicroEnd.getMin() < TIME_10) {
			timeMicroString += "0";
		}
		timeMicroString += to_string(timeMicroEnd.getMin());
	}
	
	outData << setw(TIME_WIDTH) << left << timeMicroString;
	return outData.str();
}

//This function converts the date value
//of the target task into a formated string
string DataProcessor::getDateLine(TimeMacro timeMacroBeg){
	ostringstream outData;
	//If there is deadline date associated with the task
	if(timeMacroBeg.getDate() != 0){
		outData << setw(DATE_WIDTH) << right
				<< timeMacroBeg.getDate() << "-"
				<< timeMacroBeg.getMonth() << "-"
				<< timeMacroBeg.getYear();
	}

	return outData.str();
}