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
	dataStorage.addTaskList(task); //dataStorage is a DataStorage object initialized in O/C
								   //addTaskList is DataStorage's API to add task  to the private taskList
	ostringstream out;
	out << "'" << task.getDescription() << "'" << "is successfully added" <<endl;
	string addMessage;
	addMessage = out.str();
	return addMessage;
}

string DataProcessor::deleteTask(Data task){
	string taskUniqueNumber = task.getUniqueNumber();
	string taskDescription = task.getDescription();
	ostringstream out;
	if(dataStorage.deleteTaskList(task)){ //deleteTaskList is DataStorage's API to delete specific object in the private taskList
										  //Data Storage return bool
		out << "'" << taskUniqueNumber << " " << taskDescription << "' is deleted successfully" << endl;
	} else {
		out << "'" << taskUniqueNumber << "' does not exist" << endl; 
	}
	string deleteMessage;
	deleteMessage = out.str();
	return deleteMessage;
}

string DataProcessor::display(TimeMacro startTime, TimeMacro endTime){
	vector<Data> taskList; 
	taskList = dataStorage.getTaskList(startTime, endTime); //getTaskList() return vector
	string taskString; 
	taskString = convertTaskListToString(vector<Data> taskList);
	return taskString;
}






//Start of Yang Xiaozhou's part of DataProcessor

//This function reads in the desired keyword to be searched in the current
//task list, all tasks with description containing the keyword will be returned
string DataProcessor::searchTask(string word){
	vector<Data> currTaskList = TaskList.getDataList();
	vector<Data> returnTaskList;
	vector<Data>::iterator iter;
	string taskDescription;
	size_t found;
	
	//For every matched task, store it in returnTaskList
	for(iter = currTaskList.begin(); iter != currTaskList.end(); iter++){
		taskDescription = (*iter).getDesc();
		found = taskDescription.find(word);
		if(found != string::npos){
			returnTaskList.push_back(*iter);
		}
	}

	//Convert the taskList into a string that is ready for UI to display
	string returnTaskListString;
	returnTaskListString = convertTaskListToString(returnTaskList);

}

//This function reads in two TimeMacro objects which indicate the 
//period that the user wants tasks to be cleared.
//Post-condition: tasks under the desired period will be cleared
//from the current taskList
string DataProcessor::clearTask(TimeMacro startTime, TimeMacro endTime){
	DataBase.clearData(startTime, endTime);
	string clearMessage = getClearMessage(startTime, endTime);
	return clearMessage;
}

string DataProcessor::getClearMessage(TimeMacro startTime, TimeMacro endTime){
	string clearMessage;
	ostringstream out;
	out << "All tasks between " << startTime.getDay() << " " << startTime.getDate() << "/" 
		<< startTime.getMonth() << "/" << startTime.getYear()
		<< "-" << endTime.getDay() << " " << endTime.getDate() << "/" << endTime.getMonth << "/"
		<< endTime.getYear() << " are cleared from your schedule." ;
	return clearMessage = out.str();
}

string DataProcessor::editTask(vector<string> infoType, Data task){
	//get taskList currently in display by reference
	//match the task number
	//update the corresponding info

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


