#include "DataStorage.h"

std::vector<Data> DisplayStorage::displayList;

//getter method
//requires the time frame
//return the displayList
//for display command
std::vector<Data> & DisplayStorage::getDisplayList(TimeMacro startTime, TimeMacro endTime){
	displayList.clear(); //clear the vector everytime it starts
	std::vector<int> timePeriod;

	timePeriod = DataBase::searchPeriod(startTime,endTime);
	int endT;
	int startT;

	if(!timePeriod.empty()){
		
		if(timePeriod.size() == 1){
			endT = startT = timePeriod[0];
		}else{
			endT = timePeriod[1];
			startT = timePeriod[0];
		}
		

		for (int i = startT; i <= endT; i++){
			displayList.push_back(DataBase::dataList[i]);
		}

		DisplayStorage::updateTaskNo();
	}


	//std::vector<Data> copyVector = displayList;
	//return copyVector;
	return displayList;
}

// !!unit testing done
//getter method
//used for displaying withot time frame e.g for keyword search
//return the displayList
std::vector<Data> DisplayStorage::getDisplayList(){
	DisplayStorage::updateTaskNo();
	return displayList;
}

void DisplayStorage::clearList(){
	displayList.clear();
}

// !!unit testing done
//helper method for Data Processing
//for keyword search command
void DisplayStorage::addData(Data inData){
	displayList.push_back(inData);
	updateTaskNo();
}

// !! unit test done
//helper method for DataBase to get unique code of the data
//input is int TaskNo of the displayList
//return the uniqueCode to be processed by DataStorage
int DisplayStorage::getUniqueCode(int taskNo){
	std::vector<Data>::iterator iter = displayList.begin();
	advance(iter, taskNo-1);

	return iter->getUniqueCode();
}

// !!unit testing done
//helper method for getting Data from the displayList taskNo
//input is int taskNo
//return Data
Data DisplayStorage::getData(int taskNo){
	std::vector<Data>::iterator iter = displayList.begin();
	advance(iter, taskNo-1);

	return *iter;
}

// !!unit testing done
//helper method for getDisplayList()
//to update all taskNo in displayList vector
//after sorting or adding
void DisplayStorage::updateTaskNo(){
	//std::vector<Data>::iterator iter;
	
	int TrackNo=1;
	
	/*for(iter = displayList.begin(); iter < displayList.end(); iter++){
		if(iter->getTaskNo() != TrackNo){
			iter->updateTaskNo(TrackNo);
			
		}
		TrackNo++;
	}*/
	
	for(int i = 0; i != displayList.size(); i++){
		if(displayList[i].getTaskNo() != TrackNo){
			displayList[i].updateTaskNo(TrackNo);
		}
	}

}
