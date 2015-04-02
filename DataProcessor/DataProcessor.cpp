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
	Storing storing;
	storing.addData(task); 
	ostringstream out;
	out << convertDataObjectToLine(task) << " is added" << endl;
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
	out << convertDataObjectToLine(storing.deleteData(number)) << " is deleted from BlinkList" << endl;
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



//Start of Yang Xiaozhou's part of DataProcessor





//This function reads in the taskNumber of the task that is
//currently in display and the Data object which contains
//the updated information about the task.
//The return string is the successfuly message after edit operation
string DataProcessor::editTask(int taskNumber, Data task){
	ofstream outData;
	Storing storing;
	outData.open("log.txt");
	if(taskNumber <= 0){
		outData << "handling exception:invalid tasknumber";
		throw std::exception("Invalid Tasknumber Entered");
	}
	Data uneditedTask;
	outData << "start editing data";
	uneditedTask = storing.changeData(taskNumber, task);
	string editMessage = getEditMessage(uneditedTask) + " is edited\n";
	outData << "edit data is done";
	setLatestData(uneditedTask);
	return editMessage;

}

void DataProcessor::clearDisplayList(){
	Storing storing;
	storing.clearDisplayList();
}

string DataProcessor::clearTask(){
	Storing storing;
	storing.clearDataList();

	return "response";
}


string DataProcessor::executeUndo(){
	Data latestData;
	string latestCommand;
	vector<Data> latestVector;
	Storing storing; 

	latestVector = storing.getLatestVector();
	latestCommand = storing.getLatestCommand();
	latestData = storing.getLatestData();

	if (latestCommand == "add"){
		storing.undoAdd();
	}
	else if (latestCommand == "delete"){
		storing.addData(latestData);
	}
	else if (latestCommand == "edit"){
		storing.clearDataList();
		for(int i = 0; i != latestVector.size(); i++){
			storing.addData(latestVector[i]);
		}
	}
	else if (latestCommand == "clear"){
		storing.clearDataList();
		for(int i = 0; i != latestVector.size(); i++){
			storing.addData(latestVector[i]);
		}
	}
	setLatestData(latestData);
	string undoMessage = "You have undone your operation";
	return undoMessage;
}

//This function reads in a Data object and convert it into a string
//that contains all the information of that data and ready to be displayed
string DataProcessor::convertDataObjectToString(Data task){
	assert ( task.getDesc() != "\0");
	string taskString;
	ostringstream outData;
	TimeMacro timeMacroBeg, timeMacroEnd;
	timeMacroBeg = task.getTimeMacroBeg();
	timeMacroEnd = task.getTimeMacroEnd();
	TimeMicro timeMicroBeg, timeMicroEnd;
	timeMicroBeg = task.getTimeMicroBeg();
	timeMicroEnd = task.getTimeMicroEnd();
	int descriptionWidth = task.getDesc().length();
	int dateWidth = 40;
	string timeMicroString = "   ";
	outData << setw(descriptionWidth) << left << task.getDesc() << endl;

	outData << "   ";
	if(timeMacroBeg.getDay() != "undefined"){
		outData << setfill(' ') << setw(13) << timeMacroBeg.getDay();
	}
	else{
		outData << setfill(' ') << setw(13);
	}

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
	outData << setw(17) << left << timeMicroString;
	//If there is deadline date associated with the task
	if(timeMacroBeg.getDate() != 0){
		outData << setw(dateWidth) << right
				<< timeMacroBeg.getDate() << "-"
				<< timeMacroBeg.getMonth() << "-"
				<< timeMacroBeg.getYear();

	}

	
	taskString = outData.str();
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
	
	Storing storing;
	storing.clearDisplayList();
	vector<Data> returnTaskList;
	outData << "update current displayList to display matched tasks";
	returnTaskList = storing.displaySearch(keyword);

	//Convert the taskList into a string that is ready for UI to display
	string returnTaskListString;
	returnTaskListString = convertTaskListToString(returnTaskList);
	return returnTaskListString;

}

//This function reads in a vector of Data object and subsequently converts
//them into a string that contains all datas in the vector
//The string will be ready for display by UI
string DataProcessor::convertTaskListToString(vector<Data>& taskList){
	string taskListString;
	ostringstream outList;
	int numberOfTask = 1;
	for(int i = 0; i != taskList.size(); i++){
		outList << numberOfTask << ". "
				<< convertDataObjectToString(taskList[i]) << endl
				<< setfill('*') << setw(81)
				<< "\n";
		numberOfTask++;
	}
	assert (numberOfTask >= 1);

	taskListString = outList.str();
	return taskListString;

}

string DataProcessor::getEditMessage(Data uneditedTask){
	assert (uneditedTask.getDesc() != "\0");
	string uneditedTaskString;
	string editMessage;
	uneditedTaskString = convertDataObjectToString(uneditedTask);
	ostringstream out;
	out << uneditedTaskString << " ";
	editMessage = out.str(); 
	
	return editMessage;
}

//this function reads in the task number 
//and update the status of the corresponding
//task
string DataProcessor::markDone(int taskNo){
	ostringstream outData;
	Data targetData;
	Storing storing;

	targetData = storing.getData(taskNo);
	targetData.updateCompleteStatus(true);
	storing.changeData(taskNo, targetData);
	outData << convertDataObjectToLine(targetData) << " is done";
	return outData.str();
}

//This function calls up a list of commands 
//available at BlinkList
string DataProcessor::showCommands(){
	Storing storing;
	string commandList = storing.retrieveCommandList();
	return commandList;
}

//This function calls up a list of features
//features will be more elaborated than command file
string DataProcessor::showFeatures(){
	Storing storing;
	string featureList = storing.retrieveFeatureList();
	return featureList;
}

//This function receives a Data object
//and converts it into a line of string
//that is ready to be put into response string
string DataProcessor::convertDataObjectToLine(Data task){
	assert ( task.getDesc() != "\0");
	setLatestData(task);
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

//This function gets a list of floating tasks
//and return it to Operation Center for displaying
string DataProcessor::showFloat(){
	Storing storing;
	vector<Data> floatingTaskList = storing.displayfloat();
	string floatingTaskListString = convertTaskListToString(floatingTaskList);
	return floatingTaskListString;
}

//This function get a list of completed tasks
//and return it to Operation Center for displaying
string DataProcessor::showDone(){
	Storing storing;
	vector<Data> completedTaskList = storing.displayDone();
	string completedTaskListString = convertTaskListToString(completedTaskList);
	return completedTaskListString;
}