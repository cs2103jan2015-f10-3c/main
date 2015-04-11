//@author A0093895J
#include "Parser.h"

const unsigned int Parser::LENGTH_OF_DATE_NUMBER = 3;  //"d/m"
const unsigned int Parser::LENGTH_OF_DATE_ALPHABET = 5;  //"d MMM"
const unsigned int Parser::LENGTH_OF_YEAR_ALPHABET = 5;
const unsigned int Parser::LENGTH_OF_STARTING_TIME = 4;  //"9:00"
const unsigned int Parser::LENGTH_OF_TIME_PERIOD = 9;  //"9:00-9:30"
const unsigned int Parser::START_OF_YEAR = 1900;
const unsigned int Parser::YEAR_MIN = 2000;
const unsigned int Parser::YEAR_MAX = 2100;

const unsigned int Parser::ZERO = 0;
const unsigned int Parser::ONE = 1;
const unsigned int Parser::TWO = 2;
const unsigned int Parser::THREE = 3;
const unsigned int Parser::FOUR = 4;
const unsigned int Parser::FIVE = 5;
const unsigned int Parser::SIX = 6;
const unsigned int Parser::SEVEN = 7;
const unsigned int Parser::EIGHT = 8;
const unsigned int Parser::NINE = 9;
const unsigned int Parser::TEN = 10;
const unsigned int Parser::ELEVEN = 11;
const unsigned int Parser::TWELVE = 12;
const unsigned int Parser::TWENTY_THREE = 23;
const unsigned int Parser::TWENTY_EIGHT = 28;
const unsigned int Parser::TWENTY_NINE = 29;
const unsigned int Parser::THIRTY = 30;
const unsigned int Parser::THIRTY_ONE = 31;
const unsigned int Parser::FIFTY_NINE = 59;
const unsigned int Parser::HUNDRAD = 100;
const unsigned int Parser::FOUR_HUNDRAD = 400;
const char Parser::AM[] = "am";
const char Parser::PM[] = "pm";
const char Parser::M[] = "m";

const unsigned int Parser::TIMEMICRO_INITIAL = -1;
const char Parser::EMPTY_STRING[] = "";
const char Parser::SPACE[] = " ";
const char Parser::SLASH[] = "/";
const char Parser::SPACE_SLASH[] = " /";
const char Parser::COLON[] = ":";
const char Parser::DOT[] = ".";
const char Parser::DASH[] = "-";

const char Parser::JAN_CAP[] = "Jan";
const char Parser::FEB_CAP[] = "Feb";
const char Parser::MAR_CAP[] = "Mar";
const char Parser::APR_CAP[] = "Apr";
const char Parser::MAY_CAP[] = "May";
const char Parser::JUN_CAP[] = "Jun";
const char Parser::JUL_CAP[] = "Jul";
const char Parser::AUG_CAP[] = "Aug";
const char Parser::SEP_CAP[] = "Sep";
const char Parser::OCT_CAP[] = "Oct";
const char Parser::NOV_CAP[] = "Nov";
const char Parser::DEC_CAP[] = "Dec";
const char Parser::JAN_SMALL[] = "jan";
const char Parser::FEB_SMALL[] = "feb";
const char Parser::MAR_SMALL[] = "mar";
const char Parser::APR_SMALL[] = "apr";
const char Parser::MAY_SMALL[] = "may";
const char Parser::JUN_SMALL[] = "jun";
const char Parser::JUL_SMALL[] = "jul";
const char Parser::AUG_SMALL[] = "aug";
const char Parser::SEP_SMALL[] = "sep";
const char Parser::OCT_SMALL[] = "oct";
const char Parser::NOV_SMALL[] = "nov";
const char Parser::DEC_SMALL[] = "dec";

const char Parser::MONDAY[] = "Monday";
const char Parser::TUESDAY[] = "Tuesday";
const char Parser::WEDNESDAY[] = "Wednesday";
const char Parser::THURSDAY[] = "Thursday";
const char Parser::FRIDAY[] = "Friday";
const char Parser::SATURDAY[] = "Saturday";
const char Parser::SUNDAY[] = "Sunday";

const char Parser::COMMAND_ADD[] = "add";
const char Parser::COMMAND_EDIT[] = "edit";
const char Parser::COMMAND_SEARCH[] = "search";
const char Parser::COMMAND_UNDO[] = "undo";
const char Parser::COMMAND_DELETE[] = "delete";
const char Parser::COMMAND_DONE[] = "done";
const char Parser::COMMAND_UNDONE[] = "undone";
const char Parser::COMMAND_SHOW[] = "show";
const char Parser::COMMAND_CLEAR[] = "clear";
const char Parser::COMMAND_PATH[] = "path";
const char Parser::COMMAND_HELP[] = "help";
const char Parser::COMMAND_TODAY[] = "today";
const char Parser::COMMAND_TOMORROW[] = "tomorrow";
const char Parser::COMMAND_THIS_WEEK[] = "this week";
const char Parser::COMMAND_THIS_MONTH[] = "this month";
const char Parser::COMMAND_COMMANDS[] = "commands";
const char Parser::COMMAND_FLOAT[] = "float";
const char Parser::COMMAND_FEATURES[] = "features";

const char Parser::ERROR_MESSAGE_COMMAND[] = "Please enter the correct command";
const char Parser::ERROR_MESSAGE_INPUT[] = "Please enter correct input following the command word";
const char Parser::ERROR_MESSAGE_EDIT[] = "Please enter content you want to edit";
const char Parser::ERROR_MESSAGE_TASK_NO[] = "Please enter correct task number after command word";
const char Parser::ERROR_MESSAGE_SHOW[] = "Please enter correct time period or task type";
const char Parser::ERROR_MESSAGE_DIRECTORY[] = "Please enter the correct directory";
const char Parser::ERROR_MESSAGE_DATE[] = "Please enter the correct date";
const char Parser::ERROR_MESSAGE_YEAR[] = "Please enter the correct year";
const char Parser::ERROR_MESSAGE_TIME[] = "Please enter the correct time";
const char Parser::ERROR_MESSAGE_DESC[] = "Please enter task description";

const char Parser::LOG_START[] = "Parser starts to parse user input";
const char Parser::LOG_SUCCESS[] = "Parser has parsed user input successfully";
const char Parser::LOG_ERROR[] = "Parser has found an invalid user input";



