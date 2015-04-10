#include "stdafx.h"
#include "CppUnitTest.h"
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataProcessorTest
{		
	TEST_CLASS(DataProcessorTest)
	{
	public:
		
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

		//TEST_METHOD(DeleteTaskTest){
		//	DataProcessor myDataProcessor;
		//	int taskNo = 3;
		//	std::string actualDeleteMessage = myDataProcessor.deleteTask(taskNo);
		//	std::string expectedDeleteMessage = "breakfast at utown is deleted from BlinkList";
		//	ostringstream out;
		//	out << expectedDeleteMessage << endl;
		//	expectedDeleteMessage = out.str();
		//	Assert::AreEqual(expectedDeleteMessage, actualDeleteMessage);
		//}

		//TEST_METHOD(EditTaskTest){
		//	DataProcessor myDataProcessor;
		//	myDataProcessor.clearTask();
		//	TimeMacro start(1, 2, 2000);
		//	TimeMicro begin(1,30);
		//	TimeMicro end(2, 30);
		//	Data task1(start, begin, end, "jim");
		//	Data task2(start, begin, end, "john");
		//	std::string addMessage = myDataProcessor.addTask(task1);
		//	std::string actualEditMessage = myDataProcessor.editTask(1, task2);
		//	std::string expectedEditMessage = "jim on undefined, 1-2-2000  is edited";
		//	Assert::AreEqual(expectedEditMessage, actualEditMessage);
		//}

		//@author A0113538J
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
			std::string string1 = myDataProcessor.addTask(task1);
			std::string string2 = myDataProcessor.addTask(task2);
			std::string string3 = myDataProcessor.addTask(task3);
			std::string actualTaskList = myDataProcessor.searchTask("and");
			ostringstream out;
			out << "1. jim is smart and stupid" << endl
				<< "                                                          1-2-2000" << endl 
				<< "________________________________________________________________________________" << endl
				<< "2. jane is sexy and fat" << endl
				<< "                                                          1-2-2001" << endl 
				<< "________________________________________________________________________________" << endl;
			std::string expectedTaskList = out.str();
			Assert::AreEqual(expectedTaskList, actualTaskList);
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
			actualResponse = myDataProcessor.executeUndo();
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

	};
}