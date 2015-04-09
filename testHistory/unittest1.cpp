//@author A0093895J
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
		}
		

	};
}