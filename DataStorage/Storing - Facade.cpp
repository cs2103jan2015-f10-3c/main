//@author A0114002J

#include "Storing.h"

//go into specific methods implementation
//in different classes
//for explanation on methods

//magic string definition
const char Storing::LOGGING_MESSAGE_1[] = "Exception is caught in Storing (facade) Class";
const char Storing::LOGGING_MESSAGE_2[] = "Exception is thrown from Storing (facade) Class";
const char Storing::ERROR_MESSAGE_1[] = "Please enter a valid task number. \n";
const char Storing::ERROR_MESSAGE_2[] = "Data could not be found. \n";
const char Storing::ERROR_MESSAGE_3[] = "Exception of unknown type is caught. \n"; 

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
		log.logging(LOGGING_MESSAGE_1);
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
		log.logging(LOGGING_MESSAGE_1);
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
	} 
	catch (int errorNo){
		Logger log;
		log.logging(LOGGING_MESSAGE_1);
		handleException(errorNo);
	}
}

std::string Storing::retrieveFeatureList(){
	try{
		PrewrittenData prewrittenData;
		return prewrittenData.retrieveList(feature);
	} 
	catch (int errorNo){
		Logger log;
		log.logging(LOGGING_MESSAGE_1);
		handleException(errorNo);
	}
}

bool Storing::findPathName(){
	std::string pathName;
	PrewrittenData prewrittenData;
	LocalStorage *localStorage = LocalStorage::getInstance();

	try {
		pathName = prewrittenData.retrieveList(path); //return exception when not found
		adjustRetrievedPath(pathName);
	} 
	catch (int errorNo){
		Logger log;
		log.logging(LOGGING_MESSAGE_1);
		handleException(errorNo);
	}

	localStorage->setPathName(pathName); // store path locally
	return true;
}

//private method
//adjusting pathName from retrieved file
//by deleting newline
void Storing::adjustRetrievedPath(std::string& pathName){
	pathName = pathName.substr(0,pathName.size()-1);
}

bool Storing::saveUserPathName(std::string userPathName){
	bool status;
	std::ofstream out;

	LocalStorage *localStorage = LocalStorage::getInstance();
	localStorage->firstSave(); //set up for first time saving
	status = localStorage->directoryCheck(out, userPathName); //return validity of directory given by user
	
	PrewrittenData prewrittenData;
	if(status == true){
		prewrittenData.savePath(userPathName); //save path in path.txt
		localStorage->setPathName(userPathName); // store path locally
	}
	return status;
}

void Storing::loadData(bool& status, std::string directory){
	LocalStorage *localStorage = LocalStorage::getInstance();
	directory = localStorage->checkPathName(); //check whether there's path stored
	localStorage->loadData(status, directory);
}

bool Storing::saveData(std::string directory){
	LocalStorage *localStorage = LocalStorage::getInstance();
	directory = localStorage->checkPathName(); //check whether there's path stored
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
		log.logging(LOGGING_MESSAGE_1);
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
	log.logging(LOGGING_MESSAGE_2);

	switch (errorNo){
	case 1:
		errorMessage = ERROR_MESSAGE_1;
		throw errorMessage;
	case 2:
		errorMessage = ERROR_MESSAGE_2;
		throw errorMessage;

	}

}

