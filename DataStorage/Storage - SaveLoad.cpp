#include "DataStorage.h"

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
			<< '\t' << dataList[i].getPsedoDate() << '\t' << tMacroBeg
			<< '\t' << tMacroEnd << "\t\t" << tMicroBeg << "\t\t" << tMicroEnd
			<< "\t\t" << isDone << "\t\t" << dataList[i].getDesc();

	}	
}

void DataBase::writeHeading (std::string fileName, std::ofstream& out){
	out <<"uCode \t psedoDate" 
		<< '\t' << "macroTBeg" << "\t\t" << "macroTEnd" << "\t\t" 
		<< "microTBeg" << "\t" << "microTEnd" << "\t" << "completeStatus" 
		<< "\t" << "desc" << '\n';
}