//This method is called by OperationCenter.
//It takes in user's input message
//and updates error message if the user's command word is incorrect.
void Parser::parseInput (string userInput) {
	string commandWord;
	Logger logStart;
	logStart.logging (LOG_START);

	commandWord = extractCommandWord (userInput);

	try {
		checkCommandWord (userInput, commandWord);
		Logger logSuccess;
		logSuccess.logging (LOG_SUCCESS);
	}

	catch (const char* errorMessge) {
		Logger logError;
		Logger logMessage;
		logError.logging (LOG_ERROR);
		logMessage.logging (errorMessge);
		updateErrorMessage (errorMessge);
	}
}


//This method is to recognise different user's command word
//and call for different actions accordingly.
//If the user enters an incorrect command word,
//it will throw an exception.
void Parser::checkCommandWord (string userInput, string commandWord) {
	if (commandWord == COMMAND_ADD) {
		parseAdd (userInput, commandWord);
	}
	else if (commandWord == COMMAND_EDIT) {
		parseEdit (userInput, commandWord);
	}
	else if (commandWord == COMMAND_SEARCH) {
		parseSearch (userInput, commandWord);
	}
	else if (commandWord == COMMAND_UNDO) {
		parseUndo (userInput, commandWord);
	}
	else if (commandWord == COMMAND_DELETE) {
		parseDelete (userInput, commandWord);
	}
	else if (commandWord == COMMAND_DONE) {
		parseDone (userInput, commandWord);
	}
	else if (commandWord == COMMAND_UNDONE) {
		parseUndone (userInput, commandWord);
	}
	else if (commandWord == COMMAND_SHOW) {
		parseShow (userInput, commandWord);
	}
	else if (commandWord == COMMAND_CLEAR) {
		parseClear (userInput, commandWord);
	}
	else if (commandWord == COMMAND_PATH) {
		parsePath (userInput, commandWord);
	}
	else if (commandWord == COMMAND_HELP) {
		parseHelp (userInput, commandWord);
	}
	else {
		throw ERROR_MESSAGE_COMMAND;
	}
}


//This method is to extract command word 
//which is the first word from the user's input.
//It assumes each word is separated by a whitespace in user's input.
//If the user input only consists one word,
//this single word will be extracted.
string Parser::extractCommandWord (string userInput) {
	int end = 0;
	string commandWord;
	end = userInput.find_first_of (SPACE);
	commandWord = userInput.substr (ZERO, end);
	return commandWord;
}


//This method is to parse user's input if the command word is "add".
//There are at most 3 things to be parsed:
//date, time and task description.
//A task must have a description and end with a description
//else, an exception will be thrown.
//Date and time may be omitted and they can switch order if there are any
//If a task only has a time but no date,
//it assumes to be today.
void Parser::parseAdd (string userInput, string commandWord) {
	TimeMacro timeMacro;
	TimeMicro timeMicroBeg;
	TimeMicro timeMicroEnd;
	string inputToBeParsed = userInput;
	string desc;

	inputToBeParsed = inputToBeParsed.substr (commandWord.size());
	if (inputToBeParsed != EMPTY_STRING && inputToBeParsed != SPACE) {
		//This "if" condition is to account for the cases where
		//the user only enters the command word
		//or enters a command word followed by a white space.
		//These cases may usually happen when the users are careless.
		inputToBeParsed = inputToBeParsed.substr (ONE);

		parseDateNumber (inputToBeParsed, timeMacro);
		parseDateAlphabet (inputToBeParsed, timeMacro);

		parseTimeTwentyFour (inputToBeParsed, timeMicroBeg, timeMicroEnd);
		parseTimeTwelve (inputToBeParsed, timeMicroBeg, timeMicroEnd);

		if (timeMacro.getDate() == ZERO &&
			timeMacro.getMonth() == ZERO &&
			timeMacro.getYear() == ZERO) {
				parseDateNumber (inputToBeParsed, timeMacro);
				parseDateAlphabet (inputToBeParsed, timeMacro);
		}
		//This "if" block is to make sure the date can be parsed
		//even if it is put after the time.
		
		desc = inputToBeParsed;

		if (desc == EMPTY_STRING) {
			throw ERROR_MESSAGE_DESC;
		}

		updateCommand (commandWord);
		updateTimeMacro (timeMacro);
		updateTimeMicroPeriod (timeMicroBeg, timeMicroEnd);
		updateDesc (desc);

		if (timeMacro.getDate() == ZERO &&
			timeMicroBeg.getHour() != TIMEMICRO_INITIAL) {
				getTodayDate (timeMacro);
		}
		updateTimeMacro (timeMacro);
	}
	else {
		throw ERROR_MESSAGE_INPUT;
	}
}


//This method is to parse user's input if the command word is "edit".
//There are at most 4 things to be parsed:
//task number, date, time and task description.
//The command word "edit" must be followed by a task number.
//a task will end with a description if there is one
//date, time and description can also stand alone and switch order
//The task number must be followed by something to edit
void Parser::parseEdit (string userInput, string commandWord) {
	TimeMacro timeMacro;
	TimeMicro timeMicroBeg;
	TimeMicro timeMicroEnd;
	string desc;
	int taskNo;
	string inputToBeParsed;
	string index;

	inputToBeParsed = userInput.substr (commandWord.size());
	if (inputToBeParsed != EMPTY_STRING && inputToBeParsed != SPACE) {
		inputToBeParsed = inputToBeParsed.substr (ONE);

		index = parseTaskNo (inputToBeParsed);
		taskNo = convertStringToInteger (index);
		if (taskNo < ONE) {
			throw ERROR_MESSAGE_TASK_NO;
		}

		inputToBeParsed = inputToBeParsed.substr(index.size ());
		if (inputToBeParsed != EMPTY_STRING && inputToBeParsed != SPACE) {
			inputToBeParsed = inputToBeParsed.substr(ONE);

			parseDateNumber (inputToBeParsed, timeMacro);
			parseDateAlphabet (inputToBeParsed, timeMacro);

			parseTimeTwentyFour (inputToBeParsed, timeMicroBeg, timeMicroEnd);
			parseTimeTwelve (inputToBeParsed, timeMicroBeg, timeMicroEnd);

			if (timeMacro.getDate() == ZERO &&
				timeMacro.getMonth() == ZERO &&
				timeMacro.getYear() == ZERO) {
					parseDateNumber (inputToBeParsed, timeMacro);
					parseDateAlphabet (inputToBeParsed, timeMacro);
			}

			desc = inputToBeParsed;

			updateCommand (commandWord);
			updateTaskNo (taskNo);
			updateTimeMacro (timeMacro);
			updateTimeMicroPeriod (timeMicroBeg, timeMicroEnd);
			updateDesc (desc);
		}

		else {
			throw ERROR_MESSAGE_EDIT;
		}
	}
	else {
		throw ERROR_MESSAGE_INPUT;
	}
}

