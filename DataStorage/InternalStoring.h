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
	void parseLoad(std::string strData, int& i);
	std::string tokenizerSlash(std::string& str);
	std::string tokenizerSpace(std::string& str);
	TimeMacro macroParser(std::string tempMacro);
	TimeMicro microParser(std::string tempMicro);
	std::string convertTimeMacroToString(std::string type, int i);
	std::string convertTimeMicroToString(std::string type, int i);


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
	static void displaySearch(std::vector<Data> tempList, std::string keyword);
	static void displayFloat(std::vector<Data> tempList);
	static void displayDone(std::vector<Data> tempList);
	static void enterDataToList(std::vector<long long> timePeriod);
	static std::vector<Data> getListFromLocal();

public:
	//API for facade Class
	static std::vector<Data>& getDisplayList(TimeMacro startTime, TimeMacro endTime);
	static std::vector<Data>& getDisplayList(DisplayType type, std::string);
	static void clearList();
	static Data getData(int taskNo);

	//API for LocalStorage
	static int getUniqueCode(int taskNo);
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