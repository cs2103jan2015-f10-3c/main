#include "InternalStoring.h"

/////////////////////////////////////////////
//Definition of static attributes

std::string History::latestCommand;
Data History::latestData;
std::vector<Data> History::latestVector;

//End of Definition
////////////////////////////////////////////


std::string History::getLatestCommand(){
	return latestCommand;
}

Data History::getLatestData(){
	return latestData;
}

std::vector<Data>& History::getLatestVector(){
	return latestVector;
}




void History::updateLatestCommand(std::string inCommand){
	latestCommand = inCommand;
}

void History::updateLatestData(Data inData){
	latestData = inData;
}

void History::updateLatestVector(){
	latestVector.clear(); //clear the container
	LocalStorage *localStorage;
	localStorage = LocalStorage::getInstance();

	latestVector = localStorage->getDataList();

}