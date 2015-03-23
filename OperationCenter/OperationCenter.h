#ifndef OPERATIONCENTER_H
#define OPERATIONCENTER_H

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
#include "DataProcessor.h"
#include "Parser.h"

using namespace std;
class OperationCenter{

public:

	OperationCenter() {}
	static void executeInput (string input);
	static string getResponse();
	static string getDisplay();
	static void saveData();
	static void loadData(bool& status);
};

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


public:
	static void executeInput(string input);
	static void saveData();
	static void loadData(bool& status);

};

class Feedback{
private:
	 static string display;
	 static string response;
public:

	static string getDisplay(){
		return display;
	}
	static string getResponse(){
		return response;
	}
	static void updateDisplay(string newDisplay){
		display = newDisplay;
	}
	static void updateResponse(string newResponse){
		response = newResponse;
	}
};

#endif