//This method is to parse user's input if the command word is "search".
//The whole string after the command word "search" will be parsed
//and recognised as the key word.
void Parser::parseSearch (string userInput, string commandWord) {
	string desc = userInput.substr (commandWord.size());
	int end = 0;
	if (desc != EMPTY_STRING && desc != SPACE) {
		desc = desc.substr (ONE);

		updateCommand (commandWord);
		updateDesc (desc);
	}
	else {
		throw ERROR_MESSAGE_INPUT;
	}
}


//This method is to parse user's input if the command word is "undo".
//Only the command word "undo" will be parsed.
void Parser::parseUndo (string userInput, string commandWord) {
    updateCommand (commandWord);

	string leftOver = userInput.substr (commandWord.size());
	if (leftOver != EMPTY_STRING && leftOver != SPACE) {
		throw ERROR_MESSAGE_COMMAND;
	}
}


//This method is to parse user's input if the command word is "delete".
//The command word "delete" must be followed by a task number.
void Parser::parseDelete (string userInput, string commandWord) {
	int taskNo;
	string index = userInput.substr (commandWord.size());
	if (index != EMPTY_STRING && index != SPACE) {
		index = index.substr (ONE);
		taskNo = convertStringToInteger (index);
		if (taskNo < ONE) {
			throw ERROR_MESSAGE_TASK_NO;
		}
		updateCommand (commandWord);
		updateTaskNo (taskNo);
	}
	else {
		throw ERROR_MESSAGE_TASK_NO;
	}
}


//This method is to parse user's input if the command word is "done".
//The command word "done" must be followed by a task number.
void Parser::parseDone (string userInput, string commandWord) {
	int taskNo;
	string index = userInput.substr (commandWord.size());
	if (index != EMPTY_STRING && index != SPACE) {
		index = index.substr (ONE);
		taskNo = convertStringToInteger (index);
		if (taskNo < ONE) {
			throw ERROR_MESSAGE_TASK_NO;
		}
		updateCommand (commandWord);
		updateTaskNo (taskNo);
		updateStatus (true);
	}
	else {
		throw ERROR_MESSAGE_TASK_NO;
	}
}


//This method is to parse user's input if the command word is "undone".
//The command word "undone" must be followed by a task number.
void Parser::parseUndone (string userInput, string commandWord) {
	int taskNo;
	string index = userInput.substr (commandWord.size());
	if (index != EMPTY_STRING && index != SPACE) {
		index = index.substr (ONE);
		taskNo = convertStringToInteger (index);
		if (taskNo < ONE) {
			throw ERROR_MESSAGE_TASK_NO;
		}
		updateCommand (commandWord);
		updateTaskNo (taskNo);
		updateStatus (false);
	}
	else {
		throw ERROR_MESSAGE_TASK_NO;
	}
}

//This method is to parse user's input if the command word is "show".
//1st case: the command word "show" is followed by a date.
//Then the date/month/year/day will be updated.
//2nd case: the command word "show" is followed by a period.
//The user can enter "show today", "show tomorrow",
//"show this week" and "show this month".
//The starting and ending date/month/year/day will be updated.
//3rd case: the command word "show" is followed by the 
//words "commands", "float", "done", or "features".
//Then the command word will become "show commands" or "show float", etc.
//If the word following "show" does not fall into these 2 cases,
//it will throw an exception.
void Parser::parseShow (string userInput, string commandWord) {
	string inputToBeParsed = userInput.substr (commandWord.size ());
	TimeMacro timeMacroBeg;
	TimeMacro timeMacroEnd;
	int dateInt;
	int monthInt;

	if (inputToBeParsed != EMPTY_STRING && inputToBeParsed != SPACE) {
		inputToBeParsed = inputToBeParsed.substr(ONE);

		if (isDateNumber (inputToBeParsed, dateInt, monthInt) ||
			isDateAlphabet (inputToBeParsed, dateInt)) {
				parseDateNumber (inputToBeParsed, timeMacroBeg);
				parseDateAlphabet (inputToBeParsed, timeMacroBeg);

				if (inputToBeParsed != EMPTY_STRING && inputToBeParsed != SPACE) {
					throw ERROR_MESSAGE_SHOW;
				}

				updateCommand (commandWord);
				timeMacroEnd = timeMacroBeg;
				updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}		
		else if (inputToBeParsed == COMMAND_TODAY) {
			getTodayDate (timeMacroBeg);
			timeMacroEnd = timeMacroBeg;
			updateCommand (commandWord);
			updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}
		else if (inputToBeParsed == COMMAND_TOMORROW) {
			getTomorrowDate (timeMacroBeg);
			timeMacroEnd = timeMacroBeg;
			updateCommand (commandWord);
			updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}
		else if (inputToBeParsed == COMMAND_THIS_WEEK) {
			getMondayDate (timeMacroBeg);
			getSundayDate (timeMacroEnd);
			updateCommand (commandWord);
			updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}
		else if (inputToBeParsed == COMMAND_THIS_MONTH) {
			getThisMonth (timeMacroBeg, timeMacroEnd);
			updateCommand (commandWord);
			updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}
		else if (inputToBeParsed == COMMAND_COMMANDS ||
			inputToBeParsed == COMMAND_FLOAT ||
			inputToBeParsed == COMMAND_DONE ||
			inputToBeParsed == COMMAND_FEATURES) {
				commandWord = commandWord + SPACE + inputToBeParsed;
				updateCommand (commandWord);
		}
		else {
			throw ERROR_MESSAGE_SHOW;
		}
	}
	else {
		throw ERROR_MESSAGE_SHOW;
	}
}


