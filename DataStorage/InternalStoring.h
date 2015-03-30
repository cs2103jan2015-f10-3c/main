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

class LocalStorage {
private:
	friend class DisplayStorage;
	friend class SaveLoad;

	//Private Attribute
	static std::vector<Data> dataList;
	static int uniqueCodeStore;

	//Helper Methods for internal working
	static void sortDataList();
	static int allocateUniqueCode(int& uniqueCodeStore);
	static void allocatePsedoDate();
	static void radixDistribute(std::queue<Data> digitQ[], int power);
	static void radixCollect(std::queue<Data> digitQ[]);
	static Data getData(int uniqueNo);


public: 
	//API for Facade Class
	static void addData(Data& inData);	
	static Data deleteData(int taskNo);
	static Data editData(int taskNo, Data updatedData);
	static void clearDataList();
	static void undoAdd();
	static std::vector<Data>& getDataList();

	//API for DisplayStorage
	static std::vector<long long> searchPeriod(TimeMacro startTime, TimeMacro endTime);
	
	//API for SaveLoad
	static int getUniqueCodeStore();
	static void updateUniqueCodeStore(int);
};

class History {
private:
	//private attribute
	static std::string latestCommand;
	static Data latestData;
	static std::vector<Data> latestVector;

public:
	//API for facade class
	static std::string getLatestCommand();
	static Data getLatestData();
	static std::vector<Data>& getLatestVector();
	static void updateLatestCommand(std::string inCommand);
	static void updateLatestData(Data inData);
	static void updateLatestVector();

};

class DisplayStorage {
private:
	//private attribute
	static std::vector<Data> displayList;
	
	//Helper Method for internal working
	static void updateTaskNo();
	static void displaySearch(std::string keyword);
	static void displayFloat();
	static void displayDone();
	static void enterDataToList(std::vector<long long> timePeriod);

public:
	//API for facade Class
	static std::vector<Data>& getDisplayList(TimeMacro startTime, TimeMacro endTime);
	static std::vector<Data>& getDisplayList(DisplayType type, std::string);
	static void clearList();
	static Data getData(int taskNo);

	//API for LocalStorage
	static int getUniqueCode(int taskNo);
};

class SaveLoad {
private:
	//Helper methods for internal working
	static void writeHeading (std::string fileName, std::ofstream& out);
	static void parseLoad(std::string strData, int& i);
	static std::string tokenizerSlash(std::string& str);
	static std::string tokenizerSpace(std::string& str);
	static TimeMacro macroParser(std::string tempMacro);
	static TimeMicro microParser(std::string tempMicro);
	static std::string convertTimeMacroToString(std::string type, int i);
	static std::string convertTimeMicroToString(std::string type, int i);

public:
	//API for facade class
	static std::stringstream retrieveList(ListType type);
	static void saveData();
	static void loadData(bool& status);

};


#endif