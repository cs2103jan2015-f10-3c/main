#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <string>
#include <time.h>
#include <exception>
#include "Commons.h"

using namespace std;

class Parser {
private: 

	//private attributes
	string _command;
	Data _myData;
	int _taskNo;
	string _errorMessage;
	string _directory;


	//setters
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

	void updateErrorMessage (string errorMessage) {
		_errorMessage = errorMessage;
	}

	void updateStatus (bool status) {
		_myData.updateCompleteStatus (status);
	}

	void updateDirectory (string directory) {
		_directory = directory;
	}
	

	//private static variables
	static const unsigned int LENGTH_OF_DATE_NUMBER;
	static const unsigned int LENGTH_OF_DATE_ALPHABET;
	static const unsigned int LENGTH_OF_YEAR_ALPHABET;
	static const unsigned int START;
	static const unsigned int ONE;
	static const unsigned int TWO;
	static const unsigned int THREE;
	static const unsigned int FOUR;
	static const unsigned int FIVE;
	static const unsigned int SIX;
	static const unsigned int SEVEN;
	static const unsigned int LENGTH_OF_STARTING_TIME;
	static const unsigned int LENGTH_OF_TIME_PERIOD;
	static const char ERROR_MESSAGE_COMMAND[100];
	static const char ERROR_MESSAGE_INPUT[100];
	static const char ERROR_MESSAGE_EDIT[100];
	static const char ERROR_MESSAGE_TASK_NO[100];
	static const char ERROR_MESSAGE_SHOW[100];
	static const char ERROR_MESSAGE_DIRECTORY[100];
	static const char ERROR_MESSAGE_DATE[100];
	static const char ERROR_MESSAGE_YEAR[100];
	static const char ERROR_MESSAGE_TIME[100];
	static const char ERROR_MESSAGE_DESC[100];


	
public:

	//default constructor
	Parser () {}


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

	string getErrorMessage () {
		return _errorMessage;
	}

	string getDirectory () {
		return _directory;
	}


	//API for OperationCenter to access
	void parseInput (string userInput);
	
	//public methods
	string extractCommandWord (string userInput);
	void checkCommandWord (string userInput, string commandWord);
	void parseAdd (string userInput, string commandWord);
	void parseEdit (string userInput, string commandWord);
	void parseSearch (string userInput, string commandWord);
	void parseUndo (string userInput, string commandWord);
	void parseDelete (string userInput, string commandWord);
	void parseDone (string userInput, string commandWord);
	void parseUndone (string userInput, string commandWord);
	void parseShow (string userInput, string commandWord);
	void parseClear (string userInput, string commandWord);
	void parsePath (string userInput, string commandWord);
	void parseHelp (string userInput, string commandWord);
    void parseDateNumber (string& inputToBeParsesd, TimeMacro& timeMacro);
	void parseDateAlphabet (string& inputToBeParsesd, TimeMacro& timeMacro);
	void parseTimeTwentyFour (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd);
	void parseTimeTwelve (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd);
	string parseTaskNo (string inputToBeParsed);
	bool isInteger (string index);
	int convertStringToInteger (string index);
	bool isDateNumber (string inputToBeParsed, int& dateInt, int& monthInt);
	bool isYearNumber (string inputToBeParsed, int& yearInt);
	bool isDateAlphabet (string inputToBeParsed, int& dateInt);
	bool isYearAlphabet (string inputToBeParsed, int& yearInt);
	string convertDateToDayOfTheWeek (int date, int month, int year);
	bool isStartingTimeTwentyFour (string inputToBeParsed, int& hourInt, int& minuteInt);
	bool isTimePeriodTwentyFour (string inputToBeParsed, int& hourBegInt, int& hourEndInt, 
		int& minuteBegInt, int& minuteEndInt);
	bool isStartingTimeTwelve (string inputToBeParsed, int& hourInt, int& minuteInt);
	bool isTimePeriodTwelve (string inputToBeParsed, int& hourBegInt, int& hourEndInt, 
		int& minuteBegInt, int& minuteEndInt);
	bool isStringEqual (string inputString, vector<string> compString);
	int convertAlphabetMonthToInteger (string month);
	void getTodayDate (TimeMacro& timeMacro);
	void getTomorrowDate (TimeMacro& timeMacro);
	void getMondayDate (TimeMacro& timeMacro);
	void getSundayDate (TimeMacro& timeMacro);
	void getThisMonth (TimeMacro& timeMacroBeg, TimeMacro& timeMacroEnd);
	bool isLeapYear (int year);
	

};
#endif