#pragma once
#include <InternalStorage.h>

class Storing {
public:
	static void addData(Data inData);
	static Data deleteData(int taskNo);
	static Data changeData(int taskNo, Data& inData);
	static Data getData(int taskNo);

	static std::stringstream retrieveCommandList();
	static std::stringstream retrieveFeatureList();

	static std::string getLatestCommand();
	static Data getLatestData();

	
	//use command patter in the future
	static std::vector<Data> display(TimeMacro TBegin, TimeMacro TEnd);
	static std::vector<Data> displaySearch(std::string word);
	static std::vector<Data> displayDone();
	static std::vector<Data> displayfloat();


};
