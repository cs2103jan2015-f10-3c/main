#include "stdafx.h"
#include "CppUnitTest.h"
#include "Commons.h"
#include "DataStorage.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStorageUnitTesting
{		
	
	TEST_CLASS(DataBaseUnitTesting)
	{
	public:
		
		TEST_METHOD(UniqueCodeTest)
		{
			// TODO: Your test code here
			Assert::AreEqual(1, DataBase::allocateUniqueCode());
			
			Assert::AreEqual(2, DataBase::allocateUniqueCode());

		}
	};

	TEST_CLASS(DisplayStorageUnitTesting)
	{
	public:
			
	//test addData, getDisplayList and updateTaskNo
		TEST_METHOD(addGetData)
		{
			Data myData;
			Data yourData;
			myData.updateCompleteStatus(false);
			yourData.updateDesc("Thurs");
			Data hData;

			DisplayStorage::addData(myData);
			DisplayStorage::addData(yourData);
			DisplayStorage::addData(hData);

			std::vector<Data> dList;
			dList = DisplayStorage::getDisplayList();

			std::vector<Data>::iterator iter;
			iter=dList.begin();
			Assert::AreEqual(false, iter->getCompleteStatus());
			Assert::AreEqual(1, iter->getTaskNo());
			iter++;
			std::string myS = "Thurs";
			Assert::AreEqual(myS, iter->getDesc());
			Assert::AreEqual(2, iter->getTaskNo());
			iter++;
			Assert::AreEqual(3, iter->getTaskNo());
		}
	};

}