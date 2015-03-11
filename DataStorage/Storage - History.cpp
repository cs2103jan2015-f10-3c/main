#include "DataStorage.h"

std::string History::getLatestCommand(){
	return latestCommand;
}

Data History::getLatestData(){
	return latestData;
}

std::vector<Data> History::getLatestVector(){
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

	std::vector<Data>::iterator iter;

	for(iter = IterStorage::getIterBeg(); iter <= IterStorage::getIterEnd(); iter++){
		latestVector.push_back(*iter);
	}
}