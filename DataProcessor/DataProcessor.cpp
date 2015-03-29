#include <assert.h>
#include <exception>
#include <iomanip>
#include "DataProcessor.h"

//using namespace std;

const string DataProcessor::ADD_MESSAGE = "is added";
const string DataProcessor::DELETE_MESSAGE = "is deleted from BlinkList";
const string DataProcessor::CLEAR_MESSAGE = "all contents are cleared";
const string DataProcessor::EDIT_MESSAGE = "is edited";


//This function reads in the Data object to be added,
//then return the string reporting the adding which contains the descripiton of the data added
string DataProcessor::addTask(Data task){
	DataBase::addData(task); 
	ostringstream out;
	out << convertDataObjectToLine (task) << " is added" <<endl;
	string addMessage;
	addMessage = out.str();
	return addMessage;
}

//This function reads in the number of the task to be deleted,
//then return the string reporting the deletion which contains the description of the data deleted
string DataProcessor::deleteTask(int number){
	ostringstream out;
	out << convertDataObjectToLine (DataBase::deleteData(number)) << " is deleted from BlinkList" << endl;
	string deleteMessage;
	deleteMessage = out.str();
	return deleteMessage;
}

//This function reads in two TimeMacro objects,
//then return the string which contains the list of task belonging to the desired time frame
string DataProcessor::displayTask(TimeMacro startTime, TimeMacro endTime){
	string taskString; 
	taskString = convertTaskListToString(DisplayStorage::getDisplayList(startTime, endTime));
	return taskString;
}

void DataProcessor::saveData(){
	DataBase::saveData();
}

void DataProcessor::loadData(bool& status){
	DataBase::loadData(status);
}



//Start of Yang Xiaozhou's part of DataProcessor



//This function reads in two TimeMacro objects which indicate the 
//period that the user wants tasks to be cleared.
//Post-condition: tasks under the desired period will be cleared
//from the current taskList
string DataProcessor::clearTask(){
	ofstream outData;
	//logging
	outData.open("log.txt");
	outData << "start clearing Data";
	DataBase::clearData();
	outData << "all data cleared";
	
	string clearMessage = getClearMessage();
	return clearMessage;
}

//This function produces the response message for clearing Data
string DataProcessor::getClearMessage(){
	string clearMessage;
	ostringstream out;
	out << " All tasks between are cleared from your schedule." ;
	return clearMessage = out.str();
}

//This function reads in the taskNumber of the task that is
//currently in display and the Data object which contains
//the updated information about the task.
//The return string is the successfuly message after edit operation
string DataProcessor::editTask(int taskNumber, Data task){
	ofstream outData;
	//logging
	outData.open("log.txt");
	//exception
	if(taskNumber <= 0){
		outData << "handling exception:invalid tasknumber";
		throw std::exception("Invalid Tasknumber Entered");
	}
	
	outData << "start editing data";
	Data uneditedTask = DataBase::editData(taskNumber, task);
	string editMessage = getEditMessage(uneditedTask) ;
	outData << "edit data is done";
	return editMessage;

}

//This function returns the edit message
string DataProcessor::getEditMessage(Data uneditedTask){
	assert (uneditedTask.getDesc() != "\0");
	string uneditedTaskString = convertDataObjectToLine(uneditedTask) + " is edited\n";
	return uneditedTaskString;
}


//This function executes undo operation
//return value is the response message to user
string DataProcessor::executeUndo(){
	vector<Data> latestVector = History::getLatestVector();
	string latestCommand = History::getLatestCommand();
	Data latestData = History::getLatestData();
	int	uniqueCode = latestData.getUniqueCode();

	if (latestCommand == "add"){
		DataBase::undoAdd(uniqueCode);
	}
	else if (latestCommand == "delete"){
		DataBase::addData(latestData);
	}
	else if (latestCommand == "edit" || latestCommand == "clear"){
		undoEditOrClear(latestVector);
	}

	string undoMessage = "You have undone your operation";
	return undoMessage;
}

//This function restores the dataList in DataBase
//to its latest version 
//This is a helper method for Undo
void DataProcessor::undoEditOrClear(vector<Data> latestVector){
		DataBase::clearDataList();
		for(int i = 0; i != latestVector.size(); i++){
			DataBase::addData(latestVector[i]);
		}
}

