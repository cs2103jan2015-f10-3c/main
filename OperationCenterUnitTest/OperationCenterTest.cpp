#include "stdafx.h"
#include "CppUnitTest.h"
#include <time.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OperationCenterUnitTest
{		
	TEST_CLASS(OperationCenterTest)
	{
	public:
		
		TEST_METHOD(testSetCurrentTime)
		{
			time_t t = time (0);   // get time now
			struct tm now;
			localtime_s (&now, &t);

			TimeMacro expectedTime(now.tm_mday, now.tm_mon + 1, now.tm_year + 1900);
			TimeMacro actualTime = Logic::setCurrentTime();

			Assert::AreEqual(expectedTime.getDate(), actualTime.getDate());
			Assert::AreEqual(expectedTime.getMonth(), actualTime.getMonth());
			Assert::AreEqual(expectedTime.getYear(), actualTime.getYear());
		}
		TEST_METHOD(testInvalidCommand)
		{
			OperationCenter::executeInput("invalidCommand 27/3 09:00 breakfast");
			string expectedReturnResponse = "Please enter the correct command";
			string actualReturnResponse = OperationCenter::getResponse();

			Assert::AreEqual(expectedReturnResponse, actualReturnResponse);
		}

	};
}