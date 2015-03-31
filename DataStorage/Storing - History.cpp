#include "InternalStoring.h"

/////////////////////////////////////////////
//Definition of Methods for singleton pattern

History* History::instance = NULL;

History* History::getInstance(){
	if (instance = NULL){
		instance = new History;
	}
	return instance;
}

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