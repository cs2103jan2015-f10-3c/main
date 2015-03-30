#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <assert.h>
#include "Commons.h"
#include "Storing.h"

using namespace std;
class DataProcessor{
private:

	static const string ADD_MESSAGE;
	static const string DELETE_MESSAGE;
	static const string CLEAR_MESSAGE;
	static const string EDIT_MESSAGE;

public:

	DataProcessor(){}
	string addTask(Data task);
	string displayTask(TimeMacro startTime, TimeMacro endTime);
	string deleteTask(int number);
	string clearTask();
	string executeUndo();
	string searchTask(string keyword);
	string editTask(int taskNumber, Data task);
	string markDone(int taskNo);
	static void showCommands();
	static void saveData();
	static void loadData(bool& status);

	string convertTaskListToString(vector<Data> & taskList);
	string convertDataObjectToString(Data task);
	string getClearMessage(TimeMacro startTime, TimeMacro endTime);
	string getEditMessage(Data uneditedTask);

};
#endif
