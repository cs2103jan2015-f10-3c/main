//@author A0114002J

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

typedef enum ListType {command, feature, heading, path};
typedef enum DisplayType {search, done, floating};
typedef enum TimeType {begin, end, alarm};


//acts as internal database
//all data entry is recorded in this class
//saving and loading is done into and from this class.
//using singleton pattern
class LocalStorage {
private:
	friend class LocalStoringUnitTest;

	//Magic String declarations
	//used in Storing - local.cpp
	static const char LOGGING_MESSAGE_1[100];
	static const char LOGGING_MESSAGE_2[100];
	static const char LOGGING_MESSAGE_3[100];
	static const char LOGGING_MESSAGE_4[100];
	static const char LOGGING_MESSAGE_5[100];
	static const char LOGGING_MESSAGE_6[100];
	static const char LOGGING_MESSAGE_7[100];
	static const char ADD[10];
	static const char EDIT[10];
	static const char DELETE_WORD[10];
	static const char CLEAR[10];
	static const int TIME_MICRO_DEFAULT;
	static const int TIME_MACRO_DEFAULT;
	static const int TIME_MICRO_ADJUSTMENT;
	static const int NO_OF_DIGITS;
	static const int LENGTH_OF_PSEDODATE;
	static const int ZERO;
	static const int TEN_THOUSAND;
	static const int ONE_MILLION;
	static const int HUNDRED_MILLION;
	
	//used in Storing - SaveLoad.cpp
	static const char DEFAULT_SAVE_DIRECTORY[100];
	static const char SLASH[10];
	static const char TAB[10];
	static const char TRUE_STRING[10];
	static const char FALSE_STRING[10];
	static const char EMPTY_STRING[10];

	//Singleton instance and private constructor
	static LocalStorage* instance;
	LocalStorage () {}

	//Private Attribute
	std::vector<Data> dataList;
	int uniqueCodeStore;
	std::string pathName;
	
	//Helper Methods for internal working in Storing - Local.cpp
	std::vector<Data> deleteDataOfUniqueCode(int uniqueCode);
	long long allocateTimeMacroToPsedoDate(TimeMacro time);
	long long allocateTimeMicroToPsedoDate(long long time, TimeMicro tMicro);
	std::vector<long long> searchRelevantDates(long long pStartTime, long long pEndTime);
	void sortDataList();
	int allocateUniqueCode(int& uniqueCodeStore);
	void allocatePsedoDate();
	void radixDistribute(std::queue<Data> digitQ[], int power);
	void radixCollect(std::queue<Data> digitQ[]);
	Data getData(int uniqueNo);
	Data updateData(Data dataToEdit, Data updatedData);
	void checkTaskNoValidity(int taskNo);

	//Helper methods for internal working in Storing - SaveLoad.cpp
	void writeHeading (std::string fileName, std::ofstream& out);
	void parseLoad(std::string strData, int i, Data& data);
	std::string tokenizerSlash(std::string& str);
	std::string tokenizerSpace(std::string& str);
	TimeMacro macroParser(std::string tempMacro);
	TimeMicro microParser(std::string tempMicro);
	std::string convertTimeMacroToString(TimeType type, int i);
	std::string convertTimeMicroToString(TimeType type, int i);
	void adjustFormat(std::string& inputDirectory);
	std::string getPathName();


public: 
	//get instance for singleton pattern
	static LocalStorage* getInstance();
	
	//API for DisplayStorage in Storing - Local.cpp
	std::vector<long long> searchPeriod(TimeMacro startTime, TimeMacro endTime);

	//API for PrewrittenData in Storing - SaveLoad.cpp
	void setPathName(std::string inPathName);

	//API for Facade Class in Storing - Local.cpp
	void addData(Data& inData);	
	Data deleteData(int taskNo);
	Data editData(int taskNo, Data updatedData);
	void clearDataList();
	void undoAdd();
	std::vector<Data>& getDataList();
	
	//API for Facade Class in Storing - SaveLoad.cpp
	bool saveData(std::string directory);
	void loadData(bool& status, std::string directory);
	bool directoryCheck(std::ofstream& out, std::string directory);
	std::string checkPathName();
	void firstSave();

};


//an internal storage 
//for storing latest data.
//Singleton method was tried
//but was not implemented
//as it caused unsolvable bug
class History {
private:
	static const char LOGGING_MESSAGE_1[100];
	static const char LOGGING_MESSAGE_2[100];
	static const char LOGGING_MESSAGE_3[100];

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




//container to store list to be displayed
//using singleton pattern
class DisplayStorage {
private:
	static const char LOGGING_MESSAGE_1[100];
	static const char LOGGING_MESSAGE_2[100];
	static const char DEFAULT_DESCRIPTION[10];
	static const int MAX_DISPLAY_FLOATING;
	static const int MAX_DISPLAY_TIMED;

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
	void checkTaskNoValidity(int taskNo);
	void displayDoneFloating(std::vector<Data> tempList);
	void displayDoneTimed(std::vector<Data> tempList);

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
	int getListSize();
};





//to retrieve data from prewritten .txt files
class PrewrittenData {
private:
	static const char ALL_COMMANDS_FILE[100];
	static const char ALL_FEATURES_FILE[100];
	static const char HEADING_TEMPLATE_FILE[100];
	static const char PATH_FILE[100];
	static const char LOGGING_MESSAGE_1[100];
	static const char LOGGING_MESSAGE_2[100];
	static const char LOGGING_MESSAGE_3[100];
	static const char DIRECTORY_FILE[100];

	std::string retrievedList;
	std::string txtFile;

	//helper method
	std::string determineListType(ListType type);

public:
	PrewrittenData() {}

	//API for facade class
	std::string retrieveList(ListType type);
	void retrieveList(ListType type, std::ofstream& out);
	void savePath(std::string inPath);
};



#endif