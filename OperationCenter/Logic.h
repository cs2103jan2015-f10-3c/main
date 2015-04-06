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
	static const char COMMA[10];
	static const char DASH[10];
	static const char COLON[10];
	static const char ADD_COMMAND[100];
	static const char DELETE_COMMAND[100];
	static const char SHOW_COMMAND[100];
	static const char CLEAR_COMMAND[100];
	static const char SORT_COMMAND[100];
	static const char SEARCH_COMMAND[100];
	static const char EDIT_COMMAND[100];
	static const char EXIT_COMMAND[100];
	static const char UNDO_COMMAND[100];
	static const char UNDONE_COMMAND[100];
	static const char HELP_REQUEST[100];
	static const char EMPTY_RESPONSE[100];
	static const char IVALID_COMMAND_MESSAGE[100];
	static const char DONE_COMMAND[100];
	static const char SHOW_COMMANDS[100];
	static const char SHOW_FEATURES[100];
	static const char SHOW_DONE[100];
	static const char SHOW_FLOAT[100];
	static const char SHOW_TODAY[100];
	static const char FLOAT_NOT_FOUND_MESSAGE[100];
	static const char DONE_NOT_FOUND_MESSAGE[100];
	static const char SEARCH_NOT_FOUND_MESSAGE[100];
	static const char HELP_MESSAGE[200];
	static const char CANNOT_UNDO_MESSAGE[200];
	static const char WELCOME_MESSAGE[100];
	static const char TODAY_MESSAGE[100];
	static const char NO_SAVED_DATA_MESSAGE[100];
	static const char NO_TASK_TO_SHOW_MESSAGE[100];
	static const char NO_TASK_TODAY_MESSAGE[100];
	static const char NO_TASK_ON_MESSAGE[100];
	static const char AGENDA_FOR_MESSAGE[100];
	static const char NO_FLOAT_TASK_MESSAGE[100];
	static const char FLOAT_TASK_MESSAGE[100];
	static const char PATH_COMMAND[100];
	static const char LOAD_COMMAND[100];
	static const char PATH_MESSAGE[100];
	static const char REINPUT_PATH[100];

	static int undoCount;


public:
	static void executeInput(string input);
	static void executeCommand(string& returnDisplay, string& returnResponse, string command, string directory, Data task, int taskNo, TimeMacro currentTime);
	static void saveData();
	static void loadData(bool& status);
	static string displayIfEmpty(string returnDisplay, TimeMacro current, TimeMacro start, TimeMacro end);
	static string displayToday(string returnDisplay, TimeMacro current);
	static TimeMacro setCurrentTime();
	static string showWelcomeMessage(bool status);
	static string displaySpecificDay(DataProcessor dataProcessor, TimeMacro current);
	static void updateUndoCount(string command);
	static void checkCommand(string command);
	static void clearScreen();
};

#endif