//This method is to parse user's input if the command word is "clear".
//Only the command word "clear" will be parsed.
//If the command word "clear" is followed by some other input,
//an exception is thrown.
void Parser::parseClear (string userInput, string commandWord) {
	updateCommand (commandWord);

	string leftOver = userInput.substr (commandWord.size());
	if (leftOver != EMPTY_STRING && leftOver != SPACE) {
		throw ERROR_MESSAGE_COMMAND;
	}
}


//This method is to parse user's input if the command word is "path".
//The command word "path" must be followed by a directory.
void Parser::parsePath (string userInput, string commandWord) {
	string inputToBeParsed = userInput.substr (commandWord.size ());

	if (inputToBeParsed != EMPTY_STRING && inputToBeParsed != SPACE) {
		inputToBeParsed = inputToBeParsed.substr(ONE);

		updateCommand (commandWord);
		updateDirectory (inputToBeParsed);	
	}
	else {
		throw ERROR_MESSAGE_DIRECTORY;
	}
}


//This method is to parse user's input if the command word is "help".
//Only the command word "help" will be parsed.
//If the command word "help" is followed by some other input,
//an exception is thrown.
void Parser::parseHelp (string userInput, string commandWord) {
	updateCommand (commandWord);

	string leftOver = userInput.substr (commandWord.size());
	if (leftOver != EMPTY_STRING && leftOver != SPACE) {
		throw ERROR_MESSAGE_COMMAND;
	}
}


//This method is to parse date after the start of the string is recoganised as a date.
//The formats it recognises are "dd/mm/yyyy", "d/mm/yyyy", "dd/m/yyyy", "d/m/yyyy",
//"dd/mm", "d/mm", "dd/m", "d/m".
//If the year is not specified, it assumes to be this year.
//Date/month/year/day will be updated.
void Parser::parseDateNumber (string& inputToBeParsesd, TimeMacro& timeMacro) {
	int end = 0;
	int dateInt;
	int monthInt;
	int yearInt;
	string day;

	if (isDateNumber (inputToBeParsesd, dateInt, monthInt)) {
		timeMacro.updateDate (dateInt);
		timeMacro.updateMonth (monthInt);

		end = inputToBeParsesd.find_first_of (SLASH);
		inputToBeParsesd = inputToBeParsesd.substr (end + ONE);
		if (isYearNumber (inputToBeParsesd, yearInt)) {
			timeMacro.updateYear (yearInt);
		}
		else {
			time_t t = time (ZERO);
			struct tm now;
			localtime_s (&now, &t);
			now.tm_year = now.tm_year + START_OF_YEAR;
			yearInt = now.tm_year;
			timeMacro.updateYear (yearInt);
		}

		day = convertDateToDayOfTheWeek (dateInt, monthInt, yearInt);
		timeMacro.updateDay (day);

		end = inputToBeParsesd.find_first_of (SPACE);
		if (end != string::npos) {
			inputToBeParsesd = inputToBeParsesd.substr (end + ONE);
		}
		else {
			inputToBeParsesd = EMPTY_STRING;
		}
	}
}


//This method is to parse date after the start of the string is recoganised as a date.
//The formats it recognises are date (integer) followed by month (abbreviation),
//followed by year (integer). eg. 21 Mar 2015
//If the year is not specified, it assumes it is this year.
//Date/month/year/day will be updated.
void Parser::parseDateAlphabet (string& inputToBeParsesd, TimeMacro& timeMacro) {
	int end = 0;
	int dateInt;
	int monthInt;
	int yearInt;
	string day;

	if (isDateAlphabet (inputToBeParsesd, dateInt)) {
		timeMacro.updateDate (dateInt);

		end = inputToBeParsesd.find_first_of (SPACE);
		inputToBeParsesd = inputToBeParsesd.substr (end + ONE);
		monthInt = convertAlphabetMonthToInteger (inputToBeParsesd.substr (ZERO, THREE));
		timeMacro.updateMonth (monthInt);
		inputToBeParsesd = inputToBeParsesd.substr (THREE);

		if (isYearAlphabet (inputToBeParsesd, yearInt)) {
			timeMacro.updateYear (yearInt);
			if (inputToBeParsesd.size() > SIX) {
				inputToBeParsesd = inputToBeParsesd.substr (SIX); //there is still content after the year
			}
			else {
				inputToBeParsesd = EMPTY_STRING;
			}
		}

		else {
			if (inputToBeParsesd.size() > ONE) {
				inputToBeParsesd = inputToBeParsesd.substr (ONE);
			}

			time_t t = time (ZERO);
			struct tm now;
			localtime_s (&now, &t);
			now.tm_year = now.tm_year + START_OF_YEAR;
			yearInt = now.tm_year;
			timeMacro.updateYear (yearInt);
		}

		day = convertDateToDayOfTheWeek (dateInt, monthInt, yearInt);
		timeMacro.updateDay (day);
	}
}

//This method is to parse date after the start of the string 
//is recoganised as a time or a time period.
//It recoganise the time format "hh:mm" and parse it accordingly.
//If the string starts with a time,
//only starting hour and minute will be updated.
//If the string starts with a time period,
//both starting and ending hour and minute will be updated.
void Parser::parseTimeTwentyFour (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd) {
	int end = 0;
	int hourBegInt;
	int hourEndInt;
	int minuteBegInt;
	int minuteEndInt;

	if (isTimePeriodTwentyFour (inputToBeParsed, hourBegInt, hourEndInt, minuteBegInt, minuteEndInt) ||
		isStartingTimeTwentyFour (inputToBeParsed, hourBegInt, minuteBegInt)) {
			timeMicroBeg.updateHour (hourBegInt);
			timeMicroBeg.updateMin (minuteBegInt);

			if (isTimePeriodTwentyFour (inputToBeParsed, hourBegInt, hourEndInt, minuteBegInt, minuteEndInt)) {	
				timeMicroEnd.updateHour (hourEndInt);
				timeMicroEnd.updateMin (minuteEndInt);
				assert (timeMicroEnd.getHour() != TIMEMICRO_INITIAL);
				assert (timeMicroEnd.getMin() != TIMEMICRO_INITIAL);
			}

			assert (timeMicroBeg.getHour() != TIMEMICRO_INITIAL);
			assert (timeMicroBeg.getMin() != TIMEMICRO_INITIAL);

			end = inputToBeParsed.find_first_of (SPACE);
			if (end == string::npos) {
				inputToBeParsed = EMPTY_STRING;
			}
			else {
				inputToBeParsed = inputToBeParsed.substr (end + ONE);
			}
	}
}


