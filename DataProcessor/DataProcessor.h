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
#include "InternalStorage.h"

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
	void undoEditOrClear(vector<Data> latestVector);
	static void showCommands();
	static void saveData();
	static void loadData(bool& status);

	string convertTaskListToString(vector<Data> & taskList);
	string convertDataObjectToString(Data task);
	string convertDataObjectToLine(Data task);
	string getClearMessage();
	string getEditMessage(Data uneditedTask);

};
#endif
