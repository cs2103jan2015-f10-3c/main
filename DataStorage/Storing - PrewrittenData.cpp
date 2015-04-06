#include "InternalStoring.h"

//magic string implementation
const char PrewrittenData::ALL_COMMANDS_FILE[] = "all_commands.txt";
const char PrewrittenData::ALL_FEATURES_FILE[] = "all_features.txt";
const char PrewrittenData::HEADING_TEMPLATE_FILE[] = "heading_template.txt";
const char PrewrittenData::PATH_FILE[] = "path.txt";

void PrewrittenData::savePath(std::string inPath){
	pathName = inPath;
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
			throw 2; 
		}
	} catch (int errorNo){
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
		out << "List could not be found"; 
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
