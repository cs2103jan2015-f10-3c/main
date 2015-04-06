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
#include <Windows.h>
#include "Commons.h"
#include "DataProcessor.h"
#include "Parser.h"
#include "Logic.h"
#include "Feedback.h"

using namespace std;
class OperationCenter{

public:

	OperationCenter() {}
	static void executeInput (string input);
	static string getResponse();
	static string getDisplay();
	static void saveData();
	static void loadData(bool& status);
	static string showWelcomeMessage(bool status);
	static void clearScreen();
};



#endif