//This method is to parse date after the start of the string 
//is recoganised as a time or a time period.
//The formats it recognises are "hh", "h", "hh.mm", "h.mm"
//followed by "am" or "pm".
//If the string starts with a time,
//only starting hour and minute will be updated.
//If the string starts with a time period,
//both starting and ending hour and minute will be updated.
void Parser::parseTimeTwelve (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd) {
	int end = 0;
	int hourBegInt;
	int hourEndInt;
	int minuteBegInt;
	int minuteEndInt;

	if (isTimePeriodTwelve (inputToBeParsed, hourBegInt, hourEndInt, minuteBegInt, minuteEndInt) ||
		isStartingTimeTwelve (inputToBeParsed, hourBegInt, minuteBegInt)) {
			timeMicroBeg.updateHour (hourBegInt);
			timeMicroBeg.updateMin (minuteBegInt);

			if (isTimePeriodTwelve (inputToBeParsed, hourBegInt, hourEndInt, minuteBegInt, minuteEndInt)) {				
				timeMicroEnd.updateHour (hourEndInt);
				timeMicroEnd.updateMin (minuteEndInt);
				assert (timeMicroEnd.getHour() != TIMEMICRO_INITIAL);
				assert (timeMicroEnd.getMin() != TIMEMICRO_INITIAL);
			}

			assert (timeMicroBeg.getHour() != TIMEMICRO_INITIAL);
			assert (timeMicroBeg.getMin() != TIMEMICRO_INITIAL);

			end = inputToBeParsed.find_first_of (SPACE);
			if (end == string::npos) {
				inputToBeParsed = EMPTY_STRING;
			}
			else {
				inputToBeParsed = inputToBeParsed.substr (end + ONE);
			}
	}	
}

//This method is to parse the task numnber.
//It assumes the task number is separated with the following string
//with a whitespace,
//or the task number is the end of the string.
//The task number returned is a string.
string Parser::parseTaskNo (string inputToBeParsed) {
	int lengthOfTaskNo = inputToBeParsed.find_first_of (SPACE);
	string index = inputToBeParsed.substr (ZERO, lengthOfTaskNo);
	return index;
}


//This method is to check whether an input string is an interger string
//It will return false if at least one character is not integer character
bool Parser::isInteger (string index) {
	for (int i = 0; i != index.size (); i++) {
		if (!isdigit (index[i])) {
			return false;
		}
	}
	return true;
}


//This method is to convert an input string to an integer.
//An exception will be thrown if the string is not an integer string.
int Parser::convertStringToInteger (string index) {
	if (!isInteger (index)) {
		throw ERROR_MESSAGE_TASK_NO;
	}
	else {
		int taskNo = atoi (index.c_str());
		return taskNo;
	}	
}

//This method is to check if the start of the string is a date.
//This method only checks for date and month.
//The formats of date and month can be
//"dd/mm", "dd/m", "d/mm", "d/m".
//The string firstly needs to be longer than the date format.
bool Parser::isDateNumber (string inputToBeParsed, int& dateInt, int& monthInt) {
	int end;
	string date;
	string month;

	if (inputToBeParsed.size() >= LENGTH_OF_DATE_NUMBER) {
		end = inputToBeParsed.find_first_of (SLASH);
		if (end == ONE || end == TWO) {
			date = inputToBeParsed.substr (ZERO, end);
			if (isInteger (date)) {
				dateInt = convertStringToInteger (date);
				if (dateInt < ONE || dateInt > THIRTY_ONE) {
					throw ERROR_MESSAGE_DATE;
				}

				inputToBeParsed = inputToBeParsed.substr (end + ONE);
				end = inputToBeParsed.find_first_of(SPACE_SLASH);
				if (end == ONE || end == TWO ||
					(end == string::npos && 
					(inputToBeParsed.size() == ONE || inputToBeParsed.size () == TWO))) {
						month = inputToBeParsed.substr (ZERO, end);
						if (isInteger (month)) {
							monthInt= convertStringToInteger (month);
							if (monthInt < ONE || monthInt > TWELVE) {
								throw ERROR_MESSAGE_DATE;
							}

							if ((monthInt == FOUR || monthInt == SIX ||
								monthInt == NINE || monthInt == ELEVEN) &&
								dateInt == THIRTY_ONE) {
									throw ERROR_MESSAGE_DATE;
							}
							return true;
						}
				}
			}
		}
	}

	return false;
}


//This method checks if the date format includes a year.
//If the date and month are followed by "/yyyy",
//it returns true;
//else, it returns false
bool Parser::isYearNumber (string inputToBeParsed, int& yearInt) {
	int end;
	string year;

	end = inputToBeParsed.find_first_of (SLASH);
	if (end == ONE || end == TWO) {
		year = inputToBeParsed.substr (end + ONE, FOUR);
		if (isInteger (year)) {
			yearInt = convertStringToInteger (year);
			if (yearInt < YEAR_MIN || yearInt > YEAR_MAX) {
				throw ERROR_MESSAGE_YEAR;
			}
			return true;
		}
	}

	return false;
}


