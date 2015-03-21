#include "DataProcessor.h"

using namespace std;

const string DataProcessor::ADD_MESSAGE = "is added";
const string DataProcessor::DELETE_MESSAGE = "is deleted from BlinkList";
const string DataProcessor::CLEAR_MESSAGE = "all contents are cleared";
const string DataProcessor::EDIT_MESSAGE = "is edited";


//This function reads in the Data object to be added,
//then return the string reporting the adding which contains the descripiton of the data added
string DataProcessor::addTask(Data task){
	DataBase::addData(task); 
	ostringstream out;
	out << convertDataObjectToString (task) << " is added" <<endl;
	string addMessage;
	addMessage = out.str();
	return addMessage;
}

//This function reads in the number of the task to be deleted,
//then return the string reporting the deletion which contains the description of the data deleted
string DataProcessor::deleteTask(int number){
	assert(number > 0);
	ostringstream out;
	out << convertDataObjectToString (DataBase::deleteData(number)) << " is deleted from BlinkList" << endl;
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

void DataProcessor::loadData(){
	DataBase::loadData();
}



//Start of Yang Xiaozhou's part of DataProcessor



//This function reads in two TimeMacro objects which indicate the 
//period that the user wants tasks to be cleared.
//Post-condition: tasks under the desired period will be cleared
//from the current taskList
string DataProcessor::clearTask(TimeMacro startTime, TimeMacro endTime){
	DataBase::clearData(startTime, endTime);
	//string clearMessage = getClearMessage(startTime, endTime);
	//return clearMessage;
	return " all contents are cleared";
}

//This function produces the string that contains the clear feature message
//string DataProcessor::getClearMessage(TimeMacro startTime, TimeMacro endTime){
//	string clearMessage;
//	ostringstream out;
//	out << "All tasks between " << startTime.getDay() << " " << startTime.getDate() << "/" 
//		<< startTime.getMonth() << "/" << startTime.getYear()
//		<< "-" << endTime.getDay() << " " << endTime.getDate() << "/" << endTime.getMonth << "/"
//		<< endTime.getYear() << " are cleared from your schedule." ;
//	return clearMessage = out.str();
//}

//This function reads in the taskNumber of the task that is
//currently in display and the Data object which contains
//the updated information about the task.
//The return string is the successfuly message after edit operation
string DataProcessor::editTask(int taskNumber, Data task){
	Data uneditedTask;
	uneditedTask = DataBase::editData(taskNumber, task);
	string editMessage = getEditMessage(uneditedTask) + " is edited";
	return editMessage;
}



string DataProcessor::executeUndo(){
	string dummy;
	return dummy;
}

//This function reads in a Data object and convert it into a string
//that contains all the information of that data and ready to be displayed
string DataProcessor::convertDataObjectToString(Data task){
	string taskString;
	ostringstream outData;
	TimeMacro timeMacroBeg, timeMacroEnd;
	timeMacroBeg = task.getTimeMacroBeg();
	timeMacroEnd = task.getTimeMacroEnd();
	TimeMicro timeMicroBeg, timeMicroEnd;
	timeMicroBeg = task.getTimeMicroBeg();
	timeMicroEnd = task.getTimeMicroEnd();

	outData << task.getDesc();


	//If there is deadline date associated with the task
	if(timeMacroBeg.getDate() != 0){
		outData << " on " 
			<< timeMacroBeg.getDay() << ", "
				<< timeMacroBeg.getDate() << "-"
				<< timeMacroBeg.getMonth() << "-"
				<< timeMacroBeg.getYear();

	}
	//if(timeMacroEnd.getDate() != 0){
	//	outData << "-"
	//			<< timeMacroEnd.getDate() << ""
	//			<< timeMacroEnd.getMonth() << "/"
	//			<< timeMacroEnd.getYear();
	//}else
	//{
	//	//If there is a start date and no end date specified
	//	
	//}
	
	if(timeMacroBeg.getDate() != 0){
				outData << " ";
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
	
	taskString = outData.str();
	return taskString;

}

//This function reads in the desired keyword to be searched in the current
//task list, all tasks with description containing the keyword will be returned
string DataProcessor::searchTask(string keyword){
	vector<Data>& currTaskList = DataBase::getDataList();
	vector<Data> returnTaskList;
	//vector<Data>::iterator iter;
	string taskDescription;
	size_t found;
	
	//For every matched task, store it in returnTaskList
	for(int i = 0; i != currTaskList.size(); i++){
		taskDescription = currTaskList[i].getDesc();
		found = taskDescription.find(keyword);
		if(found != string::npos){
			DisplayStorage::addData(currTaskList[i]);
		}
	}

	returnTaskList = DisplayStorage::getDisplayList();

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
			<< convertDataObjectToString(taskList[i]) << endl;
		numberOfTask++;
	}

	taskListString = outList.str();
	return taskListString;

}

string DataProcessor::getEditMessage(Data uneditedTask){
	string uneditedTaskString;
	string editMessage;
	uneditedTaskString = convertDataObjectToString(uneditedTask);
	ostringstream out;
	out << uneditedTaskString << " ";
	editMessage = out.str(); 
	
	return editMessage;
}