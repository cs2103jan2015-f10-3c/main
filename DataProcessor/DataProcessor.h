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
	Data _latestData;

public:

	DataProcessor(){}
	void setLatestData(Data data);
	Data getLatestData();
	
	string addTask(Data task);
	string displayTask(TimeMacro startTime, TimeMacro endTime);
	string deleteTask(int number);
	string clearTask();
	string executeUndo();
	string searchTask(string keyword);
	string editTask(int taskNumber, Data task);
	string markDone(int taskNo);
	string unDone(int taskNo);
	string showFloat();
	string showDone();
	static string showCommands();
	static string showFeatures();
	static void saveData();
	static void loadData(bool& status);
	static void clearDisplayList();
	
	string convertTaskListToString(vector<Data> & taskList);
	string convertDataObjectToString(Data task);
	string convertDataObjectToLine(Data task);
	string getClearMessage();
	string getEditMessage(Data uneditedTask);

};
#endif
