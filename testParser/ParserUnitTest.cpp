//@author A0093895J
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
		TEST_METHOD(testIsLeapYear1)
		{
			Parser parser;
			int year = 2004;
			Assert::IsTrue (parser.isLeapYear (year));
		}

		//To test for a non-leap year
		TEST_METHOD(testIsNotLeapYear)
		{
			Parser parser;
			int year = 2015;
			Assert::IsFalse (parser.isLeapYear (year));
		}

		//To test for a leap year which can be divided by 400
		TEST_METHOD(testIsLeapYear2)
		{
			Parser parser;
			int year = 2000;
			Assert::IsTrue (parser.isLeapYear (year));
		}

		//To test whether a string is contained in a vector.
		//In this case, it is contained in the vector.
		TEST_METHOD(testStringEqual)
		{
			Parser parser;
			string string = "abc";
			vector<std::string> stringVector;
			stringVector.push_back ("abc");
			stringVector.push_back ("def");
			Assert::IsTrue (parser.isStringEqual (string, stringVector));
		}

		//To test whether a string is contained in a vector.
		//In this case, it is not contained in the vector.
		TEST_METHOD(testStringNotEqual)
		{
			Parser parser;
			string string = "abc";
			vector<std::string> stringVector;
			stringVector.push_back ("abb");
			stringVector.push_back ("def");
			Assert::IsFalse (parser.isStringEqual (string, stringVector));
		}

		//To test whether can update and get today's date correctly
		TEST_METHOD(testTodayDate)
		{
			Parser parser;
			TimeMacro timeMacro;
			string dayOfTheWeek = "Sunday";
			parser.getTodayDate (timeMacro);
			Assert::AreEqual (timeMacro.getDate(), 12);
			Assert::AreEqual (timeMacro.getMonth(), 4);
			Assert::AreEqual (timeMacro.getYear(), 2015);
			Assert::AreEqual (timeMacro.getDay(), dayOfTheWeek);
		}

		//To test whether a date can be converted to day of the week correctly
		TEST_METHOD(testConvertDateToDay)
		{
			Parser parser;
			TimeMacro timeMacro;
			string dayOfTheWeek = "Thursday";
			Assert::AreEqual (parser.convertDateToDayOfTheWeek (12, 3, 2015), dayOfTheWeek);
		}

		//To test whether a string can be converted to an integer
		//The boundary case is 1
		TEST_METHOD(testConvertStringToInteger)
		{
			Parser parser;
			string index = "1";			
			Assert::AreEqual (parser.convertStringToInteger (index), 1);
		}

		//To test whether a string can be converted to a month
		TEST_METHOD(testConvertStringToMonthJanCap)
		{
			Parser parser;
			string month = "Jan";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 1);
		}

		TEST_METHOD(testConvertStringToMonthJanSmall)
		{
			Parser parser;
			string month = "jan";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 1);
		}

		TEST_METHOD(testConvertStringToMonthFebCap)
		{
			Parser parser;
			string month = "Feb";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 2);
		}

		TEST_METHOD(testConvertStringToMonthFebSmall)
		{
			Parser parser;
			string month = "feb";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 2);
		}

		TEST_METHOD(testConvertStringToMonthMarCap)
		{
			Parser parser;
			string month = "Mar";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 3);
		}

		TEST_METHOD(testConvertStringToMonthMarSmall)
		{
			Parser parser;
			string month = "mar";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 3);
		}

		TEST_METHOD(testConvertStringToMonthAprCap)
		{
			Parser parser;
			string month = "Apr";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 4);
		}

		TEST_METHOD(testConvertStringToMonthAprSmall)
		{
			Parser parser;
			string month = "apr";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 4);
		}

		TEST_METHOD(testConvertStringToMonthMayCap)
		{
			Parser parser;
			string month = "May";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 5);
		}

		TEST_METHOD(testConvertStringToMonthMaySamll)
		{
			Parser parser;
			string month = "may";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 5);
		}

		TEST_METHOD(testConvertStringToMonthJunCap)
		{
			Parser parser;
			string month = "Jun";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 6);
		}

		TEST_METHOD(testConvertStringToMonthJunSmall)
		{
			Parser parser;
			string month = "jun";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 6);
		}

		TEST_METHOD(testConvertStringToMonthJulCap)
		{
			Parser parser;
			string month = "Jul";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 7);
		}

		TEST_METHOD(testConvertStringToMonthJulSmall)
		{
			Parser parser;
			string month = "jul";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 7);
		}

		TEST_METHOD(testConvertStringToMonthAugCap)
		{
			Parser parser;
			string month = "Aug";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 8);
		}

		TEST_METHOD(testConvertStringToMonthAugSmall)
		{
			Parser parser;
			string month = "aug";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 8);
		}

		TEST_METHOD(testConvertStringToMonthSepCap)
		{
			Parser parser;
			string month = "Sep";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 9);
		}

		TEST_METHOD(testConvertStringToMonthSepSmall)
		{
			Parser parser;
			string month = "sep";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 9);
		}

		TEST_METHOD(testConvertStringToMonthOctCap)
		{
			Parser parser;
			string month = "Oct";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 10);
		}

		TEST_METHOD(testConvertStringToMonthOctSmall)
		{
			Parser parser;
			string month = "oct";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 10);
		}

		TEST_METHOD(testConvertStringToMonthNovCap)
		{
			Parser parser;
			string month = "Nov";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 11);
		}

		TEST_METHOD(testConvertStringToMonthNovSmall)
		{
			Parser parser;
			string month = "nov";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 11);
		}

		TEST_METHOD(testConvertStringToMonthDecCap)
		{
			Parser parser;
			string month = "Dec";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 12);
		}

		TEST_METHOD(testConvertStringToMonthDecCapSmall)
		{
			Parser parser;
			string month = "dec";	
			Assert::AreEqual (parser.convertAlphabetMonthToInteger (month), 12);
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "hh:mm-hh:mm"
		//"00:00-23:59" is also the boundary case
		TEST_METHOD(testIsTimePeriodTwentyFour1)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "00:00-23:59";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
			Assert::AreEqual (hourBeg, 0);
			Assert::AreEqual (hourEnd, 23);
			Assert::AreEqual (minuteBeg, 0);
			Assert::AreEqual (minuteEnd, 59);
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "h:mm-hh:mm"
		//"0:00-23:59" is also the boundary case
		TEST_METHOD(testIsTimePeriodTwentyFour2)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "0:00-23:59";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
			Assert::AreEqual (hourBeg, 0);
			Assert::AreEqual (hourEnd, 23);
			Assert::AreEqual (minuteBeg, 0);
			Assert::AreEqual (minuteEnd, 59);
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "hh:mm-h:mm"
		TEST_METHOD(testIsTimePeriodTwentyFour3)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "00:00-9:59";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
			Assert::AreEqual (hourBeg, 0);
			Assert::AreEqual (hourEnd, 9);
			Assert::AreEqual (minuteBeg, 0);
			Assert::AreEqual (minuteEnd, 59);
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "h:mm-h:mm"
		TEST_METHOD(testIsTimePeriodTwentyFour4)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "0:00-9:59";
			Assert::IsTrue (parser.isTimePeriodTwentyFour (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
			Assert::AreEqual (hourBeg, 0);
			Assert::AreEqual (hourEnd, 9);
			Assert::AreEqual (minuteBeg, 0);
			Assert::AreEqual (minuteEnd, 59);
		}

		//To test whether a string is a time period
		//In this case, the string is not a time period but a starting time
		TEST_METHOD(testIsNotTimePeriodTwentyFour)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "09:00";
			Assert::IsFalse (parser.isTimePeriodTwentyFour (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
		}

		//To test whether a string is a starting time
		//The format is hh:mm
		//The boundary case is 00:00
		TEST_METHOD(testIsStartingTimeTwentyFour1)
		{
			Parser parser;
			int hour;
			int minute;
			string testString = "00:00";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString, hour, minute));
			Assert::AreEqual (hour, 0);
			Assert::AreEqual (minute, 0);
		}

		//To test whether a string is a starting time
		//The format is hh:mm
		//The boundary case is 23:59
		TEST_METHOD(testIsStartingTimeTwentyFour2)
		{
			Parser parser;
			int hour;
			int minute;
			string testString = "23:59";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString, hour, minute));
			Assert::AreEqual (hour, 23);
			Assert::AreEqual (minute, 59);
		}

		//To test whether a string is a starting time
		//The format is h:mm
		//The boundary case is 0:00
		TEST_METHOD(testIsStartingTimeTwentyFour3)
		{
			Parser parser;
			int hour;
			int minute;
			string testString = "0:00";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString, hour, minute));
			Assert::AreEqual (hour, 0);
			Assert::AreEqual (minute, 0);
		}

		//To test whether a string is a starting time
		//The format is h:mm
		//The boundary case is 9:59
		TEST_METHOD(testIsStartingTimeTwentyFour4)
		{
			Parser parser;
			int hour;
			int minute;
			string testString = "9:59";
			Assert::IsTrue (parser.isStartingTimeTwentyFour (testString, hour, minute));
			Assert::AreEqual (hour, 9);
			Assert::AreEqual (minute, 59);
		}

		//To test whether a string is a starting time
		//In this case, the string is not a starting time but a date
		TEST_METHOD(testIsNotStartingTimeTwentyFour)
		{
			Parser parser;
			int hour;
			int minute;
			string testString = "12/03/2015 dinner tonight";
			Assert::IsFalse (parser.isStartingTimeTwentyFour (testString, hour, minute));
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "ham-hpm"
		TEST_METHOD(testIsTimePeriodTwelve1)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "1am-9pm";
			Assert::IsTrue (parser.isTimePeriodTwelve (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
			Assert::AreEqual (hourBeg, 1);
			Assert::AreEqual (hourEnd, 21);
			Assert::AreEqual (minuteBeg, 0);
			Assert::AreEqual (minuteEnd, 0);
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "hham-hhpm"
		TEST_METHOD(testIsTimePeriodTwelve2)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "01am-12pm";
			Assert::IsTrue (parser.isTimePeriodTwelve (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
			Assert::AreEqual (hourBeg, 1);
			Assert::AreEqual (hourEnd, 12);
			Assert::AreEqual (minuteBeg, 0);
			Assert::AreEqual (minuteEnd, 0);
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "h.mmam-h.mmpm"
		TEST_METHOD(testIsTimePeriodTwelve3)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "1.00am-9.59pm";
			Assert::IsTrue (parser.isTimePeriodTwelve (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
			Assert::AreEqual (hourBeg, 1);
			Assert::AreEqual (hourEnd, 21);
			Assert::AreEqual (minuteBeg, 0);
			Assert::AreEqual (minuteEnd, 59);
		}

		//To test whether a string is a time period
		//In this case, the string is a time period
		//with the format "hh.mmam-hh.mmpm"
		TEST_METHOD(testIsTimePeriodTwelve4)
		{
			Parser parser;
			int hourBeg;
			int hourEnd;
			int minuteBeg;
			int minuteEnd;
			string testString = "01.00am-12.59pm";
			Assert::IsTrue (parser.isTimePeriodTwelve (testString, hourBeg, hourEnd, 
				minuteBeg, minuteEnd));
			Assert::AreEqual (hourBeg, 1);
			Assert::AreEqual (hourEnd, 12);
			Assert::AreEqual (minuteBeg, 0);
			Assert::AreEqual (minuteEnd, 59);
		}

		//To test whether a string is a starting time
		//The boundary case is 01.00pm
		TEST_METHOD(testIsStartingTimeTwelve1)
		{
			Parser parser;
			int hour;
			int minute;
			string testString = "01.00pm";
			Assert::IsTrue (parser.isStartingTimeTwelve (testString, hour, minute));
			Assert::AreEqual (hour, 13);
			Assert::AreEqual (minute, 0);
		}

		//To test whether a string is a starting time
		//The boundary case is 12.59am
		TEST_METHOD(testIsStartingTimeTwelve2)
		{
			Parser parser;
			int hour;
			int minute;
			string testString = "12.59am";
			Assert::IsTrue (parser.isStartingTimeTwelve (testString, hour, minute));
			Assert::AreEqual (hour, 0);
			Assert::AreEqual (minute, 59);
		}

		//To test whether a string is a date
		//The format is dd/mm/yyyy
		//The boundary case is 01/01/2000
		TEST_METHOD(testIsDateNumber1)
		{
			Parser parser;
			int date;
			int month;
			string testString = "01/01/2000";
			Assert::IsTrue (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a date
		//The format is dd/mm/yyyy
		//The boundary case is 31/12/2100
		TEST_METHOD(testIsDateNumber2)
		{
			Parser parser;
			int date;
			int month;
			string testString = "31/12/2100";
			Assert::IsTrue (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a date
		//The format is d/mm/yyyy
		//The boundary case is 1/01/2000
		TEST_METHOD(testIsDateNumber3)
		{
			Parser parser;
			int date;
			int month;
			string testString = "1/01/2000";
			Assert::IsTrue (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a date
		//The format is d/mm/yyyy
		//The boundary case is 9/12/2100
		TEST_METHOD(testIsDateNumber4)
		{
			Parser parser;
			int date;
			int month;
			string testString = "9/12/2100";
			Assert::IsTrue (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a date
		//The format is dd/m/yyyy
		//The boundary case is 01/1/2000
		TEST_METHOD(testIsDateNumber5)
		{
			Parser parser;
			int date;
			int month;
			string testString = "01/1/2000";
			Assert::IsTrue (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a date
		//The format is dd/m/yyyy
		//The boundary case is 30/9/2100
		TEST_METHOD(testIsDateNumber6)
		{
			Parser parser;
			int date;
			int month;
			string testString = "30/9/2100";
			Assert::IsTrue (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a date
		//The format is d/m/yyyy
		//The boundary case is 1/1/2000
		TEST_METHOD(testIsDateNumber7)
		{
			Parser parser;
			int date;
			int month;
			string testString = "1/1/2000";
			Assert::IsTrue (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a date
		//The format is d/m/yyyy
		//The boundary case is 9/9/2100
		TEST_METHOD(testIsDateNumber8)
		{
			Parser parser;
			int date;
			int month;
			string testString = "9/9/2100";
			Assert::IsTrue (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a date
		//In this case, the string is not a date but a task description
		TEST_METHOD(testIsNotDateNumber)
		{
			Parser parser;
			int date;
			int month;
			string testString = "dinner tonight";
			Assert::IsFalse (parser.isDateNumber (testString, date, month));
		}

		//To test whether a string is a year
		//The format is "mm/yyyy"
		//The boundary case is "01/2000"
		TEST_METHOD(testIsYearNumber1)
		{
			Parser parser;
			int year;
			string testString = "01/2000";
			Assert::IsTrue (parser.isYearNumber (testString, year));
		}

		//To test whether a string is a year
		//The format is "mm/yyyy"
		//The boundary case is "12/2100"
		TEST_METHOD(testIsYearNumber2)
		{
			Parser parser;
			int year;
			string testString = "12/2100";
			Assert::IsTrue (parser.isYearNumber (testString, year));
		}

		//To test whether a string is a date
		//The format is dd MMM yyyy
		//The boundary case is 01 Jan 2000
		TEST_METHOD(testIsDateAlphabet1)
		{
			Parser parser;
			int date;
			string testString = "01 Jan 2000";
			Assert::IsTrue (parser.isDateAlphabet (testString, date));
		}

		//To test whether a string is a date
		//The format is dd MMM yyyy
		//The boundary case is 31 dec 2100
		TEST_METHOD(testIsDateAlphabet2)
		{
			Parser parser;
			int date;
			string testString = "31 dec 2100";
			Assert::IsTrue (parser.isDateAlphabet (testString, date));
		}

		//To test whether a string is a date
		//The format is d MMM yyyy
		//The boundary case is 1 Jan 2000
		TEST_METHOD(testIsDateAlphabet3)
		{
			Parser parser;
			int date;
			string testString = "1 Jan 2000";
			Assert::IsTrue (parser.isDateAlphabet (testString, date));
		}

		//To test whether a string is a year
		//The format is " yyyy"
		//The boundary case is 2000
		TEST_METHOD(testIsYearAlphabet1)
		{
			Parser parser;
			int year;
			string testString = " 2000";
			Assert::IsTrue (parser.isYearAlphabet (testString, year));
		}

		//To test whether a string is a year
		//The format is " yyyy"
		//The boundary case is 2100
		TEST_METHOD(testIsYearAlphabet2)
		{
			Parser parser;
			int year;
			string testString = " 2100";
			Assert::IsTrue (parser.isYearAlphabet (testString, year));
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
		TEST_METHOD(testparseTimeTwentyFourPeriod)
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
		TEST_METHOD(testparseTimeTwentyFourStarting)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "00:00";
			parser.parseTimeTwentyFour (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 0);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), -1);
			Assert::AreEqual (timeMicroEnd.getMin(), -1);
		}

		//To test whether can parse a time period
		TEST_METHOD(testparseTimeTwelvePeriod)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "1.00am-12.59pm";
			parser.parseTimeTwelve (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 1);
			Assert::AreEqual (timeMicroBeg.getMin(), 0);
			Assert::AreEqual (timeMicroEnd.getHour(), 12);
			Assert::AreEqual (timeMicroEnd.getMin(), 59);
		}

		//To test whether can parse a starting time
		TEST_METHOD(testparseTimeTwelveStarting)
		{
			Parser parser;
			TimeMicro timeMicroBeg;
			TimeMicro timeMicroEnd;
			string testString = "1.00pm";
			parser.parseTimeTwelve (testString, timeMicroBeg, timeMicroEnd);
			Assert::AreEqual (timeMicroBeg.getHour(), 13);
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
			parser.parseUndo (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
		}

		//To test whether can parse for the "delete" feature
		//The boundary case is 1
		TEST_METHOD(testParseDelete)
		{
			Parser parser;
			string input = "delete 1";
			string commandWord = "delete";
			parser.parseDelete (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 1);
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
		TEST_METHOD(testparseNotDateNumber)
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
			string dayOfTheWeek = "Monday";
			parser.getTomorrowDate (timeMacro);
			Assert::AreEqual (timeMacro.getDate(), 13);
			Assert::AreEqual (timeMacro.getMonth(), 4);
			Assert::AreEqual (timeMacro.getYear(), 2015);
			Assert::AreEqual (timeMacro.getDay(), dayOfTheWeek);
		}

		//To test whether can update and get this Monday's date correctly
		TEST_METHOD(testMonday)
		{
			Parser parser;
			TimeMacro timeMacro;
			parser.getMondayDate (timeMacro);
			Assert::AreEqual (timeMacro.getDate(), 6);
			Assert::AreEqual (timeMacro.getMonth(), 4);
			Assert::AreEqual (timeMacro.getYear(), 2015);
		}

		//To test whether can update and get this Sunday's date correctly
		TEST_METHOD(testSunday)
		{
			Parser parser;
			TimeMacro timeMacro;
			parser.getSundayDate (timeMacro);
			Assert::AreEqual (timeMacro.getDate(), 12);
			Assert::AreEqual (timeMacro.getMonth(), 4);
			Assert::AreEqual (timeMacro.getYear(), 2015);
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
		TEST_METHOD(testparseShowThisMonth)
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

		//To test whether can parse "show this week"
		TEST_METHOD(testparseShowThisWeek)
		{
			Parser parser;
			string userInput = "show this week";
			string commandWord = "show";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 6);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getDate (), 12);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getMonth (), 4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroEnd ()).getYear (), 2015);
		}

		//To test whether can parse "show today"
		TEST_METHOD(testparseShowToday)
		{
			Parser parser;
			string userInput = "show today";
			string commandWord = "show";
			string expectedDay = "Sunday";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 12);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (), 4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
		}

		//To test whether can parse "show tomorrow"
		TEST_METHOD(testparseShowTomorrow)
		{
			Parser parser;
			string userInput = "show tomorrow";
			string commandWord = "show";
			string expectedDay = "Monday";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 13);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (),4);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2015);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
		}

		TEST_METHOD(testparseShowADay)
		{
			Parser parser;
			string userInput = "show 01/01/2000";
			string commandWord = "show";
			string expectedDay = "Saturday";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDate (), 1);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getMonth (),1);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getYear (), 2000);
			Assert::AreEqual (((parser.getData ()).getTimeMacroBeg ()).getDay (), expectedDay);
		}

		//To test whether can parse "show commands"
		TEST_METHOD(testparseShowCommands)
		{
			Parser parser;
			string userInput = "show commands";
			string commandWord = "show";
			parser.parseShow (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), userInput);
		}

		//To test whether can parse "clear"
		TEST_METHOD(testparseClear)
		{
			Parser parser;
			string userInput = "clear";
			string commandWord = "clear";
			parser.parseClear (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
		}

		//To test whether can parse "path"
		TEST_METHOD(testparsePath)
		{
			Parser parser;
			string userInput = "path c:/user/admin";
			string commandWord = "path";
			string path = "c:/user/admin";
			parser.parsePath (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getDirectory (), path);
		}

		//To test whether can parse "help"
		TEST_METHOD(testparseHelp)
		{
			Parser parser;
			string userInput = "help";
			string commandWord = "help";
			parser.parseHelp (userInput, commandWord);

			Assert::AreEqual (parser.getCommand (), commandWord);
		}

		//To test whether can parse a string to search for a single keyword
		TEST_METHOD(testParseSearchWord)
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
		TEST_METHOD(testParseSearchPhrase)
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
		TEST_METHOD(testParseEdit)
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
		TEST_METHOD(testParseAddStartingTime)
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
		TEST_METHOD(testParseAddPeriod)
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
		TEST_METHOD(testParseInputAdd)
		{
			Parser parser;
			string userInput = "add 13/03/2015 10:00-14:00 project work";
			string expectedDay = "Friday";
			string expecedDesc = "project work";
			string commandWord = "add";
			parser.parseInput (userInput);

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

		//To test whether can parse for "edit" feature
		TEST_METHOD(testParseInputEdit)
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
		TEST_METHOD(testParseInputDelete)
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
		TEST_METHOD(testParseDone)
		{
			Parser parser;
			string input = "done 1";
			string commandWord = "done";
			parser.parseDone (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 1);
			Assert::AreEqual ((parser.getData ()).getCompleteStatus (), true);
		}

		//To test whether error message is updated
		//if done is not followed by a task number.
		TEST_METHOD(testParseErrorDone)
		{
			Parser parser;
			string input = "done a";
			string errorMessage = "Please enter correct task number after command word";
			parser.parseInput (input);
			Assert::AreEqual (parser.getErrorMessage (), errorMessage);
		}

		//To test whether can parse for "mark it as undone" feature
		//The boundary case is 1
		TEST_METHOD(testParseUndone)
		{
			Parser parser;
			string input = "undone 1";
			string commandWord = "undone";
			parser.parseUndone (input, commandWord);
			Assert::AreEqual (parser.getCommand (), commandWord);
			Assert::AreEqual (parser.getTaskNo (), 1);
			Assert::AreEqual ((parser.getData ()).getCompleteStatus (), false);
		}

		//To test whether an error message is updated
		//when the date is invalid
		TEST_METHOD(testErrorDateAlphabet)
		{
			Parser parser;
			string input = "add 30 feb 2000 breakfast";
			string errorMessage = "Please enter the correct date";
			parser.parseInput (input);
			Assert::AreEqual (parser.getErrorMessage(), errorMessage);
		}

		//To test whether a string is a date
		//If it is an invalid date or month, an error message is updated.
		TEST_METHOD(testErrorDateNumber)
		{
			Parser parser;
			string input = "add 32/13/2015 breakfast";
			string errorMessage = "Please enter the correct date";
			parser.parseInput (input);
			Assert::AreEqual (parser.getErrorMessage(), errorMessage);
		}

		//To test whether an error message is updated
		//when the time is invalid
		TEST_METHOD(testErrorStartingTimeTwelve)
		{
			Parser parser;
			string input = "add 13.60am breakfast";
			string errorMessage = "Please enter the correct time";
			parser.parseInput (input);
			Assert::AreEqual (parser.getErrorMessage (), errorMessage);
		}

		//To test whether a string is a starting time
		//If it is an invalid time, an error message is updated
		TEST_METHOD(testErrorStartingTimeTwentyFour)
		{
			Parser parser;
			string input = "add 24:00 sleep";
			string errorMessage = "Please enter the correct time";
			parser.parseInput (input);
			Assert::AreEqual (parser.getErrorMessage(), errorMessage);
		}

		//To test whether an error message is updated
		//when the year is invalid
		TEST_METHOD(testErrorYearAlphabet)
		{
			Parser parser;
			string input = "add 8 apr 2101 breakfast";
			string errorMessage = "Please enter the correct year";
			parser.parseInput (input);
			Assert::AreEqual (parser.getErrorMessage(), errorMessage);
		}

		//To test whether an error message is updated
		//when the year is invalid
		TEST_METHOD(testErrorYearNumber)
		{
			Parser parser;
			string input = "add 12/12/2101 breakfast";
			string errorMessage = "Please enter the correct year";
			parser.parseInput (input);
			Assert::AreEqual (parser.getErrorMessage (), errorMessage);
		}

		//To test whether an error message is updated
		//when the word "clear" is followed by something else
		TEST_METHOD(testparseClearError)
		{
			Parser parser;
			string userInput = "clear 1";
			string commandWord = "clear";
			string errorMessage = "Please enter the correct command";
			parser.parseInput (userInput);
			Assert::AreEqual (parser.getErrorMessage (), errorMessage);
		}

		//To test whether an error message is updated
		//when the word "help" is followed by something else
		TEST_METHOD(testparseHelpError)
		{
			Parser parser;
			string userInput = "help a";
			string commandWord = "help";
			string errorMessage = "Please enter the correct command";
			parser.parseInput (userInput);
			Assert::AreEqual (parser.getErrorMessage (), errorMessage);
		}

	};
}