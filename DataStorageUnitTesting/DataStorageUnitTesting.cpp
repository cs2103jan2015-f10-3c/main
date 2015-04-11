#include "stdafx.h"
#include "CppUnitTest.h"
#include "Commons.h"
#include "fstream"
#include "InternalStoring.h"
#include "Storing.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace DataStorageUnitTesting
{		
	//@author A0114002J
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
			data1.updateCompleteStatus(true);

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

		//check whether directory exists
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
		
		//test method for setPath and checkPath
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

	TEST_CLASS(DisplayStorageUnitTesting)
	{
	public:

		//test of getDisplayList
		//with for two time periods
		TEST_METHOD(getDisplayTypePeriod){
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
			displayStorage->clearList();

			//initiate displayList
			std::vector<Data> result;
			result = displayStorage->getDisplayList(time1,time2); 
			
			Assert::AreEqual(str3,result[0].getDesc());
			Assert::AreEqual(str1,result[1].getDesc());
			Assert::AreEqual(str2,result[2].getDesc());

			//for the same time period
			result = displayStorage->getDisplayList(time1,time1);

			Assert::AreEqual(str3,result[0].getDesc());
			Assert::AreEqual(str1,result[1].getDesc());
		}
		
		//test of getDisplayList
		//for completed tasks
		TEST_METHOD(getDisplayListDone){
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

			data2.updateCompleteStatus(true);
			data3.updateCompleteStatus(true);

			localStorage->addData(data1); 
			localStorage->addData(data2);
			localStorage->addData(data3);

			DisplayStorage *displayStorage = DisplayStorage::getInstance();
			displayStorage->clearList();

			//initiate displayList
			std::vector<Data> result;
			result = displayStorage->getDisplayList(done); 
			
			Assert::AreEqual(str2,result[0].getDesc());
			Assert::AreEqual(str3,result[1].getDesc());

		}

		TEST_METHOD(getDisplayListFloat){
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time3(10,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM3(9,0);
			TimeMicro timeM4(12,45);

			std::string str1 = "task 1";
			std::string str2 = "task 2";
			std::string str3 = "task 3";

			Data data1(time1,timeM1,timeM4,str1); //task 1 10/04/2015 11:30-12:45
			Data data3(time3,timeM3,timeM4,str3); //task 3 10/04/2015 09:00-12:45

			Data data2;
			data2.updateDesc(str2); //task 2 floating

			localStorage->addData(data1); 
			localStorage->addData(data2);
			localStorage->addData(data3);

			DisplayStorage *displayStorage = DisplayStorage::getInstance();
			displayStorage->clearList();

			//initiate displayList
			std::vector<Data> result;
			result = displayStorage->getDisplayList(floating); 
			
			Assert::AreEqual(str2,result[0].getDesc());

		}

		TEST_METHOD(getDisplayListSearch){
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time3(10,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM3(9,0);
			TimeMicro timeM4(12,45);

			std::string str1 = "task 1";
			std::string str2 = "task 2";
			std::string str3 = "task 3";

			Data data1(time1,timeM1,timeM4,str1); //task 1 10/04/2015 11:30-12:45
			Data data3(time3,timeM3,timeM4,str3); //task 3 10/04/2015 09:00-12:45

			Data data2;
			data2.updateDesc(str2); //task 2 floating

			localStorage->addData(data1); 
			localStorage->addData(data2);
			localStorage->addData(data3);

			DisplayStorage *displayStorage = DisplayStorage::getInstance();
			displayStorage->clearList();

			//initiate displayList
			std::vector<Data> result;
			std::string keyword = "task";
			result = displayStorage->getDisplayList(search, keyword); 
			
			Assert::AreEqual(str2,result[0].getDesc());
			Assert::AreEqual(str3,result[1].getDesc());
			Assert::AreEqual(str1,result[2].getDesc());
		}

		TEST_METHOD(getData){
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time3(10,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM3(9,0);
			TimeMicro timeM4(12,45);

			std::string str1 = "task 1";
			std::string str2 = "task 2";
			std::string str3 = "task 3";

			Data data1(time1,timeM1,timeM4,str1); //task 1 10/04/2015 11:30-12:45
			Data data3(time3,timeM3,timeM4,str3); //task 3 10/04/2015 09:00-12:45

			Data data2;
			data2.updateDesc(str2); //task 2 floating

			localStorage->addData(data1); 
			localStorage->addData(data2);
			localStorage->addData(data3);

			DisplayStorage *displayStorage = DisplayStorage::getInstance();
			displayStorage->clearList();
			std::string keyword = "task";
			displayStorage->getDisplayList(search, keyword); 
			
			Data result = displayStorage->getData(2);

			Assert::AreEqual(str3,result.getDesc());

			//test for exception
			try{
			result = displayStorage->getData(10);
			}
			catch(int errorNo){
				Assert::AreEqual(1,errorNo);
			}
		}
	};

	TEST_CLASS(HistoryUnitTest){
	public:
		TEST_METHOD(getUpdateLatestCommand){
			std::string command = "add";

			History::updateLatestData(command);
			Assert::AreEqual(command, History::getLatestCommand());
		}

		TEST_METHOD(getUpdateLatestVector){
			LocalStorage *localStorage = LocalStorage::getInstance();
			localStorage->clearDataList();

			TimeMacro time1(10,04,2015);
			TimeMacro time3(10,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM3(9,0);
			TimeMicro timeM4(12,45);

			std::string str1 = "task 1";
			std::string str2 = "task 2";
			std::string str3 = "task 3";

			Data data1(time1,timeM1,timeM4,str1); //task 1 10/04/2015 11:30-12:45
			Data data3(time3,timeM3,timeM4,str3); //task 3 10/04/2015 09:00-12:45

			Data data2;
			data2.updateDesc(str2); //task 2 floating

			localStorage->addData(data1); 
			localStorage->addData(data2);
			localStorage->addData(data3);

			History::updateLatestVector();

			std::vector<Data> result;
			result = History::getLatestVector();

			Assert::AreEqual(str2,result[0].getDesc());
			Assert::AreEqual(str3,result[1].getDesc());
			Assert::AreEqual(str1,result[2].getDesc());

		}
		
		TEST_METHOD(getUpdateLatestData){
			TimeMacro time1(10,04,2015);

			TimeMicro timeM1(11,30);
			TimeMicro timeM4(12,45);

			std::string str1 = "task 1";

			Data data1(time1,timeM1,timeM4,str1); //task 1 10/04/2015 11:30-12:45

			History::updateLatestData(data1);

			Assert::AreEqual(str1,History::getLatestData().getDesc());

		}

	};

	TEST_CLASS(PrewrittenDataUnitTest){
		TEST_METHOD(retrieveListAllCommands){
			PrewrittenData prewrittenData;
			try{
				std::string result;
				result = prewrittenData.retrieveList(command);
				Assert::AreEqual(false, result.empty());
			}
			catch(int errorNo){
				Assert::AreEqual(2,errorNo);
			}
		}

		TEST_METHOD(retrieveListAllFeatures){
			PrewrittenData prewrittenData;
			try{
				std::string result;
				result = prewrittenData.retrieveList(feature);
				Assert::AreEqual(false, result.empty());
			}
			catch(int errorNo){
				Assert::AreEqual(2,errorNo);
			}
		}

		TEST_METHOD(retrieveListPath){
			PrewrittenData prewrittenData;
			try{
				std::string result;
				result = prewrittenData.retrieveList(path);
				Assert::AreEqual(false, result.empty());
			}
			catch(int errorNo){
				Assert::AreEqual(2,errorNo);
			}
		}
	};

	TEST_CLASS(FacadeUnitTest){
		TEST_METHOD(retrieveFeatureList){
			Storing storing;
			std::string result;
			try{
				result = storing.retrieveFeatureList();
				Assert::AreEqual(false,result.empty());
			}
			catch(std::string str){
				Assert::AreEqual(false, str.empty());
			}

			
		}

		TEST_METHOD(findPathName){
			Storing storing;
			bool result;
			try{
				result = storing.findPathName();
				Assert::AreEqual(true,result);
			}
			catch(std::string str){
				Assert::AreEqual(false, str.empty());
			}
		}
		
		
		TEST_METHOD(loadData){
			Storing storing;
			bool status;
			std::string directory = "";
			storing.loadData(status, directory);
		}
		
		//test for exception
		TEST_METHOD(getData){
			Storing storing;
			try{
				storing.getData(1000);
			}
			catch(std::string errorMessage){
				Assert::AreEqual(false,errorMessage.empty());
			}
		}
	};
	//bool Storing::findPathName(){
	//	void Storing::adjustRetrievedPath(std::string& pathName){
	//		void Storing::loadData(bool& status, std::string directory){
	//			Data Storing::getData(int taskNo){//exception
}