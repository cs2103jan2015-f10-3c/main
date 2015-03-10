#include "Parser.h"

static const int LENGTH_OF_DATE = 10;  //"dd/mm/yyyy"
static const string DATE_FIRST_DIGIT = "0123";
static const string DATE_SECOND_DIGIT = "0123456789";
static const string MONTH_FIRST_DIGIT = "01";
static const string MONTH_SECOND_DIGIT = "0123456789";
static const string YEAR_FIRST_DIGIT = "2";
static const string YEAR_SECOND_DIGIT = "0123456789";
static const string YEAR_THIRD_DIGIT = "0123456789";
static const string YEAR_FOURTH_DIGIT = "0123456789";
static const int LENGTH_OF_STARTING_TIME = 5;  //"09:00"
static const int LENGTH_OF_TIME_PERIOD = 11;  //"09:00-10:30"
static const string HOUR_FIRST_DIGIT = "012";
static const string HOUR_SECOND_DIGIT = "01234567890";
static const string MINUTE_FIRST_DIGIT = "012345";
static const string MINUTE_SECOND_DIGIT = "0123456789";
static const int LENGTH_OF_ATTRIBUTE = 4;


void Parser::parseInput (string userInput) {
	string commandWord;

	commandWord = extractCommandWord (userInput); //not sure
	if (commandWord == "add") {
		ParseAdd (userInput, commandWord);
	}
	else if (commandWord == "edit") {
		ParseEdit (userInput, commandWord);
	}
	else if (commandWord == "search") {
		ParseSearch (userInput, commandWord);
	}
	else if (commandWord == "undo") {
		ParseUndo (commandWord);
	}
	else if (commandWord == "delete") {
		ParseDelete (userInput, commandWord);
	}
	else if (commandWord == "display") {
		ParseDisplay (userInput, commandWord);
	}
}

string Parser::extractCommandWord (string userInput) {
	int end = 0;
	string commandWord;
	end = userInput.find_first_of (" ");
	commandWord = userInput.substr (0, end);
	return commandWord;
}

//Assume a task will always have a description
void Parser::ParseAdd (string userInput, string commandWord) {
	Parser returnInput;
	TimeMacro timeMacroBeg;
	TimeMicro timeMicro;
	string inputToBeParsed = userInput;
	string desc;
	inputToBeParsed = inputToBeParsed.substr (commandWord.size() + 1);
	timeMacroBeg = parseDate (inputToBeParsed);
	if (isDate (inputToBeParsed)) {
        inputToBeParsed = inputToBeParsed.substr (LENGTH_OF_DATE);
	}
	timeMicro = parseTime (inputToBeParsed);
	if (isTimePeriod (inputToBeParsed)) {
		desc = inputToBeParsed.substr (LENGTH_OF_TIME_PERIOD);
	}
	if (isStartingTime (inputToBeParsed)) {
		desc = inputToBeParsed.substr (LENGTH_OF_STARTING_TIME);
	}
	returnInput = Parser (commandWord, timeMacroBeg, timeMicro, desc);
}

//assume desc put as the last one
void Parser::ParseEdit (string userInput, string commandWord) {
	Parser returnInput;
	TimeMacro timeMacro;
	TimeMicro timeMicro;
	string desc;
	string inputToBeParsed = userInput;
	string index = parseTaskNo (string inputToBeParsed);
	int taskNo = atoi (index.c_str());

	inputToBeParsed = inputToBeParsed.substr(index.size () + 1);
	int end = 0;
	string attribute;
	int end = inputToBeParsed.find_first_of (' ');
	while (end != string::npos) {
		attribute = inputToBeParsed.substr (0, end);
		inputToBeParsed = inputToBeParsed.substr (LENGTH_OF_ATTRIBUTE + 1);
		if (attribute == "date") {
			timeMacro = parseDate (inputToBeParsed);
			inputToBeParsed = inputToBeParsed.substr (0, LENGTH_OF_DATE + 1);
		}
		else if (attribute == "time") {
			timeMicro = parseTime (inputToBeParsed);
			if (isStartingTime (inputToBeParsed)) {
                inputToBeParsed = inputToBeParsed.substr (0, LENGTH_OF_STARTING_TIME + 1);
			}
			else if (isTimePeriod (inputToBeParsed)) {
				inputToBeParsed = inputToBeParsed.substr (0, LENGTH_OF_TIME_PERIOD + 1);
			}
		}
		else if (attribute == "desc") {
            string desc = inputToBeParsed.substr (5);
			inputToBeParsed = "";
		}
		end = inputToBeParsed.find_first_of (' ');
	}
	returnInput = Parser (commandWord, timeMacro, timeMicro, desc);
}

