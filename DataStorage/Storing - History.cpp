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
	Logger log;
	log.logging("latestCommand is updated"); // write in log
}

void History::updateLatestData(Data inData){
	latestData = inData;
	Logger log;
	log.logging("latestData is updated"); //write in log
}

void History::updateLatestVector(){
	latestVector.clear(); //clear the container
	LocalStorage *localStorage;
	localStorage = LocalStorage::getInstance();

	latestVector = localStorage->getDataList();
	
	Logger log;
	log.logging("latestVector is updated"); //write in log
}