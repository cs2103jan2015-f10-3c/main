#include "DataProcessor.h"

using namespace std;

DataProcessor::DataProcessor(){
}

string DataProcessor::showWelcomeMessage(){
	string welcomeMessage;
	welcomeMessage = "Welcome to BlinkList";
	return welcomeMessage;
}

string DataProcessor::addTask(Data task){
	DataBase::addData(task); //dataStorage is a DataStorage object initialized in O/C
								   //addTaskList is DataStorage's API to add task  to the private taskList
	ostringstream out;
	out << "'" << task.getDesc() << "'" << "is successfully added" <<endl;
	string addMessage;
	addMessage = out.str();
	return addMessage;
}

string DataProcessor::deleteTask(int number){
	Data data = DataBase::deleteData(number);
	ostringstream out;
	out << "'" << data.getDesc() <<  "' is deleted" << endl;
	string deleteMessage;
	deleteMessage = out.str();
	return deleteMessage;
}

string DataProcessor::displayTask(TimeMacro startTime, TimeMacro endTime){
	string taskString; 
	taskString = convertTaskListToString(DisplayStorage::getDisplayList(startTime, endTime));
	return taskString;
}






//Start of Yang Xiaozhou's part of DataProcessor

//This function reads in the desired keyword to be searched in the current
//task list, all tasks with description containing the keyword will be returned
string DataProcessor::searchTask(string keyword){
	vector<Data> currTaskList = DataBase::getDataList(keyword);
	vector<Data> returnTaskList;
	vector<Data>::iterator iter;
	string taskDescription;
	size_t found;
	
	//For every matched task, store it in returnTaskList
	for(iter = currTaskList.begin(); iter != currTaskList.end(); iter++){
		taskDescription = (*iter).getDesc();
		found = taskDescription.find(keyword);
		if(found != string::npos){
			returnTaskList.push_back(*iter);
		}
	}

	//Update current display list to show matched tasks
	DisplayStorage::updateDisplayList(returnTaskList);

	//Convert the taskList into a string that is ready for UI to display
	string returnTaskListString;
	returnTaskListString = convertTaskListToString(returnTaskList);
	return returnTaskListString;

}

//This function reads in two TimeMacro objects which indicate the 
//period that the user wants tasks to be cleared.
//Post-condition: tasks under the desired period will be cleared
//from the current taskList
string DataProcessor::clearTask(TimeMacro startTime, TimeMacro endTime){
	DataBase::clearData(startTime, endTime);
	string clearMessage = getClearMessage(startTime, endTime);
	return clearMessage;
}

//This function produces the string that contains the clear feature message
string DataProcessor::getClearMessage(TimeMacro startTime, TimeMacro endTime){
	string clearMessage;
	ostringstream out;
	out << "All tasks between " << startTime.getDay() << " " << startTime.getDate() << "/" 
		<< startTime.getMonth() << "/" << startTime.getYear()
		<< "-" << endTime.getDay() << " " << endTime.getDate() << "/" << endTime.getMonth << "/"
		<< endTime.getYear() << " are cleared from your schedule." ;
	return clearMessage = out.str();
}

//This function reads in the taskNumber of the task that is
//currently in display and the Data object which contains
//the updated information about the task.
//The return string is the successfuly message after edit operation
string DataProcessor::editTask(int taskNumber, Data task){
	Data uneditedTask;
	uneditedTask = DisplayStorage::editData(taskNumber, task);
	string editMessage = getEditMessage(uneditedTask);

	return editMessage;
}

string getEditMessage(Data uneditedTask){
	string uneditedTaskString;
	string editMessage;
	uneditedTaskString = convertDataObjectToString(uneditedTask);
	ostringstream out;
	out << uneditedTaskString << " is edited successfully.";
	editMessage = out.str(); 
	
	return editMessage;
}

string DataProcessor::executeUndo(){

}

//This function reads in a Data object and convert it into a string
//that contains all the information of that data and ready to be displayed
string convertDataObjectToString(Data task){
	string taskString;
	ostringstream outData;
	outData << task.getTimeMacro << " " 
			<< task.getTimeMicro << " " 
			<< task.getDesc << endl;
	taskString = outData.str();
	return taskString;

}

//This function reads in a vector of Data object and subsequently converts
//them into a string that contains all datas in the vector
//The string will be ready for display by UI
string convertTaskListToString(vector<Data> taskList){
	string taskListString;
	ostringstream outList;
	vector<Data>::iterator iter;
	int numberOfTask = 1;
	for(iter = taskList.begin(); iter != taskList.end(); iter++){
		outList << numberOfTask << ". "
				<< convertDataObjectToString(*iter); 
		numberOfTask++;
	}

	taskListString = outList.str();
	return taskListString;

}