void Parser::ParseSearch (string userInput, string commandWord) {
	Parser returnInput;
	string desc = userInput.substr (commandWord.size() + 1);
	returnInput = Parser (commandWord, desc);
}

void Parser::ParseUndo (string commandWord) {
	Parser returnInput;
	returnInput = Parser (commandWord);
}

void Parser::ParseDelete (string userInput, string commandWord) {
	Parser returnInput;
	string index = userInput.substr (commandWord.size() + 1);
	int taskNo = atoi (index.c_str());
	returnInput = Parser (commandWord, taskNo);
}

void Parser::ParseDisplay (string userInput, string commandWord) {
	Parser returnInput;
	TimeMacro timeMacroBeg;
	TimeMacro timeMacroEnd;

	string period = userInput.substr (commandWord.size() + 1);

	if (period == "today") {
		getTodayDate (timeMacroBeg);
	}
	else if (period == "tomorrow") {
		getTomorrowDate (timeMacroBeg);
	}
	else if (period == "this month") {
		getThisMonth (timeMacroBeg, timeMacroEnd);
	}
	returnInput = Parser (commandWord, timeMacroBeg, timeMacroEnd);
}

TimeMacro Parser::parseDate (string inputToBeParsesd) {
	TimeMacro timeMacro;
	if (isDate (inputToBeParsesd)) {
		string date = inputToBeParsesd.substr (0, 2);
		string month = inputToBeParsesd.substr (3, 2);
		string year = inputToBeParsesd.substr (6, 4);
		int dateInt = atoi (date.c_str());
		int monthInt = atoi (month.c_str());
		int yearInt = atoi (year.c_str());
		string day = convertDateToDayOfTheWeek (dateInt, monthInt, yearInt);
		timeMacro.updateDate (dateInt);
		timeMacro.updateDay (day);
		timeMacro.updateMonth (monthInt);
		timeMacro.updateYear (yearInt);
	}
	return timeMacro;
}

TimeMicro Parser::parseTime (string inputToBeParsed) {
	TimeMicro timeMicro;
	if (isTimePeriod (inputToBeParsed) || isStartingTime (inputToBeParsed)) {
        string hourBeg = inputToBeParsed.substr (0, 2);
		string minuteBeg = inputToBeParsed.substr (3, 2);
		int hourBegInt = atoi (hourBeg.c_str());
		int minuteBegInt = atoi (minuteBeg.c_str());
		timeMicro.updateHourBeg (hourBegInt);
		timeMicro.updateMinBeg (minuteBegInt);
	}
	if (isTimePeriod (inputToBeParsed)) {
		string hourEnd = inputToBeParsed.substr (6, 2);
		string minuteEnd = inputToBeParsed.substr (8, 2);
		int hourEndInt = atoi (hourEnd.c_str());
		int minuteEndInt = atoi (minuteEnd.c_str());
		timeMicro.updateHourEnd (hourEndInt);
		timeMicro.updateMinEnd (minuteEndInt);
	}
	return timeMicro;
}

string Parser::parseTaskNo (string inputToBeParsed) {
	int lengthOfTaskNo = inputToBeParsed.find_first_of (' ');
	string index = inputToBeParsed.substr (0, lengthOfTaskNo);
	return index;
}

