#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "Commons.h"
#include <iterator>
#include <queue>

class DataBase {
private:
	//Private Attribute
	static std::vector<Data> dataList;
	static int uniqueNo;

	//Private method
	static void updateTaskNo();
	static void allocateUniqueCode(Data inData);
	static void sortDataList();
	static void allocatePsedoDate();
	static void radixDistribute(std::queue<Data> digitQ[], int power);
	static void radixCollect(std::queue<Data> digitQ[]);
	static std::vector<Data>::iterator getData(int uniqueNo);


public: 
	//API for Data Processing
	static Data addData(Data inData);	
	static Data deleteData(int taskNo);
	static Data editData(int taskNo, Data updatedData);
	static Data clearData(TimeMacro startTime, TimeMacro endTime);
	static std::vector<Data> getDataList();
	
	//Helper method for DisplayStorage
	static void searchPeriod(TimeMacro startTime, TimeMacro endTime);
	
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
	static std::vector<Data> getDisplayList(TimeMacro startTime, TimeMacro endTime);
	static std::vector<Data> getDisplayList();
	static void addData(Data inData);
	
	//Helper method for DataBase
	static int getUniqueCode(int taskNo);
	static Data getData(int taskNo);

};

//helper class for searching/clearing/etc methods
//Store two iteration
//Used by class DataBase and DisplayStorage
class IterStorage {
private:
	static std::vector<Data>::iterator iterBeg;
	static std::vector<Data>::iterator iterEnd;

public:
	static void updateIterBeg(std::vector<Data>::iterator iBeg) {
		iterBeg = iBeg; 
	}
	static void updateIterEnd(std::vector<Data>::iterator iEnd) {
		iterEnd = iEnd;
	}
	static std::vector<Data>::iterator getIterBeg() {
		return iterBeg;
	}
	static std::vector<Data>::iterator getIterEnd() {
		return iterEnd;
	}
	
};


#endif