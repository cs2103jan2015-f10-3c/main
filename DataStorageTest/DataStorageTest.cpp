#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStorageTest
{		
	TEST_CLASS(DataStorageTest)
	{
	public:
		
		TEST_METHOD(AllocatePsedoDateTest)
		{
			TimeMacro date(3, 12, 1995);
			TimeMacro start(1, 2, 2000);
			TimeMicro begin(1,30);
			TimeMicro end(2, 30);
			Data task1(start, begin, end, "jim overslept");
			Data task2("jim drank monster energy");
			DataBase::addData(task1);
			DataBase::addData(task2);
			DataBase::allocatePsedoDate();
			std::vector<Data> dataList = DataBase::getDataList();
			Data actualTask = dataList[0];
			/*std::string actualDesc = actualTask.getDesc();
			std::string expectedDesc = "jim overslept";
			Assert::AreEqual(expectedDesc, actualDesc);*/
			int actualPsedoDate = actualTask.getPsedoDate();
			int expectedPsedoDate = 0;
			Assert::AreEqual(expectedPsedoDate, actualPsedoDate);
		}
		
	};
}