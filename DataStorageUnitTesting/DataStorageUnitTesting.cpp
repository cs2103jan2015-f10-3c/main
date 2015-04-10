#include "stdafx.h"
#include "CppUnitTest.h"
#include "Commons.h"
#include "fstream"
#include "InternalStoring.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStorageUnitTesting
{		
	
	TEST_CLASS(LocalStoringUnitTest)
	{
	public:
		
		//test for adding method
		//test for the automatic sorting inside the method
		TEST_METHOD(addMethodTest)
		{
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();
			
			TimeMacro time1(10,04,2015);
			TimeMacro time2(11,04,2015);
			TimeMacro time3(10,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM2(10,0);
			TimeMicro timeM3(9,0);
			TimeMicro timeM4(12,45);
			TimeMicro timeM5(0,0);

			std::string str1 = "task 1";
			std::string str2 = "task 2";
			std::string str3 = "task 3";

			Data data1(time1,timeM1,timeM5,str1); //task 1 10/04/2015 11:30
			Data data2(time2,timeM2,timeM5,str2); //task 2 11/04/2015 10:00
			Data data3(time3,timeM3,timeM4,str3); //task 3 10/04/2015 09:00-12:45

			localStorage->addData(data1);
			localStorage->addData(data2);
			localStorage->addData(data3);

			std::vector<Data> result;
			result = localStorage->getDataList();

			Assert::AreEqual(str3,result[0].getDesc());
			Assert::AreEqual(str1,result[1].getDesc());
			Assert::AreEqual(str2,result[2].getDesc());
		}

		//test deleteData method within boundary
		//and its exception
		TEST_METHOD(deleteData){
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time2(11,04,2015);
			TimeMacro time3(10,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM2(10,0);
			TimeMicro timeM3(9,0);
			TimeMicro timeM4(12,45);
			TimeMicro timeM5(0,0);

			std::string str1 = "task 1";
			std::string str2 = "task 2";
			std::string str3 = "task 3";

			Data data1(time1,timeM1,timeM4,str1); //task 1 10/04/2015 11:30-12:45
			Data data2(time2,timeM2,timeM5,str2); //task 2 11/04/2015 10:00
			Data data3(time3,timeM3,timeM4,str3); //task 3 10/04/2015 09:00-12:45

			localStorage->addData(data1); 
			localStorage->addData(data2);
			localStorage->addData(data3);

			DisplayStorage *displayStorage = DisplayStorage::getInstance();

			//initiate displayList
			//so that we can use taskNo
			displayStorage->getDisplayList(time1,time2); 

			//delete data with 2 as taskNo in displayList
			//expected deleted data is str1
			Data result = localStorage->deleteData(1);  

			Assert::AreEqual(str3,result.getDesc());

			//test for exception
			//taskNo inserted is out of bound
			try{
			localStorage->deleteData(9);
			}
			catch (int errorNo){
				Assert::AreEqual(1,errorNo);
			}
		}

		TEST_METHOD(editData){
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time2(11,04,2015);
			TimeMacro time3(10,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM2(10,0);
			TimeMicro timeM3(9,0);
			TimeMicro timeM4(12,45);
			TimeMicro timeM5(0,0);

			std::string str1 = "task 1";
			std::string str2 = "task 2";
			std::string str3 = "task 3";

			Data data1(time1,timeM1,timeM4,str1); //task 1 10/04/2015 11:30-12:45
			Data data2(time2,timeM2,timeM5,str2); //task 2 11/04/2015 10:00
			Data data3(time3,timeM3,timeM4,str3); //task 3 10/04/2015 09:00-12:45

			data3.updateAlarmMacro(time1);
			data3.updateAlarmMicro(timeM1);
			data3.updateTimeMacroEnd(time2);
			data3.updateCompleteStatus(true);

			localStorage->addData(data1); 
			localStorage->addData(data2);

			DisplayStorage *displayStorage = DisplayStorage::getInstance();

			//initiate displayList
			//so that we can use taskNo
			displayStorage->getDisplayList(time1,time2); 

			//edit by changing Data 1 to Data 3
			Data result = localStorage->editData(1,data3);

			Assert::AreEqual(str3,result.getDesc());

			//test for the exception
			//when out of bound
			try{
			localStorage->editData(9, data2);
			}
			catch (int errorNo){
				Assert::AreEqual(1,errorNo);
			}

		}

		TEST_METHOD(clearDataList){
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time2(11,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM2(10,0);
			TimeMicro timeM5(0,0);

			std::string str1 = "task 1";
			std::string str2 = "task 2";

			Data data1(time1,timeM1,timeM5,str1); //task 1 10/04/2015 11:30
			Data data2(time2,timeM2,timeM5,str2); //task 2 11/04/2015 10:00

			localStorage->addData(data1);
			localStorage->addData(data2);

			//clearing method
			localStorage->clearDataList();

			std::vector<Data> result;
			result = localStorage->getDataList();

			//determine that the list is really empty
			Assert::AreEqual(true,result.empty());

		}

		TEST_METHOD(undoAdd){
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time2(11,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM2(10,0);
			TimeMicro timeM5(0,0);

			std::string str1 = "task 1";
			std::string str2 = "task 2";

			Data data1(time1,timeM1,timeM5,str1); //task 1 10/04/2015 11:30
			Data data2(time2,timeM2,timeM5,str2); //task 2 11/04/2015 10:00

			localStorage->addData(data2);
			localStorage->addData(data1);

			localStorage->undoAdd();

			std::vector<Data> result = localStorage->getDataList();

			Assert::AreEqual(str2,result[0].getDesc());
			
			//determine that there is only one data left
			result.pop_back();
			Assert::AreEqual(true,result.empty());

		}

		//save to default path
		TEST_METHOD(saveData){
			bool result;
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time2(11,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM2(10,0);
			TimeMicro timeM5(0,0);

			std::string str1 = "task 1";
			std::string str2 = "task 2";

			Data data1(time1,timeM1,timeM5,str1); //task 1 10/04/2015 11:30
			Data data2(time2,timeM2,timeM5,str2); //task 2 11/04/2015 10:00
			data1.updateCompleteStatus(false);

			localStorage->addData(data2);
			localStorage->addData(data1);
			result = localStorage->saveData("");
			Assert::AreEqual(true,result);
		}

		//load from default path
		TEST_METHOD(loadData){
			bool result = false;
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->loadData(result, "");

			std::vector<Data> result1 = localStorage->getDataList();
			std::string str1 = "task 1";

			Assert::AreEqual(str1,result1[0].getDesc());
			Assert::AreEqual(true,result);
		}

		TEST_METHOD(directoryCheck){
			bool result;
			LocalStorage *localStorage = LocalStorage::getInstance();
			std::ofstream out;

			//change into your directory
			std::string directory = "C:/NG only";
			result = localStorage->directoryCheck(out, directory);
			Assert::AreEqual(true,result);

			std::ofstream out1;
			//exception test
			directory = "sample";
			result = localStorage->directoryCheck(out1, directory);
			Assert::AreEqual(false,result);

		}

		TEST_METHOD(checkSetPathLocally){
			LocalStorage *localStorage = LocalStorage::getInstance();
			std::string result;
			std::string defaultPath = "";
			//check for default path
			result = localStorage->checkPathName();
			Assert::AreEqual(defaultPath,result);

			std::string pathName = "pathName";
			localStorage->setPathName(pathName);
			result = localStorage->checkPathName();
			Assert::AreEqual(pathName,result);

		}
	};

	//TEST_CLASS(DisplayStorageUnitTesting)
	//{
	//public:
	//		
	////test addData, getDisplayList and updateTaskNo
	//	TEST_METHOD(addGetData)
	//	{
	//		Data myData;
	//		Data yourData;
	//		myData.updateCompleteStatus(false);
	//		yourData.updateDesc("Thurs");
	//		Data hData;

	//		DisplayStorage::addData(myData);
	//		DisplayStorage::addData(yourData);
	//		DisplayStorage::addData(hData);

	//		std::vector<Data> dList;
	//		dList = DisplayStorage::getDisplayList();

	//		std::vector<Data>::iterator iter;
	//		iter=dList.begin();
	//		Assert::AreEqual(false, iter->getCompleteStatus());
	//		Assert::AreEqual(1, iter->getTaskNo());
	//		iter++;
	//		std::string myS = "Thurs";
	//		Assert::AreEqual(myS, iter->getDesc());
	//		Assert::AreEqual(2, iter->getTaskNo());
	//		iter++;
	//		Assert::AreEqual(3, iter->getTaskNo());
	//	}

	//	TEST_METHOD(getUniqueCodeTest){
	//		Data myStory;
	//		Data hello;
	//		myStory.updateDesc("THURS");
	//		hello.updateDesc("lala");
	//		hello.updateUniqueCode(3);

	//		DisplayStorage::clearList();
	//		DisplayStorage::addData(myStory);
	//		DisplayStorage::addData(hello);

	//		Assert::AreEqual (3,DisplayStorage::getUniqueCode(2));

	//	}

	//	TEST_METHOD(getDataTest){
	//		Data myStory;
	//		Data hello;
	//		myStory.updateDesc("THURS");
	//		hello.updateDesc("lala");
	//		hello.updateUniqueCode(3);

	//		DisplayStorage::clearList();
	//		DisplayStorage::addData(myStory);
	//		DisplayStorage::addData(hello);

	//		Data save = DisplayStorage::getData(2);
	//		std::string boredom = "lala";
	//		Assert::AreEqual(boredom, save.getDesc());

	//	}
	//};

}