#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testParser
{		
	TEST_CLASS(testParser)
	{
	public:
		
		TEST_METHOD(testExtractCommand1)
		{
			Parser parser;
			string testString = "add 08/03/2015 go for tutorial";
			string expected = "add";
			Assert::AreEqual (parser.extractCommandWord (testString), expected);
			// TODO: Your test code here
		}

		TEST_METHOD(testExtractCommand2)
		{
			Parser parser;
			string testString = "undo";
			string expected = "undo";
			Assert::AreEqual (parser.extractCommandWord (testString), expected);
			// TODO: Your test code here
		}

		TEST_METHOD(testLeapYear1)
		{
			Parser parser;
			int year = 2004;
			Assert::IsTrue (parser.isLeapYear (year));
			// TODO: Your test code here
		}

		TEST_METHOD(testLeapYear2)
		{
			Parser parser;
			int year = 2015;
			Assert::IsFalse (parser.isLeapYear (year));
			// TODO: Your test code here
		}

		TEST_METHOD(testLeapYear3)
		{
			Parser parser;
			int year = 2000;
			Assert::IsTrue (parser.isLeapYear (year));
			// TODO: Your test code here
		}

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

		TEST_METHOD(testConvertDateToDay1)
		{
			Parser parser;
			TimeMacro timeMacro;
			string dayOfTheWeek = "Thursday";
			Assert::AreEqual (parser.convertDateToDayOfTheWeek (12, 3, 2015), dayOfTheWeek);
		}

		TEST_METHOD(testConvertDateToDay2)
		{
			Parser parser;
			TimeMacro timeMacro;
			string dayOfTheWeek = "Wednesday";
			Assert::AreEqual (parser.convertDateToDayOfTheWeek (18, 3, 2015), dayOfTheWeek);
		}

		TEST_METHOD(testSearchSubstring1)
		{
			Parser parser;
			Assert::IsTrue (parser.searchSubstring ("abcdefg", 'a'));
		}

		TEST_METHOD(testSearchSubstring2)
		{
			Parser parser;
			Assert::IsFalse (parser.searchSubstring ("abcdefg", 'm'));
		}

		TEST_METHOD(testIsTimePeriod1)
		{
			Parser parser;
			string testString = "09:00-10:00";
			Assert::IsTrue (parser.isTimePeriod (testString));
		}

		TEST_METHOD(testIsTimePeriod2)
		{
			Parser parser;
			string testString = "09:00";
			Assert::IsFalse (parser.isTimePeriod (testString));
		}

		TEST_METHOD(testIsTimePeriod3)
		{
			Parser parser;
			string testString = "dinner tonight";
			Assert::IsFalse (parser.isTimePeriod (testString));
		}

		TEST_METHOD(testIsTimePeriod4)
		{
			Parser parser;
			string testString = "09:00-10:00 dinner tonight";
			Assert::IsTrue (parser.isTimePeriod (testString));
		}

		TEST_METHOD(testIsStartingTime1)
		{
			Parser parser;
			string testString = "09:00-10:00 dinner tonight";
			Assert::IsTrue (parser.isStartingTime (testString));
		}

		TEST_METHOD(testIsStartingTime2)
		{
			Parser parser;
			string testString = "09:00 dinner tonight";
			Assert::IsTrue (parser.isStartingTime (testString));
		}

		TEST_METHOD(testIsStartingTime3)
		{
			Parser parser;
			string testString = "12/03/2015 dinner tonight";
			Assert::IsFalse (parser.isStartingTime (testString));
		}

		TEST_METHOD(testIsDate1)
		{
			Parser parser;
			string testString = "12/03/2015 dinner tonight";
			Assert::IsTrue (parser.isDate (testString));
		}

		TEST_METHOD(testIsDate2)
		{
			Parser parser;
			string testString = "12/3/2015 dinner tonight";
			Assert::IsFalse (parser.isDate (testString));
		}

		TEST_METHOD(testParseTaskNo1)
		{
			Parser parser;
			string testString = "3 dinner";
			string expected = "3";
			Assert::AreEqual (parser.parseTaskNo (testString), expected);
		}

		TEST_METHOD(testParseTaskNo2)
		{
			Parser parser;
			string testString = "45 dinner";
			string expected = "45";
			Assert::AreEqual (parser.parseTaskNo (testString), expected);
		}

		TEST_METHOD(testParseTime1)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "09:00-10:00";
			parser.parseTime (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 9);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), 10);
			Assert::AreEqual (timeMicroEnd.getMin(), 0);
		}

		TEST_METHOD(testParseTime2)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "09:00-10:00 breakfast";
			parser.parseTime (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 9);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), 10);
			Assert::AreEqual (timeMicroEnd.getMin(), 0);
		}

		TEST_METHOD(testParseTime3)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "19:00 breakfast";
			parser.parseTime (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 19);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), -1);
			Assert::AreEqual (timeMicroEnd.getMin(), -1);
		}

		TEST_METHOD(testParseUndo)
		{
			Parser parser;
			string input = "undo";
			string commandWord = "undo";
			parser.ParseUndo (input);
			Assert::AreEqual (parser.getCommand (), commandWord);
		}

		TEST_METHOD(testParseDelete1)
		{
			Parser parser;
			string input = "delete 3";
			string commandWord = "delete";
			parser.ParseDelete (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 3);
		}

		TEST_METHOD(testParseDelete2)
		{
			Parser parser;
			string input = "delete 388";
			string commandWord = "delete";
			parser.ParseDelete (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 388);
		}

		TEST_METHOD(testParseDate1)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "12/03/2015 09:00 breakfast";
			string expectedDay = "Thursday";
			parser.parseDate (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 12);
			Assert::AreEqual (timeMacro.getMonth (), 3);
			Assert::AreEqual (timeMacro.getYear (), 2015);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

		TEST_METHOD(testParseDate2)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "18/03/2015 breakfast";
			string expectedDay = "Wednesday";
			parser.parseDate (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 18);
			Assert::AreEqual (timeMacro.getMonth (), 3);
			Assert::AreEqual (timeMacro.getYear (), 2015);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

		TEST_METHOD(testParseDate3)
		{
			Parser parser;
			TimeMacro timeMacro;
			string testString = "20/03/2015";
			string expectedDay = "Friday";
			parser.parseDate (testString, timeMacro);
			Assert::AreEqual (timeMacro.getDate (), 20);
			Assert::AreEqual (timeMacro.getMonth (), 3);
			Assert::AreEqual (timeMacro.getYear (), 2015);
			Assert::AreEqual (timeMacro.getDay (), expectedDay);
		}

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

		TEST_METHOD(testThisMonth)
		{
			Parser parser;
			TimeMacro timeMacroBeg;
			TimeMacro timeMacroEnd;
			parser.getThisMonth (timeMacroBeg, timeMacroEnd);
			Assert::AreEqual (timeMacroBeg.getDate(), 0);
			Assert::AreEqual (timeMacroBeg.getMonth(), 3);
			Assert::AreEqual (timeMacroBeg.getYear(), 2015);
			Assert::AreEqual (timeMacroEnd.getDate(), 0);
			Assert::AreEqual (timeMacroEnd.getMonth(), 3);
			Assert::AreEqual (timeMacroEnd.getYear(), 2015);
		}

		TEST_METHOD(testParseDisplay1)
		{
			Parser parser;
			//TimeMacro timeMacroBeg;
			//TimeMacro timeMacroEnd;
			string userInput = "display this week";
			string commandWord = "display";
			parser.ParseDisplay (userInput, commandWord);
			Data myData = parser.getData ();

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual ((myData.getTimeMacroBeg ()).getDate (), 0);
			Assert::AreEqual ((myData.getTimeMacroBeg ()).getMonth (), 3);
			Assert::AreEqual ((myData.getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual ((myData.getTimeMacroEnd ()).getDate (), 0);
			Assert::AreEqual ((myData.getTimeMacroEnd ()).getMonth (), 3);
			Assert::AreEqual ((myData.getTimeMacroEnd ()).getYear (), 2015);
		}

		TEST_METHOD(testParseSearch1)
		{
			Parser parser;
			string userInput = "search breakfast";
			string commandWord = "search";
			string expectedDesc = "breakfast";
			Data myData = parser.getData ();
			parser.ParseDisplay (userInput, commandWord);
			
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (myData.getDesc (), expectedDesc);
		}

	};
}