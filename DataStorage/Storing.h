#pragma once
#include "InternalStoring.h"

class Storing {
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

	//methods that call PrewrittenData Class
	std::stringstream& retrieveCommandList();
	std::stringstream& retrieveFeatureList();

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

};


