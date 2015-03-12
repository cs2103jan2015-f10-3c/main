#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTesting
{		
	TEST_CLASS(TimeMicroTest)
	{
	public:

		//positive test of get and update hour
		TEST_METHOD(getUpdateHourTest)
		{
			// TODO: Your test code here
			TimeMicro time;
			time.updateHour(1);
			Assert::AreEqual(1,time.getHour());

		}
		
		//default hour kick in (constructor)
		TEST_METHOD(getUpdateHourTest2)
		{
			// TODO: Your test code here
			TimeMicro time;
			time.updateHour(-5);
			Assert::AreEqual(-1,time.getHour());

		}

		//postive test of get and update hour
		TEST_METHOD(getUpdateMinTest)
		{
			// TODO: Your test code here
			TimeMicro time;
			time.updateMin(0);
			Assert::AreEqual(0,time.getMin());
		}

		//default min kick in (constructor)
		TEST_METHOD(getUpdateMinTest2)
		{
			// TODO: Your test code here
			TimeMicro time;
			time.updateMin(60);
			Assert::AreEqual(-1,time.getMin());
		}

	};

	TEST_CLASS(TimeMacroTest)
	{
	public:
		
		TEST_METHOD(getUpdateDayTest)
		{
			TimeMacro time;
			time.updateDay("Thursday");
			std::string day ="Thursday";
			Assert::AreEqual(day,time.getDay());
		}

		TEST_METHOD(getUpdateDayTest2)
		{
			TimeMacro time;
			time.updateDay("thursday");
			std::string day ="undefined";
			Assert::AreEqual(day,time.getDay());
		}

		TEST_METHOD(getUpdateDateTest)
		{
			TimeMacro time;
			time.updateDate(05);
			Assert::AreEqual(05,time.getDate());
		}

		TEST_METHOD(getUpdateDateTest2)
		{
			TimeMacro time;
			time.updateDate(99);
			Assert::AreEqual(0,time.getDate());
		}

		TEST_METHOD(getUpdateMonthTest)
		{
			TimeMacro time;
			time.updateMonth(01);
			Assert::AreEqual(1,time.getMonth());
		}

		TEST_METHOD(getUpdateMonthTest2)
		{
			TimeMacro time;
			time.updateMonth(60);
			Assert::AreEqual(0,time.getMonth());
		}

		TEST_METHOD(getUpdateYearTest)
		{
			TimeMacro time;
			time.updateYear(2014);
			Assert::AreEqual(2014,time.getYear());
		}

		TEST_METHOD(getUpdateYearTest2)
		{
			TimeMacro time;
			time.updateYear(1000);
			Assert::AreEqual(0,time.getYear());
		}

	};

	TEST_CLASS(DataTest)
	{
	public:
		
		TEST_METHOD(getUpdateDataTest)
		{
			// TODO: Your test code here
			TimeMacro time;			
			time.updateDate(10);
			time.updateMonth(01);
			time.updateYear(2015);
			time.updateDay("Wednesday");

			TimeMacro time2;
			time2.updateDate(11);
			time2.updateMonth(10);
			time2.updateYear(2017);
			time2.updateDay("Friday");

			TimeMicro timeM1;
			timeM1.updateHour(1);
			timeM1.updateMin(5);

			TimeMicro timeM2;
			timeM2.updateHour(2);
			timeM2.updateMin(7);

			Data myData;
			myData.updateTimeMacroBeg(time);
			myData.updateTimeMacroEnd(time2);
			myData.updateTimeMicroBeg(timeM1);
			myData.updateTimeMicroEnd(timeM2);

			TimeMacro time3 = myData.getTimeMacroBeg();
			TimeMacro time4 = myData.getTimeMacroEnd();
			TimeMicro time5 = myData.getTimeMicroBeg();
			TimeMicro time6 = myData.getTimeMicroEnd();

			std::string day1 = "Wednesday";
			std::string day2 = "Friday";

			Assert::AreEqual(10,time3.getDate());
			Assert::AreEqual(1,time3.getMonth());
			Assert::AreEqual(2015,time3.getYear());
			Assert::AreEqual(11,time4.getDate());
			Assert::AreEqual(10,time4.getMonth());
			Assert::AreEqual(2017,time4.getYear());
			Assert::AreEqual(day1, time3.getDay());
			Assert::AreEqual(day2, time4.getDay());
			Assert::AreEqual(1, time5.getHour());
			Assert::AreEqual(5, time5.getMin());
			Assert::AreEqual(2, time6.getHour());
			Assert::AreEqual(7, time6.getMin());
		
		}	
//Data unit testing to be continued..

	};




}