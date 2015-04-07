#include "InternalStoring.h"

//magic string definition
const char PrewrittenData::ALL_COMMANDS_FILE[] = "all_commands.txt";
const char PrewrittenData::ALL_FEATURES_FILE[] = "all_features.txt";
const char PrewrittenData::HEADING_TEMPLATE_FILE[] = "heading_template.txt";
const char PrewrittenData::PATH_FILE[] = "path.txt";
const char PrewrittenData::LOGGING_MESSAGE_1[] = "Exception is caught in PrewrittenData Class";
const char PrewrittenData::LOGGING_MESSAGE_2[] = "Exception is thrown from PrewrittenData Class";
const char PrewrittenData::LOGGING_MESSAGE_3[] = "Heading for storage could not be found";
const char PrewrittenData::DIRECTORY_FILE[] = "path.txt";

void PrewrittenData::savePath(std::string inPath){
	pathName = inPath;

	std::string directory = DIRECTORY_FILE;
	std::ofstream out;
	out.open(directory.c_str());

	out << inPath << std::endl;
}

std::string PrewrittenData::getPath(){
	return pathName;
}

bool PrewrittenData::checkPath(){
	std::string foundPath = retrieveList(path);
	savePath(foundPath);
	return true;
}

//API for Retrieve list from .txt file
std::string PrewrittenData::retrieveList(ListType type){
	std::stringstream ss;
	txtFile = determineListType(type);
	std::ifstream in(txtFile);
	
	try{
		//if file exists
		if (in){
			while (getline(in,retrievedList)){
				ss << retrievedList << std::endl;
			} 
		} else {
			Logger log;
			log.logging(LOGGING_MESSAGE_2);
			throw 2; 
		}
	} catch (int errorNo){
		Logger log;
		log.logging(LOGGING_MESSAGE_1);
		throw errorNo;
	}
	
	retrievedList = ss.str();
	return retrievedList;
}

void PrewrittenData::retrieveList(ListType type, std::ofstream& out){	
	txtFile = determineListType(type);

	std::ifstream in(txtFile);
	
	//if file exists
	if (in){
		while (getline(in,retrievedList)){
			out << retrievedList << std::endl;
		} 
	} else {
		Logger log;
		log.logging(LOGGING_MESSAGE_3);
	}
}

//helper method to determine list type
std::string PrewrittenData::determineListType(ListType type){
	switch(type){
	case command:
		txtFile = ALL_COMMANDS_FILE;
		break;
	case feature:
		txtFile = ALL_FEATURES_FILE;
		break;
	case heading:
		txtFile = HEADING_TEMPLATE_FILE;
		break;
	case path:
		txtFile = PATH_FILE;
		break;
	}
	
	return txtFile;
}
