#include "Storing.h"

//go into specific methods implementation
//in different classes
//for explanation on methods

void Storing::addData(Data& inData){
	LocalStorage *localStorage = LocalStorage::getInstance();
	localStorage->addData(inData);
}

Data Storing::deleteData(int taskNo){
	try{
	LocalStorage *localStorage = LocalStorage::getInstance();
	return localStorage->deleteData(taskNo);
	}
	catch (int errorNo){
		Logger log;
		log.logging("Exception is caught in Storage Facade class");
		handleException(errorNo);
	}
}

Data Storing::changeData(int taskNo, Data& inData){
	try{
	LocalStorage *localStorage = LocalStorage::getInstance();
	return localStorage->editData(taskNo, inData);
	}
	catch (int errorNo){
		Logger log;
		log.logging("Exception is caught in Storage Facade class");
		handleException(errorNo);
	}
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
	try{
		PrewrittenData prewrittenData;
		return prewrittenData.retrieveList(command);
	} catch (int errorNo){
		Logger log;
		log.logging("Exception is caught in Storage Facade class");
		handleException(errorNo);
	}
}

std::string Storing::retrieveFeatureList(){
	try{
		PrewrittenData prewrittenData;
		return prewrittenData.retrieveList(feature);
	} catch (int errorNo){
		Logger log;
		log.logging("Exception is caught in Storage Facade class");
		handleException(errorNo);
	}
}

bool Storing::findPathName(){
	try {
		PrewrittenData prewrittenData;
		return prewrittenData.checkPath();
	} catch (int errorNo){
		Logger log;
		log.logging("Exception is caught in Storage Facade class");
		handleException(errorNo);
	}
}

bool Storing::saveUserPathName(std::string userPathName){
	bool status;
	LocalStorage *localStorage = LocalStorage::getInstance();
	status = localStorage->saveData(userPathName);
	
	PrewrittenData prewrittenData;
	if(status == true){
		prewrittenData.savePath(userPathName);
	}

	return status;
}

void Storing::loadData(bool& status, std::string directory){
	LocalStorage *localStorage = LocalStorage::getInstance();
	directory = localStorage->checkPathName();
	localStorage->loadData(status, directory);
}

bool Storing::saveData(std::string directory){
	LocalStorage *localStorage = LocalStorage::getInstance();
	directory = localStorage->checkPathName();
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
	try{
		DisplayStorage *display = DisplayStorage::getInstance();
		return display->getData(taskNo);
	}
	catch (int errorNo){
		Logger log;
		log.logging("Exception is caught in Storage Facade class");
		handleException(errorNo);
	}
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

void Storing::handleException(int errorNo){
	std::string errorMessage;
	Logger log;
	log.logging("Exception is thrown from Storage Facade class");

	switch (errorNo){
	case 1:
		errorMessage = "Please enter a valid task number. \n";
		throw errorMessage;
		break;
	case 2:
		errorMessage = "Data could not be found. \n";
		throw errorMessage;
		break;
	default:
		errorMessage = "Exception of unknown type is caught. \n";
		break;

	}

}

