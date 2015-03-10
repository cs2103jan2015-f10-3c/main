#include "DataStorage.h"

//getter method
//requires the time frame
//return the displayList
std::vector<Data> DisplayStorage::getDisplayList(TimeMacro startTime, TimeMacro endTime){

	DataBase::searchPeriod(startTime,endTime);

	std::vector<Data>::iterator iter;
	int trackNo;
	
	for(iter = IterStorage::iterBeg; iter <= IterStorage::iterEnd; iter++){
		iter->updateTaskNo(trackNo);
		displayList.push_back(*iter);
		
		trackNo++;
	}

	return displayList;
}


//getter method
//used for displaying withot time frame e.g for keyword search
//return the displayList
std::vector<Data> DisplayStorage::getDisplayList(){
	return displayList;
}


//may not need
/*
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
*/