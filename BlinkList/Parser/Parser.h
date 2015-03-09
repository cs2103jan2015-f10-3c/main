#ifndef PARSER_H
#define PARSER_H
#include <string>
#include <time.h>
#include "Commons.h"

using namespace std;

class Parser {
private: 
	string _command;
	int _taskNo;
	string _taskDesc;
	string _keyword;
	TimeMicro _timeMicro;
	TimeMacro _timeMacroBeg;
	TimeMacro _timeMacroEnd;

	Parser () {
	}

	Parser (string commandWord, TimeMacro timeMacroBeg, TimeMicro timeMicro, string desc) {
		_command = commandWord;
		_timeMacroBeg = timeMacroBeg;
		_timeMicro = timeMicro;
		_taskDesc = desc;
	}

	Parser (string commandWord, string keyword) {
		_command = commandWord;
		_keyword = keyword;
	}

	Parser (string commandWord) {
		_command = commandWord;
	}

	Parser (string commandWord, int taskNo) {
		_command = commandWord;
		_taskNo = taskNo;
	}
/*
	Parser (TimeMacro timeMacro) {
		_myData.updateTimemacro (timeMacro);
	}
	*/
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
	string getCommand ();
	int getTaskNo ();
	string getTaskDesc ();
	string getKeyword ();
	TimeMicro getTimeMicro ();
	TimeMacro getTimeMacroBeg ();
	TimeMacro getTimeMacroEnd ();


	Parser parseInput (string userInput);
	string extractCommandWord (string userInput);
	Parser ParseAdd (string userInput, string commandWord, Parser returnInput);
	Parser ParseEdit (string userInput, string commandWord, Parser returnInput);
	Parser ParseSearch (string userInput, string commandWord, Parser returnInput);
	Parser ParseUndo (string commandWord, Parser returnInput);
	Parser ParseDelete (string userInput, string commandWord, Parser returnInput);
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