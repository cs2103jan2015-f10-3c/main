#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include "Commons.h"


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
	static void addData(Data inData);	
	static void deleteData(int uniqueCode);
	static void getData(int startNo, int endNo);
	static void clearData(TimeMacro startTime, TimeMacro endTime);
	static IterStorage searchPeriod(TimeMacro startTime, TimeMacro endTime);
	//maynotneed
	//	static std::vector<Data> getDataList();


};

class History {
private:

public:

};

class DisplayStorage {
private:
	static std::vector<Data> displayList;

public:
	static std::vector<Data> getDisplayList(TimeMacro startTime, TimeMacro endTime);
	
	static void updateTaskNo();

};

//helper class for searching/clearing/etc methods
class IterStorage {
public:
	static std::vector<Data>::iterator iterBeg;
	static std::vector<Data>::iterator iterEnd;


};


#endif