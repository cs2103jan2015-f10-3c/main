#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <string>
#include <time.h>
#include "Commons.h"

using namespace std;

class Parser {
private: 
	string _command;
	Data _myData;
	int _taskNo;

	void updateCommand (string commandWord) {
		_command = commandWord;
	}

	void updateTaskNo (int taskNo) {
		_taskNo = taskNo;
	}

	void updateTimeMicro (TimeMicro timeMicro) {
		_myData.updateTimeMicroBeg (timeMicro);
	}

	void updateTimeMicroPeriod (TimeMicro timeMicroBeg, TimeMicro timeMicroEnd) {
		_myData.updateTimeMicroBeg (timeMicroBeg);
		_myData.updateTimeMicroEnd (timeMicroEnd);
	}

	void updateTimeMacro (TimeMacro timeMacro) {
		_myData.updateTimeMacroBeg (timeMacro);
	}

	void updateTimeMacroPeriod (TimeMacro timeMacroBeg, TimeMacro timeMacroEnd) {
		_myData.updateTimeMacroBeg (timeMacroBeg);
		_myData.updateTimeMacroEnd (timeMacroEnd);
	}

	void updateDesc (string desc) {
		_myData.updateDesc (desc);
	}
	

	static const unsigned int LENGTH_OF_DATE;
    static const string DATE_FIRST_DIGIT;
    static const string DATE_SECOND_DIGIT;
    static const string MONTH_FIRST_DIGIT;
    static const string MONTH_SECOND_DIGIT;
    static const string YEAR_FIRST_DIGIT;
    static const string YEAR_SECOND_DIGIT;
    static const string YEAR_THIRD_DIGIT;
    static const string YEAR_FOURTH_DIGIT;
	static const unsigned int LENGTH_OF_STARTING_TIME;
	static const unsigned int LENGTH_OF_TIME_PERIOD;
	static const string HOUR_FIRST_DIGIT;
	static const string HOUR_SECOND_DIGIT;
	static const string MINUTE_FIRST_DIGIT;
	static const string MINUTE_SECOND_DIGIT;
	//static const unsigned int LENGTH_OF_ATTRIBUTE;

public: 
	//default constructor
	Parser () {
		_command = "";
		_myData;
		_taskNo = 0;
	}

	//getters
    string Parser::getCommand () {
	    return _command;
    }

    int Parser::getTaskNo () {
	    return _taskNo;
    }

    Data getData () {
		return _myData;
	}


	void parseInput (string userInput);
	string extractCommandWord (string userInput);
	void parseAdd (string userInput, string commandWord);
	void parseEdit (string userInput, string commandWord);
	void parseSearch (string userInput, string commandWord);
	void parseUndo (string commandWord);
	void parseDelete (string userInput, string commandWord);
	void parseDisplay (string userInput, string commandWord);
    void parseDate (string inputToBeParsesd, TimeMacro& timeMacro);
	void parseTime (string inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd);
	string parseTaskNo (string inputToBeParsed);
	bool isDate (string inputToBeParsed);
	string convertDateToDayOfTheWeek (int date, int month, int year);
	bool isStartingTime (string inputToBeParsed);
	bool isTimePeriod (string inputToBeParsed);
	bool searchSubstring (string timeString, char substring);
	void getTodayDate (TimeMacro& timeMacro);
	void getTomorrowDate (TimeMacro& timeMacro);
	void getThisMonth (TimeMacro& timeMacroBeg, TimeMacro& timeMacroEnd);
	bool isLeapYear (int year);
	
};
#endif