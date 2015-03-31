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
	return History::getLatestCommand();
}

Data Storing::getLatestData(){
	return History::getLatestData();
}

std::vector<Data> Storing::getLatestVector(){
	return History::getLatestVector();
}


Data Storing::getData(int taskNo){
	return DisplayStorage::getData(taskNo);
}

std::vector<Data> Storing::display(TimeMacro tBegin, TimeMacro tEnd){
	return DisplayStorage::getDisplayList(tBegin, tEnd);
}

std::vector<Data> Storing::displaySearch(std::string word){
	return DisplayStorage::getDisplayList(search, word);
}

std::vector<Data> Storing::displayDone(){
	return DisplayStorage::getDisplayList(done,"");
}

std::vector<Data> Storing::displayfloat(){
	return DisplayStorage::getDisplayList(floating,"");
}

void Storing::clearDisplayList(){
	return DisplayStorage::clearList();
}



