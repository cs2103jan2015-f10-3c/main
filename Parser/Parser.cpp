#include "Parser.h"

const unsigned int Parser::LENGTH_OF_DATE_NUMBER = 3;  //"d/m"
const unsigned int Parser::LENGTH_OF_DATE_ALPHABET = 5;  //"d MMM"
const unsigned int Parser::LENGTH_OF_YEAR_ALPHABET = 5;
const unsigned int Parser::START = 0;
const unsigned int Parser::ONE = 1;
const unsigned int Parser::TWO = 2;
const unsigned int Parser::THREE = 3;
const unsigned int Parser::FOUR = 4;
const unsigned int Parser::FIVE = 5;
const unsigned int Parser::SIX = 6;
const unsigned int Parser::SEVEN = 7;
const unsigned int Parser::LENGTH_OF_STARTING_TIME = 4;  //"9:00"
const unsigned int Parser::LENGTH_OF_TIME_PERIOD = 9;  //"9:00-9:30"
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



//This method is called by OperationCenter.
//It takes in user's input message
//and updates error message if the user's command word is incorrect.
void Parser::parseInput (string userInput) {
	string commandWord;

	commandWord = extractCommandWord (userInput);

	try {
		checkCommandWord (userInput, commandWord);
	}

	catch (const char* errorMessge) {
		updateErrorMessage (errorMessge);
	}
}


