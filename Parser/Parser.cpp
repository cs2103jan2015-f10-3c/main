#include "Parser.h"

const unsigned int Parser::LENGTH_OF_DATE = 10;  //"dd/mm/yyyy"
const string Parser::DATE_FIRST_DIGIT = "0123";
const string Parser::DATE_SECOND_DIGIT = "0123456789";
const string Parser::MONTH_FIRST_DIGIT = "01";
const string Parser::MONTH_SECOND_DIGIT = "0123456789";
const string Parser::YEAR_FIRST_DIGIT = "2";
const string Parser::YEAR_SECOND_DIGIT = "0123456789";
const string Parser::YEAR_THIRD_DIGIT = "0123456789";
const string Parser::YEAR_FOURTH_DIGIT = "0123456789";
const unsigned int Parser::LENGTH_OF_STARTING_TIME = 5;  //"09:00"
const unsigned int Parser::LENGTH_OF_TIME_PERIOD = 11;  //"09:00-10:30"
const string Parser::HOUR_FIRST_DIGIT = "012";
const string Parser::HOUR_SECOND_DIGIT = "01234567890";
const string Parser::MINUTE_FIRST_DIGIT = "012345";
const string Parser::MINUTE_SECOND_DIGIT = "0123456789";
//const unsigned int Parser::LENGTH_OF_ATTRIBUTE = 4;


void Parser::parseInput (string userInput) {
	string commandWord;

	commandWord = extractCommandWord (userInput); //not sure
	if (commandWord == "add") {
		//cout << "parseAdd function triggered.";
		parseAdd (userInput, commandWord);
	}
	else if (commandWord == "edit") {
		parseEdit (userInput, commandWord);
	}
	else if (commandWord == "search") {
		parseSearch (userInput, commandWord);
	}
	else if (commandWord == "undo") {
		parseUndo (commandWord);
	}
	else if (commandWord == "delete") {
		parseDelete (userInput, commandWord);
	}
	else if (commandWord == "display") {
		parseDisplay (userInput, commandWord);
	}
}

string Parser::extractCommandWord (string userInput) {
	int end = 0;
	string commandWord;
	end = userInput.find_first_of (" ");
	commandWord = userInput.substr (0, end);
	return commandWord;
}

//a task will end with a description if there is one
//all 3 attributes can stand alone
void Parser::parseAdd (string userInput, string commandWord) {
	TimeMacro timeMacro;
	TimeMicro timeMicroBeg;
	TimeMicro timeMicroEnd;
	string inputToBeParsed = userInput;
	string desc;
	inputToBeParsed = inputToBeParsed.substr (commandWord.size() + 1);
		//cout << "inputToBeParsed = " << inputToBeParsed << endl;

		parseDate (inputToBeParsed, timeMacro);
	inputToBeParsed = inputToBeParsed.substr (LENGTH_OF_DATE + 1);
	parseTime (inputToBeParsed, timeMicroBeg, timeMicroEnd);
	if (isTimePeriod (inputToBeParsed)) {
			inputToBeParsed = inputToBeParsed.substr (LENGTH_OF_TIME_PERIOD + 1);
	    }
	    else if (isStartingTime (inputToBeParsed)) {
            inputToBeParsed = inputToBeParsed.substr (LENGTH_OF_STARTING_TIME + 1);
        }
		desc = inputToBeParsed;

	
	updateCommand (commandWord);
	updateTimeMacro (timeMacro);
	updateTimeMicroPeriod (timeMicroBeg, timeMicroEnd);
	updateDesc (desc);
}

//a task will end with a description if there is one
//all 3 attributes can stand alone
//The task no must be followed by something to edit
void Parser::parseEdit (string userInput, string commandWord) {
	TimeMacro timeMacro;
	TimeMicro timeMicroBeg;
	TimeMicro timeMicroEnd;
	string desc;
	string inputToBeParsed = userInput.substr (commandWord.size() + 1);
	string index = parseTaskNo (inputToBeParsed);
	int taskNo = atoi (index.c_str());
	
	inputToBeParsed = inputToBeParsed.substr(index.size () + 1);

	parseDate (inputToBeParsed, timeMacro);
	inputToBeParsed = inputToBeParsed.substr (LENGTH_OF_DATE + 1);
	parseTime (inputToBeParsed, timeMicroBeg, timeMicroEnd);
	if (isTimePeriod (inputToBeParsed)) {
			inputToBeParsed = inputToBeParsed.substr (LENGTH_OF_TIME_PERIOD + 1);
	    }
	    else if (isStartingTime (inputToBeParsed)) {
            inputToBeParsed = inputToBeParsed.substr (LENGTH_OF_STARTING_TIME + 1);
        }
		desc = inputToBeParsed;


	updateCommand (commandWord);
	updateTaskNo (taskNo);
	updateTimeMacro (timeMacro);
	updateTimeMicroPeriod (timeMicroBeg, timeMicroEnd);
    updateDesc (desc);
}

