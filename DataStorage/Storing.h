#pragma once
#include "InternalStoring.h"

//facade class for all InternalStorage classes
class Storing {
private:
	static const char Storing::LOGGING_MESSAGE_1[100];
	static const char Storing::LOGGING_MESSAGE_2[100];
	static const char Storing::ERROR_MESSAGE_1[100];
	static const char Storing::ERROR_MESSAGE_2[100];
	static const char Storing::ERROR_MESSAGE_3[100]; 

	void adjustRetrievedPath(std::string& pathName);

public:
	Storing() {}

	//methods that call LocalStorage class
	void addData(Data&);
	Data deleteData(int taskNo);
	Data changeData(int taskNo, Data& inData);
	void clearDataList();
	void undoAdd();
	void loadData(bool& status , std::string directory = "");
	bool saveData(std::string directory = "");
	bool saveUserPathName(std::string userPathName);

	//methods that call PrewrittenData Class
	std::string retrieveCommandList();
	std::string retrieveFeatureList();
	bool findPathName();

	//methods that call History Class
	std::string getLatestCommand();
	Data getLatestData();
	std::vector<Data>& getLatestVector();
	
	//methods that call DisplayStorage Class
	Data getData(int taskNo);
	std::vector<Data>& display(TimeMacro tBegin, TimeMacro tEnd);
	std::vector<Data>& displaySearch(std::string word);
	std::vector<Data>& displayDone();
	std::vector<Data>& displayfloat();
	void clearDisplayList();
	
	//method for exception handling
	void handleException(int errorNo);
};


