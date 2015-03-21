#include "DataStorage.h"

void DataBase::loadData(){
	std::ifstream in("test.txt");
	if (in){
		std::string temp;
		getline(in,temp);

		std::string strData;
		int i=0;
		while(getline(in,strData)){
			parseLoad(strData, i);

		}	
	}
}

void DataBase::parseLoad(std::string strData, int& i){
	std::stringstream streamConverter;

	std::string tempMacroTBeg;
	std::string tempMacroTEnd;
	std::string tempMicroTBeg;
	std::string tempMicroTEnd;
	std::string tempCompleteStatus;
	int uniqueCode;
	std::string desc;
	std::string temp;

	temp = tokenizerSpace(strData);
	streamConverter << temp;
	streamConverter >> uniqueCode;

	tempMacroTBeg = tokenizerSpace(strData);
	tempMacroTEnd = tokenizerSpace(strData);
	tempMicroTBeg = tokenizerSpace(strData);
	tempMicroTEnd = tokenizerSpace(strData);
	tempCompleteStatus = tokenizerSpace(strData);
	desc = tokenizerSpace(strData);

	Data data;

	data.updateUniqueCode(uniqueCode); 
	data.updateDesc(desc);

	TimeMacro inMacroTBeg = macroParser(tempMacroTBeg);
	data.updateTimeMacroBeg(inMacroTBeg);

	TimeMacro inMacroTEnd = macroParser(tempMacroTEnd);
	data.updateTimeMacroEnd(inMacroTEnd);

	TimeMicro inMicroTBeg = microParser(tempMicroTBeg);
	data.updateTimeMicroBeg(inMicroTBeg);

	TimeMicro inMicroTEnd = microParser(tempMicroTEnd);
	data.updateTimeMicroEnd(inMicroTEnd);

	dataList.push_back(data);

	i++;
}

TimeMacro DataBase::macroParser(std::string tempMacro){
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

TimeMicro DataBase::microParser(std::string tempMicro){
	TimeMicro temp;
	int inHour;
	int inMin;

	std::istringstream(tokenizerSlash(tempMicro)) >> inHour;
	temp.updateHour(inHour);
	std::istringstream(tempMicro) >> inMin;
	temp.updateMin(inMin);

	return temp;
}


std::string DataBase::tokenizerSlash(std::string& str){
	size_t start = 0;
	size_t end = str.find_first_of("/");
	std::string firstToken = str.substr(start, end - start);

	str.erase(0,end+1);

	return firstToken;
}

std::string DataBase::tokenizerSpace(std::string& str){
	size_t start = str.find_first_not_of('\t');
	
	//if there is more than one \t
	if(start != 0){
		str.erase(0,start);
		start =0;
	}

	size_t end = str.find_first_of('\t');
	std::string firstToken = str.substr(start, end - start);

	str.erase(0,end+1);

	return firstToken;
}

void DataBase::saveData(){
	std::string fileName = "test.txt";
	std::ofstream out;
	out.open(fileName.c_str());
 		 	
	writeHeading(fileName, out);


	for(int i=0; i != dataList.size(); i++){
		std::string tMacroBeg = dataList[i].getTimeMacroBeg().getDay() + '/'
			+ std::to_string(dataList[i].getTimeMacroBeg().getDate()) + '/'
			+ std::to_string(dataList[i].getTimeMacroBeg().getMonth()) + '/'
			+ std::to_string(dataList[i].getTimeMacroBeg().getYear());

		std::string tMacroEnd = dataList[i].getTimeMacroEnd().getDay() + '/'
			+ std::to_string(dataList[i].getTimeMacroEnd().getDate()) + '/'
			+ std::to_string(dataList[i].getTimeMacroEnd().getMonth()) + '/'
			+ std::to_string(dataList[i].getTimeMacroEnd().getYear());

		std::string tMicroBeg = std::to_string(dataList[i].getTimeMicroBeg().getHour()) + '/'
			+ std::to_string(dataList[i].getTimeMicroBeg().getMin());

		std::string tMicroEnd = std::to_string(dataList[i].getTimeMicroEnd().getHour()) + '/'
			+ std::to_string(dataList[i].getTimeMicroEnd().getMin());

		std::string isDone;
		if(dataList[i].getCompleteStatus() == true){
			isDone = "true";
		} else {
			isDone = "false";
		}

		out <<dataList[i].getUniqueCode()
			<< '\t' << tMacroBeg
			<< '\t' << tMacroEnd << "\t\t" << tMicroBeg << "\t\t" << tMicroEnd
			<< "\t\t" << isDone << "\t\t" << dataList[i].getDesc() << '\n';

	}	
}

void DataBase::writeHeading (std::string fileName, std::ofstream& out){
	out <<"uCode" 
		<< '\t' << "macroTBeg" << "\t\t" << "macroTEnd" << "\t\t" 
		<< "microTBeg" << "\t" << "microTEnd" << "\t" << "completeStatus" 
		<< "\t" << "desc" << '\n';
}