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

		TEST_METHOD(SearchPeriodTest)
		{
			TimeMacro time1;
			TimeMacro time2;

			time1.updateDate(06);
			time1.updateMonth(01);
			time1.updateYear(2014);
			time2.updateDate(30);
			time2.updateMonth(04);
			time2.updateYear(2016);

			TimeMacro time3;
			TimeMacro time4;
			TimeMacro time5;
			TimeMacro time6;

			time3.updateDate(05);
			time3.updateMonth(01);
			time3.updateYear(2015);
			time4.updateDate(30);
			time4.updateMonth(03);
			time4.updateYear(2015);
			time5.updateDate(01);
			time5.updateMonth(05);
			time5.updateYear(2015);
			time6.updateDate(30);
			time6.updateMonth(06);
			time6.updateYear(2015);

			Data data1;
			Data data2;
			Data data3;
			Data data4;

			data1.updateTimeMacroBeg(time3);
			data2.updateTimeMacroBeg(time4);
			data3.updateTimeMacroBeg(time5);
			data4.updateTimeMacroBeg(time6);
			data1.updateDesc("LOL");
			data2.updateDesc("niahaha");
			data3.updateDesc("buahamama");
			data4.updateDesc("killingmeslowly");
			
			DataBase::addData(data1);
			DataBase::addData(data2);
			DataBase::addData(data3);
			DataBase::addData(data4);

			DataBase::searchPeriod(time5,time5);

			std::vector<Data>::iterator iter1 = IterStorage::getIterBeg();
			std::vector<Data>::iterator iter2 = IterStorage::getIterEnd();
			std::string hex = "buahamama";
			std::string lampu = "buahamama";

			Assert::AreEqual(hex,iter1->getDesc());
			Assert::AreEqual(lampu,iter2->getDesc());

		}

		TEST_METHOD(getDataReturnIterTest){
			DataBase::addData(

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

		TEST_METHOD(getUniqueCodeTest){
			Data myStory;
			Data hello;
			myStory.updateDesc("THURS");
			hello.updateDesc("lala");
			hello.updateUniqueCode(3);

			DisplayStorage::clearList();
			DisplayStorage::addData(myStory);
			DisplayStorage::addData(hello);

			Assert::AreEqual (3,DisplayStorage::getUniqueCode(2));

		}

		TEST_METHOD(getDataTest){
			Data myStory;
			Data hello;
			myStory.updateDesc("THURS");
			hello.updateDesc("lala");
			hello.updateUniqueCode(3);

			DisplayStorage::clearList();
			DisplayStorage::addData(myStory);
			DisplayStorage::addData(hello);

			Data save = DisplayStorage::getData(2);
			std::string boredom = "lala";
			Assert::AreEqual(boredom, save.getDesc());

		}
	};

}