//This function reads in a Data object and convert it into a string
//that contains all the information of that data and ready to be displayed
string DataProcessor::convertDataObjectToString(Data task){
	assert ( task.getDesc() != "\0");
	ostringstream outData;
	TimeMacro timeMacroBeg = task.getTimeMacroBeg();
	TimeMacro timeMacroEnd = task.getTimeMacroEnd();
	TimeMicro timeMicroBeg = task.getTimeMicroBeg();
	TimeMicro timeMicroEnd = task.getTimeMicroEnd();
	int descriptionWidth = task.getDesc().length();
	int dateWidth = 40;
	string timeMicroString = "   ";
	outData << setw(descriptionWidth) << left << task.getDesc() << endl;

	//Check if there is deadline time associated with the task
	if(timeMicroBeg.getHour() != -1){
		if (timeMicroBeg.getHour() < 10) {
			timeMicroString += "0";
		}
		timeMicroString += to_string(timeMicroBeg.getHour()) + ":";
		if (timeMicroBeg.getMin() < 10) {
			timeMicroString += "0";
		}
		timeMicroString += to_string(timeMicroBeg.getMin());

	}
	if(timeMicroEnd.getHour() != -1){
		timeMicroString += "-";
		if (timeMicroEnd.getHour() < 10) {
			timeMicroString += "0";
		}
		timeMicroString += to_string(timeMicroEnd.getHour()) + ":";
		if (timeMicroEnd.getMin() < 10) {
			timeMicroString += "0";
		}
		timeMicroString += to_string(timeMicroEnd.getMin());
	}
	
	outData << setw(20) << left << timeMicroString
			<< setfill(' ') << setw(13) << timeMacroBeg.getDay();
	//If there is deadline date associated with the task
	if(timeMacroBeg.getDate() != 0){
		outData << setw(dateWidth) << right
				<< timeMacroBeg.getDate() << "-"
				<< timeMacroBeg.getMonth() << "-"
				<< timeMacroBeg.getYear();
	}
	
	string taskString = outData.str();
	return taskString;
}

//This function reads in the desired keyword to be searched in the current
//task list, all tasks with description containing the keyword will be returned
string DataProcessor::searchTask(string keyword){
	ofstream outData;
	outData.open("log.txt");
	if(keyword.size() == 0){
		outData << "handling exception: empty keyword entere";
		throw std::exception("Empty Keyword Entered");
	}

	vector<Data> returnTaskList = DataBase::displaySearch(keyword);
	string matchedTaskListString = convertTaskListToString(returnTaskList);
	return matchedTaskListString;

}

//This function reads in a vector of Data object and subsequently converts
//them into a string that contains all datas in the vector
//The string will be ready for display by UI
string DataProcessor::convertTaskListToString(vector<Data>& taskList){
	ostringstream outList;
	int numberOfTask = 1;
	for(int i = 0; i != taskList.size(); i++){
		outList << numberOfTask << ". "
				<< convertDataObjectToString(taskList[i])
				<< setfill('-') << setw(81);
		numberOfTask++;
	}
	assert (numberOfTask >= 1);

	string taskListString = outList.str();
	return taskListString;

}


//This function reads in the task number 
//and update the status of the corresponding
//task as done
string DataProcessor::markDone(int taskNo){
	assert(taskNo != 0);
	ostringstream outData;
	Data targetData = DisplayStorage::getData(taskNo);
	targetData.updateCompleteStatus(true);
	DataBase::editData(taskNo, targetData);
	outData << convertDataObjectToLine(targetData) << " is done";
	return outData.str();
}

//This function calls up a list of commands 
//available at BlinkList
void DataProcessor::showCommands(){
	SaveLoad::retrieveCommandList();
}

//This function receives a Data object
//and converts it into a line of string
//that is ready to be put into response string
string DataProcessor::convertDataObjectToLine(Data task){
	assert ( task.getDesc() != "\0");
	ostringstream outData;
	TimeMacro timeMacroBeg = task.getTimeMacroBeg();
	TimeMacro timeMacroEnd = task.getTimeMacroEnd();
	TimeMicro timeMicroBeg = task.getTimeMicroBeg();
	TimeMicro timeMicroEnd = task.getTimeMicroEnd();
	
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

	string taskString = outData.str();
	return taskString;

}