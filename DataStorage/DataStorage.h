#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include <fstream>
#include <sstream>
#include "Commons.h"


class DataBase {
private:
	friend class DisplayStorage;
	friend class DataBaseUnitTesting;
	friend class DataProcessing;

	//Private Attribute
	static std::vector<Data> dataList;
	static int uniqueCodeStore;

	//Private method
	static void sortDataList();
	static int allocateUniqueCode(int& uniqueCodeStore);
	static void allocatePsedoDate();
	static void radixDistribute(std::queue<Data> digitQ[], int power);
	static void radixCollect(std::queue<Data> digitQ[]);
	static Data getData(int uniqueNo);

	static void writeHeading (std::string fileName, std::ofstream& out);
	static void parseLoad(std::string strData, int& i);
	static std::string tokenizerSlash(std::string& str);
	static std::string tokenizerSpace(std::string& str);
	static TimeMacro macroParser(std::string tempMacro);
	static TimeMicro microParser(std::string tempMicro);
	static std::string convertTimeMacroToString(std::string type, int i);
	static std::string convertTimeMicroToString(std::string type, int i);



public: 
	//API for Data Processing
	static void addData(Data& inData);	
	static Data deleteData(int taskNo);
	static Data editData(int taskNo, Data updatedData);
	static Data clearData(TimeMacro startTime, TimeMacro endTime);
	static std::vector<Data> getDataList();
	static void clearDataList();
	static void saveData();
	static void loadData();

	//Helper method for DisplayStorage
	static std::vector<long long> searchPeriod(TimeMacro startTime, TimeMacro endTime);
	
};

class History {
private:
	//private attribute
	static std::string latestCommand;
	static Data latestData;
	static std::vector<Data> latestVector;

public:
	//API for Data Processing
	static std::string getLatestCommand();
	static Data getLatestData();
	static std::vector<Data> getLatestVector();
	static void updateLatestCommand(std::string inCommand);
	static void updateLatestData(Data inData);
	static void updateLatestVector();

};

class DisplayStorage {
private:
	//private attribute
	static std::vector<Data> displayList;
	
	//private method
	static void updateTaskNo();

public:
	//API for Data Processing
	static std::vector<Data>& getDisplayList(TimeMacro startTime, TimeMacro endTime);
	static std::vector<Data> getDisplayList();
	static void addData(Data inData);
	static void clearList();

	//Helper method for DataBase
	static int getUniqueCode(int taskNo);
	static Data getData(int taskNo);

};




#endif