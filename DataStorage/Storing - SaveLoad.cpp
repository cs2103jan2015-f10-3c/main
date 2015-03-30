#include "InternalStoring.h"

//API for Retrieve list from .txt file
std::stringstream SaveLoad::retrieveList(ListType type){
	std::string list;
	std::stringstream listStream;
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
			listStream << list << std::endl;
		} 
	} else {
		listStream << "List could not be found"; 
	}

	return listStream;
}


//API for loading Data from txt file
void SaveLoad::loadData(bool& status){
	std::ifstream in("test.txt");
	//if file exists
	if (in){

		std::string strUnique;
		getline(in,strUnique);
		std::stringstream streamUnique;
		int uniqueNo;

		streamUnique << strUnique;
		streamUnique >> uniqueNo;
		LocalStorage::updateUniqueCodeStore(uniqueNo);


		//throw away Heading
		std::string temp;
		getline(in,temp);

		std::string strData;
		int i=0; //iterator for vector
		
		while(getline(in,strData)){
			parseLoad(strData, i);
			} 
		
		status = true; //tell command file exist to display

		} else {
			LocalStorage::updateUniqueCodeStore(0);
			status = false;
	}
}



//API for saving data into file
void SaveLoad::saveData(){
	std::string fileName = "test.txt";
	std::ofstream out;
	out.open(fileName.c_str());

	out << LocalStorage::getUniqueCodeStore() <<'\n';
 		 	
	writeHeading(fileName, out); //write Heading for readability

	
	for(int i=0; i != LocalStorage::dataList.size(); i++){
		std::string tMacroBeg = convertTimeMacroToString("Begin", i);
		std::string tMacroEnd = convertTimeMacroToString("End", i);
		std::string alarmMacro = convertTimeMacroToString("Alarm", i);

		std::string tMicroBeg = convertTimeMicroToString("Begin", i);
		std::string tMicroEnd = convertTimeMicroToString("End", i);
		std::string alarmMicro = convertTimeMicroToString("Alarm", i);

		//convert boolean into string
		std::string isDone;
		if(LocalStorage::dataList[i].getCompleteStatus() == true){
			isDone = "true";
		} else {
			isDone = "false";
		}

		//save into file
		out <<LocalStorage::dataList[i].getUniqueCode()
			<< '\t' << tMacroBeg
			<< "\t\t" << tMacroEnd << "\t\t" << tMicroBeg << "\t\t" << tMicroEnd
			<< "\t\t" << isDone << "\t\t" << LocalStorage::dataList[i].getPriority() 
			<< "\t\t" << alarmMacro << "\t\t" << alarmMicro << "\t\t"
			<< LocalStorage::dataList[i].getDesc() << '\n';

	}	
}

//////////////////////////////////////////
//Start of Helper Methods for Loading Data

//helper method for loadDate to parse input
void SaveLoad::parseLoad(std::string strData, int& i){
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

	tempMacroTBeg = tokenizerSpace(strData);
	tempMacroTEnd = tokenizerSpace(strData);
	tempMicroTBeg = tokenizerSpace(strData);
	tempMicroTEnd = tokenizerSpace(strData);
	tempCompleteStatus = tokenizerSpace(strData);
	priority = tokenizerSpace(strData);
	tempAlarmMacro = tokenizerSpace(strData);
	tempAlarmMicro = tokenizerSpace(strData);
	desc = tokenizerSpace(strData);

	Data data;

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

	LocalStorage::addData(data);

	i++;
}

//helper method to parseLoad to parse string and convert to TimeMacro
TimeMacro SaveLoad::macroParser(std::string tempMacro){
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
TimeMicro SaveLoad::microParser(std::string tempMicro){
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
std::string SaveLoad::tokenizerSlash(std::string& str){
	size_t start = 0;
	size_t end = str.find_first_of("/");
	std::string firstToken = str.substr(start, end - start); //get the first token

	//delete the first token from remaining string
	str.erase(0,end+1);

	return firstToken;
}

//helper method for loadParser to get individual token
std::string SaveLoad::tokenizerSpace(std::string& str){
	size_t start = str.find_first_not_of('\t');
	
	//if there is more than one \t
	if(start != 0){
		str.erase(0,start);
		start =0;
	}

	size_t end = str.find_first_of('\t');
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
std::string SaveLoad::convertTimeMacroToString(std::string type, int i){
	std::string tMacro;

	_ASSERTE (type == "Begin" || type == "End" || type == "Alarm");

	if(type == "Begin"){
		tMacro = LocalStorage::dataList[i].getTimeMacroBeg().getDay() + '/'
		+ std::to_string(LocalStorage::dataList[i].getTimeMacroBeg().getDate()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getTimeMacroBeg().getMonth()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getTimeMacroBeg().getYear());
	}

	if(type == "End"){
		tMacro = LocalStorage::dataList[i].getTimeMacroEnd().getDay() + '/'
		+ std::to_string(LocalStorage::dataList[i].getTimeMacroEnd().getDate()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getTimeMacroEnd().getMonth()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getTimeMacroEnd().getYear());
	}

	if(type == "Alarm"){
		tMacro = LocalStorage::dataList[i].getAlarmMacro().getDay() + '/'
		+ std::to_string(LocalStorage::dataList[i].getAlarmMacro().getDate()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getAlarmMacro().getMonth()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getAlarmMacro().getYear());
	}

	return tMacro;
}

//helper method to convert TimeMicro into String
std::string SaveLoad::convertTimeMicroToString(std::string type, int i){
	std::string tMicro;

	_ASSERTE (type == "Begin" || type == "End" || type == "Alarm");

	if(type == "Begin"){
		tMicro = std::to_string(LocalStorage::dataList[i].getTimeMicroBeg().getHour()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getTimeMicroBeg().getMin());
	}

	if(type == "End"){
		tMicro = std::to_string(LocalStorage::dataList[i].getTimeMicroEnd().getHour()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getTimeMicroEnd().getMin());
	}

	if(type == "Alarm"){
		tMicro = std::to_string(LocalStorage::dataList[i].getAlarmMicro().getHour()) + '/'
		+ std::to_string(LocalStorage::dataList[i].getAlarmMicro().getMin());
	}

	return tMicro;
}

//write heading for output file
void SaveLoad::writeHeading (std::string fileName, std::ofstream& out){
	out << retrieveList(heading);
}

//End of Helper method for Saving Data
//////////////////////////////////////