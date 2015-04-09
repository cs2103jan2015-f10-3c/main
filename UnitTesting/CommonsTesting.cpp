#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

//@author A0114002J
namespace UnitTesting
{		
	TEST_CLASS(TimeMicroTest)
	{
	public:

		//positive test of get and update hour
		TEST_METHOD(getUpdateHourTest)
		{
			//boundary case
			TimeMicro time;
			time.updateHour(1);
			Assert::AreEqual(1,time.getHour());

			//boundary case
			time.updateHour(24);
			Assert::AreEqual(24,time.getHour());

			//partition in the middle
			time.updateHour(12);
			Assert::AreEqual(12,time.getHour());

		}

		//postive test of get and update Min
		TEST_METHOD(getUpdateMinTest)
		{
			//boundary case
			TimeMicro time;
			time.updateMin(1);
			Assert::AreEqual(1,time.getMin());

			//boundary case
			time.updateMin(59);
			Assert::AreEqual(59,time.getMin());

			//partition in the middle
			time.updateMin(30);
			Assert::AreEqual(30,time.getMin());

		}

		//check for default;
		TEST_METHOD(TimeMicroCheckDefault)
		{
			TimeMicro time;
			//check default min
			Assert::AreEqual(-1,time.getMin());
			//check default hour
			Assert::AreEqual(-1,time.getHour());
		}

		//TimeMicro constructor
		TEST_METHOD(TimeMicroConstructor)
		{
			TimeMicro time(1,1);
			TimeMicro time2;
			time2.updateHour(1);
			time2.updateMin(1);

			Assert::AreEqual(time2.getMin(),time.getMin());
			Assert::AreEqual(time2.getHour(),time.getHour());
		}

	};

	TEST_CLASS(TimeMacroTest)
	{
	public:
		//positive test get and update day
		TEST_METHOD(getUpdateDayTest)
		{
			TimeMacro time;
			time.updateDay("Thursday");
			std::string day ="Thursday";
			Assert::AreEqual(day,time.getDay());
		}

		//boundary cases of get and update day
		TEST_METHOD(getUpdateDateTest)
		{
			TimeMacro time;
			time.updateDate(01);
			Assert::AreEqual(01,time.getDate());

			time.updateDate(30);
			Assert::AreEqual(30,time.getDate());
		}

		TEST_METHOD(getUpdateMonthTest)
		{
			TimeMacro time;
			time.updateMonth(01);
			Assert::AreEqual(1,time.getMonth());
			
			time.updateMonth(12);
			Assert::AreEqual(12,time.getMonth());

		}

		TEST_METHOD(getUpdateYearTest)
		{
			TimeMacro time;
			time.updateYear(2014);
			Assert::AreEqual(2014,time.getYear());
		}

		TEST_METHOD(TimeMacroCheckDefault){
			TimeMacro time;
			std::string str = "undefined";
			Assert::AreEqual(str,time.getDay());
			Assert::AreEqual(0,time.getDate());
			Assert::AreEqual(0,time.getMonth());
			Assert::AreEqual(0,time.getYear());
		}

		TEST_METHOD(TimeMacroConstructor){
			TimeMacro time(31,12,2015);
			std::string str = "undefined";
			Assert::AreEqual(str,time.getDay());
			Assert::AreEqual(31,time.getDate());
			Assert::AreEqual(12,time.getMonth());
			Assert::AreEqual(2015,time.getYear());

		}

	};

	TEST_CLASS(DataTest)
	{
	public:
		
		TEST_METHOD(getUpdateTimeDataTest)
		{
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

		TEST_METHOD(getUpdateDataAttributes){
			Data data;
			data.updateTaskNo(15);
			Assert::AreEqual(15,data.getTaskNo());
			
			TimeMacro time(1,12,2015);
			data.updateAlarmMacro(time);
			Assert::AreEqual(12,data.getAlarmMacro().getMonth());

			TimeMicro time2(12,30);
			data.updateAlarmMicro(time2);
			Assert::AreEqual(30,data.getAlarmMicro().getMin());

			std::string str= "HIGH";
			data.updatePriority(str);
			Assert::AreEqual(str,data.getPriority());

			data.updateCompleteStatus(true);
			Assert::AreEqual(true,data.getCompleteStatus());
		}

	};




}