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
	static string _command;
	static Data _myData;
	static int _taskNo;
	static string _errorMessage;
	static string _directory;

	static void updateCommand (string commandWord) {
		_command = commandWord;
	}

	static void updateTaskNo (int taskNo) {
		_taskNo = taskNo;
	}

	static void updateTimeMicro (TimeMicro timeMicro) {
		_myData.updateTimeMicroBeg (timeMicro);
	}

	static void updateTimeMicroPeriod (TimeMicro timeMicroBeg, TimeMicro timeMicroEnd) {
		_myData.updateTimeMicroBeg (timeMicroBeg);
		_myData.updateTimeMicroEnd (timeMicroEnd);
	}

	static void updateTimeMacro (TimeMacro timeMacro) {
		_myData.updateTimeMacroBeg (timeMacro);
	}

	static void updateTimeMacroPeriod (TimeMacro timeMacroBeg, TimeMacro timeMacroEnd) {
		_myData.updateTimeMacroBeg (timeMacroBeg);
		_myData.updateTimeMacroEnd (timeMacroEnd);
	}

	static void updateDesc (string desc) {
		_myData.updateDesc (desc);
	}

	static void updateErrorMessage (string errorMessage) {
		_errorMessage = errorMessage;
	}

	static void updateStatus (bool status) {
		_myData.updateCompleteStatus (status);
	}

	static void updateDirectory (string directory) {
		_directory = directory;
	}
	

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
	static const char SLASH;
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
	Parser () {
		_command = "";
		_myData;
		_taskNo = 0;
	}

	//getters
    static string Parser::getCommand () {
	    return _command;
    }

    static int Parser::getTaskNo () {
	    return _taskNo;
    }

    static Data getData () {
		return _myData;
	}

	static string getErrorMessage () {
		return _errorMessage;
	}

	static string getDirectory () {
		return _directory;
	}

	static void parseInput (string userInput);
	static string extractCommandWord (string userInput);
	static void checkCommandWord (string userInput, string commandWord);
	static void parseAdd (string userInput, string commandWord);
	static void parseEdit (string userInput, string commandWord);
	static void parseSearch (string userInput, string commandWord);
	static void parseUndo (string userInput, string commandWord);
	static void parseDelete (string userInput, string commandWord);
	static void parseDone (string userInput, string commandWord);
	static void parseUndone (string userInput, string commandWord);
	static void parseShow (string userInput, string commandWord);
	static void parseClear (string userInput, string commandWord);
	static void parsePath (string userInput, string commandWord);
	static void parseHelp (string userInput, string commandWord);
    static void parseDateNumber (string& inputToBeParsesd, TimeMacro& timeMacro);
	static void parseDateAlphabet (string& inputToBeParsesd, TimeMacro& timeMacro);
	static void parseTimeTwentyFour (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd);
	static void parseTimeTwelve (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd);
	static string parseTaskNo (string inputToBeParsed);
	static bool isInteger (string index);
	static int convertStringToInteger (string index);
	static bool isDateNumber (string inputToBeParsed, int& dateInt, int& monthInt);
	static bool isYearNumber (string inputToBeParsed, int& yearInt);
	static bool isDateAlphabet (string inputToBeParsed, int& dateInt);
	static bool isYearAlphabet (string inputToBeParsed, int& yearInt);
	static string convertDateToDayOfTheWeek (int date, int month, int year);
	static bool isStartingTimeTwentyFour (string inputToBeParsed, int& hourInt, int& minuteInt);
	static bool isTimePeriodTwentyFour (string inputToBeParsed, int& hourBegInt, int& hourEndInt, 
		int& minuteBegInt, int& minuteEndInt);
	static bool isStartingTimeTwelve (string inputToBeParsed, int& hourInt, int& minuteInt);
	static bool isTimePeriodTwelve (string inputToBeParsed, int& hourBegInt, int& hourEndInt, 
		int& minuteBegInt, int& minuteEndInt);
	static bool isSlash (string directory);
	static bool isStringEqual (string inputString, vector<string> compString);
	static int convertAlphabetMonthToInteger (string month);
	static void getTodayDate (TimeMacro& timeMacro);
	static void getTomorrowDate (TimeMacro& timeMacro);
	static void getMondayDate (TimeMacro& timeMacro);
	static void getSundayDate (TimeMacro& timeMacro);
	static void getThisMonth (TimeMacro& timeMacroBeg, TimeMacro& timeMacroEnd);
	static bool isLeapYear (int year);
	
};
#endif