//This method is to check if the start of the string is a date.
//This method only checks for date and month.
//The format is date (integer) 
//followed by month (abbreviation, the first alphabet can be both capital or small)
//eg. 21 Mar or 21 mar.
//The string firstly needs to be longer than the date format.
bool Parser::isDateAlphabet (string inputToBeParsed, int& dateInt) {
	int end;
	string date;
	string month;
	vector<string> monthList;
	monthList.push_back (JAN_CAP);
	monthList.push_back (FEB_CAP);
	monthList.push_back (MAR_CAP);
	monthList.push_back (APR_CAP);
	monthList.push_back (MAY_CAP);
	monthList.push_back (JUN_CAP);
	monthList.push_back (JUL_CAP);
	monthList.push_back (AUG_CAP);
	monthList.push_back (SEP_CAP);
	monthList.push_back (OCT_CAP);
	monthList.push_back (NOV_CAP);
	monthList.push_back (DEC_CAP);
	monthList.push_back (JAN_SMALL);
	monthList.push_back (FEB_SMALL);
	monthList.push_back (MAR_SMALL);
	monthList.push_back (APR_SMALL);
	monthList.push_back (MAY_SMALL);
	monthList.push_back (JUN_SMALL);
	monthList.push_back (JUL_SMALL);
	monthList.push_back (AUG_SMALL);
	monthList.push_back (SEP_SMALL);
	monthList.push_back (OCT_SMALL);
	monthList.push_back (NOV_SMALL);
	monthList.push_back (DEC_SMALL);

	if (inputToBeParsed.size() >= LENGTH_OF_DATE_ALPHABET) {
		end = inputToBeParsed.find_first_of (SPACE);
		if (end == ONE || end == TWO) {
			date = inputToBeParsed.substr (ZERO, end);
			if (isInteger (date)) {
				dateInt = convertStringToInteger (date);
				if (dateInt < ONE || dateInt > THIRTY_ONE) {
					throw ERROR_MESSAGE_DATE;
				}

				inputToBeParsed = inputToBeParsed.substr (end + ONE);
				month = inputToBeParsed.substr (ZERO, THREE);
				if (isStringEqual (month, monthList)) {
					if ((month == APR_CAP || month == APR_SMALL ||
						month == JUN_CAP || month == JUN_SMALL ||
						month == SEP_CAP || month == SEP_SMALL ||
						month == NOV_CAP || month == NOV_SMALL) &&
						dateInt == THIRTY_ONE) {
							throw ERROR_MESSAGE_DATE;
					}
					else if ((month == FEB_CAP || month == FEB_SMALL) &&
						(dateInt == THIRTY_ONE || dateInt == THIRTY)) {
							throw ERROR_MESSAGE_DATE;
					}
					return true;
				}
			}
		}
	}

	return false;
}


//This method checks if the date format includes a year.
//If the date and month are followed by " yyyy",
//it returns true;
//else, it returns false
bool Parser::isYearAlphabet (string inputToBeParsed, int& yearInt) {
	int end = 0;
	string year;
	if (inputToBeParsed.size() >= LENGTH_OF_YEAR_ALPHABET) {
		end = inputToBeParsed.find_first_of (SPACE);
		if (end == ZERO) {
			year = inputToBeParsed.substr (end + ONE, FOUR);
			if (isInteger (year)) {
				yearInt = convertStringToInteger (year);
				if (yearInt > YEAR_MAX || yearInt < YEAR_MIN) {
					throw ERROR_MESSAGE_YEAR;
				}
				return true;
			}
		}
	}

	return false;
}


//This method is to check if the start of the string is a starting time
//(which may be followed by an ending time).
//The string firstly needs to be longer than the time format.
//Then it must follow the format "hh:mm" or "h:mm"
//in order to be recognised as a starting time.
bool Parser::isStartingTimeTwentyFour (string inputToBeParsed, int& hourInt, int& minuteInt) {
	int end = 0;
	string hour;
	string minute;

	if (inputToBeParsed.size() >= LENGTH_OF_STARTING_TIME) {
		end = inputToBeParsed.find_first_of (COLON);
		if (end == ONE || end == TWO) {
			hour = inputToBeParsed.substr (ZERO, end);
			if (isInteger (hour)) {
				hourInt = convertStringToInteger (hour);
				if (hourInt < ZERO || hourInt > TWENTY_THREE) {
					throw ERROR_MESSAGE_TIME;
				}

				inputToBeParsed = inputToBeParsed.substr (end + ONE);
				minute = inputToBeParsed.substr (ZERO, TWO);
				if (isInteger (minute)) {
					minuteInt = convertStringToInteger (minute);
					if (minuteInt < ZERO || minuteInt > FIFTY_NINE) {
						throw ERROR_MESSAGE_TIME;
					}
					return true;
				}
			}
		}
	}

	return false;
}


//This method is to check if the start of the string is a time period.
//The string firstly needs to be longer than the time period format.
//Then it must follow the format "hh:mm-hh:mm", "h:mm-h:mm",
//"h:mm-hh:mm", or "hh:mm-h:mm"
//in order to be recognised as a time period.
bool Parser::isTimePeriodTwentyFour (string inputToBeParsed, int& hourBegInt, int& hourEndInt, 
		int& minuteBegInt, int& minuteEndInt) {
	int end = 0;
	if (inputToBeParsed.size() >= LENGTH_OF_TIME_PERIOD) {
		if (isStartingTimeTwentyFour (inputToBeParsed, hourBegInt, minuteBegInt)) {
			end = inputToBeParsed.find_first_of (DASH);
			if (end == FOUR || end == FIVE) {
				inputToBeParsed = inputToBeParsed.substr (end + ONE);
				if (isStartingTimeTwentyFour (inputToBeParsed, hourEndInt, minuteEndInt)) {
					return true;
				}
			}
		}
	}

	return false;
}


//This method is to check if the start of the string is a starting time
//(which may be followed by an ending time).
//The string firstly needs to be longer than the time format.
//Then it must follow the format "h", "hh", "h.mm", or "hh.mm"
//followed by "am" or "pm"
//in order to be recognised as a starting time.
bool Parser::isStartingTimeTwelve (string inputToBeParsed, int& hourInt, int& minuteInt) {
	int end = 0;
	string hour;
	string minute;

	if (inputToBeParsed.size () >= SIX) {  //"9.00am"
		end = inputToBeParsed.find_first_of (DOT);
		if (end == ONE || end == TWO) { //case 9.00am or 09.00am
			hour = inputToBeParsed.substr (ZERO, end);
			if (isInteger (hour)) {
				hourInt = convertStringToInteger (hour);
				if (hourInt < ONE || hourInt > TWELVE) {
					throw ERROR_MESSAGE_TIME;
				}

				minute = inputToBeParsed.substr (end + ONE, TWO);
				if (isInteger (minute)) {
					minuteInt = convertStringToInteger (minute);
					if (minuteInt < ZERO || minuteInt > FIFTY_NINE) {
						throw ERROR_MESSAGE_TIME;
					}

					if (inputToBeParsed.substr (end + THREE, TWO) == AM ||
						inputToBeParsed.substr (end + THREE, TWO) == PM) {
							if (inputToBeParsed.substr (end + THREE, TWO) == AM) {
								if (hourInt == TWELVE) {
									hourInt = ZERO;
								}
							}

							else {
								if (hourInt <= ELEVEN && hourInt >= ONE) {
									hourInt += TWELVE;
								}
							}
								return true;
					}
				}
			}
		}
	}

	if (inputToBeParsed.size () >= THREE) {  //"9am"
		end = inputToBeParsed.find_first_of (M);
		if (end == TWO || end == THREE) { //case 9am or 19am
			hour = inputToBeParsed.substr (ZERO, end - ONE);
			if (isInteger (hour)) {
				hourInt = convertStringToInteger (hour);
				if (hourInt < ONE || hourInt > TWELVE) {
					throw ERROR_MESSAGE_TIME;
				}
				minuteInt = ZERO;

				if (inputToBeParsed.substr (end - ONE, TWO) == AM ||
					inputToBeParsed.substr (end - ONE, TWO) == PM) {
						if (inputToBeParsed.substr (end - ONE, TWO) == AM) {
							if (hourInt == TWELVE) {
								hourInt = ZERO;
							}
						}
							
						else {
							if (hourInt <= ELEVEN && hourInt >= ONE) {
								hourInt += TWELVE;
							}
						}
							
						return true;
				}
			}
		}
	}

	return false;
}