void Parser::parseSearch (string userInput, string commandWord) {
	string desc = userInput.substr (commandWord.size() + 1);

    updateCommand (commandWord);
	updateDesc (desc);
}

void Parser::parseUndo (string commandWord) {
    updateCommand (commandWord);
}

void Parser::parseDelete (string userInput, string commandWord) {
	string index = userInput.substr (commandWord.size() + 1);
	int taskNo = atoi (index.c_str());
	updateCommand (commandWord);
	updateTaskNo (taskNo);
}

void Parser::parseDisplay (string userInput, string commandWord) {
	TimeMacro timeMacroBeg;
	TimeMacro timeMacroEnd;

	string period = userInput.substr (commandWord.size() + 1);

	if (period == "today") {
		getTodayDate (timeMacroBeg);
		getTodayDate (timeMacroEnd);
	}
	else if (period == "tomorrow") {
		getTomorrowDate (timeMacroBeg);
		getTomorrowDate (timeMacroEnd);
	}
	else if (period == "this month") {
		getThisMonth (timeMacroBeg, timeMacroEnd);
	}

	updateCommand (commandWord);
	updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
}

void Parser::parseDate (string inputToBeParsesd, TimeMacro& timeMacro) {
	if (isDate (inputToBeParsesd)) {
		//cout << "inputToBeParsed is date" << endl;
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
	}else{
		//cout << "inputToBeParsed is not recognised as date." << endl;
	}
}

void Parser::parseTime (string inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd) {
	if (isTimePeriod (inputToBeParsed) || isStartingTime (inputToBeParsed)) {
        string hourBeg = inputToBeParsed.substr (0, 2);
		string minuteBeg = inputToBeParsed.substr (3, 2);
		int hourBegInt = atoi (hourBeg.c_str());
		int minuteBegInt = atoi (minuteBeg.c_str());
		timeMicroBeg.updateHour (hourBegInt);
		timeMicroBeg.updateMin (minuteBegInt);
	}
	if (isTimePeriod (inputToBeParsed)) {
		string hourEnd = inputToBeParsed.substr (6, 2);
		string minuteEnd = inputToBeParsed.substr (9, 2);
		int hourEndInt = atoi (hourEnd.c_str());
		int minuteEndInt = atoi (minuteEnd.c_str());
		timeMicroEnd.updateHour (hourEndInt);
		timeMicroEnd.updateMin (minuteEndInt);
	}
}

string Parser::parseTaskNo (string inputToBeParsed) {
	int lengthOfTaskNo = inputToBeParsed.find_first_of (' ');
	string index = inputToBeParsed.substr (0, lengthOfTaskNo);
	return index;
}

bool Parser::isDate (string inputToBeParsed) {
	if (inputToBeParsed.size() >= LENGTH_OF_DATE) {
		if (searchSubstring ("0123", inputToBeParsed[0]) &&
			searchSubstring ("0123456789", inputToBeParsed[1]) &&
			inputToBeParsed[2] == '/' &&
			searchSubstring ("01", inputToBeParsed[3]) &&
			searchSubstring ("0123456789", inputToBeParsed[4]) &&
			inputToBeParsed[5] == '/' &&
			searchSubstring ("2", inputToBeParsed[6]) &&
			searchSubstring ("0123456789", inputToBeParsed[7]) &&
			searchSubstring ("0123456789", inputToBeParsed[8]) &&
			searchSubstring ("0123456789", inputToBeParsed[9])) {
				//cout << "is date." << endl;
				return true;
		}
		else {
			//cout << "is not date, fail 1." << endl;
			return false;
		}
	}
	else {
		//cout << "is not date, fail 2." << endl;
		return false;
	}
}

