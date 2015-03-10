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
	string display(TimeMacro startTime, TimeMacro endTime);
	string deleteTask(Data task);
	string clearTask(TimeMacro startTime, TimeMacro endTime);
	string executeUndo();
	string searchTask(string word);
	string editTask(vector<string> infoType, Data task);

	string convertTaskListToString(vector<Data> taskList);
	//new function
	string getClearMessage(TimeMacro startTime, TimeMacro endTime)

};
#endif