bool Parser::isDate (string inputToBeParsed) {
	if (inputToBeParsed.size() >= LENGTH_OF_DATE) {
		if (searchSubstring (DATE_FIRST_DIGIT, inputToBeParsed[0]) &&
			searchSubstring (DATE_SECOND_DIGIT, inputToBeParsed[1]) &&
			inputToBeParsed[2] == '/' &&
			searchSubstring (MONTH_FIRST_DIGIT, inputToBeParsed[3]) &&
			searchSubstring (MONTH_SECOND_DIGIT, inputToBeParsed[4]) &&
			inputToBeParsed[5] == '/' &&
			searchSubstring (YEAR_FIRST_DIGIT, inputToBeParsed[6]) &&
			searchSubstring (YEAR_SECOND_DIGIT, inputToBeParsed[7]) &&
			searchSubstring (YEAR_THIRD_DIGIT, inputToBeParsed[8]) &&
			searchSubstring (YEAR_FOURTH_DIGIT, inputToBeParsed[9])) {
				return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Parser::isStartingTime (string inputToBeParsed) {
	if (inputToBeParsed.size() >= LENGTH_OF_STARTING_TIME) {
		if (searchSubstring (HOUR_FIRST_DIGIT, inputToBeParsed[0]) &&
			searchSubstring (HOUR_SECOND_DIGIT, inputToBeParsed[1]) &&
			inputToBeParsed[2] == ':' &&
			searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[3]) &&
			searchSubstring (MINUTE_SECOND_DIGIT, inputToBeParsed[4])) {
				return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Parser::isTimePeriod (string inputToBeParsed) {
	if (inputToBeParsed.size() >= LENGTH_OF_TIME_PERIOD) {
		if (isStartingTime (inputToBeParsed) &&
			inputToBeParsed[5] == '-' &&
			searchSubstring (HOUR_FIRST_DIGIT, inputToBeParsed[6]) &&
			searchSubstring (HOUR_SECOND_DIGIT, inputToBeParsed[7]) &&
			inputToBeParsed[8] == ':' &&
			searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[9]) &&
			searchSubstring (MINUTE_SECOND_DIGIT, inputToBeParsed[10])) {
				return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Parser::searchSubstring (string string, char substring) {
	int index = 0;
	for (index = 0; index < string.size(); index ++) {
		if (substring == string[index]) {
			return true;
		}
	}
	return false;
}

string Parser::convertDateToDayOfTheWeek (int date, int month, int year) {
  time_t rawtime;
  struct tm * timeinfo;
  const char * weekday[] = { "Sunday", "Monday",
                             "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  timeinfo->tm_year = year - 1900;
  timeinfo->tm_mon = month - 1;
  timeinfo->tm_mday = date;

  mktime ( timeinfo );

  return (weekday[timeinfo->tm_wday]);
}

void Parser::getTodayDate (TimeMacro timeMacro) {
    time_t t = time (0);   // get time now
    struct tm *now = localtime (&t);
    now -> tm_year = now -> tm_year + 1900;
    now -> tm_mon = now -> tm_mon + 1;
    now -> tm_mday = now->tm_mday;
	timeMacro.updateYear (now -> tm_year);
	timeMacro.updateMonth (now -> tm_mon);
	timeMacro.updateDate (now -> tm_yday);
}

void Parser::getTomorrowDate (TimeMacro timeMacro) {
    time_t t = time (0);   // get time now
    struct tm *now = localtime (&t);
    now -> tm_year = now -> tm_year + 1900;
    now -> tm_mon = now -> tm_mon + 1;
    now -> tm_mday = now->tm_mday;

	if (now -> tm_mday == 31) {
		if (now -> tm_mon == 12) {
			now -> tm_year += 1;
			now -> tm_mon = 1;
		}
		else {
			now -> tm_mon += 1;
		}
		now -> tm_mday = 1;
	}
	else if (now -> tm_mday == 30) {
		if (now -> tm_mon == 4 || now -> tm_mon == 6 ||
			now -> tm_mon == 9 || now -> tm_mon == 11) {
				now -> tm_mday = 1;
				now -> tm_mon += 1;
		}
	}
	else if (now -> tm_mday == 28 && !isLeapYear (now -> tm_year) &&
		now -> tm_mon == 2) {
			now -> tm_mday = 1;
			now -> tm_mon += 1;
	}
	else if (now -> tm_mday == 29 && isLeapYear (now -> tm_year) &&
		now -> tm_mon ==2) {
			now -> tm_mday =1;
			now ->tm_mon += 1;
	}
	else {
		now -> tm_mday += 1;
	}

    timeMacro.updateYear (now -> tm_year);
	timeMacro.updateMonth (now -> tm_mon);
	timeMacro.updateDate (now -> tm_yday);
}

void Parser::getThisMonth (TimeMacro timeMacroBeg, TimeMacro timeMacroEnd) {
	time_t t = time (0);   // get time now
    struct tm *now = localtime (&t);
    now -> tm_year = now -> tm_year + 1900;
    now -> tm_mon = now -> tm_mon + 1;
    now -> tm_mday = now->tm_mday;

	timeMacroBeg.updateYear (now -> tm_year);
	timeMacroBeg.updateMonth (now -> tm_mon);
	timeMacroBeg.updateDate (0);

	timeMacroEnd.updateYear (now -> tm_year);
	timeMacroEnd.updateMonth (now -> tm_mon);
	timeMacroEnd.updateDate (34);
}

bool Parser::isLeapYear (int year) {
	if (year % 4 != 0) {
		return false;
	}
	else if (year % 100 != 0) {
		return true;
	}
	else if (year % 400 != 0) {
		return false;
	}
	else {
		return true;
	}
}