bool Parser::isStartingTime (string inputToBeParsed) {
	if (inputToBeParsed.size() >= LENGTH_OF_STARTING_TIME) {
		if (searchSubstring ("012", inputToBeParsed[0]) &&
			searchSubstring ("0123456789", inputToBeParsed[1]) &&
			inputToBeParsed[2] == ':' &&
			searchSubstring ("012345", inputToBeParsed[3]) &&
			searchSubstring ("0123456789", inputToBeParsed[4])) {
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
			searchSubstring ("012", inputToBeParsed[6]) &&
			searchSubstring ("0123456789", inputToBeParsed[7]) &&
			inputToBeParsed[8] == ':' &&
			searchSubstring ("012345", inputToBeParsed[9]) &&
			searchSubstring ("0123456789", inputToBeParsed[10])) {
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

bool Parser::searchSubstring (string timeString, char substring) {
	//cout << "searchSubstring triggered." << endl;
	//cout << "finding " << substring << " in " << timeString << endl;
	unsigned int index = 0;
	for (index = 0; index < timeString.size(); index ++) {
		//cout << substring << "||" << timeString[index] << endl;
		if (substring == timeString[index]) {
			return true;
		}
	}
	return false;
}

string Parser::convertDateToDayOfTheWeek (int date, int month, int year) {
  time_t rawtime;
  struct tm timeinfo;
  const char * weekday[] = { "Sunday", "Monday",
                             "Tuesday", "Wednesday",
                             "Thursday", "Friday", "Saturday"};

  time ( &rawtime );
  localtime_s (&timeinfo, &rawtime);
  timeinfo.tm_year = year - 1900;
  timeinfo.tm_mon = month - 1;
  timeinfo.tm_mday = date;

  mktime ( &timeinfo );

  return (weekday[timeinfo.tm_wday]);
}

void Parser::getTodayDate (TimeMacro& timeMacro) {
    time_t t = time (0);   // get time now
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + 1900;
    now.tm_mon = now.tm_mon + 1;
	string dayOfTheWeek = convertDateToDayOfTheWeek (now.tm_mday, now.tm_mon, now.tm_year);
	
	timeMacro.updateYear (now.tm_year);
	timeMacro.updateMonth (now.tm_mon);
	timeMacro.updateDate (now.tm_mday);
	timeMacro.updateDay (dayOfTheWeek);
}

void Parser::getTomorrowDate (TimeMacro& timeMacro) {
    time_t t = time (0);   // get time now
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + 1900;
    now.tm_mon = now.tm_mon + 1;

	if (now.tm_mday == 31) {
		if (now.tm_mon == 12) {
			now.tm_year += 1;
			now.tm_mon = 1;
		}
		else {
			now.tm_mon += 1;
		}
		now.tm_mday = 1;
	}
	else if (now.tm_mday == 30) {
		if (now.tm_mon == 4 || now.tm_mon == 6 ||
			now.tm_mon == 9 || now.tm_mon == 11) {
				now.tm_mday = 1;
				now.tm_mon += 1;
		}
	}
	else if (now.tm_mday == 28 && !isLeapYear (now.tm_year) &&
		now.tm_mon == 2) {
			now.tm_mday = 1;
			now.tm_mon += 1;
	}
	else if (now.tm_mday == 29 && isLeapYear (now.tm_year) &&
		now.tm_mon ==2) {
			now.tm_mday =1;
			now.tm_mon += 1;
	}
	else {
		now.tm_mday += 1;
	}

	string dayOfTheWeek = convertDateToDayOfTheWeek (now.tm_mday, now.tm_mon, now.tm_year);
    timeMacro.updateYear (now.tm_year);
	timeMacro.updateMonth (now.tm_mon);
	timeMacro.updateDate (now.tm_mday);
	timeMacro.updateDay (dayOfTheWeek);
}

void Parser::getThisMonth (TimeMacro& timeMacroBeg, TimeMacro& timeMacroEnd) {
	time_t t = time (0);   // get time now
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + 1900;
    now.tm_mon = now.tm_mon + 1;

	timeMacroBeg.updateYear (now.tm_year);
	timeMacroBeg.updateMonth (now.tm_mon);
	timeMacroBeg.updateDate (1);

	timeMacroEnd.updateYear (now.tm_year);
	timeMacroEnd.updateMonth (now.tm_mon);
	timeMacroEnd.updateDate (31);
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