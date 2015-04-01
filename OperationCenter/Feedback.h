#ifndef FEEDBACK_H
#define FEEDBACK_H

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

using namespace std;

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