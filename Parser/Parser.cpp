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


//This method is called by Operation Center.
//It takes in user's input message
//and updates error message if the user's command word is incorrect.
void Parser::parseInput (string userInput) {
	string commandWord;

	commandWord = extractCommandWord (userInput);

	try {
	checkCommandWord (commandWord, userInput);
	}

	catch (const char* errorMessge) {
		updateErrorMessage ("Please enter the correct command");
		//cout << getErrorMessage () << endl;
	}
}


//This method is to recognise different user's command word
//and call for different actions accordingly.
//If the user enters an incorrect command word,
//it will throw an exception.
void Parser::checkCommandWord (string commandWord, string userInput) {
	if (commandWord == "add") {
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
	else if (commandWord == "done") {
		parseDone (userInput, commandWord);
	}
	else {
		throw "non-existing command";
	}
}


//This method is to extract command word from user's input.
//Since the command word is only one word,
//it will extract the first word from the user's input.
//It assumes each word is separated by a whitespace in user's input.
//If the user input only consists one word,
//this single word will be extracted.
string Parser::extractCommandWord (string userInput) {
	int end = 0;
	string commandWord;
	end = userInput.find_first_of (" ");
	commandWord = userInput.substr (0, end);
	return commandWord;
}


//This method is to parse user's input if the command word is "add".
//There are at most 3 things to be parsed:
//timeMacro, timeMicro and task description.
//a task will end with a description if there is one
//all 3 attributes can stand alone
void Parser::parseAdd (string userInput, string commandWord) {
	TimeMacro timeMacro;
	TimeMicro timeMicroBeg;
	TimeMicro timeMicroEnd;
	string inputToBeParsed = userInput;
	string desc;
	inputToBeParsed = inputToBeParsed.substr (commandWord.size() + 1);

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


//This method is to parse user's input if the command word is "edit".
//There are at most 4 things to be parsed:
//task number, timeMacro, timeMicro and task description.
//The command word "edit" must be followed by a task number.
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

//This method is to parse user's input if the command word is "search".
//The whole string after the command word "search" will be parsed
//and recognised as the key word.
void Parser::parseSearch (string userInput, string commandWord) {
	string desc = userInput.substr (commandWord.size() + 1);

    updateCommand (commandWord);
	updateDesc (desc);
}


////This method is to parse user's input if the command word is "undo".
//Only the command word "undo" will be parsed.
void Parser::parseUndo (string commandWord) {
    updateCommand (commandWord);
}


//This method is to parse user's input if the command word is "delete".
//The command word "delete" will be followed by a task number.
void Parser::parseDelete (string userInput, string commandWord) {
	string index = userInput.substr (commandWord.size() + 1);
	int taskNo = atoi (index.c_str());
	updateCommand (commandWord);
	updateTaskNo (taskNo);
}


//This method is to parse user's input if the command word is "display".
//The command word display is to be followed by a period.
//So far, this method is able to parse the period when the period is
//"today", "tomorrow" and "this month".
//The starting and ending date/month/year/day will be updated.
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


//This method is to parse user's input if the command word is "done".
//The command word "done" will be followed by a task number.
void Parser::parseDone (string userInput, string commandWord) {
	string index = userInput.substr (commandWord.size() + 1);
	int taskNo = atoi (index.c_str());
	updateCommand (commandWord);
	updateTaskNo (taskNo);
	updateStatus (true);
}

//This method is to parse date after the start of the string is recoganised as a date.
//It recoganise the date format "dd/mm/yyyy" and parse it accordingly.
//Date/month/year/day will be updated.
void Parser::parseDate (string inputToBeParsesd, TimeMacro& timeMacro) {
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
}


//This method is to parse date after the start of the string 
//is recoganised as a time or a time period.
//It recoganise the time format "hh:mm" and parse it accordingly.
//If the string starts with a time,
//only starting hour and minute will be updated.
//If the string starts with a time period,
//both starting and ending hour and minute will be updated.
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


//This method is to parse the task numnber.
//It assumes the task number will be separated with the following string
//with a whitespace,
//or the task number is the end of the string.
//The task number which is originally a string
//will be converted to an integer.
string Parser::parseTaskNo (string inputToBeParsed) {
	int lengthOfTaskNo = inputToBeParsed.find_first_of (' ');
	string index = inputToBeParsed.substr (0, lengthOfTaskNo);
	return index;
}


//This method is to check if the start of the string is a date.
//The string firstly needs to be longer than the date format.
//Then it must follow the format "dd/mm/yyyy"
//in order to be recognised as a date.
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


//This method is to check if the start of the string is a starting time
//(which may be followed by an ending time).
//The string firstly needs to be longer than the time format.
//Then it must follow the format "hh:mm"
//in order to be recognised as a starting time.
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


//This method is to check if the start of the string is a time period.
//The string firstly needs to be longer than the time period format.
//Then it must follow the format "hh:mm-hh:mm"
//in order to be recognised as a time period.
//Please note that the format for time period overlaps and includes
//the format for starting time.
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


//This method is to check if a specific character is in a string.
bool Parser::searchSubstring (string timeString, char substring) {
	unsigned int index = 0;
	for (index = 0; index < timeString.size(); index ++) {
		if (substring == timeString[index]) {
			return true;
		}
	}
	return false;
}


//This method takes in date, month and year
//and convert them to day of the week.
//Day of the week in the Data object will be updated.
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


//This method is to get today's date, month, year and day
//and store them in a TimeMacro object
//which will be passed to its caller.
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


//This method is to get tomorrow's date, month, year and day
//and store them in a TimeMacro object
//which will be passed to its caller.
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


//This method is to get the starting date and ending date
//of this month.
//The starting and ending date, month and year
//will be stored in two TimeMacro objects
//which will be passed to its caller.
//Please no
void Parser::getThisMonth (TimeMacro& timeMacroBeg, TimeMacro& timeMacroEnd) {
	time_t t = time (0);
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
//One potential bug:
//the date period must be the start and end of this month
//there may be bug when the ending date of month changes


//This method is to check if a certain year is a leap year or not
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