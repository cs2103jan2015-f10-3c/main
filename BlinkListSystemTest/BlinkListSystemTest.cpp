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
		
		//@angelitasasmita
		//For command "add"	
		//testing for different format
		//also testing for sorting of the container
		TEST_METHOD(addDifferentInputFormat)			
		{
			OperationCenter::executeInput("clear");

			//format: DD/MM/YYYY HH:MM-HH:MM Desc
			OperationCenter::executeInput("add 01/04/2015 11:00-12:00 task 1");
			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "task 1 on Wednesday, 1-4-2015 at 11:00-12:00 is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			//format: DD/MM HH:MM Desc
			OperationCenter::executeInput("add 01/04 11:00 task 2");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "task 2 on Wednesday, 1-4-2015 at 11:00 is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			//format: D/M Desc
			OperationCenter::executeInput("add 1/4 task 3");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "task 3 on Wednesday, 1-4-2015  is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);
			
			//format: D MMM HH:MM-HH:MM Desc
			OperationCenter::executeInput("add 1 Apr 10:00-12:00 task 4");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "task 4 on Wednesday, 1-4-2015 at 10:00-12:00 is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "Your agenda for Wednesday, 1-4-2015:" << endl
				<< "1. task 3" << endl
				<< "   Wednesday                                                           1-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 4" << endl
				<< "   Wednesday       10:00-12:00                                         1-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 1" << endl
				<< "   Wednesday       11:00-12:00                                         1-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "4. task 2" << endl
				<< "   Wednesday       11:00                                               1-4-2015" << endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
			
			//format: Desc 
			//floating task
			OperationCenter::executeInput("add task 5");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "task 5 is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);
			
			actualDisplay = OperationCenter::getDisplay();
			expectedDisplay;
			ostringstream out2;
			out2<< "Your tasks with unspecified date are as follows: " << endl
				<< "1. task 5" << endl 
				<< "                                                                               " <<endl
				<< "********************************************************************************"<< endl;
			expectedDisplay = out2.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);

			//add in different date
			//format: DD MMM YYYY HH:MM Desc
			OperationCenter::executeInput("add 10 Apr 2015 12:00 task 6");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "task 6 on Friday, 10-4-2015 at 12:00 is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			//add in different date
			//format: D/MM/YY Desc
			OperationCenter::executeInput("add 9/04/15 task 7");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "task 7 on Thursday, 9-4-2015  is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			OperationCenter::executeInput("show this month");
			actualDisplay = OperationCenter::getDisplay();
			expectedDisplay;
			ostringstream out3;
			out3<< "1. task 3" << endl
				<< "   Wednesday                                                           1-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 4" << endl
				<< "   Wednesday       10:00-12:00                                         1-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 1" << endl
				<< "   Wednesday       11:00-12:00                                         1-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "4. task 2" << endl
				<< "   Wednesday       11:00                                               1-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "5. task 7" << endl
				<< "   Thursday                                                            9-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "6. task 6" << endl
				<< "   Friday          12:00                                              10-4-2015" << endl
				<< "********************************************************************************" << endl;
			expectedDisplay = out3.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}


		//Kevin
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
				<< "   Saturday        12:00                                              25-4-2015" <<endl 
				<< "********************************************************************************"<< endl
				<< "2. task 3" << endl
				<< "   Saturday        16:00                                              25-4-2015" <<endl
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

		TEST_METHOD(editTimeTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 9:00");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast on Thursday, 2-4-2015 at 10:00 is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Thursday, 2-4-2015:" << endl
				<< "1. breakfast" << endl
				<< "   Thursday        09:00                                               2-4-2015" << endl 
				<< "********************************************************************************"<< endl
				<< endl;
			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}



		//Chunhan
		//For command "edit"
		TEST_METHOD(editDescriptionTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 exercise");

			ostringstream outResponse;
			string acturalResponse = OperationCenter::getResponse();
			outResponse << "breakfast on Thursday, 2-4-2015 at 10:00 is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Thursday, 2-4-2015:" << endl
				<< "1. exercise" << endl
				<< "   Thursday        10:00                                               2-4-2015" << endl 
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
			outResponse << "breakfast on Thursday, 2-4-2015 at 10:00 is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "You have no task on Thursday, 2-4-2015\n";
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
			outResponse << "breakfast on Thursday, 2-4-2015 at 10:00 is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "You have no task on Thursday, 2-4-2015\n";
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
			outResponse << "breakfast on Thursday, 2-4-2015 at 10:00 is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "You have no task on Thursday, 2-4-2015\n";
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
			outResponse << "breakfast on Thursday, 2-4-2015 at 10:00 is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "You have no task on Thursday, 2-4-2015\n";
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
			outResponse << "breakfast on Thursday, 2-4-2015 at 10:00 is edited" << endl;
			string expectedResponse = outResponse.str();
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "You have no task on Thursday, 2-4-2015\n";
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



		//@Yang Xiaozhou A0113538J
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
				<< "   Thursday        14:00                                               2-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 2" << endl
				<< "   Thursday        15:00                                               2-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 3" << endl
				<< "   Thursday        16:00-17:00                                         2-4-2015" << endl
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
				<< "   Friday          14:00                                               3-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 2" << endl
				<< "   Friday          15:00                                               3-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 3" << endl
				<< "   Friday          16:00                                               3-4-2015" <<endl
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
				<< "   Thursday        14:00                                               2-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 2" << endl
				<< "   Friday          15:00                                               3-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 3" << endl
				<< "   Saturday        16:00                                               4-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "4. task 4" << endl
				<< "   Sunday          17:00                                               5-4-2015" << endl
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
				<< "   Thursday        14:00                                               2-4-2015" << endl 
				<< "********************************************************************************" << endl
				<< "2. task 2" << endl
				<< "   Friday          15:00                                              10-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "3. task 3" << endl
				<< "   Saturday        16:00                                              25-4-2015" << endl
				<< "********************************************************************************" << endl
				<< "4. task 4" << endl
				<< "   Thursday        17:00                                              30-4-2015" << endl
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
				<< "   Thursday        17:00                                              30-4-2015" << endl
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
		}
	};
}
