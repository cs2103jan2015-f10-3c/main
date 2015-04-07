#include "InternalStoring.h"

//Implementation of LocalStorage class
//for saving and loading methods
//.cpp file is separated from Storing - Local.cpp
//to allow for more room

//magic string definition
const char LocalStorage::DEFAULT_SAVE_DIRECTORY[] = "save.txt";
const char LocalStorage::SLASH[] = "/";
const char LocalStorage::TAB[] = "\t";
const char LocalStorage::TRUE_STRING[] = "true";
const char LocalStorage::FALSE_STRING[] = "false";
const char LocalStorage::EMPTY_STRING[] = "";

//API for loading Data from txt file
void LocalStorage::loadData(bool& status, std::string& directory){
	adjustFormat(directory);
	
	std::ifstream in(directory);
	//if file exists
	if (in){

		std::string strUnique;
		getline(in,strUnique);
		std::stringstream streamUnique;
		int uniqueNo;

		streamUnique << strUnique;
		streamUnique >> uniqueNo;
		uniqueCodeStore = uniqueNo;

		//throw away Heading
		std::string temp;
		getline(in,temp);

		std::string strData;
		int i=0; //iterator for vector
		Data data;

		while(getline(in,strData)){
			parseLoad(strData, i, data);
			dataList.push_back(data);
			i++;
			} 
		
		status = true; //tell command file exist to display

		} else {
			uniqueCodeStore = 0;
			status = false;
	}
}

void LocalStorage::firstSave(){
	uniqueCodeStore = 0;
}

//check whether user input directory exists
bool LocalStorage::directoryCheck(std::ofstream& out){
	try{
		if(!out.is_open()){
			Logger log;
			log.logging(LOGGING_MESSAGE_2);
			throw false;
		} else {
			return true;
		}
	}
	catch (const bool status) {
		Logger log;
		log.logging(LOGGING_MESSAGE_1);
		return status;
	}
}

//format the input directory from user
//so that it can be read by all compiler
void LocalStorage::adjustFormat(std::string& inputDirectory){
	if (inputDirectory != EMPTY_STRING){
		inputDirectory += SLASH;
	}
	inputDirectory += DEFAULT_SAVE_DIRECTORY;
}


//API for saving data into file
bool LocalStorage::saveData(std::string& directory){
	adjustFormat(directory);
	bool status;

	std::ofstream out;
	out.open(directory.c_str());
	status = directoryCheck(out);

	if(status){
		out << uniqueCodeStore << std::endl;
 		 	
		writeHeading(directory, out); //write Heading for readability

		//converting Time type to string 
		//according different types
		for(int i=0; i != dataList.size(); i++){
			std::string tMacroBeg = convertTimeMacroToString(begin, i);
			std::string tMacroEnd = convertTimeMacroToString(end, i);
			std::string alarmMacro = convertTimeMacroToString(alarm, i);

			std::string tMicroBeg = convertTimeMicroToString(begin, i);
			std::string tMicroEnd = convertTimeMicroToString(end, i);
			std::string alarmMicro = convertTimeMicroToString(alarm, i);

			//convert boolean into string
			std::string isDone;
			if(dataList[i].getCompleteStatus() == true){
				isDone = TRUE_STRING;
			} else {
				isDone = FALSE_STRING;
			}

			//save into file
			out << dataList[i].getUniqueCode()
				<< TAB << tMacroBeg
				<< TAB << TAB << tMacroEnd << TAB << TAB << tMicroBeg << TAB << TAB << tMicroEnd
				<< TAB << TAB << isDone << TAB << TAB << dataList[i].getPriority() 
				<< TAB << TAB << alarmMacro << TAB << TAB << alarmMicro << TAB << TAB
				<< dataList[i].getDesc() << std::endl;
		}
	}	
	return status;
}

//////////////////////////////////////////
//Start of Helper Methods for Loading Data

//helper method for loadDate to parse input
void LocalStorage::parseLoad(std::string strData, int i, Data& data){
	std::stringstream streamConverter; //to help convert string to int

	std::string tempMacroTBeg;
	std::string tempMacroTEnd;
	std::string tempMicroTBeg;
	std::string tempMicroTEnd;
	std::string tempCompleteStatus;
	int uniqueCode;
	std::string desc;
	std::string priority;
	std::string tempAlarmMacro;
	std::string tempAlarmMicro;
	std::string temp;

	//get uniqueCode and convert to int
	temp = tokenizerSpace(strData);
	streamConverter << temp;
	streamConverter >> uniqueCode;

	//get each data by getting rid of spaces
	tempMacroTBeg = tokenizerSpace(strData);
	tempMacroTEnd = tokenizerSpace(strData);
	tempMicroTBeg = tokenizerSpace(strData);
	tempMicroTEnd = tokenizerSpace(strData);
	tempCompleteStatus = tokenizerSpace(strData);
	priority = tokenizerSpace(strData);
	tempAlarmMacro = tokenizerSpace(strData);
	tempAlarmMicro = tokenizerSpace(strData);
	desc = tokenizerSpace(strData);
	
	//update Data object
	data.updateUniqueCode(uniqueCode); 
	data.updateDesc(desc);
	TimeMacro inMacroTBeg = macroParser(tempMacroTBeg);
	data.updateTimeMacroBeg(inMacroTBeg);
	TimeMacro inMacroTEnd = macroParser(tempMacroTEnd);
	data.updateTimeMacroEnd(inMacroTEnd);
	TimeMacro inAlarmMacro = macroParser(tempAlarmMacro);
	data.updateAlarmMacro(inAlarmMacro);
	TimeMicro inMicroTBeg = microParser(tempMicroTBeg);
	data.updateTimeMicroBeg(inMicroTBeg);
	TimeMicro inMicroTEnd = microParser(tempMicroTEnd);
	data.updateTimeMicroEnd(inMicroTEnd);
	TimeMicro inAlarmMicro = microParser(tempAlarmMicro);
	data.updateAlarmMicro(inAlarmMicro);

	//update completeStatus for Data object
	if(tempCompleteStatus == TRUE_STRING){
		data.updateCompleteStatus(true);
	} else {
		if (tempCompleteStatus == FALSE_STRING){
			data.updateCompleteStatus(false);
		}
	}

}

