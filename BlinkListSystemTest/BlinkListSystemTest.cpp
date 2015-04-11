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
		
		//@author A0114002J
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
			
			//format: D MMM HHam-HHpm Desc
			OperationCenter::executeInput("add 1 Apr 10am-12pm task 4");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "task 4 on Wednesday, 1-4-2015 at 10:00-12:00 is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "Your agenda for Wednesday, 1-4-2015:" << endl << endl
				<< "1. task 3" << endl
				<< "   Wednesday                                                           1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "2. task 4" << endl
				<< "   Wednesday       10:00-12:00                                         1-4-2015" << endl
				<< "________________________________________________________________________________" << endl
				<< "3. task 1" << endl
				<< "   Wednesday       11:00-12:00                                         1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "4. task 2" << endl
				<< "   Wednesday       11:00                                               1-4-2015" << endl
				<< "________________________________________________________________________________" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
			
			//add in different date
			//format: DD MMM YYYY HHPM Desc
			OperationCenter::executeInput("add 10 Apr 2015 12pm task 6");
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
			out3<< "Your Agenda for This Month: " << endl << endl
				<< "1. task 3" << endl
				<< "   Wednesday                                                           1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "2. task 4" << endl
				<< "   Wednesday       10:00-12:00                                         1-4-2015" << endl
				<< "________________________________________________________________________________" << endl
				<< "3. task 1" << endl
				<< "   Wednesday       11:00-12:00                                         1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "4. task 2" << endl
				<< "   Wednesday       11:00                                               1-4-2015" << endl
				<< "________________________________________________________________________________" << endl
				<< "5. task 7" << endl
				<< "   Thursday                                                            9-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "6. task 6" << endl
				<< "   Friday          12:00                                              10-4-2015" << endl
				<< "________________________________________________________________________________" << endl;
			expectedDisplay = out3.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(addFloatingTask)
		{
			//format: Desc 
			//floating task
			OperationCenter::executeInput("add task 5");
			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "task 5 is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);

		}

		TEST_METHOD(addDefault)
		{
			//format: HH:MM Desc
			//by default without date
			//will add task to Today
			OperationCenter::executeInput("add 12:30 lunch");
			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "lunch on Saturday, 11-4-2015 at 12:30 is added\n";
			Assert::AreEqual(expectedResponse, actualResponse);
		}

		TEST_METHOD(addException){
			//no description
			OperationCenter::executeInput("add 4 apr");
			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "Please enter task description";
			Assert::AreEqual(expectedResponse, actualResponse);

			//date outside boundary
			OperationCenter::executeInput("add 33/4 task");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "Please enter the correct date";
			Assert::AreEqual(expectedResponse, actualResponse);

			//month outside boundary
			OperationCenter::executeInput("add 31/14 task");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "Please enter the correct date";
			Assert::AreEqual(expectedResponse, actualResponse);

			//year outside boundary
			OperationCenter::executeInput("add 31/12/1000 task");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "Please enter the correct year";
			Assert::AreEqual(expectedResponse, actualResponse);

			//time outside boundary
			OperationCenter::executeInput("add 31/12 25:00 task");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "Please enter the correct time";
			Assert::AreEqual(expectedResponse, actualResponse);

			//incorrect time
			OperationCenter::executeInput("add 13am task");
			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "Please enter the correct time";
			Assert::AreEqual(expectedResponse, actualResponse);
		}

		//@author A0114002J
		//exception response when command entry is wrong
		TEST_METHOD(wrongCommandException)
		{
			OperationCenter::executeInput("adds hellow");

			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "Please enter the correct command";
			Assert::AreEqual(expectedResponse, actualResponse);

		}

		//@author A0114002J
		//For command "clear"	
		TEST_METHOD(clear)			
		{
			OperationCenter::executeInput("add 01/04/2015 11:00-12:00 task 1");
			OperationCenter::executeInput("add 01/04 11:00 task 2");
			OperationCenter::executeInput("add 1/4 task 3");
			OperationCenter::executeInput("add 1 Apr 10:00-12:00 task 4");
			OperationCenter::executeInput("clear");

			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "all contents are cleared";
			Assert::AreEqual(expectedResponse, actualResponse);
			
		}

		//@author A0114002J
		//For command "search"
		TEST_METHOD(searchWordPhrase)
		{
			OperationCenter::executeInput("add 01/04/2015 11:00-12:00 task 1 running");
			OperationCenter::executeInput("add 01/04 11:00 task 2 sitting up");
			OperationCenter::executeInput("add 1/4 task 3");
			OperationCenter::executeInput("add jogging");
			OperationCenter::executeInput("add 1 Apr 10:00-12:00 task 4");
			
			//word search
			OperationCenter::executeInput("search task");

			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out << "1. task 3" << endl
				<< "   Wednesday                                                           1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "2. task 4" << endl
				<< "   Wednesday       10:00-12:00                                         1-4-2015" << endl
				<< "________________________________________________________________________________" << endl
				<< "3. task 1 running" << endl
				<< "   Wednesday       11:00-12:00                                         1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "4. task 2 sitting up" << endl
				<< "   Wednesday       11:00                                               1-4-2015" << endl
				<< "________________________________________________________________________________" << endl;
			
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
			
			//phrase search
			OperationCenter::executeInput("search sit");

			actualDisplay = OperationCenter::getDisplay();
			expectedDisplay;
			ostringstream out2;
			out2<< "1. task 2 sitting up" << endl
				<< "   Wednesday       11:00                                               1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl;

			expectedDisplay = out2.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);

			//sentence search
			OperationCenter::executeInput("search task 1 running");

			actualDisplay = OperationCenter::getDisplay();
			expectedDisplay;
			ostringstream out3;
			out3<< "1. task 1 running" << endl
				<< "   Wednesday       11:00-12:00                                         1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl;
				
			expectedDisplay = out3.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);

			//exception for search
			OperationCenter::executeInput("search blabla");

			actualResponse = OperationCenter::getResponse(); 
			expectedResponse = "Oops, there is no matching task in your BlinkList\n";
			Assert::AreEqual(expectedResponse, actualResponse);

		}



		//@author A0114421Y
		//For command "delete"
		TEST_METHOD(deleteUntilNoMoreTaskLeftTest)			
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

		TEST_METHOD(deleteWithTasksLeftTest)
		{
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
			out	<< "Your agenda for Saturday, 25-4-2015:" << endl << endl
				<< "1. task 1" << endl
				<< "   Saturday        12:00                                              25-4-2015" <<endl 
				<< "________________________________________________________________________________"<< endl
				<< "2. task 3" << endl
				<< "   Saturday        16:00                                              25-4-2015" <<endl
				<< "________________________________________________________________________________" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(deleteFloatingTask)
		{
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
			out	<< "Your tasks with unspecified date are as follows: " << endl << endl
				<< "1. task 2" << endl << "                   " <<endl
				<< "________________________________________________________________________________"<< endl
				<< "2. task 3" << endl << "                   " <<endl
				<< "________________________________________________________________________________" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);

		}

		TEST_METHOD(deleteUntilNoMoreFloatingTaskTest)
		{	
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

		TEST_METHOD(deleteWithoutTaskNumber)
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add task 1");
			OperationCenter::executeInput("add task 2");
			OperationCenter::executeInput("add task 3");

			OperationCenter::executeInput("delete");
			string actualResponse1 = OperationCenter::getResponse();
			string expectedResponse1 = "Please enter correct task number after command word";
			Assert::AreEqual(expectedResponse1, actualResponse1);

			OperationCenter::executeInput("delete ");
			string actualResponse2 = OperationCenter::getResponse();
			string expectedResponse2 = "Please enter correct task number after command word";
			Assert::AreEqual(expectedResponse2, actualResponse2);
		}

		//For command "done"
		TEST_METHOD(doneAllTasksTest)
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 25/4 12:00 task 1");
			OperationCenter::executeInput("done 1");

			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "task 1 on Saturday, 25-4-2015 at 12:00 is done\n";
			Assert::AreEqual(expectedResponse, actualResponse);
			
			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay = "You have no task on Saturday, 25-4-2015\n";
			Assert::AreEqual(expectedDisplay, actualDisplay);

			OperationCenter::executeInput("show done");
			string actualDisplay1 = OperationCenter::getDisplay();
			string expectedDisplay1;
			ostringstream out;
			out << "1. task 1" << endl
				<< "   Saturday        12:00                                              25-4-2015" <<endl 
				<< "________________________________________________________________________________"<< endl;
			expectedDisplay1 = out.str();
			Assert::AreEqual(expectedDisplay1, actualDisplay1);
		}

		TEST_METHOD(doneSomeTasksTest)
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 25/4 12:00 task 1");
			OperationCenter::executeInput("add 25/4 14:00 task 2");
			OperationCenter::executeInput("add 25/4 16:00 task 3");
			OperationCenter::executeInput("done 2");

			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "task 2 on Saturday, 25-4-2015 at 14:00 is done\n";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "Your agenda for Saturday, 25-4-2015:" << endl << endl
				<< "1. task 1" << endl
				<< "   Saturday        12:00                                              25-4-2015" <<endl 
				<< "________________________________________________________________________________"<< endl
				<< "2. task 3" << endl
				<< "   Saturday        16:00                                              25-4-2015" <<endl
				<< "________________________________________________________________________________" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);

			OperationCenter::executeInput("done 1");

			string actualResponse1 = OperationCenter::getResponse();
			string expectedResponse1 = "task 1 on Saturday, 25-4-2015 at 12:00 is done\n";
			Assert::AreEqual(expectedResponse1, actualResponse1);

			string actualDisplay1 = OperationCenter::getDisplay();
			string expectedDisplay1;
			ostringstream out1;
			out1 << "Your agenda for Saturday, 25-4-2015:" << endl << endl
				 << "1. task 3" << endl
				 << "   Saturday        16:00                                              25-4-2015" <<endl 
				 << "________________________________________________________________________________"<< endl;

			expectedDisplay1 = out1.str();
			Assert::AreEqual(expectedDisplay1, actualDisplay1);

			OperationCenter::executeInput("show done");
			string actualDisplay2 = OperationCenter::getDisplay();
			string expectedDisplay2;
			ostringstream out2;
			out2 << "1. task 2" << endl
				 << "   Saturday        14:00                                              25-4-2015" <<endl 
				 << "________________________________________________________________________________"<< endl
				 << "2. task 1" << endl
				 << "   Saturday        12:00                                              25-4-2015" <<endl
				 << "________________________________________________________________________________" << endl;
			expectedDisplay2 = out2.str();
			Assert::AreEqual(expectedDisplay2, actualDisplay2);
		}

		TEST_METHOD(doneWithoutTaskNumberTest)
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add task 1");
			OperationCenter::executeInput("add task 2");
			OperationCenter::executeInput("add task 3");

			OperationCenter::executeInput("done");
			string actualResponse1 = OperationCenter::getResponse();
			string expectedResponse1 = "Please enter correct task number after command word";
			Assert::AreEqual(expectedResponse1, actualResponse1);

			OperationCenter::executeInput("done ");
			string actualResponse2 = OperationCenter::getResponse();
			string expectedResponse2 = "Please enter correct task number after command word";
			Assert::AreEqual(expectedResponse2, actualResponse2);

		}

		TEST_METHOD(showWelcomeMessageFalseTest)
		{
			bool status = false;
			string actualMessage = OperationCenter::showWelcomeMessage(status);
			string expectedMessage = "Welcome to BlinkList!\n\nThere is no saved data\n\n";
			Assert::AreEqual(expectedMessage, actualMessage);
		}

		TEST_METHOD(showWelcomeMessageTrueTest)
		{
			OperationCenter::executeInput("clear");
			bool status = true;
			string actualMessage = OperationCenter::showWelcomeMessage(status);
			string expectedMessage = "Welcome to BlinkList!\n\nToday's Agenda is as follows:\n\n:) You have no task for today\n\n";
			Assert::AreEqual(expectedMessage, actualMessage);
		}

		TEST_METHOD(findPathTrueTest){
			bool actualStatus = OperationCenter::findPath();
			bool expectedStatus = true;
			Assert::AreEqual(expectedStatus, actualStatus);
		}
		//@author A0093895J
		//For command "edit"
		TEST_METHOD(editTimeTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 9:00");

			string acturalResponse = OperationCenter::getResponse();
			string expectedResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is edited\n";
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Thursday, 2-4-2015:" << endl
				<< endl
				<< "1. breakfast" << endl
				<< "   Thursday        09:00                                               2-4-2015" << endl 
				<< "________________________________________________________________________________"<< endl;

			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}


		TEST_METHOD(editDescriptionTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 exercise");

			string acturalResponse = OperationCenter::getResponse();
			string expectedResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is edited\n";
			Assert::AreEqual (acturalResponse, expectedResponse);

			ostringstream outDisplay;
			string actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Thursday, 2-4-2015:" << endl
				<< endl
				<< "1. exercise" << endl
				<< "   Thursday        10:00                                               2-4-2015" << endl 
				<< "________________________________________________________________________________"<< endl;

			string expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editDateTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 3/4");

			string acturalResponse = OperationCenter::getResponse();
			string expectedResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is edited\n";
			Assert::AreEqual (acturalResponse, expectedResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay = "You have no task on Thursday, 2-4-2015\n";
			Assert::AreEqual(expectedDisplay, actualDisplay);

			OperationCenter::executeInput ("show 3/4");
			ostringstream outDisplay;
			actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Friday, 3-4-2015:" << endl
				<< endl
				<< "1. breakfast" << endl
				<< "   Friday          10:00                                               3-4-2015" << endl 
				<< "________________________________________________________________________________"<< endl;
			expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editDateTimeTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 3/4 9am");

			string acturalResponse = OperationCenter::getResponse();
			string expectedResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is edited\n";
			Assert::AreEqual (acturalResponse, expectedResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay = "You have no task on Thursday, 2-4-2015\n";
			Assert::AreEqual(expectedDisplay, actualDisplay);

			OperationCenter::executeInput ("show 3/4");
			ostringstream outDisplay;
			actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Friday, 3-4-2015:" << endl
				<< endl
				<< "1. breakfast" << endl
				<< "   Friday          09:00                                               3-4-2015" << endl 
				<< "________________________________________________________________________________"<< endl;
			expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editTimeDateTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 9am 3/4");

			string acturalResponse = OperationCenter::getResponse();
			string expectedResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is edited\n";
			Assert::AreEqual (acturalResponse, expectedResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay = "You have no task on Thursday, 2-4-2015\n";
			Assert::AreEqual(expectedDisplay, actualDisplay);

			OperationCenter::executeInput ("show 3/4");
			ostringstream outDisplay;
			actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Friday, 3-4-2015:" << endl
				<< endl
				<< "1. breakfast" << endl
				<< "   Friday          09:00                                               3-4-2015" << endl 
				<< "________________________________________________________________________________"<< endl;
			expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editDateTimeDescriptionTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 3/4 9am exercise");

			string acturalResponse = OperationCenter::getResponse();
			string expectedResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is edited\n";
			Assert::AreEqual (acturalResponse, expectedResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay = "You have no task on Thursday, 2-4-2015\n";
			Assert::AreEqual(expectedDisplay, actualDisplay);

			OperationCenter::executeInput ("show 3/4");
			ostringstream outDisplay;
			actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Friday, 3-4-2015:" << endl
				<< endl
				<< "1. exercise" << endl
				<< "   Friday          09:00                                               3-4-2015" << endl 
				<< "________________________________________________________________________________"<< endl;
			expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editTimeDateDescriptionTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 1 9am 3/4 exercise");

			string acturalResponse = OperationCenter::getResponse();
			string expectedResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is edited\n";
			Assert::AreEqual (acturalResponse, expectedResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay = "You have no task on Thursday, 2-4-2015\n";
			Assert::AreEqual(expectedDisplay, actualDisplay);

			OperationCenter::executeInput ("show 3/4");
			ostringstream outDisplay;
			actualDisplay = OperationCenter::getDisplay();
			outDisplay	<< "Your agenda for Friday, 3-4-2015:" << endl
				<< endl
				<< "1. exercise" << endl
				<< "   Friday          09:00                                               3-4-2015" << endl 
				<< "________________________________________________________________________________"<< endl;
			expectedDisplay = outDisplay.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(editErrorMessageTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			OperationCenter::executeInput ("edit 9am 3/4 exercise");

			string acturalResponse = OperationCenter::getResponse();
			string expectedResponse = "Please enter correct task number after command word";
			Assert::AreEqual (acturalResponse, expectedResponse);
		}

		TEST_METHOD(undoAddTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			string actualAddResponse = OperationCenter::getResponse(); 
			string expectedAddResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("undo");
			string actualUndoResponse = OperationCenter::getResponse(); 
			string expectedUndoResponse = "You have undone your operation\n";
			Assert::AreEqual (actualUndoResponse, expectedUndoResponse);
		}

		TEST_METHOD(undoEditTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			string actualAddResponse = OperationCenter::getResponse(); 
			string expectedAddResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("edit 1 9:00");
			string actualEditResponse = OperationCenter::getResponse(); 
			string expectedEditResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is edited\n";
			Assert::AreEqual (actualEditResponse, expectedEditResponse);

			OperationCenter::executeInput ("undo");
			string actualUndoResponse = OperationCenter::getResponse(); 
			string expectedUndoResponse = "You have undone your operation\n";
			Assert::AreEqual (actualUndoResponse, expectedUndoResponse);
		}

		TEST_METHOD(undoDeleteTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			string actualAddResponse = OperationCenter::getResponse(); 
			string expectedAddResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("delete 1");
			string actualDeleteResponse = OperationCenter::getResponse(); 
			string expectedDeleteResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is deleted from BlinkList\n";
			Assert::AreEqual (actualDeleteResponse, expectedDeleteResponse);

			OperationCenter::executeInput ("undo");
			string actualUndoResponse = OperationCenter::getResponse(); 
			string expectedUndoResponse = "You have undone your operation\n";
			Assert::AreEqual (actualUndoResponse, expectedUndoResponse);
		}

		TEST_METHOD(undoDoneTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			string actualAddResponse = OperationCenter::getResponse(); 
			string expectedAddResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("done 1");
			string actualDoneResponse = OperationCenter::getResponse(); 
			string expectedDoneResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is done\n";
			Assert::AreEqual (actualDoneResponse, expectedDoneResponse);

			OperationCenter::executeInput ("undo");
			string actualUndoResponse = OperationCenter::getResponse(); 
			string expectedUndoResponse = "You have undone your operation\n";
			Assert::AreEqual (actualUndoResponse, expectedUndoResponse);
		}

		TEST_METHOD(undoUndoneTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			string actualAddResponse = OperationCenter::getResponse(); 
			string expectedAddResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("done 1");
			string actualDoneResponse = OperationCenter::getResponse(); 
			string expectedDoneResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is done\n";
			Assert::AreEqual (actualDoneResponse, expectedDoneResponse);

			OperationCenter::executeInput ("show done");
			OperationCenter::executeInput ("undone 1");
			string actualUndoneResponse = OperationCenter::getResponse(); 
			string expectedUndoneResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is reopened\n";
			Assert::AreEqual (actualUndoneResponse, expectedUndoneResponse);

			OperationCenter::executeInput ("undo");
			string actualUndoResponse = OperationCenter::getResponse(); 
			string expectedUndoResponse = "You have undone your operation\n";
			Assert::AreEqual (actualUndoResponse, expectedUndoResponse);
		}

		TEST_METHOD(undoClearTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			string actualAddResponse = OperationCenter::getResponse(); 
			string expectedAddResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("add 3/4 1pm lunch");
			actualAddResponse = OperationCenter::getResponse(); 
			expectedAddResponse = "lunch on Friday, 3-4-2015 at 13:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("add 4/4 6pm dinner");
			actualAddResponse = OperationCenter::getResponse(); 
			expectedAddResponse = "dinner on Saturday, 4-4-2015 at 18:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("clear");
			string actualClearResponse = OperationCenter::getResponse(); 
			string expectedClearResponse = "all contents are cleared";
			Assert::AreEqual (actualClearResponse, expectedClearResponse);

			OperationCenter::executeInput ("undo");
			string actualUndoResponse = OperationCenter::getResponse(); 
			string expectedUndoResponse = "You have undone your operation\n";
			Assert::AreEqual (actualUndoResponse, expectedUndoResponse);
		}

		TEST_METHOD(undoErrorTest)			
		{
			OperationCenter::executeInput ("clear");
			OperationCenter::executeInput ("add 2/4 10am breakfast");
			string actualAddResponse = OperationCenter::getResponse(); 
			string expectedAddResponse = "breakfast on Thursday, 2-4-2015 at 10:00 is added\n";
			Assert::AreEqual (actualAddResponse, expectedAddResponse);

			OperationCenter::executeInput ("undo");
			OperationCenter::executeInput ("undo");
			string actualUndoResponse = OperationCenter::getResponse(); 
			string expectedUndoResponse = "You can only undo the latest command and undo once";
			Assert::AreEqual (actualUndoResponse, expectedUndoResponse);
		}

		TEST_METHOD(PathTest)			
		{
			OperationCenter::executeInput ("path c:");
			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "New user path: c:\n"
				"Please type 'show commands' or 'show features' to get started\n";
			Assert::AreEqual (actualResponse, expectedResponse);
		}

		TEST_METHOD(PathErrorTest)			
		{
			OperationCenter::executeInput ("path C:/focus");
			string actualResponse = OperationCenter::getResponse(); 
			string expectedResponse = "Please reinput path ";
			Assert::AreEqual (actualResponse, expectedResponse);
		}

		//@author A0113538J
		//For command "show"
		TEST_METHOD(show_today_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 12/4 2pm task 1");
			OperationCenter::executeInput("add 3/4 3pm task 2");
			OperationCenter::executeInput("add 4/4 4pm-5pm task 3");
			OperationCenter::executeInput("show today");

			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "";
			Assert::AreEqual(expectedResponse, actualResponse);

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "Your agenda for Sunday, 12-4-2015:" << endl << endl
				<< "1. task 1" << endl
				<< "   Sunday          14:00                                              12-4-2015" << endl 
				<< "________________________________________________________________________________" << endl;
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
			//out	<< "1. task 1" << endl
			//	<< "   Friday          14:00                                               3-4-2015" << endl 
			//	<< "________________________________________________________________________________" << endl
			//	<< "2. task 2" << endl
			//	<< "   Friday          15:00                                               3-4-2015" << endl
			//	<< "________________________________________________________________________________" << endl
			//	<< "3. task 3" << endl
			//	<< "   Friday          16:00                                               3-4-2015" <<endl
			//	<< "________________________________________________________________________________" << endl;
			out << "You have no task within the specified time period" << endl;
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
			/*out	<< "1. task 1" << endl
				<< "   Thursday        14:00                                               2-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "2. task 2" << endl
				<< "   Friday          15:00                                               3-4-2015" << endl
				<< "________________________________________________________________________________" << endl
				<< "3. task 3" << endl
				<< "   Saturday        16:00                                               4-4-2015" << endl
				<< "________________________________________________________________________________" << endl
				<< "4. task 4" << endl
				<< "   Sunday          17:00                                               5-4-2015" << endl
				<< "________________________________________________________________________________" << endl;*/
			out << "You have no task within the specified time period" << endl;
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
			out	<< "Your Agenda for This Month: " << endl
				<< endl
				<< "1. task 1" << endl
				<< "   Thursday        14:00                                               2-4-2015" << endl 
				<< "________________________________________________________________________________" << endl
				<< "2. task 2" << endl
				<< "   Friday          15:00                                              10-4-2015" << endl
				<< "________________________________________________________________________________" << endl
				<< "3. task 3" << endl
				<< "   Saturday        16:00                                              25-4-2015" << endl
				<< "________________________________________________________________________________" << endl
				<< "4. task 4" << endl
				<< "   Thursday        17:00                                              30-4-2015" << endl
				<< "________________________________________________________________________________" << endl;
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
			string expectedResponse = "task 4 on Thursday, 30-4-2015 at 17:00 is done\n";
			Assert::AreEqual(expectedResponse, actualResponse);
			
			OperationCenter::executeInput("show done");

			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "1. task 4" << endl
				<< "   Thursday        17:00                                              30-4-2015" << endl
				<< "________________________________________________________________________________" << endl;
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

		TEST_METHOD(show_specific_day_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 1/4 task 1");
			OperationCenter::executeInput("add 2/4 task 2");
			OperationCenter::executeInput("add 3/4 task 3");
			OperationCenter::executeInput("add 30/4/2015 3pm task 4");
			OperationCenter::executeInput("show 1/4/2015");
			
			string actualResponse = OperationCenter::getResponse();
			string expectedResponse = "";
			Assert::AreEqual(expectedResponse, actualResponse);
			
			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out	<< "Your agenda for Wednesday, 1-4-2015:" << endl << endl
				<< "1. task 1" << endl
				<< "   Wednesday                                                           1-4-2015" << endl 
				<< "________________________________________________________________________________" << endl;
			expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(show_commands_test)			
		{
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("show commands");
			
			
			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay;
			ostringstream out;
			out << "BlinkList Commands\n"
			<< "-------------------------------------------------------------------------\n"
			<< "1. Add\n"
			<< "add DD MMM HH:MM Description\n"
			<< endl
			<< "2. Edit\n"
			<< "edit # DD MMM HH:MM Description\n"
			<< endl
			<< "3. Delete\n"
			<< "delete #\n"
			<< endl
			<< "4. Clear\n"
			<< "clear\n"
			<< endl
			<< "5. Show\n"
			<< "show today\n"
			<< "show tomorrow\n"
			<< "show this week\n"
			<< "show this month\n"
			<< "show DD/MM/YYYY (show a particular day, date format may vary)\n"
			<< "show done\n"
			<< "show float\n"
			<< endl
			<< "6. Search\n"
			<< "search Keyword\n"
			<< endl
			<< "7. Undo\n"
			<< "undo\n"
			<< endl
			<< "8. Done\n"
			<< "done #\n"
			<< endl
			<< "9. Undone\n"
			<< "undone #\n"
			<< endl
			<< "10. Help\n"
			<< "help\n"
			<< endl
			<< "* # refers to the number on your displayed list\n"
			<< endl
			<< "-------------------------------end of all commands-----------------------\n";
			expectedDisplay = out.str();
			expectedDisplay = "";
			Assert::AreNotEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(show_features_test){
			OperationCenter::executeInput("show features");
			string actualDisplay = OperationCenter::getDisplay();
			string expectedDisplay = "";
			Assert::AreNotEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(undone_test){
			OperationCenter::executeInput("clear");
			OperationCenter::executeInput("add 11/4 11:00 task 1");
			OperationCenter::executeInput("done 1");

			//Invalid task number
			OperationCenter::executeInput("show done");
			OperationCenter::executeInput("undone 0");
			string expectedResponse = "Please enter correct task number after command word";
			string actualResponse = OperationCenter::getResponse();
			Assert::AreEqual(expectedResponse, actualResponse);
			
			//Normal case
			OperationCenter::executeInput("show done");
			OperationCenter::executeInput("undone 1");
			expectedResponse = "task 1 on Saturday, 11-4-2015 at 11:00 is reopened\n";
			actualResponse = OperationCenter::getResponse();
			Assert::AreEqual(expectedResponse, actualResponse);

		}


	};
}
