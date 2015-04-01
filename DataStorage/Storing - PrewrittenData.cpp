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
	}

	std::ifstream in(txtFile);
	
	//if file exists
	if (in){
		while (getline(in,list)){
			std::cout << list << std::endl;
		} 
	} else {
		std::cout << "List could not be found"; 
	}
	
}

void PrewrittenData::retrieveList(ListType type, std::ofstream& out){
	std::string txtFile;
	std::string list;
	
	switch(type){
	case heading:
		txtFile = "heading_template.txt";
		break;
	}

	std::ifstream in(txtFile);
	
	//if file exists
	if (in){
		while (getline(in,list)){
			out << list << std::endl;
		} 
	} else {
		out << "List could not be found"; 
	}
}
