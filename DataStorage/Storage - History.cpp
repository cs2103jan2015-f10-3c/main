#include "DataStorage.h"

std::string History::latestCommand;
Data History::latestData;
std::vector<Data> History::latestVector;


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
	latestVector = DataBase::getDataList();

}