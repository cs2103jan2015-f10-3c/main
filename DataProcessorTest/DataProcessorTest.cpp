#include "stdafx.h"
#include "CppUnitTest.h"
#include <sstream>
#include <exception>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataProcessorTest
{		
	TEST_CLASS(DataProcessorTest)
	{
	public:
		
		//@author A0114421Y
		TEST_METHOD(AddTaskTest)
		{
			Data task1("jim");
			DataProcessor myDataProcessor;
			ostringstream out;
			std::string expectedAddMessage = "jim is added";
			out << expectedAddMessage << endl;
			std::string actualAddMessage = myDataProcessor.addTask(task1);
			expectedAddMessage = out.str();
			Assert::AreEqual(expectedAddMessage, actualAddMessage);
			// TODO: Your test code here
		}

		TEST_METHOD(DisplayTaskTest){

			TimeMacro start(1, 2, 2000);
			TimeMacro end(1, 2, 2001);
			TimeMacro date(31, 1, 2000);
			Data task1(start, "jim");
			Data task2(end, "john");
			Data task3(date, "jane");
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();
			//string displayTask(TimeMacro startTime, TimeMacro endTime);
			
			myDataProcessor.addTask(task1);
			myDataProcessor.addTask(task2);
			myDataProcessor.addTask(task3);
			std::string actualDisplay = myDataProcessor.displayTask(start, end);
			ostringstream out;
			out << "1. jim" << endl
				<< "                                                          1-2-2000" << endl 
				<< "________________________________________________________________________________" << endl
				<< "2. john" << endl
				<< "                                                          1-2-2001" << endl 
				<< "________________________________________________________________________________" << endl;

			std::string expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}
		
		
		//@author A0113538J
		TEST_METHOD(Delete_Task_Test){
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();
			myDataProcessor.clearDisplayList();
			std::string actualDeleteMessage;
			
			//Exception: invalid task number
			try{ 
				actualDeleteMessage = myDataProcessor.deleteTask(1);
			}catch(string errorMessage){
				actualDeleteMessage = errorMessage;
			}
			std::string expectedDeleteMessage = "Please enter a valid task number. \n";
			Assert::AreEqual(expectedDeleteMessage, actualDeleteMessage);

			//Normal case
			TimeMacro start(1, 2, 2000);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, begin, end, "jim");
			bool status = true;
			myDataProcessor.loadData(status);
			myDataProcessor.addTask(task1);
			myDataProcessor.searchTask("jim");
			actualDeleteMessage = myDataProcessor.deleteTask(1);
			expectedDeleteMessage = "jim on undefined, 1-2-2000 at 01:30-02:30 is deleted from BlinkList\n";
			Assert::AreEqual(expectedDeleteMessage, actualDeleteMessage);
		}

		TEST_METHOD(Edit_Task_Test){
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();
			myDataProcessor.clearDisplayList();
			TimeMacro start(1, 2, 2000);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, begin, end, "jim");
			Data task2(start, begin, end, "john");

			//Exeception: invalid task number
			std::string addMessage = myDataProcessor.addTask(task1);
			std::string actualEditMessage;
			try{
				actualEditMessage = myDataProcessor.editTask(1, task2);
			}catch(string errorMessage){
				actualEditMessage = errorMessage;
			}
			std::string expectedEditMessage = "Please enter a valid task number. \n";
			Assert::AreEqual(expectedEditMessage, actualEditMessage);

			//Normal case
			myDataProcessor.searchTask("jim");
			actualEditMessage = myDataProcessor.editTask(1, task2);
			expectedEditMessage = "jim on undefined, 1-2-2000 at 01:30-02:30 is edited\n";
			Assert::AreEqual(expectedEditMessage, actualEditMessage);
		}

		TEST_METHOD(GetEditMessageTest){
			TimeMacro start(1, 2, 2000);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, begin, end, "jim overslept");
			DataProcessor myDataProcessor;
			std::string actualEditMessage = myDataProcessor.getEditMessage(task1);
			std::string expectedEditMessage = "jim overslept on undefined, 1-2-2000 at 01:30-02:30 is edited\n";
			Assert::AreEqual(expectedEditMessage, actualEditMessage);
		}

		TEST_METHOD(set_get_latest_data_test){
			TimeMacro start(1, 2, 2000);
			TimeMicro begin(15,30);
			TimeMicro end(16, 30);
			Data task1(start, begin, end, "jim overslept");
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();
			myDataProcessor.setLatestData(task1);
			Data actualData = myDataProcessor.getLatestData();
			Assert::AreEqual(task1.getDesc(), actualData.getDesc());
			Assert::AreEqual(task1.getTimeMacroBeg().getDate(), start.getDate());
			Assert::AreEqual(task1.getTimeMicroBeg().getHour(), begin.getHour());
			Assert::AreEqual(task1.getTimeMicroEnd().getHour(), end.getHour());

		}

		
		TEST_METHOD(ConvertDataObjectToStringTest){
			TimeMacro start(10, 4, 2015);
			TimeMicro begin(14,00);
			TimeMicro end(15,00);
			Data task1(start, begin, end, "jim overslept");
			DataProcessor myDataProcessor;
			std::string actualEditMessage = myDataProcessor.convertDataObjectToString(task1);
			std::string expectedEditMessage;
			ostringstream out;
			out	<< "jim overslept" << endl
				<< "      14:00-15:00                                        10-4-2015"; 
			expectedEditMessage = out.str();
			Assert::AreEqual(expectedEditMessage, actualEditMessage);
		}

		TEST_METHOD(SearchTest){
			TimeMacro start(1, 2, 2000);
			TimeMacro date(1, 2, 2001);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, "jim is smart and stupid");
			Data task2(start, "john is a good boy");
			Data task3(date, "jane is sexy and fat");
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();

			std::string string1 = myDataProcessor.addTask(task1);
			std::string string2 = myDataProcessor.addTask(task2);
			std::string string3 = myDataProcessor.addTask(task3);
			ostringstream out;
			std::string expectedTaskList = "";
			std::string actualTaskList;
			
			//Boundary case: No task matched
			actualTaskList = myDataProcessor.searchTask("something");
			Assert::AreEqual(expectedTaskList, actualTaskList);

			//Partition in the middle
			actualTaskList = myDataProcessor.searchTask("and");
			out << "1. jim is smart and stupid" << endl
				<< "                                                          1-2-2000" << endl 
				<< "________________________________________________________________________________" << endl
				<< "2. jane is sexy and fat" << endl
				<< "                                                          1-2-2001" << endl 
				<< "________________________________________________________________________________" << endl;
			expectedTaskList = out.str();
			Assert::AreEqual(expectedTaskList, actualTaskList);
			myDataProcessor.clearTask();
		}

		TEST_METHOD(clear_task_test){
			TimeMacro start(1, 2, 2000);
			TimeMacro date(1, 2, 2001);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, "jim is smart and stupid");
			Data task2(start, "john is a good boy");
			Data task3(date, "jane is sexy and fat");
			DataProcessor myDataProcessor;
			std::string string1 = myDataProcessor.addTask(task1);
			std::string string2 = myDataProcessor.addTask(task2);
			std::string string3 = myDataProcessor.addTask(task3);
			string expectedResponse = "all contents are cleared";
			string actualResponse;
			actualResponse = myDataProcessor.clearTask();
			Assert::AreEqual(expectedResponse, actualResponse);
		}

		TEST_METHOD(execute_undo_test){
			TimeMacro start(1, 2, 2000);
			TimeMacro date(1, 2, 2001);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, "jim is smart and stupid");
			Data task2(start, "john is a good boy");
			Data task3(date, "jane is sexy and fat");
			DataProcessor myDataProcessor;
			std::string string1 = myDataProcessor.addTask(task1);
			std::string string2 = myDataProcessor.addTask(task2);
			std::string string3 = myDataProcessor.addTask(task3);
			
			string expectedResponse = "You have undone your operation\n";
			string actualResponse;
			
			//Undo "add" command
			actualResponse = myDataProcessor.executeUndo();
			Assert::AreEqual(expectedResponse, actualResponse);

			//Undo "delete" command
			myDataProcessor.searchTask("jim");
			myDataProcessor.deleteTask(1);
			actualResponse = myDataProcessor.executeUndo();
			Assert::AreEqual(expectedResponse,actualResponse);

			//Undo "done" command
			myDataProcessor.searchTask("john");
			myDataProcessor.markDone(1);
			actualResponse = myDataProcessor.executeUndo();
			Assert::AreEqual(expectedResponse,actualResponse);

			//Undo "undone" command
			myDataProcessor.searchTask("john");
			myDataProcessor.unDone(1);
			actualResponse = myDataProcessor.executeUndo();
			Assert::AreEqual(expectedResponse,actualResponse);

			//Undo "edit" command
			myDataProcessor.searchTask("john");
			myDataProcessor.editTask(1, task2);			
			actualResponse = myDataProcessor.executeUndo();
			Assert::AreEqual(expectedResponse,actualResponse);

			//Undo "clear" command
			myDataProcessor.clearTask();
			actualResponse = myDataProcessor.executeUndo();
			Assert::AreEqual(expectedResponse,actualResponse);

		}

		TEST_METHOD(mark_done_test){
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();
			myDataProcessor.clearDisplayList();
			TimeMacro date(10, 4, 2015);
			Data task1(date, "jim is smart and stupid");
			myDataProcessor.addTask(task1);
			
			//Exception: invalid task number
			string actualResponse;
			string expectedResponse = "Please enter a valid task number. \n";
			try {
				actualResponse = myDataProcessor.markDone(1);
			}catch(string errorMessage){
				actualResponse = errorMessage;
			}
			Assert::AreEqual(expectedResponse,actualResponse);

			//Normal case
			myDataProcessor.searchTask("jim");
			expectedResponse = "jim is smart and stupid on undefined, 10-4-2015  is done\n";
			actualResponse;
			actualResponse = myDataProcessor.markDone(1);
			Assert::AreEqual(expectedResponse, actualResponse);
		}
		
		TEST_METHOD(get_done_message_test){
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();			
			TimeMacro date(10, 4, 2015);
			Data task1(date, "jim is smart and stupid");
			string expectedResponse = "jim is smart and stupid on undefined, 10-4-2015  is done\n";
			string actualResponse;
			actualResponse = myDataProcessor.getDoneMessage(task1);
			Assert::AreEqual(expectedResponse, actualResponse);
		}

		TEST_METHOD(undone_test){
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();
			myDataProcessor.clearDisplayList();
			TimeMacro date(10, 4, 2015);
			Data task1(date, "jim is smart and stupid");
			myDataProcessor.addTask(task1);
			
			//Exception: invalid task number
			string actualResponse;
			string expectedResponse = "Please enter a valid task number. \n";
			try {
				actualResponse = myDataProcessor.unDone(1);
			}catch(string errorMessage){
				actualResponse = errorMessage;
			}
			Assert::AreEqual(expectedResponse,actualResponse);
			
			//Normal case
			myDataProcessor.searchTask("jim");
			myDataProcessor.markDone(1);
			myDataProcessor.searchTask("jim");			
			expectedResponse = "jim is smart and stupid on undefined, 10-4-2015  is reopened\n";
			actualResponse;
			actualResponse = myDataProcessor.unDone(1);
			Assert::AreEqual(expectedResponse, actualResponse);
		}
		
		TEST_METHOD(get_undone_message_test){
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();			
			TimeMacro date(10, 4, 2015);
			Data task1(date, "jim is smart and stupid");
			string expectedResponse = "jim is smart and stupid on undefined, 10-4-2015  is reopened\n";
			string actualResponse;
			actualResponse = myDataProcessor.getUndoneMessage(task1);
			Assert::AreEqual(expectedResponse, actualResponse);
		}

		TEST_METHOD(show_float_test){
			DataProcessor myDataProcessor;
			myDataProcessor.clearTask();
			myDataProcessor.clearDisplayList();
			Data task1("jim is smart and stupid");
			string actualTaskList = myDataProcessor.showFloat();
			string expectedTaskList;
			expectedTaskList = "";
			Assert::AreEqual(expectedTaskList, actualTaskList);

			myDataProcessor.addTask(task1);
			actualTaskList = myDataProcessor.showFloat();
			ostringstream out;
			out << "1. jim is smart and stupid" << endl
				<< "                   " << endl
				<< "________________________________________________________________________________" << endl;
			expectedTaskList = out.str();
			Assert::AreEqual(expectedTaskList,actualTaskList);

		}

		TEST_METHOD(check_path_existence_test){
			DataProcessor myDataProcessor;
			myDataProcessor.savePath("c:\\");
			try{
				bool actualStatus = myDataProcessor.checkPathExistence();
				bool expectedStatus = true;
				Assert::AreEqual(expectedStatus, actualStatus);
			}catch(string errorMessage){
				string actualMessage = errorMessage;
				string expectedMessage = "Data could not be found. \n";
				Assert::AreEqual(expectedMessage, actualMessage);
			}


		}
	};
}