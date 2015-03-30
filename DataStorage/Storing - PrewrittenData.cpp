#include "InternalStoring.h"

//API for Retrieve list from .txt file
void PrewrittenData::retrieveList(ListType type){
	std::string list;
	std::string txtFile;

	switch(type){
	case command:
		txtFile = "all_commands.txt";
		break;
	case feature:
		txtFile = "all_features.txt";
		break;
	case heading:
		txtFile = "heading_template.txt";
		break;
	}

	std::ifstream in(txtFile);
	
	//if file exists
	if (in){
		while (getline(in,list)){
			retrievedList << list << std::endl;
		} 
	} else {
		retrievedList << "List could not be found"; 
	}

}

std::stringstream PrewrittenData::getRetrievedList(){
	std::stringstream list;
	list << retrievedList;

	return list;
}