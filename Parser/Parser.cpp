#include "Parser.h"

const unsigned int Parser::LENGTH_OF_DATE_FULL_NUMBER = 5;  //"dd/mm"
const unsigned int Parser::LENGTH_OF_DATE_ABBRE_NUMBER = 3;  //"d/m"
const unsigned int Parser::LENGTH_OF_DATE_FULL_ALPHABET = 6;  //"dd MMM"
const unsigned int Parser::LENGTH_OF_DATE_ABBRE_ALPHABET = 5;  //"d MMM"
const char Parser::DATE_FIRST_DIGIT[] = "0123";
const char Parser::MONTH_FIRST_DIGIT[] = "01";
const char Parser::YEAR_FIRST_DIGIT[] = "2";
const unsigned int Parser::LENGTH_OF_STARTING_TIME = 4;  //"9:00"
const unsigned int Parser::LENGTH_OF_TIME_PERIOD = 9;  //"9:00-9:30"
const char Parser::TWENTY_FOUR_HOUR_FIRST_DIGIT[] = "012";
const char Parser::TWELVE_HOUR_FIRST_DIGIT[] = "01";
const char Parser::MINUTE_FIRST_DIGIT[] = "012345";
const char Parser::NON_NEGATIVE_DIGIT[] = "0123456789";
const char Parser::POSITIVE_DIGIT[] = "123456789";
const char Parser::ERROR_MESSAGE_COMMAND[] = "Please enter the correct command";
const char Parser::ERROR_MESSAGE_INPUT[] = "Please enter correct input following the command word";
const char Parser::ERROR_MESSAGE_EDIT[] = "Please enter content you want to edit";
const char Parser::ERROR_MESSAGE_TASK_NO[] = "Please enter correct task number after command word";
const char Parser::ERROR_MESSAGE_SHOW[] = "Please enter correct time period or task type";
const char Parser::ERROR_MESSAGE_DIRECTORY[] = "Please enter the correct directory";
const char Parser::ERROR_MESSAGE_DATE[] = "Please enter the correct date";
const char Parser::ERROR_MESSAGE_TIME[] = "Please enter the correct time";


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
		updateErrorMessage (errorMessge);
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
	else if (commandWord == "done") {
		parseDone (userInput, commandWord);
	}
	else if (commandWord == "show") {
		parseShow (userInput, commandWord);
	}
	else if (commandWord == "clear") {
		parseClear (userInput, commandWord);
	}
	else if (commandWord == "save" ||
		commandWord == "load" ) {
		parseSaveLoad (userInput, commandWord);
	}
	else {
		throw ERROR_MESSAGE_COMMAND;
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
//a task must have a description and end with a description
//date and time may be omitted and they can switch order if there are any
void Parser::parseAdd (string userInput, string commandWord) {
	TimeMacro timeMacro;
	TimeMicro timeMicroBeg;
	TimeMicro timeMicroEnd;
	string inputToBeParsed = userInput;
	string desc;

	inputToBeParsed = inputToBeParsed.substr (commandWord.size());
	if (inputToBeParsed != "" && inputToBeParsed != " ") {
		inputToBeParsed = inputToBeParsed.substr (1);

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
//task number, timeMacro, timeMicro and task description.
//The command word "edit" must be followed by a task number.
//a task will end with a description if there is one
//date, time and description can also stand alone
//The task no must be followed by something to edit
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
		inputToBeParsed = inputToBeParsed.substr (1);

		index = parseTaskNo (inputToBeParsed);
		taskNo = convertStringToInteger (index);

		inputToBeParsed = inputToBeParsed.substr(index.size ());
		if (inputToBeParsed != "" && inputToBeParsed != " ") {
			inputToBeParsed = inputToBeParsed.substr(1);

			parseDateNumber (inputToBeParsed, timeMacro);
			parseDateAlphabet (inputToBeParsed, timeMacro);

			parseTimeTwentyFour (inputToBeParsed, timeMicroBeg, timeMicroEnd);
			parseTimeTwelve (inputToBeParsed, timeMicroBeg, timeMicroEnd);

			parseDateNumber (inputToBeParsed, timeMacro);
			parseDateAlphabet (inputToBeParsed, timeMacro);

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
		desc = desc.substr (1);

		updateCommand (commandWord);
		updateDesc (desc);
	}
	else {
		throw ERROR_MESSAGE_INPUT;
	}
}


//This method is to parse user's input if the command word is "undo".
//Only the command word "undo" will be parsed.
void Parser::parseUndo (string commandWord) {
    updateCommand (commandWord);
}


//This method is to parse user's input if the command word is "delete".
//The command word "delete" will be followed by a task number.
void Parser::parseDelete (string userInput, string commandWord) {
	int taskNo;
	string index = userInput.substr (commandWord.size());
	if (index != "" && index != " ") {
		index = index.substr (1);
		taskNo = convertStringToInteger (index);
		updateCommand (commandWord);
		updateTaskNo (taskNo);
	}
	else {
		throw ERROR_MESSAGE_TASK_NO;
	}
}


//This method is to parse user's input if the command word is "done".
//The command word "done" will be followed by a task number.
void Parser::parseDone (string userInput, string commandWord) {
	int taskNo;
	string index = userInput.substr (commandWord.size());
	if (index != "" && index != " ") {
		index = index.substr (1);
		taskNo = convertStringToInteger (index);
		updateCommand (commandWord);
		updateTaskNo (taskNo);
		updateStatus (true);
	}
	else {
		throw ERROR_MESSAGE_TASK_NO;
	}
}



//This method is to parse user's input if the command word is "show".
//1st case: the command word show is followed by a period.
//So far, this method is able to parse the period when the period is
//"today", "tomorrow" and "this month".
//The starting and ending date/month/year/day will be updated.
//2nd case: the command word show is followed by the word "commands".
//Then the command word will become "show commands".
//If the word following "show" does not fall into these 2 cases,
//it will throw an exception.
void Parser::parseShow (string userInput, string commandWord) {
	string inputToBeParsed = userInput.substr (commandWord.size ());
	TimeMacro timeMacroBeg;
	TimeMacro timeMacroEnd;

	if (inputToBeParsed != "" && inputToBeParsed != " ") {
		inputToBeParsed = inputToBeParsed.substr(1);

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
}


void Parser::parseSaveLoad (string userInput, string commandWord) {
	string inputToBeParsed = userInput.substr (commandWord.size ());

	if (inputToBeParsed != "" && inputToBeParsed != " ") {
		inputToBeParsed = inputToBeParsed.substr(1);

		updateCommand (commandWord);
		updateDirectory (inputToBeParsed);	
	}
	else {
		throw ERROR_MESSAGE_DIRECTORY;
	}
}

//This method is to parse date after the start of the string is recoganised as a date.
//The formats it recognises are "dd/mm/yyyy", "d/mm/yyyy", "dd/m/yyyy", "d/m/yyyy",
//"dd/mm", "d/mm", "dd/m", "d/m".
//If the year is not specified, it assumes it is this year.
//Date/month/year/day will be updated.
void Parser::parseDateNumber (string& inputToBeParsesd, TimeMacro& timeMacro) {
	int start = 0;
	int end = 0;
	string date;
	string month;
	string year;
	int dateInt;
	int monthInt;
	int yearInt;

	if (isDateNumber (inputToBeParsesd)) {
		end = inputToBeParsesd.find_first_of ("/");
		date = inputToBeParsesd.substr (0, end);

		start = end + 1;
		inputToBeParsesd = inputToBeParsesd.substr (start);

		if (isYearNumber (inputToBeParsesd)) {
			end = inputToBeParsesd.find_first_of ("/");
			month = inputToBeParsesd.substr (0, end);
			inputToBeParsesd = inputToBeParsesd.substr (end + 1);
			year = inputToBeParsesd.substr (0, 4);
			yearInt = atoi (year.c_str());

			if (inputToBeParsesd.size() > 5) {
				inputToBeParsesd = inputToBeParsesd.substr (start + 4);
			}
			else {
				inputToBeParsesd = "";
			}
		}

		else {
			end = inputToBeParsesd.find_first_of (" ");
			month = inputToBeParsesd.substr (0, end);
			
			if (end != string::npos) {
				inputToBeParsesd = inputToBeParsesd.substr (end + 1);
			}
			else {
				inputToBeParsesd = "";
			}
			
			time_t t = time (0);
			struct tm now;
			localtime_s (&now, &t);
			now.tm_year = now.tm_year + 1900;
			yearInt = now.tm_year;
		}

		dateInt = atoi (date.c_str());
		monthInt = atoi (month.c_str());
		string day = convertDateToDayOfTheWeek (dateInt, monthInt, yearInt);
		timeMacro.updateDate (dateInt);
		timeMacro.updateDay (day);
		timeMacro.updateMonth (monthInt);
		timeMacro.updateYear (yearInt);
	}
}


//This method is to parse date after the start of the string is recoganised as a date.
//The formats it recognises are date (integer) followed by month (abbreviation),
//followed by year (integer). eg. 21 Mar 2015
//If the year is not specified, it assumes it is this year.
//Date/month/year/day will be updated.
void Parser::parseDateAlphabet (string& inputToBeParsesd, TimeMacro& timeMacro) {
	int start = 0;
	int end = 0;
	string date;
	string year;
	int dateInt;
	int monthInt;
	int yearInt;

	if (isDateAlphabet (inputToBeParsesd)) {
		end = inputToBeParsesd.find_first_of (" ");
		date = inputToBeParsesd.substr (0, end);

		start = end + 1;
		inputToBeParsesd = inputToBeParsesd.substr (start);
		monthInt = convertAlphabetMonthToInteger (inputToBeParsesd.substr (0, 3));
		inputToBeParsesd = inputToBeParsesd.substr (3);

		if (isYearAlphabet (inputToBeParsesd)) {
			year = inputToBeParsesd.substr (1, 4);
			yearInt = atoi (year.c_str());
			if (inputToBeParsesd.size() > 6) {
				inputToBeParsesd = inputToBeParsesd.substr (6); //there is still content after the year
			}
			else {
				inputToBeParsesd = "";
			}
			
		}
		else {
			if (inputToBeParsesd.size() > 2) {
				inputToBeParsesd = inputToBeParsesd.substr (1);
			}
			
			time_t t = time (0);
			struct tm now;
			localtime_s (&now, &t);
			now.tm_year = now.tm_year + 1900;
			yearInt = now.tm_year;
		}

		dateInt = atoi (date.c_str());
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
void Parser::parseTimeTwentyFour (string& inputToBeParsed, TimeMicro& timeMicroBeg, TimeMicro& timeMicroEnd) {
	int end = 0;
	if (isTimePeriodTwentyFour (inputToBeParsed) || isStartingTimeTwentyFour (inputToBeParsed)) {
		end = inputToBeParsed.find_first_of (':');
        string hourBeg = inputToBeParsed.substr (0, end);
		string minuteBeg = inputToBeParsed.substr (end + 1, 2);
		int hourBegInt = atoi (hourBeg.c_str());
		int minuteBegInt = atoi (minuteBeg.c_str());
		timeMicroBeg.updateHour (hourBegInt);
		timeMicroBeg.updateMin (minuteBegInt);


		if (!isTimePeriodTwentyFour (inputToBeParsed)) {
			end = inputToBeParsed.find_first_of (' ');
			if (end != string::npos) {
				inputToBeParsed = inputToBeParsed.substr (end + 1);
			}
			else {
				inputToBeParsed = "";
			}
		}

		else {
			end = inputToBeParsed.find_first_of ('-');
			inputToBeParsed = inputToBeParsed.substr (end + 1);
			end = inputToBeParsed.find_first_of (':');
			string hourEnd = inputToBeParsed.substr (0, end);
			string minuteEnd = inputToBeParsed.substr (end + 1, 2);
			int hourEndInt = atoi (hourEnd.c_str());
			int minuteEndInt = atoi (minuteEnd.c_str());
			timeMicroEnd.updateHour (hourEndInt);
			timeMicroEnd.updateMin (minuteEndInt);

			end = inputToBeParsed.find_first_of (' ');
			if (end == string::npos) {
				inputToBeParsed = "";
			}
			else {
				inputToBeParsed = inputToBeParsed.substr (end + 1);
			}
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
	int start = 0;
	int end = 0;
	string hourBeg;
	string hourEnd;
	string minuteBeg;
	string minuteEnd;
	int hourBegInt;
	int hourEndInt;
	int minuteBegInt;
	int minuteEndInt;
	if (isTimePeriodTwelve (inputToBeParsed) || isStartingTimeTwelve (inputToBeParsed)) {
		end = inputToBeParsed.find_first_of (".");
		//case "9.00am"/"19.00am"
		if (end == 1 || end ==2) {
			hourBeg = inputToBeParsed.substr (0, end);
			minuteBeg = inputToBeParsed.substr (end + 1, 2);
			minuteBegInt = atoi (minuteBeg.c_str());
			if (inputToBeParsed[end + 3] == 'a') {
				if (hourBeg == "12") {
					hourBegInt = 0;
				}
				else {
					hourBegInt = atoi (hourBeg.c_str());
				}
			}
			else if (inputToBeParsed[end + 3] == 'p') {
				if (hourBeg == "12") {
					hourBegInt = atoi (hourBeg.c_str());
				}
				else {
					hourBegInt = atoi (hourBeg.c_str()) +12;
				}
			}
		}
		//case "9am"/"19am"
		else {
			end = inputToBeParsed.find_first_of ('a');
			if (end == 1 || end == 2) {
				hourBeg = inputToBeParsed.substr (0, end);
				if (hourBeg == "12") {
					hourBegInt = 0;
				}
				else {
					hourBegInt = atoi (hourBeg.c_str());
				}
				minuteBegInt = 0;
			}

			end = inputToBeParsed.find_first_of ('p');
			if (end == 1 || end == 2) {
				hourBeg = inputToBeParsed.substr (0, end);
				if (hourBeg == "12") {
					hourBegInt = atoi (hourBeg.c_str());
				}
				else {
					hourBegInt = atoi (hourBeg.c_str()) +12;
				}
				minuteBegInt = 0;
			}
		}
		timeMicroBeg.updateHour (hourBegInt);
		timeMicroBeg.updateMin (minuteBegInt);

		if (!isTimePeriodTwelve (inputToBeParsed)) {
			end = inputToBeParsed.find_first_of (' ');
			if (end == string::npos) {
				inputToBeParsed = "";
			}
			else {
				inputToBeParsed = inputToBeParsed.substr (end + 1);
			}
		}

		else {
			end = inputToBeParsed.find_first_of ('-');
			inputToBeParsed = inputToBeParsed.substr (end + 1);

			end = inputToBeParsed.find_first_of (".");
			//case "9.00am"/"19.00am"
			if (end == 1 || end ==2) {
				hourEnd = inputToBeParsed.substr (0, end);
				minuteEnd = inputToBeParsed.substr (end + 1, 2);
				minuteEndInt = atoi (minuteEnd.c_str());
				if (inputToBeParsed[end + 3] == 'a') {
					if (hourEnd == "12") {
						hourEndInt = 0;
					}
					else {
						hourEndInt = atoi (hourEnd.c_str());
					}
				}
				else if (inputToBeParsed[end + 3] == 'p') {
					if (hourEnd == "12") {
						hourEndInt = atoi (hourEnd.c_str());
					}
					else {
						hourEndInt = atoi (hourEnd.c_str()) +12;
					}
				}
			}
			//case "9am"/"19am"
			else {
				end = inputToBeParsed.find_first_of ('a');
				if (end == 1 || end == 2) {
					hourEnd = inputToBeParsed.substr (0, end);
					if (hourEnd == "12") {
						hourEndInt = 0;
					}
					else {
						hourEndInt = atoi (hourEnd.c_str());
					}
					minuteEndInt = 0;
				}

				end = inputToBeParsed.find_first_of ('p');
				if (end == 1 || end == 2) {
					hourEnd = inputToBeParsed.substr (0, end);
					if (hourEnd == "12") {
						hourEndInt = atoi (hourEnd.c_str());
					}
					else {
						hourEndInt = atoi (hourEnd.c_str()) +12;
					}
					minuteEndInt = 0;
				}
			}
			timeMicroEnd.updateHour (hourEndInt);
			timeMicroEnd.updateMin (minuteEndInt);

			end = inputToBeParsed.find_first_of (' ');
			if (end == string::npos) {
				inputToBeParsed = "";
			}
			else {
				inputToBeParsed = inputToBeParsed.substr (end + 1);
			}
		}
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
bool Parser::isDateNumber (string inputToBeParsed) {
	if (inputToBeParsed.size() >= LENGTH_OF_DATE_FULL_NUMBER) {
		if (searchSubstring (DATE_FIRST_DIGIT, inputToBeParsed[0]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
			inputToBeParsed[2] == '/' &&
			searchSubstring (MONTH_FIRST_DIGIT, inputToBeParsed[3]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[4])) {
				if ((inputToBeParsed[0] == '3' &&
					inputToBeParsed[1] > '1') ||  //date > 31
					(inputToBeParsed[0] == '0' &&
					inputToBeParsed[1] == '0') || //date = 00
					(inputToBeParsed[3] == '0' &&
					inputToBeParsed[4] == '0') || //month = 00
					(inputToBeParsed[3] == '1' &&
					inputToBeParsed[4] > '2')) { //month > 12
						throw ERROR_MESSAGE_DATE;
				}
				else {
					return true;
				}
		}
	}

	if (inputToBeParsed.size() >= LENGTH_OF_DATE_ABBRE_NUMBER) {
		if (searchSubstring (POSITIVE_DIGIT, inputToBeParsed[0]) &&
			inputToBeParsed[1] == '/' &&
			searchSubstring (POSITIVE_DIGIT, inputToBeParsed[2])) {
				return true;
		}
		else if (searchSubstring (DATE_FIRST_DIGIT, inputToBeParsed[0]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
			inputToBeParsed[2] == '/' &&
			searchSubstring (POSITIVE_DIGIT, inputToBeParsed[3])) {
				if ((inputToBeParsed[0] == '0' &&
					inputToBeParsed[1] == '0') ||
					(inputToBeParsed[0] == '3' &&
					inputToBeParsed[1] > '1')) {
						throw ERROR_MESSAGE_DATE;
				}
				else {
					return true;
				}
		}
		else if (searchSubstring (POSITIVE_DIGIT, inputToBeParsed[0]) &&
			inputToBeParsed[1] == '/' &&
			searchSubstring (MONTH_FIRST_DIGIT, inputToBeParsed[2]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[3])) {
				if ((inputToBeParsed[2] == '0' &&
					inputToBeParsed[3] == '0') ||
					(inputToBeParsed[2] == '1' &&
					inputToBeParsed[3] > '2')) {
						throw ERROR_MESSAGE_DATE;
				}
				else {
					return true;
				}
		}
	}

	return false;
}


//This method checks if the date format includes a year.
//If the date and month are followed by "/yyyy",
//it returns true;
//else, it returns false
bool Parser::isYearNumber (string inputToBeParsed) {
	int end;
	end = inputToBeParsed.find_first_of ("/");
	if (end == 1 || end == 2) {
		inputToBeParsed = inputToBeParsed.substr (end + 1);
		if (inputToBeParsed[0] == '/' &&
			searchSubstring (YEAR_FIRST_DIGIT, inputToBeParsed[1]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[2]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[3]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[4])) {
				return true;
		}
	}

	return false;
}


//This method is to check if the start of the string is a date.
//This method only checks for date and month.
//The formats of date and month is date (integer) 
//followed by month (abbreviation, the first alphabet can be both capital or small)
//eg. 21 Mar or 21 mar.
//The string firstly needs to be longer than the date format.
bool Parser::isDateAlphabet (string inputToBeParsed) {
	vector<string> month;
	month.push_back ("Jan");
	month.push_back ("Feb");
	month.push_back ("Mar");
	month.push_back ("Apr");
	month.push_back ("May");
	month.push_back ("Jun");
	month.push_back ("Jul");
	month.push_back ("Aug");
	month.push_back ("Sep");
	month.push_back ("Oct");
	month.push_back ("Nov");
	month.push_back ("Dec");
	month.push_back ("jan");
	month.push_back ("feb");
	month.push_back ("mar");
	month.push_back ("apr");
	month.push_back ("may");
	month.push_back ("jun");
	month.push_back ("jul");
	month.push_back ("aug");
	month.push_back ("sep");
	month.push_back ("oct");
	month.push_back ("nov");
	month.push_back ("dec");

	if (inputToBeParsed.size() >= LENGTH_OF_DATE_FULL_ALPHABET) {
		if (searchSubstring (DATE_FIRST_DIGIT, inputToBeParsed[0]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
			inputToBeParsed[2] == ' ' &&
			isStringEqual (inputToBeParsed.substr (3, 3), month)) {
				if ((inputToBeParsed[0] == '0' &&
					inputToBeParsed[1] == '0') ||
					(inputToBeParsed[0] == '3' &&
					inputToBeParsed[1] > '1')) {
						throw ERROR_MESSAGE_DATE;
				}
				else {
					return true;
				}
		}
	}

	if (inputToBeParsed.size() >= LENGTH_OF_DATE_ABBRE_ALPHABET) {
		if (searchSubstring (POSITIVE_DIGIT, inputToBeParsed[0]) &&
			inputToBeParsed[1] == ' ' &&
			isStringEqual (inputToBeParsed.substr(2, 3), month)) {
				return true;
		}
	}

	return false;
}


//This method checks if the date format includes a year.
//If the date and month are followed by " yyyy",
//it returns true;
//else, it returns false
bool Parser::isYearAlphabet (string inputToBeParsed) {
		if (inputToBeParsed[0] == ' ' &&
			searchSubstring (YEAR_FIRST_DIGIT, inputToBeParsed[1]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[2]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[3]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[4])) {
				return true;
		}
	
	return false;
}


//This method is to check if the start of the string is a starting time
//(which may be followed by an ending time).
//The string firstly needs to be longer than the time format.
//Then it must follow the format "hh:mm"
//in order to be recognised as a starting time.
bool Parser::isStartingTimeTwentyFour (string inputToBeParsed) {
	if (inputToBeParsed.size() >= LENGTH_OF_STARTING_TIME) {
		if (searchSubstring (TWENTY_FOUR_HOUR_FIRST_DIGIT, inputToBeParsed[0]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
			inputToBeParsed[2] == ':' &&
			searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[3]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[4])) {
				if (inputToBeParsed[0] == '2' &&
					inputToBeParsed[1] > '3') {
						throw ERROR_MESSAGE_TIME;
				}
				else {
					return true;
				}
		}
		else if (searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[0]) &&
			inputToBeParsed[1] == ':' &&
			searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[2]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[3])) {
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
bool Parser::isTimePeriodTwentyFour (string inputToBeParsed) {
	int end = 0;
	if (inputToBeParsed.size() >= LENGTH_OF_TIME_PERIOD) {
		if (isStartingTimeTwentyFour (inputToBeParsed)) {
			end = inputToBeParsed.find_first_of ('-');
			if (end != string::npos) {
				inputToBeParsed = inputToBeParsed.substr (end + 1);
				if (searchSubstring (TWENTY_FOUR_HOUR_FIRST_DIGIT, inputToBeParsed[0]) &&
					searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
					inputToBeParsed[2] == ':' &&
					searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[3]) &&
					searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[4])) {
						if (inputToBeParsed[0] == '2' &&
							inputToBeParsed[1] > '3') {
								throw ERROR_MESSAGE_TIME;
						}
						else {
							return true;
						}

				}
				else if (searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[0]) &&
					inputToBeParsed[1] == ':' &&
					searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[2]) &&
					searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[3])) {
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
bool Parser::isStartingTimeTwelve (string inputToBeParsed) {
	int end = 0;
	if (inputToBeParsed.size () >= 3) {  //"9am"
		end = inputToBeParsed.find_first_of (".");	
			
		if (end == 1) { //case "9.00am"
			if (searchSubstring (POSITIVE_DIGIT, inputToBeParsed[0]) &&
				searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[2]) &&
				searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[3]) &&
				(inputToBeParsed[4] == 'a' ||
				inputToBeParsed[4] == 'p') &&
				inputToBeParsed[5] == 'm') {
					return true;
			}
		}
		else if (end == 2) {
			//case "09.00am"
			if (searchSubstring (TWELVE_HOUR_FIRST_DIGIT, inputToBeParsed[0]) &&
				searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
				searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[3]) &&
				searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[4]) &&
				(inputToBeParsed[5] == 'a' ||
				inputToBeParsed[5] == 'p') &&
				inputToBeParsed[6] == 'm') {
					if ((inputToBeParsed[0] == '0' &&
						inputToBeParsed[1] == '0') ||
						(inputToBeParsed[0] == '1' &&
						inputToBeParsed[1] > '2')) {
							throw ERROR_MESSAGE_TIME;
					}
					else {
						return true;
					}
			}
		}
		//case "9am"
		else if (searchSubstring (POSITIVE_DIGIT, inputToBeParsed[0]) &&  
			(inputToBeParsed[1] == 'a' ||
			inputToBeParsed[1] == 'p') &&
			inputToBeParsed[2] == 'm') {
				return true;
		}
		//case "19am"
		else if (searchSubstring (TWELVE_HOUR_FIRST_DIGIT, inputToBeParsed[0]) &&
			searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
			(inputToBeParsed[2] == 'a' ||
			inputToBeParsed[2] == 'p') &&
			inputToBeParsed[3] == 'm') {
				if ((inputToBeParsed[0] == '0' &&
					inputToBeParsed[1] == '0') ||
					(inputToBeParsed[0] == '1' &&
					inputToBeParsed[1] > '2')) {
						throw ERROR_MESSAGE_TIME;
				}
				else {
					return true;
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
bool Parser::isTimePeriodTwelve (string inputToBeParsed) {
	int end = 0;
	if (isStartingTimeTwelve (inputToBeParsed) &&
		inputToBeParsed.size () >= 7) {  //"9am-9pm"
			end = inputToBeParsed.find_first_of ("-");
			if (end == string::npos) {
				return false;
			}
			else {
				inputToBeParsed = inputToBeParsed.substr (end + 1);
			}

			end = inputToBeParsed.find_first_of (".");
			if (end != string::npos) {
				//case "9.00am"
				if (end == 1) {
					if (searchSubstring (POSITIVE_DIGIT, inputToBeParsed[0]) &&
						searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[2]) &&
						searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[3]) &&
						(inputToBeParsed[4] == 'a' ||
						inputToBeParsed[4] == 'p') &&
						inputToBeParsed[5] == 'm') {
							return true;
					}
				}
				else if (end == 2) {
					//case "09.00am"
					if (searchSubstring (TWELVE_HOUR_FIRST_DIGIT, inputToBeParsed[0]) &&
						searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
						searchSubstring (MINUTE_FIRST_DIGIT, inputToBeParsed[3]) &&
						searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[4]) &&
						(inputToBeParsed[5] == 'a' ||
						inputToBeParsed[5] == 'p') &&
						inputToBeParsed[6] == 'm') {
							if ((inputToBeParsed[0] == '0' &&
								inputToBeParsed[1] == '0') ||
								(inputToBeParsed[0] == '1' &&
								inputToBeParsed[1] > '2')) {
									throw ERROR_MESSAGE_TIME;
							}
							else {
								return true;
							}
					}
				}
			}
			else {
				//case "9am"
				if (searchSubstring (POSITIVE_DIGIT, inputToBeParsed[0]) &&
					(inputToBeParsed[1] == 'a' ||
					inputToBeParsed[1] == 'p') &&
					inputToBeParsed[2] == 'm') {
						return true;
				}
				//case "19am"
				else if (searchSubstring (TWELVE_HOUR_FIRST_DIGIT, inputToBeParsed[0]) &&
					searchSubstring (NON_NEGATIVE_DIGIT, inputToBeParsed[1]) &&
					(inputToBeParsed[2] == 'a' ||
					inputToBeParsed[2] == 'p') &&
					inputToBeParsed[3] == 'm') {
						if ((inputToBeParsed[0] == '0' &&
							inputToBeParsed[1] == '0') ||
							(inputToBeParsed[0] == '1' &&
							inputToBeParsed[1] > '2')) {
								throw ERROR_MESSAGE_TIME;
						}
						else {
							return true;
						}
				}
			}
	}
	return false;
}

//This method is to check if a specific character is in a string.
bool Parser::searchSubstring (const string timeString, char substring) {
	unsigned int index = 0;
	for (index = 0; index < timeString.size(); index ++) {
		if (substring == timeString[index]) {
			return true;
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