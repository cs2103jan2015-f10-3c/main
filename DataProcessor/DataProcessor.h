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

	static const char ADD_MESSAGE[100];
	static const char DELETE_MESSAGE[100];
	static const char CLEAR_MESSAGE[100];
	static const char EDIT_MESSAGE[100];
	static const char UNDO_MESSAGE[100];
	static const char DONE_MESSAGE[100];
	static const char UNDONE_MESSAGE[100];

	static const char ADD_COMMAND[100];
	static const char DELETE_COMMAND[100];
	static const char SHOW_COMMAND[100];
	static const char CLEAR_COMMAND[100];
	static const char EDIT_COMMAND[100];
	static const char NO_DATE[100];

	static const unsigned int TIME_WIDTH;
	static const unsigned int TIME_10;
	static const unsigned int NO_TIME;
	static const unsigned int DATE_WIDTH;
	static const unsigned int DAY_WIDTH;
	static const unsigned int WINDOW_WIDTH;

	static const char EXCEPTION_INVALID_TASKNUMBER[100];
	static const char EXCEPTION_EMPTY_KEYWORD[100];
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
	static void undoEditOrClear(Storing & storing, vector<Data> & latestVector);
	static void getTimeObject(TimeMacro & timeMacroBeg,TimeMicro & timeMicroBeg,
							  TimeMicro & timeMicroEnd, Data task);

	
	string convertTaskListToString(vector<Data> & taskList);
	string convertDataObjectToString(Data task);
	string convertDataObjectToLine(Data task);
	string getClearMessage();
	string getEditMessage(Data uneditedTask);
	string getDoneMessage(Data targetData);
	string getUndoneMessage(Data targetData);
	string getDescriptionLine(Data task);
	string getDayLine(TimeMacro timeMacroBeg);
	string getTimeLine(TimeMicro timeMicroBeg, TimeMicro timeMicroEnd);
	string getDateLine(TimeMacro timeMacroBeg);

};
#endif
