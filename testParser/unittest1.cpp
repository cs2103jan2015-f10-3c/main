#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testParser
{		
	TEST_CLASS(testParser)
	{
	public:
		
		//To test whether can extract "add" command
		TEST_METHOD(testExtractCommand1)
		{
			Parser parser;
			string testString = "add 08/03/2015 go for tutorial";
			string expected = "add";
			Assert::AreEqual (parser.extractCommandWord (testString), expected);
		}

		//To test whether can extract "undo" command
		TEST_METHOD(testExtractCommand2)
		{
			Parser parser;
			string testString = "undo";
			string expected = "undo";
			Assert::AreEqual (parser.extractCommandWord (testString), expected);
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
			string dayOfTheWeek = "Friday";
			parser.getTodayDate (timeMacro);
			Assert::AreEqual (timeMacro.getDate(), 13);
			Assert::AreEqual (timeMacro.getMonth(), 3);
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

		//To test whether a date can be converted to day of the week correctly
		TEST_METHOD(testConvertDateToDay2)
		{
			Parser parser;
			TimeMacro timeMacro;
			string dayOfTheWeek = "Wednesday";
			Assert::AreEqual (parser.convertDateToDayOfTheWeek (18, 3, 2015), dayOfTheWeek);
		}

		//To test if a character can be found in a given string
		//In this case, the character is present in the string
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

		//To test whether a string is a time period
		//In this case, the string is a time period
		TEST_METHOD(testisTimePeriodTwentyFour1)
		{
			Parser parser;
			string testString = "09:00-10:00";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a time period
		//In this case, the string is not a time period but a starting time
		TEST_METHOD(testisTimePeriodTwentyFour2)
		{
			Parser parser;
			string testString = "09:00";
			Assert::IsFalse (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a time period
		//In this case, the string is not a time period but a task description
		TEST_METHOD(testisTimePeriodTwentyFour3)
		{
			Parser parser;
			string testString = "dinner tonight";
			Assert::IsFalse (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a time period
		//In this case, the string is a time period followed by a task description
		TEST_METHOD(testisTimePeriodTwentyFour4)
		{
			Parser parser;
			string testString = "09:00-10:00 dinner tonight";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString));
		}

		//To test whether a string is a starting time
		//In this case, the string is a starting time which is also a time period
		TEST_METHOD(testisStartingTimeTwentyFour1)
		{
			Parser parser;
			string testString = "09:00-10:00 dinner tonight";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString));
		}

		//To test whether a string is a starting time
		//In this case, the string is a starting time followed by a task description
		TEST_METHOD(testisStartingTimeTwentyFour2)
		{
			Parser parser;
			string testString = "09:00 dinner tonight";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString));
		}

		//To test whether a string is a starting time
		//In this case, the string is not a starting time but a date
		TEST_METHOD(testisStartingTimeTwentyFour3)
		{
			Parser parser;
			string testString = "12/03/2015 dinner tonight";
			Assert::IsFalse (parser.isStartingTimeTwentyFour (testString));
		}

		//To test whether a string is a date
		//In this case, the string is a date followed by a task description
		TEST_METHOD(testisDateNumber1)
		{
			Parser parser;
			string testString = "12/03/2015 dinner tonight";
			Assert::IsTrue (parser.isDateNumber (testString));
		}

		//To test whether a string is a date
		//In this case, the string is not a date
		//because it does not follow the date format
		TEST_METHOD(testisDateNumber2)
		{
			Parser parser;
			string testString = "12/3/2015 dinner tonight";
			Assert::IsFalse (parser.isDateNumber (testString));
		}

		//To test whether a string is a task number
		//In this case, the string is a task number (one digit)
		//followed by a task description
		TEST_METHOD(testParseTaskNo1)
		{
			Parser parser;
			string testString = "3 dinner";
			string expected = "3";
			Assert::AreEqual (parser.parseTaskNo (testString), expected);
		}

		//To test whether a string is a task number
		//In this case, the string is a task number (two digits)
		//followed by a task description
		TEST_METHOD(testParseTaskNo2)
		{
			Parser parser;
			string testString = "45 dinner";
			string expected = "45";
			Assert::AreEqual (parser.parseTaskNo (testString), expected);
		}

		//To test whether can parse a time period
		TEST_METHOD(testparseTimeTwentyFour1)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "09:00-10:00";
			parser.parseTimeTwentyFour (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 9);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), 10);
			Assert::AreEqual (timeMicroEnd.getMin(), 0);
		}

		//To test whether can parse a time period followed by a task description
		TEST_METHOD(testparseTimeTwentyFour2)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "09:00-10:00 breakfast";
			parser.parseTimeTwentyFour (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 9);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), 10);
			Assert::AreEqual (timeMicroEnd.getMin(), 0);
		}

		//To test whether can parse a starting time followed by a task description
		TEST_METHOD(testparseTimeTwentyFour3)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "19:00 breakfast";
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
		//In this case, the task number has one digit
		TEST_METHOD(testParseDelete1)
		{
			Parser parser;
			string input = "delete 3";
			string commandWord = "delete";
			parser.parseDelete (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 3);
		}

		//To test whether can parse for the "delete" feature
		//In this case, the task number has three digits
		TEST_METHOD(testParseDelete2)
		{
			Parser parser;
			string input = "delete 388";
			string commandWord = "delete";
			parser.parseDelete (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 388);
		}

		//To test whether can update and get
		//date, month, year, day
		//followed by a starting time and a task description
		TEST_METHOD(testparseDateNumber1)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "12/03/2015 09:00 breakfast";
			string expectedDay = "Thursday";
			parser.parseDateNumber (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 12);
			Assert::AreEqual (timeMacro.getMonth (), 3);
			Assert::AreEqual (timeMacro.getYear (), 2015);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

		//To test whether can update and get
		//date, month, year, day
		//followed by a task description
		TEST_METHOD(testparseDateNumber2)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "18/03/2015 breakfast";
			string expectedDay = "Wednesday";
			parser.parseDateNumber (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 18);
			Assert::AreEqual (timeMacro.getMonth (), 3);
			Assert::AreEqual (timeMacro.getYear (), 2015);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

		//To test whether can update and get
		//date, month, year, day
		//followed by nothing
		TEST_METHOD(testparseDateNumber3)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "20/03/2015";
			string expectedDay = "Friday";
			parser.parseDateNumber (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 20);
			Assert::AreEqual (timeMacro.getMonth (), 3);
			Assert::AreEqual (timeMacro.getYear (), 2015);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

		//To test whether can ignore it when parsing date
		//when the input string is empty
		TEST_METHOD(testparseDateNumber4)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "";
			string expectedDay = "undefined";
			parser.parseDateNumber (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 0);
			Assert::AreEqual (timeMacro.getMonth (), 0);
			Assert::AreEqual (timeMacro.getYear (), 0);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

		//To test whether can ignore it when parsing date
		//when the input string is a time period
		TEST_METHOD(testparseDateNumber5)
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
			string dayOfTheWeek = "Saturday";
			parser.getTomorrowDate (timeMacro);
			Assert::AreEqual (timeMacro.getDate(), 14);
			Assert::AreEqual (timeMacro.getMonth(), 3);
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
			Assert::AreEqual (timeMacroBeg.getMonth(), 3);
			Assert::AreEqual (timeMacroBeg.getYear(), 2015);
			Assert::AreEqual (timeMacroEnd.getDate(), 31);
			Assert::AreEqual (timeMacroEnd.getMonth(), 3);
			Assert::AreEqual (timeMacroEnd.getYear(), 2015);
		}

		//To test whether can parse "display this month"
		TEST_METHOD(testparseShow1)
		{
			Parser parser;
			string userInput = "display this month";
			string commandWord = "display";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getDate (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getYear (), 2015);
		}

		//To test whether can parse "display today"
		TEST_METHOD(testparseShow2)
		{
			Parser parser;
			string userInput = "display today";
			string commandWord = "display";
			string expectedDay = "Friday";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 13);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
		}

		//To test whether can parse "display tomorrow"
		TEST_METHOD(testparseShow3)
		{
			Parser parser;
			string userInput = "display tomorrow";
			string commandWord = "display";
			string expectedDay = "Saturday";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 14);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
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

		//To test whether can parse for "edit" feature
		//In this case, the task number has two digits
		//and there is a time period
		TEST_METHOD(testParseEdit2)
		{
			Parser parser;
			string userInput = "edit 33 13/03/2015 09:00-10:00 work out";
			string commandWord = "edit";
			string expectedDay = "Friday";
			string expecedDesc = "work out";
			parser.parseEdit (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 13);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getHour (), 9);
			Assert::AreEqual (((parser.getData ()).getTimeMicroBeg ()).getMin (), 0);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getHour (), 10);
			Assert::AreEqual (((parser.getData ()).getTimeMicroEnd ()).getMin (), 0);
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
		//In this case, the task number has one digit
		TEST_METHOD(testParseDone1)
		{
			Parser parser;
			string input = "done 5";
			string commandWord = "done";
			parser.parseDone (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 5);
			Assert::AreEqual ((parser.getData ()).getCompleteStatus (), true);
		}

		//To test whether can parse for "mark it as done" feature
		//In this case, the task number has two digits
		TEST_METHOD(testParseDone2)
		{
			Parser parser;
			string input = "done 139";
			string commandWord = "done";
			parser.parseDone (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 139);
			Assert::AreEqual ((parser.getData ()).getCompleteStatus (), true);
		}

	};
}