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

		
		//Xiao zhou
		//For command "show"
		TEST_METHOD(show_today_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 2pm task 1");
			OperationCenter::executeInput("add 3pm task 2");
			OperationCenter::executeInput("add 4pm-5pm task 3");
			OperationCenter::executeInput("show today");

			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "1. task 1" << endl
				<< "   Thursday        14:00                                                2-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 2" << endl
				<< "   Thursday        15:00                                                2-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 3" << endl
				<< "   Thursday        16:00-17:00                                          2-4-2015" << endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}


		TEST_METHOD(show_tomorrow_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 3 apr 2pm task 1");
			OperationCenter::executeInput("add 3 apr 3pm task 2");
			OperationCenter::executeInput("add 3 apr 4pm task 3");
			OperationCenter::executeInput("show tomorrow");

			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "1. task 1" << endl
				<< "   Friday          14:00                                                3-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 2" << endl
				<< "   Friday          15:00                                                3-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 3" << endl
				<< "   Friday          16:00                                                3-4-2015" <<endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}
		
		
		TEST_METHOD(show_this_week_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 2 apr 2pm task 1");
			OperationCenter::executeInput("add 3 apr 3pm task 2");
			OperationCenter::executeInput("add 4 apr 4pm task 3");
			OperationCenter::executeInput("add 5 apr 5pm task 4");
			OperationCenter::executeInput("show this week");

			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "1. task 1" << endl
				<< "   Thursday        14:00                                                2-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 2" << endl
				<< "   Friday          15:00                                                3-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 3" << endl
				<< "   Saturday        16:00                                                4-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "4. task 4" << endl
				<< "   Sunday          17:00                                                5-4-2015" << endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(show_this_month_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 2 apr 2pm task 1");
			OperationCenter::executeInput("add 10 apr 3pm task 2");
			OperationCenter::executeInput("add 25 apr 4pm task 3");
			OperationCenter::executeInput("add 30 apr 5pm task 4");
			OperationCenter::executeInput("show this month");

			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "1. task 1" << endl
				<< "   Thursday        14:00                                                2-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 2" << endl
				<< "   Friday          15:00                                               10-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 3" << endl
				<< "   Saturday        16:00                                               25-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "4. task 4" << endl
				<< "   Thursday        17:00                                               30-4-2015" << endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(show_done_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 2 apr 2pm task 1");
			OperationCenter::executeInput("add 10 apr 3pm task 2");
			OperationCenter::executeInput("add 25 apr 4pm task 3");
			OperationCenter::executeInput("add 30 apr 5pm task 4");
			OperationCenter::executeInput("show this month");
			
			OperationCenter::executeInput("done 4");
			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "task 4 on Thursday, 30-4-2015 at 17:00 is done";
			Assert::AreEqual(expectedResponse, actualResponse);
			
			OperationCenter::executeInput("show done");

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "1. task 4" << endl
				<< "   Thursday        17:00                                               30-4-2015" << endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(show_float_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add task 1");
			OperationCenter::executeInput("add task 2");
			OperationCenter::executeInput("add task 3");
			OperationCenter::executeInput("add task 4");
			OperationCenter::executeInput("show float");
			
			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "";
			Assert::AreEqual(expectedResponse, actualResponse);

			OperationCenter::executeInput("delete 1");
			OperationCenter::executeInput("delete 1");
			OperationCenter::executeInput("delete 1");
			OperationCenter::executeInput("delete 1");
			OperationCenter::executeInput("show float");
			actualResponse = OperationCenter::getResponse();
			expectedResponse = "You have no task with unspecified date\n"; 
			
			//vector<Data> expectedTaskList;
			//Data task1("task 1");
			//Data task2("task 2");
			//Data task3("task 3");
			//Data task4("task 4");
			//expectedTaskList.push_back(task1);
			//expectedTaskList.push_back(task2);
			//expectedTaskList.push_back(task3);
			//expectedTaskList.push_back(task4);
			//Assert::AreEqual(expectedTaskList.size(), actualTaskList.size());
			//Assert::AreEqual(expectedTaskList[0].getDesc(), actualTaskList[0].getDesc());
			//Assert::AreEqual(expectedTaskList[1].getDesc(), actualTaskList[1].getDesc());
			//Assert::AreEqual(expectedTaskList[2].getDesc(), actualTaskList[2].getDesc());
			//Assert::AreEqual(expectedTaskList[3].getDesc(), actualTaskList[3].getDesc());


			/*string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "1. task 1" << "                                  " << endl
				<< "                                                                                " << endl
				<< "********************************************************************************" << endl;
				<< "2. task 2" << "                   " << endl
				<< "                                                                                " << endl                
				<< "********************************************************************************" << endl
				<< "3. task 3" << "                   " << endl
				<< "                                                                                " << endl                
				<< "********************************************************************************" << endl
				<< "4. task 4" << "                   " << endl
				<< "                                                                                " << endl                
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);*/
		}
	};
}

