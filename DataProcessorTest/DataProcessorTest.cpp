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
			Data task3(end, "jane");
			DataProcessor myDataProcessor;
			//string displayTask(TimeMacro startTime, TimeMacro endTime);
			
			myDataProcessor.addTask(task1);
			myDataProcessor.addTask(task2);
			myDataProcessor.addTask(task3);
			std::string actualDisplay = myDataProcessor.displayTask(start, end);
			ostringstream out;
			out << 1 << ". 1/2/2000  jim" << endl
				<< 2 << ". 1/2/2000  jane" << endl
				<< 3 << ". 1/2/2001  john" << endl;
			std::string expectedDisplay = out.str();
			Assert::AreEqual(expectedDisplay, actualDisplay);
		}

		TEST_METHOD(DeleteTaskTest){
			DataProcessor myDataProcessor;
			int taskNo = 3;
			std::string actualDeleteMessage = myDataProcessor.deleteTask(taskNo);
			std::string expectedDeleteMessage = "breakfast at utown is deleted from BlinkList";
			ostringstream out;
			out << expectedDeleteMessage << endl;
			expectedDeleteMessage = out.str();
			Assert::AreEqual(expectedDeleteMessage, actualDeleteMessage);
		}

		TEST_METHOD(EditTaskTest){
			TimeMacro start(1, 2, 2000);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, begin, end, "jim");
			Data task2(start, begin, end, "john");
			DataProcessor myDataProcessor;
			std::string addMessage = myDataProcessor.addTask(task1);
			std::string actualEditMessage = myDataProcessor.editTask(1, task2);
			std::string expectedEditMessage = "1/2/2000 1:30-2:30 jim is edited";
			Assert::AreEqual(expectedEditMessage, actualEditMessage);
		}

		TEST_METHOD(GetEditMessageTest){
			TimeMacro start(1, 2, 2000);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, begin, end, "jim overslept");
			DataProcessor myDataProcessor;
			std::string actualEditMessage = myDataProcessor.getEditMessage(task1);
			std::string expectedEditMessage = "1/2/2000 1:30-2:30 jim overslept";
			Assert::AreEqual(expectedEditMessage, actualEditMessage);
		}
		
		TEST_METHOD(ConvertDataObjectToStringTest){
			TimeMacro start(1, 2, 2000);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, begin, end, "jim overslept");
			DataProcessor myDataProcessor;
			std::string actualEditMessage = myDataProcessor.convertDataObjectToString(task1);
			std::string expectedEditMessage = "1/2/2000 1:30-2:30 jim overslept";
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
			out << "1. 1/2/2000  jim is smart and stupid" << endl
				<< "2. 1/2/2001  jane is sexy and fat" <<endl;
			std::string expectedTaskList = out.str();
			Assert::AreEqual(expectedTaskList, actualTaskList);
		}

	};
}