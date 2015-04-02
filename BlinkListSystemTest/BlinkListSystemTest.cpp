#include "stdafx.h"
#include "CppUnitTest.h"
#include "OperationCenter.h"
#include "Commons.h"
#include "DataProcessor.h"
#include "Storing.h"
#include "Parser.h"
#include <iomanip>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlinkListSystemTest
{		
	TEST_CLASS(SystemTest)
	{
	public:
		
		//For command "add"						//Example
		TEST_METHOD(add_normal_test)			//Example, change it if you need to.
		{
			// TODO: Your test code here
		}

		//For command "delete"
		TEST_METHOD(deleteUntilNoMoreTaskLeftTest)			//Example, change it if you need to.
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 25/4 12:00 task 1");
			OperationCenter::executeInput("delete 1");

			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "task 1 on Saturday, 25-4-2015 at 12:00 is deleted from BlinkList\n";
			Assert::AreEqual(expectedResponse, actualResponse);
			
			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay = "You have no task on Saturday, 25-4-2015\n";
			Assert::AreEqual(expectedDisplay, actualDisplay);

		}

		TEST_METHOD(deleteWithTasksLeftTest){
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 25/4 12:00 task 1");
			OperationCenter::executeInput("add 25/4 14:00 task 2");
			OperationCenter::executeInput("add 25/4 16:00 task 3");
			OperationCenter::executeInput("delete 2");

			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "task 2 on Saturday, 25-4-2015 at 14:00 is deleted from BlinkList\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "Your agenda for Saturday, 25-4-2015:" << endl
				<< "1. task 1" << endl
				<< "   Saturday        12:00                                               25-4-2015" <<endl 
				<< "********************************************************************************"<< endl
				<< "2. task 3" << endl
				<< "   Saturday        16:00                                               25-4-2015" <<endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(deleteFloatingTask){
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add task 1");
			OperationCenter::executeInput("add task 2");
			OperationCenter::executeInput("add task 3");
			OperationCenter::executeInput("delete 1");

			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "task 1 is deleted from BlinkList\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "Your tasks with unspecified date are as follows: " << endl
				<< "1. task 2" << endl << "                    " <<endl
				<< "********************************************************************************"<< endl
				<< "2. task 3" << endl << "                    " <<endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(deleteUntilNoMoreFloatingTaskTest){
			
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add task 1");
			OperationCenter::executeInput("add task 2");
			OperationCenter::executeInput("add task 3");
			
			OperationCenter::executeInput("delete 1");
			string actualResponse1 = OperationCenter::getResponse();
			string expectedResponse1 = "task 1 is deleted from BlinkList\n";
			Assert::AreEqual(expectedResponse1, actualResponse1);
			
			OperationCenter::executeInput("delete 1");
			string actualResponse2 = OperationCenter::getResponse();
			string expectedResponse2 = "task 2 is deleted from BlinkList\n";
			Assert::AreEqual(expectedResponse2, actualResponse2);
			
			OperationCenter::executeInput("delete 1");
			string actualResponse3 = OperationCenter::getResponse();
			string expectedResponse3 = "task 3 is deleted from BlinkList\n";
			Assert::AreEqual(expectedResponse3, actualResponse3);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "You have no task with unspecified date" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		//For command "edit"
		TEST_METHOD(edit_normal_test)			//Example, change it if you need to.
		{
			// TODO: Your test code here
		}

	};
}

