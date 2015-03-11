#ifndef OPERATIONCENTER_H
#define OPERATIONCENTER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <time.h>
#include "Commons.h"
#include "DataProcessor.h"
#include "Parser.h"

using namespace std;
class OperationCenter{
private:
	static const string ADD_COMMAND;
	static const string DELETE_COMMAND;
	static const string DISPLAY_COMMAND;
	static const string CLEAR_COMMAND;
	static const string SORT_COMMAND;
	static const string SEARCH_COMMAND;
	static const string EDIT_COMMAND;
	static const string EXIT_COMMAND;
	static const string EMPTY_RESPONSE;
	static const string IVALID_COMMAND_MESSAGE;

public:

	OperationCenter();
	static vector<string> executeInput (string input);

};

#endif