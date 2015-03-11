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
	static std::vector<Data> dataList;
	static int uniqueNo;

	static void updateTaskNo();
	static void allocateUniqueCode(Data inData);
	static void sortDataList();
	static void allocatePsedoDate();
	static void radixDistribute(std::queue<Data> digitQ[], int power);
	static void radixCollect(std::queue<Data> digitQ[]);


public: 
	static Data addData(Data inData);	
	static void deleteData(int uniqueCode);
	static void getData(int startNo, int endNo);
	static Data clearData(TimeMacro startTime, TimeMacro endTime);
	static void searchPeriod(TimeMacro startTime, TimeMacro endTime);
	static std::vector<Data> getDataList();


};

class History {
private:

public:

};

class DisplayStorage {
private:
	static std::vector<Data> displayList;
	static void updateTaskNo();

public:
	static std::vector<Data> getDisplayList(TimeMacro startTime, TimeMacro endTime);
	static std::vector<Data> getDisplayList();
	static void addData(Data inData);




};

//helper class for searching/clearing/etc methods
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