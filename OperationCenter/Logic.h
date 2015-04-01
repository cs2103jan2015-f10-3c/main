#ifndef LOGIC_H
#define LOGIC_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <ctime>
#include <chrono>
#include "Commons.h"
#include "Feedback.h"

using namespace std;

class Logic{

private:
	static const string ADD_COMMAND;
	static const string DELETE_COMMAND;
	static const string DISPLAY_COMMAND;
	static const string CLEAR_COMMAND;
	static const string SORT_COMMAND;
	static const string SEARCH_COMMAND;
	static const string EDIT_COMMAND;
	static const string EXIT_COMMAND;
	static const string UNDO_COMMAND;
	static const string EMPTY_RESPONSE;
	static const string IVALID_COMMAND_MESSAGE;
	static int undoCount;


public:
	static void executeInput(string input);
	static void executeCommand(string& returnDisplay, string& returnResponse, string command, Data task, int taskNo, TimeMacro currentTime);
	static void saveData();
	static void loadData(bool& status);
	static string displayIfEmpty(string returnDisplay, TimeMacro current, TimeMacro start, TimeMacro end);
	static string displayToday(string returnDisplay, TimeMacro current);
	static TimeMacro setCurrentTime();
	static string showWelcomeMessage(bool status);
	static string displaySpecificDay(DataProcessor dataProcessor, TimeMacro current);
};

#endif