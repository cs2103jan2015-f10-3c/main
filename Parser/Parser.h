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
	string _command;
	Data _myData;
	int _taskNo;
	string _errorMessage;
	string _directory;

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
	

	char message[100];
	static const unsigned int LENGTH_OF_DATE_FULL_NUMBER;
	static const unsigned int LENGTH_OF_DATE_ABBRE_NUMBER;
	static const unsigned int LENGTH_OF_DATE_FULL_ALPHABET;
	static const unsigned int LENGTH_OF_DATE_ABBRE_ALPHABET;
    static const char DATE_FIRST_DIGIT[100];
    static const char MONTH_FIRST_DIGIT[100];
    static const char YEAR_FIRST_DIGIT[100];
	static const unsigned int LENGTH_OF_STARTING_TIME;
	static const unsigned int LENGTH_OF_TIME_PERIOD;
	static const char TWENTY_FOUR_HOUR_FIRST_DIGIT[100];
	static const char TWELVE_HOUR_FIRST_DIGIT[100];
	static const char MINUTE_FIRST_DIGIT[100];
	static const char NON_NEGATIVE_DIGIT[100];
	static const char POSITIVE_DIGIT[100];
	static const char ERROR_MESSAGE_COMMAND[100];
	static const char ERROR_MESSAGE_INPUT[100];
	static const char ERROR_MESSAGE_EDIT[100];
	static const char ERROR_MESSAGE_TASK_NO[100];
	static const char ERROR_MESSAGE_SHOW[100];
	static const char ERROR_MESSAGE_DIRECTORY[100];
	static const char ERROR_MESSAGE_DATE[100];
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

	void parseInput (string userInput);
	string extractCommandWord (string userInput);
	void checkCommandWord (string commandWord, string userInput);
	void parseAdd (string userInput, string commandWord);
	void parseEdit (string userInput, string commandWord);
	void parseSearch (string userInput, string commandWord);
	void parseUndo (string commandWord);
	void parseDelete (string userInput, string commandWord);
	void parseDone (string userInput, string commandWord);
	void parseShow (string userInput, string commandWord);
	void parseClear (string userInput, string commandWord);
	void parseSaveLoad (string userInput, string commandWord);
    void parseDateNumber (string& inputToBeParsesd, TimeMacro& timeMacro);
	void parseDateAlphabet (string& inputToBeParsesd, TimeMacro& timeMacro);
	void parseTimeTwentyFour (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd);
	void parseTimeTwelve (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd);
	string parseTaskNo (string inputToBeParsed);
	bool isInteger (string index);
	int convertStringToInteger (string index);
	bool isDateNumber (string inputToBeParsed);
	bool isYearNumber (string inputToBeParsed);
	bool isDateAlphabet (string inputToBeParsed);
	bool isYearAlphabet (string inputToBeParsed);
	string convertDateToDayOfTheWeek (int date, int month, int year);
	bool isStartingTimeTwentyFour (string inputToBeParsed);
	bool isTimePeriodTwentyFour (string inputToBeParsed);
	bool isStartingTimeTwelve (string inputToBeParsed);
	bool isTimePeriodTwelve (string inputToBeParsed);
	bool searchSubstring (const string timeString, char substring);
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