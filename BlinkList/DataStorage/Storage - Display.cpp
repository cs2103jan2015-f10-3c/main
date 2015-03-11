#include "DataStorage.h"

//getter method
//requires the time frame
//return the displayList
//for display command
std::vector<Data> DisplayStorage::getDisplayList(TimeMacro startTime, TimeMacro endTime){
	displayList.clear(); //clear the vector everytime it starts

	DataBase::searchPeriod(startTime,endTime);
	
	std::vector<Data>::iterator iter;
	for (iter = IterStorage::getIterBeg(); iter <= IterStorage::getIterEnd(); iter++){
		displayList.push_back(*iter);
	}

	DisplayStorage::updateTaskNo();

	return displayList;
}


//getter method
//used for displaying withot time frame e.g for keyword search
//return the displayList
std::vector<Data> DisplayStorage::getDisplayList(){
	DisplayStorage::updateTaskNo();
	return displayList;
}

//helper method for Data Processing
//for keyword search command
void DisplayStorage:: addData(Data inData){
	displayList.push_back(inData);
}



//helper method for getDisplayList()
//to update all taskNo in displayList vector
//after sorting or adding
void DisplayStorage::updateTaskNo(){
	std::vector<Data>::iterator iter;
	int TrackNo=1;

	for(iter = displayList.begin(); iter < displayList.end(); iter++){
		if(iter->getTaskNo() != TrackNo){
			iter->updateTaskNo(TrackNo);
		}
	}
	TrackNo++;

}
