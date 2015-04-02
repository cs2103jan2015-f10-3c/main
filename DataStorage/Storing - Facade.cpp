#include "Storing.h"

//<<Interface>>
//go into specific methods implementation
//in different classes
//for explanation on methods

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


std::string Storing::retrieveCommandList(){
	PrewrittenData prewrittenData;
	return prewrittenData.retrieveList(command);
}

std::string Storing::retrieveFeatureList(){
	PrewrittenData prewrittenData;
	return prewrittenData.retrieveList(feature);
}

void Storing::loadData(bool& status, std::string directory){
	LocalStorage *localStorage = LocalStorage::getInstance();
	localStorage->loadData(status, directory);
}

bool Storing::saveData(std::string directory){
	LocalStorage *localStorage = LocalStorage::getInstance();
	return localStorage->saveData(directory);
}




std::string Storing::getLatestCommand(){
	return History::getLatestCommand();
}

Data Storing::getLatestData(){
	return History::getLatestData();
}

std::vector<Data>& Storing::getLatestVector(){
	return History::getLatestVector();
}


Data Storing::getData(int taskNo){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getData(taskNo);
}

std::vector<Data>& Storing::display(TimeMacro tBegin, TimeMacro tEnd){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getDisplayList(tBegin, tEnd);
}

std::vector<Data>& Storing::displaySearch(std::string word){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getDisplayList(search, word);
}

std::vector<Data>& Storing::displayDone(){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getDisplayList(done);
}

std::vector<Data>& Storing::displayfloat(){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->getDisplayList(floating);
}

void Storing::clearDisplayList(){
	DisplayStorage *display = DisplayStorage::getInstance();
	return display->clearList();
}



