#include "InternalStoring.h"

/////////////////////////////////////////////
//Definition of static attributes

std::string History::latestCommand;
Data History::latestData;
std::vector<Data> History::latestVector;

//magic string definition
const char History::LOGGING_MESSAGE_1[] = "latestCommand is update";
const char History::LOGGING_MESSAGE_2[] = "latestData is updated";
const char History::LOGGING_MESSAGE_3[] = "latestVector is updated";

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