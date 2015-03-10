#include "DataStorage.h"

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