//This method is to recognise different user's command word
//and call for different actions accordingly.
//If the user enters an incorrect command word,
//it will throw an exception.
void Parser::checkCommandWord (string userInput, string commandWord) {
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
		parseUndo (userInput, commandWord);
	}
	else if (commandWord == "delete") {
		parseDelete (userInput, commandWord);
	}
	else if (commandWord == "done") {
		parseDone (userInput, commandWord);
	}
	else if (commandWord == "undone") {
		parseUndone (userInput, commandWord);
	}
	else if (commandWord == "show") {
		parseShow (userInput, commandWord);
	}
	else if (commandWord == "clear") {
		parseClear (userInput, commandWord);
	}
	else if (commandWord == "path") {
		parsePath (userInput, commandWord);
	}
	else if (commandWord == "help") {
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
	end = userInput.find_first_of (' ');
	commandWord = userInput.substr (0, end);
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
	if (inputToBeParsed != "" && inputToBeParsed != " ") {
		//This "if" condition is to account for the cases where
		//the user only enters the command word
		//or enters a command word followed by a white space.
		//These cases may usually happen when the users are careless.
		inputToBeParsed = inputToBeParsed.substr (ONE);

		parseDateNumber (inputToBeParsed, timeMacro);
		parseDateAlphabet (inputToBeParsed, timeMacro);

		parseTimeTwentyFour (inputToBeParsed, timeMicroBeg, timeMicroEnd);
		parseTimeTwelve (inputToBeParsed, timeMicroBeg, timeMicroEnd);

		if (timeMacro.getDate() == 0 &&
			timeMacro.getMonth() == 0 &&
			timeMacro.getYear() == 0) {
				parseDateNumber (inputToBeParsed, timeMacro);
				parseDateAlphabet (inputToBeParsed, timeMacro);
		}
		//This "if" block is to make sure the date can be parsed
		//even if it is put after the time.
		
		desc = inputToBeParsed;

		if (desc == "") {
			throw ERROR_MESSAGE_DESC;
		}

		updateCommand (commandWord);
		updateTimeMacro (timeMacro);
		updateTimeMicroPeriod (timeMicroBeg, timeMicroEnd);
		updateDesc (desc);

		if (timeMacro.getDate() == 0 &&
			timeMicroBeg.getHour() != -1) {
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
	if (inputToBeParsed != "" && inputToBeParsed != " ") {
		inputToBeParsed = inputToBeParsed.substr (ONE);

		index = parseTaskNo (inputToBeParsed);
		taskNo = convertStringToInteger (index);
		if (taskNo < 1) {
			throw ERROR_MESSAGE_TASK_NO;
		}

		inputToBeParsed = inputToBeParsed.substr(index.size ());
		if (inputToBeParsed != "" && inputToBeParsed != " ") {
			inputToBeParsed = inputToBeParsed.substr(ONE);

			parseDateNumber (inputToBeParsed, timeMacro);
			parseDateAlphabet (inputToBeParsed, timeMacro);

			parseTimeTwentyFour (inputToBeParsed, timeMicroBeg, timeMicroEnd);
			parseTimeTwelve (inputToBeParsed, timeMicroBeg, timeMicroEnd);

			if (timeMacro.getDate() == 0 &&
				timeMacro.getMonth() == 0 &&
				timeMacro.getYear() == 0) {
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
	if (desc != "" && desc != " ") {
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
	if (leftOver != "" && leftOver != " ") {
		throw ERROR_MESSAGE_COMMAND;
	}
}


//This method is to parse user's input if the command word is "delete".
//The command word "delete" must be followed by a task number.
void Parser::parseDelete (string userInput, string commandWord) {
	int taskNo;
	string index = userInput.substr (commandWord.size());
	if (index != "" && index != " ") {
		index = index.substr (ONE);
		taskNo = convertStringToInteger (index);
		if (taskNo < 1) {
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
	if (index != "" && index != " ") {
		index = index.substr (ONE);
		taskNo = convertStringToInteger (index);
		if (taskNo < 1) {
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
	if (index != "" && index != " ") {
		index = index.substr (ONE);
		taskNo = convertStringToInteger (index);
		if (taskNo < 1) {
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
//1st case: the command word show is followed by a period.
//The user can enter "show today", "show tomorrow",
//"show this week" and "show this month".
//The starting and ending date/month/year/day will be updated.
//2nd case: the command word show is followed by the 
//words "commands", "float", "done", or "features".
//Then the command word will become "show commands" or "show float", etc.
//If the word following "show" does not fall into these 2 cases,
//it will throw an exception.
void Parser::parseShow (string userInput, string commandWord) {
	string inputToBeParsed = userInput.substr (commandWord.size ());
	TimeMacro timeMacroBeg;
	TimeMacro timeMacroEnd;

	if (inputToBeParsed != "" && inputToBeParsed != " ") {
		inputToBeParsed = inputToBeParsed.substr(ONE);

		if (inputToBeParsed == "today") {
			getTodayDate (timeMacroBeg);
			timeMacroEnd = timeMacroBeg;
			updateCommand (commandWord);
			updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}
		else if (inputToBeParsed == "tomorrow") {
			getTomorrowDate (timeMacroBeg);
			timeMacroEnd = timeMacroBeg;
			updateCommand (commandWord);
			updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}
		else if (inputToBeParsed == "this week") {
			getMondayDate (timeMacroBeg);
			getSundayDate (timeMacroEnd);
			updateCommand (commandWord);
			updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}
		else if (inputToBeParsed == "this month") {
			getThisMonth (timeMacroBeg, timeMacroEnd);
			updateCommand (commandWord);
			updateTimeMacroPeriod (timeMacroBeg, timeMacroEnd);
		}
		else if (inputToBeParsed == "commands" ||
			inputToBeParsed == "float" ||
			inputToBeParsed == "done" ||
			inputToBeParsed == "features") {
				commandWord = commandWord + " " + inputToBeParsed;
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
void Parser::parseClear (string userInput, string commandWord) {
	updateCommand (commandWord);

	string leftOver = userInput.substr (commandWord.size());
	if (leftOver != "" && leftOver != " ") {
		throw ERROR_MESSAGE_COMMAND;
	}
}


void Parser::parsePath (string userInput, string commandWord) {
	string inputToBeParsed = userInput.substr (commandWord.size ());

	if (inputToBeParsed != "" && inputToBeParsed != " ") {
		inputToBeParsed = inputToBeParsed.substr(ONE);

		updateCommand (commandWord);
		updateDirectory (inputToBeParsed);	
	}
	else {
		throw ERROR_MESSAGE_DIRECTORY;
	}
}

void Parser::parseHelp (string userInput, string commandWord) {
	updateCommand (commandWord);

	string leftOver = userInput.substr (commandWord.size());
	if (leftOver != "" && leftOver != " ") {
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

		end = inputToBeParsesd.find_first_of ('/');
		inputToBeParsesd = inputToBeParsesd.substr (end + 1);
		if (isYearNumber (inputToBeParsesd, yearInt)) {
			timeMacro.updateYear (yearInt);
		}
		else {
			time_t t = time (0);
			struct tm now;
			localtime_s (&now, &t);
			now.tm_year = now.tm_year + 1900;
			yearInt = now.tm_year;
			timeMacro.updateYear (yearInt);
		}

		day = convertDateToDayOfTheWeek (dateInt, monthInt, yearInt);
		timeMacro.updateDay (day);

		end = inputToBeParsesd.find_first_of (' ');
		if (end != string::npos) {
			inputToBeParsesd = inputToBeParsesd.substr (end + 1);
		}
		else {
			inputToBeParsesd = "";
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

		end = inputToBeParsesd.find_first_of (' ');
		inputToBeParsesd = inputToBeParsesd.substr (end + ONE);
		monthInt = convertAlphabetMonthToInteger (inputToBeParsesd.substr (START, THREE));
		timeMacro.updateMonth (monthInt);
		inputToBeParsesd = inputToBeParsesd.substr (THREE);

		if (isYearAlphabet (inputToBeParsesd, yearInt)) {
			timeMacro.updateYear (yearInt);
			if (inputToBeParsesd.size() > SIX) {
				inputToBeParsesd = inputToBeParsesd.substr (SIX); //there is still content after the year
			}
			else {
				inputToBeParsesd = "";
			}
		}

		else {
			if (inputToBeParsesd.size() > ONE) {
				inputToBeParsesd = inputToBeParsesd.substr (ONE);
			}

			time_t t = time (0);
			struct tm now;
			localtime_s (&now, &t);
			now.tm_year = now.tm_year + 1900;
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
			if (isTimePeriodTwentyFour (inputToBeParsed, hourBegInt, hourEndInt, minuteBegInt, minuteEndInt)) {
				timeMicroBeg.updateHour (hourBegInt);
				timeMicroBeg.updateMin (minuteBegInt);
				timeMicroEnd.updateHour (hourEndInt);
				timeMicroEnd.updateMin (minuteEndInt);
			}

			else {
				if (isStartingTimeTwentyFour (inputToBeParsed, hourBegInt, minuteBegInt)) {
					timeMicroBeg.updateHour (hourBegInt);
					timeMicroBeg.updateMin (minuteBegInt);
				}
			}

			end = inputToBeParsed.find_first_of (' ');
			if (end == string::npos) {
				inputToBeParsed = "";
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
			if (isTimePeriodTwelve (inputToBeParsed, hourBegInt, hourEndInt, minuteBegInt, minuteEndInt)) {
				timeMicroBeg.updateHour (hourBegInt);
				timeMicroBeg.updateMin (minuteBegInt);
				timeMicroEnd.updateHour (hourEndInt);
				timeMicroEnd.updateMin (minuteEndInt);
			}

			else {
				if (isStartingTimeTwelve (inputToBeParsed, hourBegInt, minuteBegInt)) {
					timeMicroBeg.updateHour (hourBegInt);
					timeMicroBeg.updateMin (minuteBegInt);
				}
			}

			end = inputToBeParsed.find_first_of (' ');
			if (end == string::npos) {
				inputToBeParsed = "";
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
	int lengthOfTaskNo = inputToBeParsed.find_first_of (' ');
	string index = inputToBeParsed.substr (0, lengthOfTaskNo);
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
		end = inputToBeParsed.find_first_of ('/');
		if (end == ONE || end == TWO) {
			date = inputToBeParsed.substr (0, end);
			if (isInteger (date)) {
				dateInt = convertStringToInteger (date);
				if (dateInt < 1 || dateInt > 31) {
					throw ERROR_MESSAGE_DATE;
				}

				inputToBeParsed = inputToBeParsed.substr (end + 1);
				end = inputToBeParsed.find_first_of(" /");
				if (end == ONE || end == TWO ||
					(end == string::npos && 
					(inputToBeParsed.size() == 1 || inputToBeParsed.size () ==2))) {
						month = inputToBeParsed.substr (0, end);
						if (isInteger (month)) {
							monthInt= convertStringToInteger (month);
							if (monthInt < 1 || monthInt > 12) {
								throw ERROR_MESSAGE_DATE;
							}

							if ((monthInt == 4 || monthInt == 6 ||
								monthInt == 9 || monthInt == 11) &&
								dateInt == 31) {
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

	end = inputToBeParsed.find_first_of ("/");
	if (end == ONE || end == TWO) {
		year = inputToBeParsed.substr (end + ONE, FOUR);
		if (isInteger (year)) {
			yearInt = convertStringToInteger (year);
			if (yearInt < 2000 || yearInt > 2100) {
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
	monthList.push_back ("Jan");
	monthList.push_back ("Feb");
	monthList.push_back ("Mar");
	monthList.push_back ("Apr");
	monthList.push_back ("May");
	monthList.push_back ("Jun");
	monthList.push_back ("Jul");
	monthList.push_back ("Aug");
	monthList.push_back ("Sep");
	monthList.push_back ("Oct");
	monthList.push_back ("Nov");
	monthList.push_back ("Dec");
	monthList.push_back ("jan");
	monthList.push_back ("feb");
	monthList.push_back ("mar");
	monthList.push_back ("apr");
	monthList.push_back ("may");
	monthList.push_back ("jun");
	monthList.push_back ("jul");
	monthList.push_back ("aug");
	monthList.push_back ("sep");
	monthList.push_back ("oct");
	monthList.push_back ("nov");
	monthList.push_back ("dec");

	if (inputToBeParsed.size() >= LENGTH_OF_DATE_ALPHABET) {
		end = inputToBeParsed.find_first_of (' ');
		if (end == ONE || end == TWO) {
			date = inputToBeParsed.substr (0, end);
			if (isInteger (date)) {
				dateInt = convertStringToInteger (date);
				if (dateInt < 1 || dateInt > 31) {
					throw ERROR_MESSAGE_DATE;
				}

				inputToBeParsed = inputToBeParsed.substr (end + 1);
				month = inputToBeParsed.substr (0, THREE);
				if (isStringEqual (month, monthList)) {
					if ((month == "Apr" || month == "apr" ||
						month == "Jun" || month == "jun" ||
						month == "Sep" || month == "sep" ||
						month == "Nov" || month == "nov") &&
						dateInt == 31) {
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
		end = inputToBeParsed.find_first_of (' ');
		if (end == 0) {
			year = inputToBeParsed.substr (end + 1, FOUR);
			if (isInteger (year)) {
				yearInt = convertStringToInteger (year);
				if (yearInt > 2100 || yearInt < 2000) {
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
		end = inputToBeParsed.find_first_of (':');
		if (end == ONE || end == TWO) {
			hour = inputToBeParsed.substr (START, end);
			if (isInteger (hour)) {
				hourInt = convertStringToInteger (hour);
				if (hourInt < 0 || hourInt > 23) {
					throw ERROR_MESSAGE_TIME;
				}

				inputToBeParsed = inputToBeParsed.substr (end + ONE);
				minute = inputToBeParsed.substr (START, TWO);
				if (isInteger (minute)) {
					minuteInt = convertStringToInteger (minute);
					if (minuteInt < 0 || minuteInt > 59) {
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
			end = inputToBeParsed.find_first_of ('-');
			if (end == FOUR || end == FIVE) {
				inputToBeParsed = inputToBeParsed.substr (end + 1);
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
		end = inputToBeParsed.find_first_of ('.');
		if (end == ONE || end == TWO) { //case 9.00am or 09.00am
			hour = inputToBeParsed.substr (START, end);
			if (isInteger (hour)) {
				hourInt = convertStringToInteger (hour);
				if (hourInt < 1 || hourInt > 12) {
					throw ERROR_MESSAGE_TIME;
				}

				minute = inputToBeParsed.substr (end + ONE, TWO);
				if (isInteger (minute)) {
					minuteInt = convertStringToInteger (minute);
					if (minuteInt < 0 || minuteInt > 59) {
						throw ERROR_MESSAGE_TIME;
					}

					if (inputToBeParsed.substr (end + THREE, TWO) == "am" ||
						inputToBeParsed.substr (end + THREE, TWO) == "pm") {
							if (inputToBeParsed.substr (end + THREE, TWO) == "am") {
								if (hourInt == 12) {
									hourInt = 0;
								}
							}

							else {
								if (hourInt <= 11 && hourInt >= 1) {
									hourInt += 12;
								}
							}
								return true;
					}
				}
			}
		}
	}

	if (inputToBeParsed.size () >= THREE) {  //"9am"
		end = inputToBeParsed.find_first_of ('m');
		if (end == TWO || end == THREE) { //case 9am or 19am
			hour = inputToBeParsed.substr (START, end - ONE);
			if (isInteger (hour)) {
				hourInt = convertStringToInteger (hour);
				if (hourInt < 1 || hourInt > 12) {
					throw ERROR_MESSAGE_TIME;
				}
				minuteInt = START;

				if (inputToBeParsed.substr (end - ONE, TWO) == "am" ||
					inputToBeParsed.substr (end - ONE, TWO) == "pm") {
						if (inputToBeParsed.substr (end - ONE, TWO) == "am") {
							if (hourInt == 12) {
								hourInt = 0;
							}
						}
							
						else {
							if (hourInt <= 11 && hourInt >= 1) {
								hourInt += 12;
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
			end = inputToBeParsed.find_first_of ('-');
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


bool Parser::isStringEqual (string inputString, vector<string> compString) {
	for (int i = 0; i != compString.size(); i++) {
		if (inputString == compString [i]) {
			return true;
		}
	}
	return false;
}

int Parser::convertAlphabetMonthToInteger (string month) {
	int monthInt;
	if (month == "Jan" || month == "jan") {
		monthInt = 1;
	}
	else if (month == "Feb" || month == "feb") {
		monthInt = 2;
	}
	else if (month == "Mar" || month == "mar") {
		monthInt = 3;
	}
	else if (month == "Apr" || month == "apr") {
		monthInt = 4;
	}
	else if (month == "May" || month == "may") {
		monthInt = 5;
	}
	else if (month == "Jun" || month == "jun") {
		monthInt = 6;
	}
	else if (month == "Jul" || month == "jul") {
		monthInt = 7;
	}
	else if (month == "Aug" || month == "aug") {
		monthInt = 8;
	}
	else if (month == "Sep" || month == "sep") {
		monthInt = 9;
	}
	else if (month == "Oct" || month == "oct") {
		monthInt = 10;
	}
	else if (month == "Nov" || month == "nov") {
		monthInt = 11;
	}
	else if (month == "Dec" || month == "dec") {
		monthInt = 12;
	}
	return monthInt;
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
//which its caller can access.
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
//which its caller can access.
void Parser::getTomorrowDate (TimeMacro& timeMacro) {
    time_t t = time (0);   
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


//This method is to get this Monday's date, month, year and day
//and store them in a TimeMacro object
//which its caller can access.
void Parser::getMondayDate (TimeMacro &timeMacro) {
	int day;
	int date;
	time_t t = time (0);   
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + 1900;
    now.tm_mon = now.tm_mon + 1;

	if (now.tm_wday == 0) {
		day = 6;
	}
	else {
		day = now.tm_wday - 1;
	}
	date = now.tm_mday - day;

	if (date < 1) {  //if Monday is on previous month
		if (now.tm_mon == 0) {   //if it is Jan now
			date += 31;
			timeMacro.updateMonth (12);
			timeMacro.updateYear (now.tm_year - 1);
		}
		else {
			timeMacro.updateMonth (now.tm_mon - 1);
			timeMacro.updateYear (now.tm_year);
			if (now.tm_mon == 1 ||
				now.tm_mon == 3 ||
				now.tm_mon == 5 ||
				now.tm_mon == 7 ||
				now.tm_mon ==8 ||
				now.tm_mon == 10) {  //Feb, Apr, Jun, Aug, Sep, Nov
				date += 31;
			}
			else if (now.tm_mon == 2) {  //Mar
				if (isLeapYear (now.tm_year)) {
					date += 29;
				}
				else {
					date += 28;
				}
			}
			else if (now.tm_mon == 4 ||
				now.tm_mon == 6 ||
				now.tm_mon == 9 ||
				now.tm_mon == 11) {  //May, Jul, Oct, Dec
				date += 30;
			}
		}
	}
	else {
		timeMacro.updateMonth (now.tm_mon);
		timeMacro.updateYear (now.tm_year);
	}

	timeMacro.updateDate (date);
	timeMacro.updateDay ("Monday");

}


//This method is to get this Sunday's date, month, year and day
//and store them in a TimeMacro object
//which its caller can access.
void Parser::getSundayDate (TimeMacro &timeMacro) {
	int day;
	int date;
	time_t t = time (0);   
    struct tm now;
	localtime_s (&now, &t);
    now.tm_year = now.tm_year + 1900;
    now.tm_mon = now.tm_mon + 1;

	if (now.tm_wday == 0) {
		day = 0;
	}
	else {
		day = 7 - now.tm_wday;
	}
	date = now.tm_mday + day;

	if (now.tm_mon != 11 || date <=31) { //not end of Dec
		timeMacro.updateYear (now.tm_year);
		if ((now.tm_mon == 0 || //Jan, Mar, May, Jul, Aug, Oct
			now.tm_mon == 2 ||
			now.tm_mon == 4 ||
			now.tm_mon == 6 ||
			now.tm_mon == 7 ||
			now.tm_mon == 9) && 
			date > 31) {
				date -= 31;
				timeMacro.updateMonth (now.tm_mon + 1);
		}

		else if ((now.tm_mon == 3 ||  //Apr, Jun, Sep, Nov
			now.tm_mon == 5 ||
			now.tm_mon == 8 ||
			now.tm_mon == 10) &&
			date > 30) {
				date -= 30;
				timeMacro.updateMonth (now.tm_mon + 1);
		}

		else if (now.tm_mon == 1 &&  //Feb
			isLeapYear (now.tm_year) && date > 29) {
				date -= 29;
				timeMacro.updateMonth (now.tm_mon + 1);
		}
		else if (now.tm_mon == 1 &&
			!isLeapYear (now.tm_year) && date > 28) {
				date -= 28;
				timeMacro.updateMonth (now.tm_mon + 1);
		}

		else {
			timeMacro.updateMonth (now.tm_mon);
		}
	}
	else {
		date -= 31;
		timeMacro.updateYear (now.tm_year + 1);
		timeMacro.updateMonth (0);
	}


	timeMacro.updateDate (date);
	timeMacro.updateDay ("Sunday");
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

	if (now.tm_mon == 1 || now.tm_mon == 3 ||
		now.tm_mon == 5 || now.tm_mon == 7 ||
		now.tm_mon == 8 || now.tm_mon == 10 ||
		now.tm_mon == 12) {
			timeMacroEnd.updateDate (31);
	}
	else if (now.tm_mon == 4 || now.tm_mon == 6 ||
		now.tm_mon == 9 || now.tm_mon == 11) {
			timeMacroEnd.updateDate (30);
	}
	else if (now.tm_mon == 2 && isLeapYear (now.tm_year)) {
		timeMacroEnd.updateDate (29);
	}
	else {
		timeMacroEnd.updateDate (28);
	}	
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