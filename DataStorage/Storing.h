#pragma once
#include "InternalStoring.h"

class Storing {
public:
	Storing() {}

	void addData(Data&);
	Data deleteData(int taskNo);
	Data changeData(int taskNo, Data& inData);
	void clearDataList();
	void undoAdd();
	
	std::stringstream retrieveCommandList();
	std::stringstream retrieveFeatureList();
	void loadData(bool& status);
	void saveData();

	std::string getLatestCommand();
	Data getLatestData();
	std::vector<Data> getLatestVector();
	
	Data getData(int taskNo);
	std::vector<Data> display(TimeMacro tBegin, TimeMacro tEnd);
	std::vector<Data> displaySearch(std::string word);
	std::vector<Data> displayDone();
	std::vector<Data> displayfloat();
	void clearDisplayList();

};


