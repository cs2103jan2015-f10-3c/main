//@author A0093895J
#ifndef PARSER_H
#define PARSER_H
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <assert.h>
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
	static const unsigned int LENGTH_OF_STARTING_TIME;
	static const unsigned int LENGTH_OF_TIME_PERIOD;
	static const unsigned int START_OF_YEAR;
	static const unsigned int YEAR_MIN;
	static const unsigned int YEAR_MAX;

	static const unsigned int ZERO;
	static const unsigned int ONE;
	static const unsigned int TWO;
	static const unsigned int THREE;
	static const unsigned int FOUR;
	static const unsigned int FIVE;
	static const unsigned int SIX;
	static const unsigned int SEVEN;
	static const unsigned int EIGHT;
	static const unsigned int NINE;
	static const unsigned int TEN;
	static const unsigned int ELEVEN;
	static const unsigned int TWELVE;
	static const unsigned int TWENTY_THREE;
	static const unsigned int TWENTY_EIGHT;
	static const unsigned int TWENTY_NINE;
	static const unsigned int THIRTY;
	static const unsigned int THIRTY_ONE;
	static const unsigned int FIFTY_NINE;
	static const unsigned int HUNDRAD;
	static const unsigned int FOUR_HUNDRAD;
	static const char AM[100];
	static const char PM[100];
	static const char M[100];
	
	static const unsigned int TIMEMICRO_INITIAL;
	static const char EMPTY_STRING[100];
	static const char SPACE[100];
	static const char SLASH[100];
	static const char SPACE_SLASH[100];
	static const char COLON[100];
	static const char DOT[100];
	static const char DASH[100];
	
	static const char JAN_CAP[100];
	static const char FEB_CAP[100];
	static const char MAR_CAP[100];
	static const char APR_CAP[100];
	static const char MAY_CAP[100];
	static const char JUN_CAP[100];
	static const char JUL_CAP[100];
	static const char AUG_CAP[100];
	static const char SEP_CAP[100];
	static const char OCT_CAP[100];
	static const char NOV_CAP[100];
	static const char DEC_CAP[100];
	static const char JAN_SMALL[100];
	static const char FEB_SMALL[100];
	static const char MAR_SMALL[100];
	static const char APR_SMALL[100];
	static const char MAY_SMALL[100];
	static const char JUN_SMALL[100];
	static const char JUL_SMALL[100];
	static const char AUG_SMALL[100];
	static const char SEP_SMALL[100];
	static const char OCT_SMALL[100];
	static const char NOV_SMALL[100];
	static const char DEC_SMALL[100];

	static const char MONDAY[100];
	static const char TUESDAY[100];
	static const char WEDNESDAY[100];
	static const char THURSDAY[100];
	static const char FRIDAY[100];
	static const char SATURDAY[100];
	static const char SUNDAY[100];

	static const char COMMAND_ADD[100];
	static const char COMMAND_EDIT[100];
	static const char COMMAND_SEARCH[100];
	static const char COMMAND_UNDO[100];
	static const char COMMAND_DELETE[100];
	static const char COMMAND_DONE[100];
	static const char COMMAND_UNDONE[100];
	static const char COMMAND_SHOW[100];
	static const char COMMAND_CLEAR[100];
	static const char COMMAND_PATH[100];
	static const char COMMAND_HELP[100];
	static const char COMMAND_TODAY[100];
	static const char COMMAND_TOMORROW[100];
	static const char COMMAND_THIS_WEEK[100];
	static const char COMMAND_THIS_MONTH[100];
	static const char COMMAND_COMMANDS[100];
	static const char COMMAND_FLOAT[100];
	static const char COMMAND_FEATURES[100];

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

	static const char LOG_START[100];
	static const char LOG_SUCCESS[100];
	static const char LOG_ERROR[100];

	
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