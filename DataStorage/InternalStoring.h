#ifndef INTERNAL_STORING_H_
#define INTERNAL_STORING_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <iterator>
#include <queue>
#include <fstream>
#include <sstream>
#include "Commons.h"

typedef enum ListType {command, feature, heading};
typedef enum DisplayType {search, done, floating};
typedef enum TimeType {begin, end, alarm};

//using singleton pattern
class LocalStorage {
private:

	//Singleton instance and private constructor
	static LocalStorage* instance;
	LocalStorage () {}

	//Private Attribute
	std::vector<Data> dataList;
	int uniqueCodeStore;
	
	//Helper Methods for internal working
	void sortDataList();
	int allocateUniqueCode(int& uniqueCodeStore);
	void allocatePsedoDate();
	void radixDistribute(std::queue<Data> digitQ[], int power);
	void radixCollect(std::queue<Data> digitQ[]);
	Data getData(int uniqueNo);

	//Helper methods for internal working Save and Load
	void writeHeading (std::string fileName, std::ofstream& out);
	void parseLoad(std::string strData, int i, Data& data);
	std::string tokenizerSlash(std::string& str);
	std::string tokenizerSpace(std::string& str);
	TimeMacro macroParser(std::string tempMacro);
	TimeMicro microParser(std::string tempMicro);
	std::string convertTimeMacroToString(TimeType type, int i);
	std::string convertTimeMicroToString(TimeType type, int i);


public: 
	//get instance for singleton pattern
	static LocalStorage* getInstance();

	//API for Facade Class
	void addData(Data& inData);	
	Data deleteData(int taskNo);
	Data editData(int taskNo, Data updatedData);
	void clearDataList();
	void undoAdd();
	std::vector<Data>& getDataList();
	
	void saveData();
	void loadData(bool& status);

	//API for DisplayStorage
	std::vector<long long> searchPeriod(TimeMacro startTime, TimeMacro endTime);
	
	//API for SaveLoad
	int getUniqueCodeStore();
	void updateUniqueCodeStore(int);
};

//using singleton pattern
class History {
private:
	//instance and private constructor for singleton pattern
	static History* instance;
	History() {}

	//private attribute
	std::string latestCommand;
	Data latestData;
	std::vector<Data> latestVector;

public:
	//getInstance for singleton pattern
	static History* getInstance();

	//API for facade class
	std::string getLatestCommand();
	Data getLatestData();
	std::vector<Data>& getLatestVector();
	void updateLatestCommand(std::string inCommand);
	void updateLatestData(Data inData);
	void updateLatestVector();

};

//using singleton pattern
class DisplayStorage {
private:
	//instance and private constructor for singleton pattern
	static DisplayStorage* instance;
	DisplayStorage() {}

	//private attribute
	std::vector<Data> displayList;
	
	//Helper Method for internal working
	void updateTaskNo();
	void displaySearch(std::vector<Data> tempList, std::string keyword);
	void displayFloat(std::vector<Data> tempList);
	void displayDone(std::vector<Data> tempList);
	void enterDataToList(std::vector<long long> timePeriod);
	std::vector<Data> getListFromLocal();

public:
	//getInstance for singleton pattern
	static DisplayStorage* getInstance();

	//API for facade Class
	std::vector<Data>& getDisplayList(TimeMacro startTime, TimeMacro endTime);
	std::vector<Data>& getDisplayList(DisplayType type, std::string);
	void clearList();
	Data getData(int taskNo);

	//API for LocalStorage
	int getUniqueCode(int taskNo);
};

class PrewrittenData {
private:
	std::stringstream retrievedList;

public:
	PrewrittenData() {}

	//API for facade class
	void retrieveList(ListType type);
	std::stringstream getRetrievedList();
};


#endif