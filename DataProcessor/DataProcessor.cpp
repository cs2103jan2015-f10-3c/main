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
