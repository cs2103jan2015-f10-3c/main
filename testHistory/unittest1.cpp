#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testHistory
{		
	TEST_CLASS(testHistory)
	{
	public:
		
		TEST_METHOD(testLatestCommand)
		{
			History::updateLatestCommand ("add");
			std::string expectedOutput = "add";
			Assert::AreEqual (History::getLatestCommand(), expectedOutput);
			// TODO: Your test code here
		}

		TEST_METHOD(testLatestData)
		{
			Data myData;
			TimeMacro timeMacro;
			TimeMicro timeMicro;
			timeMacro.updateDate (5);
			timeMicro.updateHour (6);
			myData.updateDesc ("breakfast");
			myData.updateTaskNo (3);
			myData.updateTimeMicroBeg (timeMicro);
			myData.updateTimeMacroEnd (timeMacro);

			History::updateLatestData (myData);
			History::getLatestData ();


			std::string expectedDesc = "breakfast";
			Assert::AreEqual ((History::getLatestData ()).getDesc (), expectedDesc);
			Assert::AreEqual ((History::getLatestData ()).getTaskNo (), 3);
			Assert::AreEqual ((History::getLatestData ()).getTimeMicroBeg ().getHour (), 6);
			Assert::AreEqual ((History::getLatestData ()).getTimeMacroEnd ().getDate (), 5);
			// TODO: Your test code here
		}
		/*
		TEST_METHOD(testLatestVector)
		{

			
			std::vector<Data> myVector;

			Data myData1;
			TimeMacro timeMacro1;
			TimeMicro timeMicro1;
			timeMacro1.updateDate (1);
			timeMicro1.updateHour (2);
			myData1.updateDesc ("breakfast");
			myData1.updateTaskNo (5);
			myData1.updateTimeMicroBeg (timeMicro1);
			myData1.updateTimeMacroEnd (timeMacro1);

			Data myData2;
			TimeMacro timeMacro2;
			TimeMicro timeMicro2;
			timeMacro2.updateDate (5);
			timeMicro2.updateHour (6);
			myData2.updateDesc ("dinner");
			myData2.updateTaskNo (3);
			myData2.updateTimeMicroBeg (timeMicro2);
			myData2.updateTimeMacroEnd (timeMacro2);


			DataBase::addData(myData1);
			DataBase::addData(myData2);

			History::updateLatestVector ();
			
			std::vector<Data> latestVector = History::getLatestVector();

			std::string expectedDesc1 = "breakfast";
			std::string expectedDesc2 = "dinner";
			Assert::AreEqual (latestVector[0].getDesc (), expectedDesc1);	
			Assert::AreEqual (latestVector[0].getTaskNo (), 5);
			Assert::AreEqual ((latestVector[0].getTimeMicroBeg ()).getHour (), 2);
			Assert::AreEqual ((latestVector[0].getTimeMacroEnd ()).getDate (), 1);

			Assert::AreEqual (latestVector[1].getDesc (), expectedDesc2);	
			Assert::AreEqual (latestVector[1].getTaskNo (), 3);
			Assert::AreEqual ((latestVector[1].getTimeMicroBeg ()).getHour (), 6);
			Assert::AreEqual ((latestVector[1].getTimeMacroEnd ()).getDate (), 5);

		}*/

	};
}