//This method is to check if the start of the string is a time period.
//The string firstly needs to be longer than the time period format.
//Then it must follow the format "h", "hh", "h.mm", or "hh.mm"
//followed by "am" or "pm"
//in order to be recognised as a time period.
bool Parser::isTimePeriodTwelve (string inputToBeParsed,  int& hourBegInt, int& hourEndInt, 
		int& minuteBegInt, int& minuteEndInt) {
	int end = 0;
	if (inputToBeParsed.size() >= SEVEN ) { //9am-9pm
		if (isStartingTimeTwelve (inputToBeParsed, hourBegInt, minuteBegInt)) {
			end = inputToBeParsed.find_first_of (DASH);
			if (end == THREE || end == FOUR ||
				end ==SIX || end == SEVEN) {
					inputToBeParsed = inputToBeParsed.substr (end + ONE);
					if (isStartingTimeTwelve (inputToBeParsed, hourEndInt, minuteEndInt)) {
						return true;
					}
			}
		}
	}

	return false;
}


//This method checks if a vector contains certain string.
bool Parser::isStringEqual (string inputString, vector<string> compString) {
	for (int i = 0; i != compString.size(); i++) {
		if (inputString == compString [i]) {
			return true;
		}
	}
	return false;
}


//This method is to month in alphabet format to integer format.
int Parser::convertAlphabetMonthToInteger (string month) {
	int monthInt;
	if (month == JAN_CAP || month == JAN_SMALL) {
		monthInt = ONE;
	}
	else if (month == FEB_CAP || month == FEB_SMALL) {
		monthInt = TWO;
	}
	else if (month == MAR_CAP || month == MAR_SMALL) {
		monthInt = THREE;
	}
	else if (month == APR_CAP || month == APR_SMALL) {
		monthInt = FOUR;
	}
	else if (month == MAY_CAP || month == MAY_SMALL) {
		monthInt = FIVE;
	}
	else if (month == JUN_CAP || month == JUN_SMALL) {
		monthInt = SIX;
	}
	else if (month == JUL_CAP || month == JUL_SMALL) {
		monthInt = SEVEN;
	}
	else if (month == AUG_CAP || month == AUG_SMALL) {
		monthInt = EIGHT;
	}
	else if (month == SEP_CAP || month == SEP_SMALL) {
		monthInt = NINE;
	}
	else if (month == OCT_CAP || month == OCT_SMALL) {
		monthInt = TEN;
	}
	else if (month == NOV_CAP || month == NOV_SMALL) {
		monthInt = ELEVEN;
	}
	else if (month == DEC_CAP || month == DEC_SMALL) {
		monthInt = TWELVE;
	}
	return monthInt;
}

//This method takes in date, month and year
//and convert them to day of the week.
//Day of the week in the Data object will be updated.
string Parser::convertDateToDayOfTheWeek (int date, int month, int year) {
  time_t rawtime;
  struct tm timeinfo;
  const char* weekday[] = {SUNDAY, MONDAY, TUESDAY, WEDNESDAY,
	  THURSDAY, FRIDAY, SATURDAY};

  time ( &rawtime );
  localtime_s (&timeinfo, &rawtime);
  timeinfo.tm_year = year - START_OF_YEAR;
  timeinfo.tm_mon = month - ONE;
  timeinfo.tm_mday = date;

  mktime ( &timeinfo );

  return (weekday[timeinfo.tm_wday]);
}


//This method is to get today's date, month, year and day
//and store them in a TimeMacro object
//which its caller can access.
void Parser::getTodayDate (TimeMacro& timeMacro) {
    time_t t = time (ZERO);   // get time now
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + START_OF_YEAR;
    now.tm_mon = now.tm_mon + ONE;
	string dayOfTheWeek = convertDateToDayOfTheWeek (now.tm_mday, now.tm_mon, now.tm_year);
	
	timeMacro.updateYear (now.tm_year);
	timeMacro.updateMonth (now.tm_mon);
	timeMacro.updateDate (now.tm_mday);
	timeMacro.updateDay (dayOfTheWeek);
}


//This method is to get tomorrow's date, month, year and day
//and store them in a TimeMacro object
//which its caller can access.
void Parser::getTomorrowDate (TimeMacro& timeMacro) {
	TimeMacro today;
	getTodayDate (today);
	int date = today.getDate();
	int month = today.getMonth();
	int year = today.getYear();

	if (date == THIRTY_ONE) {
		if (month == TWELVE) {
			year += ONE;
			month = ONE;
		}
		else {
			month += ONE;
		}
		date = ONE;
	}
	else if (date == THIRTY) {
		if (month == FOUR || month == SIX ||
			month == NINE || month == ELEVEN) {
				date = ONE;
				month += ONE;
		}
	}
	else if (date == TWENTY_EIGHT && !isLeapYear (year) &&
		month == TWO) {
			date = ONE;
			month += ONE;
	}
	else if (date == TWENTY_NINE && isLeapYear (year) &&
		month ==TWO) {
			date = ONE;
			month += ONE;
	}
	else {
		date += ONE;
	}

	string dayOfTheWeek = convertDateToDayOfTheWeek (date, month, year);
    timeMacro.updateYear (year);
	timeMacro.updateMonth (month);
	timeMacro.updateDate (date);
	timeMacro.updateDay (dayOfTheWeek);
}


