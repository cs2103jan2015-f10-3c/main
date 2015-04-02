#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testParser
{		
	TEST_CLASS(testParser)
	{
	public:
		
		//To test whether can extract "add" command
		TEST_METHOD(testExtractCommand)
		{
			Parser parser;
			string testString = "add 08/03/2015 go for tutorial";
			string expected = "add";
			Assert::AreEqual (parser.extractCommandWord (testString), expected);
		}

		//To test for invalid command
		TEST_METHOD(testInvalidCommand)
		{
			Parser parser;
			string testString = "abc";
			string expected = "Please enter the correct command";
			parser.parseInput (testString);
			Assert::AreEqual (parser.getErrorMessage(), expected);
		}

		//To test for a leap year
		TEST_METHOD(testLeapYear1)
		{
			Parser parser;
			int year = 2004;
			Assert::IsTrue (parser.isLeapYear (year));
		}

		//To test for a non-leap year
		TEST_METHOD(testLeapYear2)
		{
			Parser parser;
			int year = 2015;
			Assert::IsFalse (parser.isLeapYear (year));
		}

		//To test for a leap year which can be divided by 400
		TEST_METHOD(testLeapYear3)
		{
			Parser parser;
			int year = 2000;
			Assert::IsTrue (parser.isLeapYear (year));
		}

		//To test whether can update and get today's date correctly
		TEST_METHOD(testTodayDate)
		{
			Parser parser;
			TimeMacro timeMacro;
			string dayOfTheWeek = "Thursday";
			parser.getTodayDate (timeMacro);
			Assert::AreEqual (timeMacro.getDate(), 2);
			Assert::AreEqual (timeMacro.getMonth(), 4);
			Assert::AreEqual (timeMacro.getYear(), 2015);
			Assert::AreEqual (timeMacro.getDay(), dayOfTheWeek);
		}

		//To test whether a date can be converted to day of the week correctly
		TEST_METHOD(testConvertDateToDay1)
		{
			Parser parser;
			TimeMacro timeMacro;
			string dayOfTheWeek = "Thursday";
			Assert::AreEqual (parser.convertDateToDayOfTheWeek (12, 3, 2015), dayOfTheWeek);
		}

		//To test if a character can be found in a given string
		//In this case, the character is present in the string
		//This is a boundary case for the first character
		TEST_METHOD(testSearchSubstring1)
		{
			Parser parser;
			Assert::IsTrue (parser.searchSubstring ("abcdefg", 'a'));
		}

		//To test if a character can be found in a given string
		//In this case, the character is absent from the string
		TEST_METHOD(testSearchSubstring2)
		{
			Parser parser;
			Assert::IsFalse (parser.searchSubstring ("abcdefg", 'm'));
		}

		//To test if a character can be found in a given string
		//In this case, the character is present in the string
		//This is a boundary case for the last character
		TEST_METHOD(testSearchSubstring3)
		{
			Parser parser;
			Assert::IsTrue (parser.searchSubstring ("abcdefg", 'g'));
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "hh:mm-hh:mm"
		//"00:00-23:59" is also the boundary case
		TEST_METHOD(testIsTimePeriodTwentyFour1)
		{
			Parser parser;
			string testString = "00:00-23:59";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "h:mm-hh:mm"
		//"0:00-23:59" is also the boundary case
		TEST_METHOD(testIsTimePeriodTwentyFour2)
		{
			Parser parser;
			string testString = "0:00-23:59";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "hh:mm-h:mm"
		TEST_METHOD(testIsTimePeriodTwentyFour3)
		{
			Parser parser;
			string testString = "00:00-9:30";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "h:mm-h:mm"
		TEST_METHOD(testIsTimePeriodTwentyFour4)
		{
			Parser parser;
			string testString = "0:00-9:30";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a time period
		//In this case, the string is not a time period but a starting time
		TEST_METHOD(testIsTimePeriodTwentyFour5)
		{
			Parser parser;
			string testString = "09:00";
			Assert::IsFalse (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a starting time
		//The format is hh:mm
		//The boundary case is 00:00
		TEST_METHOD(testIsStartingTimeTwentyFour1)
		{
			Parser parser;
			string testString = "00:00";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString));
		}

		//To test whether a string is a starting time
		//The format is hh:mm
		//The boundary case is 23:59
		TEST_METHOD(testIsStartingTimeTwentyFour2)
		{
			Parser parser;
			string testString = "23:59";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString));
		}

		//To test whether a string is a starting time
		//The format is h:mm
		//The boundary case is 0:00
		TEST_METHOD(testIsStartingTimeTwentyFour3)
		{
			Parser parser;
			string testString = "0:00";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString));
		}

		//To test whether a string is a starting time
		//The format is h:mm
		//The boundary case is 9:59
		TEST_METHOD(testIsStartingTimeTwentyFour4)
		{
			Parser parser;
			string testString = "9:59";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString));
		}

		//To test whether a string is a starting time
		//In this case, the string is not a starting time but a date
		TEST_METHOD(testIsStartingTimeTwentyFour5)
		{
			Parser parser;
			string testString = "12/03/2015 dinner tonight";
			Assert::IsFalse (parser.isStartingTimeTwentyFour (testString));
		}

		//To test whether a string is a date
		//The format is dd/mm/yyyy
		//The boundary case is 01/01/2000
		TEST_METHOD(testIsDateNumber1)
		{
			Parser parser;
			string testString = "01/01/2000";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//The format is dd/mm/yyyy
		//The boundary case is 31/12/2999
		TEST_METHOD(testIsDateNumber2)
		{
			Parser parser;
			string testString = "31/12/2000";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//The format is d/mm/yyyy
		//The boundary case is 1/01/2000
		TEST_METHOD(testIsDateNumber3)
		{
			Parser parser;
			string testString = "1/01/2000";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//The format is d/mm/yyyy
		//The boundary case is 9/12/2999
		TEST_METHOD(testIsDateNumber4)
		{
			Parser parser;
			string testString = "9/12/2999";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//The format is dd/m/yyyy
		//The boundary case is 01/1/2000
		TEST_METHOD(testIsDateNumber5)
		{
			Parser parser;
			string testString = "01/1/2000";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//The format is dd/m/yyyy
		//The boundary case is 30/9/2999
		TEST_METHOD(testIsDateNumber6)
		{
			Parser parser;
			string testString = "30/9/2999";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//The format is d/m/yyyy
		//The boundary case is 1/1/2000
		TEST_METHOD(testIsDateNumber7)
		{
			Parser parser;
			string testString = "1/1/2000";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//The format is d/m/yyyy
		//The boundary case is 9/9/2999
		TEST_METHOD(testIsDateNumber8)
		{
			Parser parser;
			string testString = "9/9/2999";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//In this case, the string is not a date but a task description
		TEST_METHOD(testIsDateNumber9)
		{
			Parser parser;
			string testString = "dinner tonight";
			Assert::IsFalse (parser.isDateNumber (testString));
		}

		//To test whether can parse a task number
		TEST_METHOD(testParseTaskNo)
		{
			Parser parser;
			string testString = "3";
			string expected = "3";
			Assert::AreEqual (parser.parseTaskNo (testString), expected);
		}

		//To test whether can parse a time period
		TEST_METHOD(testparseTimeTwentyFour1)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "00:00-23:59";
			parser.parseTimeTwentyFour (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 0);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), 23);
			Assert::AreEqual (timeMicroEnd.getMin(), 59);
		}

		//To test whether can parse a starting time
		TEST_METHOD(testparseTimeTwentyFour2)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "00:00 breakfast";
			parser.parseTimeTwentyFour (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 19);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), -1);
			Assert::AreEqual (timeMicroEnd.getMin(), -1);
		}

		//To test whether can update and get the "undo" command
		TEST_METHOD(testParseUndo)
		{
			Parser parser;
			string input = "undo";
			string commandWord = "undo";
			parser.parseUndo (input);
			Assert::AreEqual (parser.getCommand (), commandWord);
		}

		//To test whether can parse for the "delete" feature
		//The boundary case is 1
		TEST_METHOD(testParseDelete1)
		{
			Parser parser;
			string input = "delete 1";
			string commandWord = "delete";
			parser.parseDelete (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 3);
		}

		//To test whether can update and get
		//date, month, year, day
		TEST_METHOD(testparseDateNumber)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "01/01/2000";
			string expectedDay = "Saturday";
			parser.parseDateNumber (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 1);
			Assert::AreEqual (timeMacro.getMonth (), 1);
			Assert::AreEqual (timeMacro.getYear (), 2000);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

		//To test whether can ignore it when parsing date
		//when the input string is a time period
		TEST_METHOD(testparseDateNumber2)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "09:00-10:00";
			string expectedDay = "undefined";
			parser.parseDateNumber (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 0);
			Assert::AreEqual (timeMacro.getMonth (), 0);
			Assert::AreEqual (timeMacro.getYear (), 0);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

		//To test whether can update and get tomorrow's date correctly
		TEST_METHOD(testTomorrowDate)
		{
			Parser parser;
			TimeMacro timeMacro;
			string dayOfTheWeek = "Friday";
			parser.getTomorrowDate (timeMacro);
			Assert::AreEqual (timeMacro.getDate(), 3);
			Assert::AreEqual (timeMacro.getMonth(), 4);
			Assert::AreEqual (timeMacro.getYear(), 2015);
			Assert::AreEqual (timeMacro.getDay(), dayOfTheWeek);
		}

		//To test whether can update and get this month's date range correctly
		TEST_METHOD(testThisMonth)
		{
			Parser parser;
			TimeMacro timeMacroBeg;
			TimeMacro timeMacroEnd;
			parser.getThisMonth (timeMacroBeg, timeMacroEnd);
			Assert::AreEqual (timeMacroBeg.getDate(), 1);
			Assert::AreEqual (timeMacroBeg.getMonth(), 4);
			Assert::AreEqual (timeMacroBeg.getYear(), 2015);
			Assert::AreEqual (timeMacroEnd.getDate(), 30);
			Assert::AreEqual (timeMacroEnd.getMonth(), 4);
			Assert::AreEqual (timeMacroEnd.getYear(), 2015);
		}

		//To test whether can parse "show this month"
		TEST_METHOD(testparseShow1)
		{
			Parser parser;
			string userInput = "show this month";
			string commandWord = "show";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 1);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getDate (), 30);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getMonth (), 4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getYear (), 2015);
		}

		//To test whether can parse "show today"
		TEST_METHOD(testparseShow2)
		{
			Parser parser;
			string userInput = "show today";
			string commandWord = "show";
			string expectedDay = "Thursday";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 2);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
		}

		//To test whether can parse "show tomorrow"
		TEST_METHOD(testparseShow3)
		{
			Parser parser;
			string userInput = "show tomorrow";
			string commandWord = "show";
			string expectedDay = "Friday";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (),4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
		}

		//To test whether can parse a string to search for a single keyword
		TEST_METHOD(testParseSearch1)
		{
			Parser parser;
			string userInput = "search breakfast";
			string commandWord = "search";
			string expectedDesc = "breakfast";
			parser.parseSearch (userInput, commandWord);
			
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual ((parser.getData ()).getDesc (), expectedDesc);
		}

		//To test whether can parse a string to search for a string
		TEST_METHOD(testParseSearch2)
		{
			Parser parser;
			string userInput = "search breakfast at UT";
			string commandWord = "search";
			string expectedDesc = "breakfast at UT";
			parser.parseSearch (userInput, commandWord);
			
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual ((parser.getData ()).getDesc (), expectedDesc);
		}

		//To test whether can parse for "edit" feature
		//In this case, the task number has a single digit
		//and there is a starting time
		TEST_METHOD(testParseEdit1)
		{
			Parser parser;
			string userInput = "edit 4 13/03/2015 09:00 breakfast";
			string commandWord = "edit";
			string expectedDay = "Friday";
			string expecedDesc = "breakfast";
			parser.parseEdit (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 13);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getHour (), 9);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getMin (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getHour (), -1);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getMin (), -1);
			Assert::AreEqual ((parser.getData ()).getDesc (), expecedDesc);
		}

		//To test whether can parse for "add" feature
		//In this case,there is a starting time
		TEST_METHOD(testParseAdd1)
		{
			Parser parser;
			string userInput = "add 13/03/2015 19:00 dinner";
			string commandWord = "add";
			string expectedDay = "Friday";
			string expecedDesc = "dinner";
			parser.parseAdd (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 13);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getHour (), 19);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getMin (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getHour (), -1);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getMin (), -1);
			Assert::AreEqual ((parser.getData ()).getDesc (), expecedDesc);
		}


		//To test whether can parse for "add" feature
		//In this case,there is a time period
		TEST_METHOD(testParseAdd2)
		{
			Parser parser;
			string userInput = "add 13/03/2015 10:00-14:00 project work";
			string commandWord = "add";
			string expectedDay = "Friday";
			string expecedDesc = "project work";
			parser.parseAdd (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 13);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getHour (), 10);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getMin (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getHour (), 14);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getMin (), 0);
			Assert::AreEqual ((parser.getData ()).getDesc (), expecedDesc);
		}

		//To test whether can parse for "add" feature
		TEST_METHOD(testParseInput1)
		{
			Parser parser;
			string userInput = "add 13/03/2015 10:00-14:00 project work";
			string expectedDay = "Friday";
			string expecedDesc = "project work";
			string commandWord = "add";
			parser.parseInput (userInput);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 13);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getHour (), 10);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getMin (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getHour (), 14);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getMin (), 0);
			Assert::AreEqual ((parser.getData ()).getDesc (), expecedDesc);
		}

		//To test whether can parse for "edit" feature
		TEST_METHOD(testParseInput2)
		{
			Parser parser;
			string userInput = "edit 9 13/03/2015 10:00 project work";
			string expectedDay = "Friday";
			string expecedDesc = "project work";
			string commandWord = "edit";
			parser.parseInput (userInput);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 9);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 13);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getHour (), 10);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getMin (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getHour (), -1);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getMin (), -1);
			Assert::AreEqual ((parser.getData ()).getDesc (), expecedDesc);
		}

		//To test whether can parse for "delete" feature
		TEST_METHOD(testParseInput3)
		{
			Parser parser;
			string userInput = "delete 99";
			string expectedDay = "undefined";
			string expecedDesc = "";
			string commandWord = "delete";
			parser.parseInput (userInput);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 99);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getHour (), -1);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getMin (), -1);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getHour (), -1);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getMin (), -1);
			Assert::AreEqual ((parser.getData ()).getDesc (), expecedDesc);
		}

		//To test whether can parse for "mark it as done" feature
		//The boundary case is 1
		TEST_METHOD(testParseDone1)
		{
			Parser parser;
			string input = "done 1";
			string commandWord = "done";
			parser.parseDone (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 1);
			Assert::AreEqual ((parser.getData ()).getCompleteStatus (), true);
		}

	};
}