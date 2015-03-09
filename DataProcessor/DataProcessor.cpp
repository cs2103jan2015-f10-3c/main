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

string DataProcessor::display(Time startTime, Time endTime){
	string taskString; 
	taskString = convertTaskListToString(dataStorage.getTaskList(startTime, endTime));
	return taskString;
}