//helper method to parseLoad to parse string and convert to TimeMacro
TimeMacro LocalStorage::macroParser(std::string tempMacro){
	TimeMacro temp;
	std::string inDay;
	int inDate;
	int inMonth;
	int inYear;

	inDay = tokenizerSlash(tempMacro);
	temp.updateDay(inDay);
	std::istringstream(tokenizerSlash(tempMacro)) >> inDate;
	temp.updateDate(inDate);
	std::istringstream(tokenizerSlash(tempMacro)) >> inMonth;
	temp.updateMonth(inMonth);
	std::istringstream(tempMacro) >> inYear;
	temp.updateYear(inYear);

	return temp;
}

//helper method to parseLoad to parse string to TimeMicro
TimeMicro LocalStorage::microParser(std::string tempMicro){
	TimeMicro temp;
	int inHour;
	int inMin;

	std::istringstream(tokenizerSlash(tempMicro)) >> inHour;
	temp.updateHour(inHour);
	std::istringstream(tempMicro) >> inMin;
	temp.updateMin(inMin);

	return temp;
}

//helper method for MicroParser and Macro Parser to get individual token
std::string LocalStorage::tokenizerSlash(std::string& str){
	size_t start = 0;
	size_t end = str.find_first_of(SLASH);
	std::string firstToken = str.substr(start, end - start); //get the first token

	//delete the first token from remaining string
	str.erase(0,end+1);

	return firstToken;
}

//helper method for loadParser to get individual token
std::string LocalStorage::tokenizerSpace(std::string& str){
	size_t start = str.find_first_not_of(TAB);
	
	//if there is more than one \t
	if(start != 0){
		str.erase(0,start);
		start =0;
	}

	size_t end = str.find_first_of(TAB);
	std::string firstToken = str.substr(start, end - start); //get the first token

	//delete the first token from the remaining string
	str.erase(0,end+1);

	return firstToken;
}

//End of Helper method for Loading Data
///////////////////////////////////////

/////////////////////////////////////////
//Start of Helper method for saving Data

//helper method to convert TimeMacro into String
//adding slash in the middle for readability
std::string LocalStorage::convertTimeMacroToString(TimeType type, int i){
	std::string tMacro;
	
	switch(type){
	case begin :
		tMacro = dataList[i].getTimeMacroBeg().getDay() + SLASH
		+ std::to_string(dataList[i].getTimeMacroBeg().getDate()) + SLASH
		+ std::to_string(dataList[i].getTimeMacroBeg().getMonth()) + SLASH
		+ std::to_string(dataList[i].getTimeMacroBeg().getYear());
		break;

	case end :
		tMacro = dataList[i].getTimeMacroEnd().getDay() + SLASH
		+ std::to_string(dataList[i].getTimeMacroEnd().getDate()) + SLASH
		+ std::to_string(dataList[i].getTimeMacroEnd().getMonth()) + SLASH
		+ std::to_string(dataList[i].getTimeMacroEnd().getYear());
		break;

	case alarm :
		tMacro = dataList[i].getAlarmMacro().getDay() + SLASH
		+ std::to_string(dataList[i].getAlarmMacro().getDate()) + SLASH
		+ std::to_string(dataList[i].getAlarmMacro().getMonth()) + SLASH
		+ std::to_string(dataList[i].getAlarmMacro().getYear());
		break;
	}

	return tMacro;
}

//helper method to convert TimeMicro into String
//adding slash in the middle for readability
std::string LocalStorage::convertTimeMicroToString(TimeType type, int i){
	std::string tMicro;

	switch(type){
	case begin :
		tMicro = std::to_string(dataList[i].getTimeMicroBeg().getHour()) + SLASH
		+ std::to_string(dataList[i].getTimeMicroBeg().getMin());
		break;

	case (end) :
		tMicro = std::to_string(dataList[i].getTimeMicroEnd().getHour()) + SLASH
		+ std::to_string(dataList[i].getTimeMicroEnd().getMin());
		break;

	case (alarm) :
		tMicro = std::to_string(dataList[i].getAlarmMicro().getHour()) + SLASH
		+ std::to_string(dataList[i].getAlarmMicro().getMin());
		break;
	}

	return tMicro;
}

//write heading for output file
void LocalStorage::writeHeading (std::string fileName, std::ofstream& out){
	PrewrittenData list;
	list.retrieveList(heading, out);
}

//End of Helper method for Saving Data
//////////////////////////////////////