//This method is to get this Monday's date, month, year and day
//and store them in a TimeMacro object
//which its caller can access.
void Parser::getMondayDate (TimeMacro &timeMacro) {
	int day;
	int date;
	time_t t = time (ZERO);   
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + START_OF_YEAR;
    now.tm_mon = now.tm_mon + ONE;

	if (now.tm_wday == ZERO) {
		day = SIX;
	}
	else {
		day = now.tm_wday - ONE;
	}
	date = now.tm_mday - day;

	if (date < ONE) {  //if Monday is on previous month
		if (now.tm_mon == ZERO) {   //if it is Jan now
			date += THIRTY_ONE;
			timeMacro.updateMonth (TWELVE);
			timeMacro.updateYear (now.tm_year - ONE);
		}
		else {
			timeMacro.updateMonth (now.tm_mon - ONE);
			timeMacro.updateYear (now.tm_year);
			if (now.tm_mon == ONE ||
				now.tm_mon == THREE ||
				now.tm_mon == FIVE ||
				now.tm_mon == SEVEN ||
				now.tm_mon ==EIGHT ||
				now.tm_mon == TEN) {  //Feb, Apr, Jun, Aug, Sep, Nov
				date += THIRTY_ONE;
			}
			else if (now.tm_mon == TWO) {  //Mar
				if (isLeapYear (now.tm_year)) {
					date += TWENTY_NINE;
				}
				else {
					date += TWENTY_EIGHT;
				}
			}
			else if (now.tm_mon == FOUR ||
				now.tm_mon == SIX ||
				now.tm_mon == NINE ||
				now.tm_mon == ELEVEN) {  //May, Jul, Oct, Dec
				date += THIRTY;
			}
		}
	}
	else {
		timeMacro.updateMonth (now.tm_mon);
		timeMacro.updateYear (now.tm_year);
	}

	timeMacro.updateDate (date);
	timeMacro.updateDay (MONDAY);

}


//This method is to get this Sunday's date, month, year and day
//and store them in a TimeMacro object
//which its caller can access.
void Parser::getSundayDate (TimeMacro &timeMacro) {
	int day;
	int date;
	time_t t = time (ZERO);   
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + START_OF_YEAR;
    now.tm_mon = now.tm_mon + ONE;

	if (now.tm_wday == ZERO) {
		day = ZERO;
	}
	else {
		day = SEVEN - now.tm_wday;
	}
	date = now.tm_mday + day;

	if (now.tm_mon != ELEVEN || date <= THIRTY_ONE) { //not end of Dec
		timeMacro.updateYear (now.tm_year);
		if ((now.tm_mon == ZERO || //Jan, Mar, May, Jul, Aug, Oct
			now.tm_mon == TWO ||
			now.tm_mon == FOUR ||
			now.tm_mon == SIX ||
			now.tm_mon == SEVEN ||
			now.tm_mon == NINE) && 
			date > THIRTY_ONE) {
				date -= THIRTY_ONE;
				timeMacro.updateMonth (now.tm_mon + 1);
		}

		else if ((now.tm_mon == THREE ||  //Apr, Jun, Sep, Nov
			now.tm_mon == FIVE ||
			now.tm_mon == EIGHT ||
			now.tm_mon == TEN) &&
			date > THIRTY) {
				date -= THIRTY;
				timeMacro.updateMonth (now.tm_mon + ONE);
		}

		else if (now.tm_mon == ONE &&  //Feb
			isLeapYear (now.tm_year) && date > TWENTY_NINE) {
				date -= TWENTY_NINE;
				timeMacro.updateMonth (now.tm_mon + ONE);
		}
		else if (now.tm_mon == ONE &&
			!isLeapYear (now.tm_year) && date > TWENTY_EIGHT) {
				date -= TWENTY_EIGHT;
				timeMacro.updateMonth (now.tm_mon + ONE);
		}

		else {
			timeMacro.updateMonth (now.tm_mon);
		}
	}
	else {
		date -= THIRTY_ONE;
		timeMacro.updateYear (now.tm_year + ONE);
		timeMacro.updateMonth (ZERO);
	}


	timeMacro.updateDate (date);
	timeMacro.updateDay (SUNDAY);
}


//This method is to get the starting date and ending date
//of this month.
//The starting and ending date, month and year
//will be stored in two TimeMacro objects
//which will be passed to its caller.
//Please no
void Parser::getThisMonth (TimeMacro& timeMacroBeg, TimeMacro& timeMacroEnd) {
	time_t t = time (ZERO);
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + START_OF_YEAR;
    now.tm_mon = now.tm_mon + ONE;

	timeMacroBeg.updateYear (now.tm_year);
	timeMacroBeg.updateMonth (now.tm_mon);
	timeMacroBeg.updateDate (ONE);

	timeMacroEnd.updateYear (now.tm_year);
	timeMacroEnd.updateMonth (now.tm_mon);

	if (now.tm_mon == ONE || now.tm_mon == THREE ||
		now.tm_mon == FIVE || now.tm_mon == SEVEN ||
		now.tm_mon == EIGHT || now.tm_mon == TEN ||
		now.tm_mon == TWELVE) {
			timeMacroEnd.updateDate (THIRTY_ONE);
	}
	else if (now.tm_mon == FOUR || now.tm_mon == SIX ||
		now.tm_mon == NINE || now.tm_mon == ELEVEN) {
			timeMacroEnd.updateDate (THIRTY);
	}
	else if (now.tm_mon == TWO && isLeapYear (now.tm_year)) {
		timeMacroEnd.updateDate (TWENTY_NINE);
	}
	else {
		timeMacroEnd.updateDate (TWENTY_EIGHT);
	}	
}

//One potential bug:
//the date period must be the start and end of this month
//there may be bug when the ending date of month changes


//This method is to check if a certain year is a leap year or not
bool Parser::isLeapYear (int year) {
	if (year % FOUR != ZERO) {
		return false;
	}
	else if (year % HUNDRAD != ZERO) {
		return true;
	}
	else if (year % FOUR_HUNDRAD != ZERO) {
		return false;
	}
	else {
		return true;
	}
}