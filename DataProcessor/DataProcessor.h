#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Commons.h"
#include "DataStorage.h"

using namespace std;
class DataProcessor{


public:

	DataProcessor();
	string showWelcomeMessage();
	string addTask(Data task);
	string displayTask(TimeMacro startTime, TimeMacro endTime);
	string deleteTask(int number);
	string clearTask(TimeMacro startTime, TimeMacro endTime);
	string executeUndo();
	string searchTask(string keyword);
	string editTask(int taskNumber, Data task);

	string convertTaskListToString(vector<Data> taskList);
	string convertDataObjectToString(Data task);
	//new function
	string getClearMessage(TimeMacro startTime, TimeMacro endTime);
	string getEditMessage(Data uneditedTask);

};
#endif