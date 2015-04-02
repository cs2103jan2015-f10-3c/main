#include "stdafx.h"
#include "CppUnitTest.h"
#include "OperationCenter.h"
#include "Commons.h"
#include "DataProcessor.h"
#include "Storing.h"
#include "Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlinkListSystemTest
{		
	TEST_CLASS(SystemTest)
	{
	public:
		
		TEST_METHOD(editTimeTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 9:00");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast" << endl
				<< "   Thursday        10:00                                                2-4-2015  is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Today's Agenda:" << endl
				<< endl
				<< "1. breakfast" << endl
				<< "   Thursday        09:00                                                2-4-2015" << endl 
				<< "********************************************************************************"<< endl
				<< endl;
			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editDescriptionTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 exercise");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast" << endl
				<< "   Thursday        10:00                                                2-4-2015  is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Today's Agenda:" << endl
				<< endl
				<< "1. exercise" << endl
				<< "   Thursday        10:00                                                2-4-2015" << endl 
				<< "********************************************************************************"<< endl
				<< endl;
			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editDateTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 3/4");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast" << endl
				<< "   Thursday        10:00                                                2-4-2015  is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "\n:) You have no task for today\n";
			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editDateTimeTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 3/4 9am");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast" << endl
				<< "   Thursday        10:00                                                2-4-2015  is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "\n:) You have no task for today\n";
			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editTimeDateTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 9am 3/4");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast" << endl
				<< "   Thursday        10:00                                                2-4-2015  is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "\n:) You have no task for today\n";
			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editDateTimeDescriptionTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 3/4 9am exercise");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast" << endl
				<< "   Thursday        10:00                                                2-4-2015  is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "\n:) You have no task for today\n";
			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editTimeDateDescriptionTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 9am 3/4 exercise");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast" << endl
				<< "   Thursday        10:00                                                2-4-2015  is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "\n:) You have no task for today\n";
			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editErrorMessageTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 9am 3/4 exercise");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "Please enter correct task number after command word";
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);
		}
	};
}