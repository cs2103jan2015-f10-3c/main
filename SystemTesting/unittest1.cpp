#include "stdafx.h"
#include "CppUnitTest.h"
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemTesting
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(ClearTest)
		{
			// TODO: Your test code here
			OperationCenter::executeInput("clear");
			string actualResponse = OperationCenter::getResponse(); 
			string actualDisplay = OperationCenter::getDisplay();
			string expectedResponse = "All tasks are cleared";
			string expectedDisplay = "";
			Assert::AreEqual(actualResponse, expectedResponse);
			Assert::AreEqual(actualDisplay, expectedDisplay);

		}

		TEST_METHOD(AddTest)
		{
			ostringstream out;
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 02/04/2015 12:00 lunch");
			string actualResponse = OperationCenter::getResponse(); 
			string actualDisplay = OperationCenter::getDisplay();
			string expectedResponse = "lunch on Thursday, 2-4-2015 at 12:00 is added\n";
			out	<< "Today's Agenda:" << endl <<endl
				<< "1. lunch" << endl
				<< "12:00            Thursday                                            2-4-2015" << endl << endl
				<< "================================================================================"<< endl;
			string expectedDisplay = out.str();
			Assert::AreEqual(actualResponse, expectedResponse);
			Assert::AreEqual(actualDisplay, expectedDisplay);

		}

	};
}