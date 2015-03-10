#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <time.h>
#include "Commons.h"

using namespace std;

class Parser {
private: 
	string _command;
	Data _myData;
	int _taskNo;

	Parser () {
	}

	Parser (string commandWord, TimeMacro timeMacro, TimeMicro timeMicro, string desc) {
		_command = commandWord;
		_myData.updateTimeMacroBeg (timeMacro);
		_myData.updateTimeMicro (timeMicro);
		_myData.updateDesc (desc);
	}

	Parser (string commandWord, string keyword) {
		_command = commandWord;
		_myData.updateDesc (keyword);
	}

	Parser (string commandWord) {
		_command = commandWord;
	}

	Parser (string commandWord, int taskNo) {
		_command = commandWord;
		_taskNo = taskNo;
	}

	static const int LENGTH_OF_DATE;
    static const string DATE_FIRST_DIGIT;
    static const string DATE_SECOND_DIGIT;
    static const string MONTH_FIRST_DIGIT;
    static const string MONTH_SECOND_DIGIT;
    static const string YEAR_FIRST_DIGIT;
    static const string YEAR_SECOND_DIGIT;
    static const string YEAR_THIRD_DIGIT;
    static const string YEAR_FOURTH_DIGIT;
	static const int LENGTH_OF_STARTING_TIME;
	static const int LENGTH_OF_TIME_PERIOD;
	static const string HOUR_FIRST_DIGIT;
	static const string HOUR_SECOND_DIGIT;
	static const string MINUTE_FIRST_DIGIT;
	static const string MINUTE_SECOND_DIGIT;
	static const int LENGTH_OF_ATTRIBUTE;

public: 

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
	void ParseAdd (string userInput, string commandWord);
	void ParseEdit (string userInput, string commandWord);
	void ParseSearch (string userInput, string commandWord);
	void ParseUndo (string commandWord);
	void ParseDelete (string userInput, string commandWord);
	TimeMacro parseDate (string inputToBeParsesd);
	TimeMicro parseTime (string inputToBeParsed);
	string parseTaskNo (string inputToBeParsed);
	bool isDate (string inputToBeParsed);
	string convertDateToDayOfTheWeek (int date, int month, int year);
	bool isStartingTime (string inputToBeParsed);
	bool isTimePeriod (string inputToBeParsed);
	bool searchSubstring (string string, char substring);
};
#endif