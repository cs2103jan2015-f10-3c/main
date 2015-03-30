#pragma once
#include "InternalStoring.h"

class Storing {
public:
	static void addData(Data&);
	static Data deleteData(int taskNo);
	static Data changeData(int taskNo, Data& inData);
	static void clearDataList();
	static void undoAdd();

	static std::stringstream retrieveCommandList();
	static std::stringstream retrieveFeatureList();
	static void loadData(bool& status);
	static void saveData();

	static std::string getLatestCommand();
	static Data getLatestData();
	static std::vector<Data> getLatestVector();
	
	static Data getData(int taskNo);
	static std::vector<Data> display(TimeMacro tBegin, TimeMacro tEnd);
	static std::vector<Data> displaySearch(std::string word);
	static std::vector<Data> displayDone();
	static std::vector<Data> displayfloat();
	static void clearDisplayList();


};


