#include "Parser.h"

const unsigned int Parser::LENGTH_OF_DATE_FULL_NUMBER = 5;  //"dd/mm"
const unsigned int Parser::LENGTH_OF_DATE_ABBRE_NUMBER = 3;  //"d/m"
const unsigned int Parser::LENGTH_OF_DATE_FULL_ALPHABET = 6;  //"dd MMM"
const unsigned int Parser::LENGTH_OF_DATE_ABBRE_ALPHABET = 5;  //"d MMM"
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
const string Parser::ERROR_MESSAGE_COMMAND = "Please enter the correct command";


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
		cout << getErrorMessage () << endl;
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
	else if (commandWord == "show") {
		try {
			parseShow (userInput, commandWord);
		}
		catch (char* errorMessge) {
			updateErrorMessage (errorMessge);
			cout << getErrorMessage () << endl;
		}
	}
	else {
		throw "Please enter the correct command";
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
	inputToBeParsed = inputToBeParsed.substr (commandWord.size() + 1);

	parseDateNumber (inputToBeParsed, timeMacro);
    parseDateAlphabet (inputToBeParsed, timeMacro);

	parseTimeTwentyFour (inputToBeParsed, timeMicroBeg, timeMicroEnd);
	parseTimeTwelve (inputToBeParsed, timeMicroBeg, timeMicroEnd);

	parseDateNumber (inputToBeParsed, timeMacro);
    parseDateAlphabet (inputToBeParsed, timeMacro);
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
//date, time and description can also stand alone
//The task no must be followed by something to edit
void Parser::parseEdit (string userInput, string commandWord) {
	TimeMacro timeMacro;
	TimeMicro timeMicroBeg;
	TimeMicro timeMicroEnd;
	string desc;
	int taskNo;
	string inputToBeParsed = userInput.substr (commandWord.size() + 1);
	string index = parseTaskNo (inputToBeParsed);

	try {
		taskNo = convertStringToInteger (index);
		inputToBeParsed = inputToBeParsed.substr(index.size () + 1);


		parseDateNumber (inputToBeParsed, timeMacro);
		parseDateAlphabet (inputToBeParsed, timeMacro);

		parseTimeTwentyFour (inputToBeParsed, timeMicroBeg, timeMicroEnd);

		parseDateNumber (inputToBeParsed, timeMacro);
		parseDateAlphabet (inputToBeParsed, timeMacro);

		if (inputToBeParsed != "") {
			desc = inputToBeParsed;
		}
		

		updateCommand (commandWord);
		updateTaskNo (taskNo);
		updateTimeMacro (timeMacro);
		updateTimeMicroPeriod (timeMicroBeg, timeMicroEnd);
		updateDesc (desc);
	}

	catch (const char* errorMessge) {
		updateErrorMessage (errorMessge);
		cout << getErrorMessage () << endl;
	}
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
	string inputToBeParserd = userInput.substr (commandWord.size() + 1);
	string index = parseTaskNo (inputToBeParserd);

	try {
		int taskNo = convertStringToInteger (index);
		updateCommand (commandWord);
		updateTaskNo (taskNo);
	}
	
	catch (const char* errorMessge) {
		updateErrorMessage (errorMessge);
		cout << getErrorMessage () << endl;
	}

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


//This method checks whether the word "commands" follows a "show" command.
//If yes, the command work will become "show commands"
//and the private attribute will be updated.
//If not, it throws an exception.
void Parser::parseShow (string userInput, string commandWord) {
	string inputToBeParsed = userInput.substr (commandWord.size () + 1);
	if (inputToBeParsed != "commands") {
		throw "Did you mean \"show commands?\"";
	}

	commandWord = commandWord + " " + userInput;
	updateCommand (commandWord);
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
	if (isTimePeriodTwentyFour (inputToBeParsed) || isStartingTimeTwentyFour (inputToBeParsed)) {
        string hourBeg = inputToBeParsed.substr (0, 2);
		string minuteBeg = inputToBeParsed.substr (3, 2);
		int hourBegInt = atoi (hourBeg.c_str());
		int minuteBegInt = atoi (minuteBeg.c_str());
		timeMicroBeg.updateHour (hourBegInt);
		timeMicroBeg.updateMin (minuteBegInt);


		if (!isTimePeriodTwentyFour (inputToBeParsed)) {
			if (inputToBeParsed.size() > 6) {
				inputToBeParsed = inputToBeParsed.substr (6);
			}
			else {
				inputToBeParsed = "";
			}
		}
		else {
			string hourEnd = inputToBeParsed.substr (6, 2);
			string minuteEnd = inputToBeParsed.substr (9, 2);
			int hourEndInt = atoi (hourEnd.c_str());
			int minuteEndInt = atoi (minuteEnd.c_str());
			timeMicroEnd.updateHour (hourEndInt);
			timeMicroEnd.updateMin (minuteEndInt);

			if (inputToBeParsed.size() > 12) {
				inputToBeParsed = inputToBeParsed.substr (12);
			}
			else {
				inputToBeParsed = "";
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
				hourBegInt = atoi (hourBeg.c_str());
			}
			else if (inputToBeParsed[end + 3] == 'p') {
				hourBegInt = atoi (hourBeg.c_str()) +12;
			}
		}
		//case "9am"/"19am"
		else {
			end = inputToBeParsed.find_first_of ('a');
			if (end == 1 || end == 2) {
				hourBeg = inputToBeParsed.substr (0, end);
				hourBegInt = atoi (hourBeg.c_str());
				minuteBegInt = 0;
			}

			end = inputToBeParsed.find_first_of ('p');
			if (end == 1 || end == 2) {
				hourBeg = inputToBeParsed.substr (0, end);
				hourBegInt = atoi (hourBeg.c_str()) + 12;
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
					hourEndInt = atoi (hourEnd.c_str());
				}
				else if (inputToBeParsed[end + 3] == 'p') {
					hourEndInt = atoi (hourEnd.c_str()) +12;
				}
			}
			//case "9am"/"19am"
			else {
				end = inputToBeParsed.find_first_of ('a');
				if (end == 1 || end == 2) {
					hourEnd = inputToBeParsed.substr (0, end);
					hourEndInt = atoi (hourEnd.c_str());
					minuteEndInt = 0;
				}

				end = inputToBeParsed.find_first_of ('p');
				if (end == 1 || end == 2) {
					hourEnd = inputToBeParsed.substr (0, end);
					hourEndInt = atoi (hourEnd.c_str()) + 12;
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
		throw "Please enter correct task number after command word";
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
		if (searchSubstring ("0123", inputToBeParsed[0]) &&
			searchSubstring ("0123456789", inputToBeParsed[1]) &&
			inputToBeParsed[2] == '/' &&
			searchSubstring ("01", inputToBeParsed[3]) &&
			searchSubstring ("0123456789", inputToBeParsed[4])) {
				return true;
		}
	}

	if (inputToBeParsed.size() >= LENGTH_OF_DATE_ABBRE_NUMBER) {
		if (searchSubstring ("123456789", inputToBeParsed[0]) &&
			inputToBeParsed[1] == '/' &&
			searchSubstring ("123456789", inputToBeParsed[2])) {
				return true;
		}
		else if (searchSubstring ("0123", inputToBeParsed[0]) &&
			searchSubstring ("0123456789", inputToBeParsed[1]) &&
			inputToBeParsed[2] == '/' &&
			searchSubstring ("123456789", inputToBeParsed[3])) {
				return true;
		}
		else if (searchSubstring ("123456789", inputToBeParsed[0]) &&
			inputToBeParsed[1] == '/' &&
			searchSubstring ("01", inputToBeParsed[2]) &&
			searchSubstring ("0123456789", inputToBeParsed[3])) {
				return true;
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
			searchSubstring ("2", inputToBeParsed[1]) &&
			searchSubstring ("0123456789", inputToBeParsed[2]) &&
			searchSubstring ("0123456789", inputToBeParsed[3]) &&
			searchSubstring ("0123456789", inputToBeParsed[4])) {
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
		if (searchSubstring ("0123", inputToBeParsed[0]) &&
			searchSubstring ("0123456789", inputToBeParsed[1]) &&
			inputToBeParsed[2] == ' ' &&
			isStringEqual (inputToBeParsed.substr (3, 3), month)) {
				return true;
		}
	}

	if (inputToBeParsed.size() >= LENGTH_OF_DATE_ABBRE_ALPHABET) {
		if (searchSubstring ("123456789", inputToBeParsed[0]) &&
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
			searchSubstring ("2", inputToBeParsed[1]) &&
			searchSubstring ("0123456789", inputToBeParsed[2]) &&
			searchSubstring ("0123456789", inputToBeParsed[3]) &&
			searchSubstring ("0123456789", inputToBeParsed[4])) {
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
bool Parser::isTimePeriodTwentyFour (string inputToBeParsed) {
	if (inputToBeParsed.size() >= LENGTH_OF_TIME_PERIOD) {
		if (isStartingTimeTwentyFour (inputToBeParsed) &&
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
		if (end != string::npos) {
			//case "9.00am"
			if (end == 1) {
				if (searchSubstring ("123456789", inputToBeParsed[0]) &&
					searchSubstring ("012345", inputToBeParsed[2]) &&
					searchSubstring ("0123456789", inputToBeParsed[3]) &&
					(inputToBeParsed[4] == 'a' ||
					inputToBeParsed[4] == 'p') &&
					inputToBeParsed[5] == 'm') {
						return true;
				}
			}
			else if (end == 2) {
				//case "09.00am"
				if (searchSubstring ("01", inputToBeParsed[0]) &&
					searchSubstring ("0123456789", inputToBeParsed[1]) &&
					searchSubstring ("012345", inputToBeParsed[3]) &&
					searchSubstring ("0123456789", inputToBeParsed[4]) &&
					(inputToBeParsed[5] == 'a' ||
					inputToBeParsed[5] == 'p') &&
					inputToBeParsed[6] == 'm') {
						return true;
				}
			}
		}
		else {
			//case "9am"
			if (searchSubstring ("123456789", inputToBeParsed[0]) &&
				(inputToBeParsed[1] == 'a' ||
				inputToBeParsed[1] == 'p') &&
				inputToBeParsed[2] == 'm') {
					return true;
			}
			//case "19am"
			else if (searchSubstring ("01", inputToBeParsed[0]) &&
				searchSubstring ("0123456789", inputToBeParsed[1]) &&
				(inputToBeParsed[2] == 'a' ||
				inputToBeParsed[2] == 'p') &&
				inputToBeParsed[3] == 'm') {
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
					if (searchSubstring ("123456789", inputToBeParsed[0]) &&
						searchSubstring ("012345", inputToBeParsed[2]) &&
						searchSubstring ("0123456789", inputToBeParsed[3]) &&
						(inputToBeParsed[4] == 'a' ||
						inputToBeParsed[4] == 'p') &&
						inputToBeParsed[5] == 'm') {
							return true;
					}
				}
				else if (end == 2) {
					//case "09.00am"
					if (searchSubstring ("01", inputToBeParsed[0]) &&
						searchSubstring ("0123456789", inputToBeParsed[1]) &&
						searchSubstring ("012345", inputToBeParsed[3]) &&
						searchSubstring ("0123456789", inputToBeParsed[4]) &&
						(inputToBeParsed[5] == 'a' ||
						inputToBeParsed[5] == 'p') &&
						inputToBeParsed[6] == 'm') {
							return true;
					}
				}
			}
			else {
				//case "9am"
				if (searchSubstring ("123456789", inputToBeParsed[0]) &&
					(inputToBeParsed[1] == 'a' ||
					inputToBeParsed[1] == 'p') &&
					inputToBeParsed[2] == 'm') {
						return true;
				}
				//case "19am"
				else if (searchSubstring ("01", inputToBeParsed[0]) &&
					searchSubstring ("0123456789", inputToBeParsed[1]) &&
					(inputToBeParsed[2] == 'a' ||
					inputToBeParsed[2] == 'p') &&
					inputToBeParsed[3] == 'm') {
						return true;
				}
			}
	}
	return false;
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