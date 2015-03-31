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
	static const std::string DEFAULT_SAVE_DIRECTORY;

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
	std::string directoryCheck(std::string& inputDirectory);
	void adjustFormat(std::string& inputDirectory);


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
	
	void saveData(std::string directory);
	void loadData(bool& status, std::string directory);

	//API for DisplayStorage
	std::vector<long long> searchPeriod(TimeMacro startTime, TimeMacro endTime);
	
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
	std::vector<Data>& getDisplayList(DisplayType type, std::string= "");
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
	void retrieveList(ListType type, std::ofstream& out);
};


#endif