#include "Storing.h"

void Storing::addData(Data& inData){
	LocalStorage *localStorage = LocalStorage::getInstance();
	localStorage->addData(inData);
}

Data Storing::deleteData(int taskNo){
	LocalStorage *localStorage = LocalStorage::getInstance();
	return localStorage->deleteData(taskNo);
}

Data Storing::changeData(int taskNo, Data& inData){
	LocalStorage *localStorage = LocalStorage::getInstance();
	return localStorage->editData(taskNo, inData);
}

void Storing::clearDataList(){
	LocalStorage *localStorage = LocalStorage::getInstance();
	localStorage->clearDataList();
}

void Storing::undoAdd(){
	LocalStorage *localStorage = LocalStorage::getInstance();
	localStorage->undoAdd();
}


std::stringstream Storing::retrieveCommandList(){
	PrewrittenData prewrittenData;
	prewrittenData.retrieveList(command);

	return prewrittenData.getRetrievedList();
}

std::stringstream Storing::retrieveFeatureList(){
	PrewrittenData prewrittenData;
	prewrittenData.retrieveList(feature);

	return prewrittenData.getRetrievedList();
}

void Storing::loadData(bool& status){
	LocalStorage *localStorage = LocalStorage::getInstance();
	return localStorage->loadData(status);
}

void Storing::saveData(){
	LocalStorage *localStorage = LocalStorage::getInstance();
	return localStorage->saveData();
}




std::string Storing::getLatestCommand(){
	History *history = History::getInstance();
	return history->getLatestCommand();
}

Data Storing::getLatestData(){
	History *history = History::getInstance();
	return history->getLatestData();
}

std::vector<Data> Storing::getLatestVector(){
	History *history = History::getInstance();
	return history->getLatestVector();
}


Data Storing::getData(int taskNo){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getData(taskNo);
}

std::vector<Data> Storing::display(TimeMacro tBegin, TimeMacro tEnd){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getDisplayList(tBegin, tEnd);
}

std::vector<Data> Storing::displaySearch(std::string word){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getDisplayList(search, word);
}

std::vector<Data> Storing::displayDone(){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getDisplayList(done,"");
}

std::vector<Data> Storing::displayfloat(){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getDisplayList(floating,"");
}

void Storing::clearDisplayList(){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->clearList();
}



