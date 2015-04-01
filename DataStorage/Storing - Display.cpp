#include "InternalStoring.h"

///////////////////////////////////////
//Singleton Definition / Implementation

DisplayStorage* DisplayStorage::instance = NULL;

DisplayStorage* DisplayStorage::getInstance(){
	if(instance == NULL){
		instance = new DisplayStorage;
	}
	return instance;
}


//End of Definition
///////////////////////////////////////


//get display list method for a time frame
std::vector<Data>& DisplayStorage::getDisplayList(TimeMacro startTime, TimeMacro endTime){
	LocalStorage *localStorage = LocalStorage::getInstance();

	std::vector<long long> timePeriod;
	timePeriod = localStorage->searchPeriod(startTime,endTime);
	
	if(!timePeriod.empty()){
		enterDataToList(timePeriod);
		updateTaskNo();
	}
	return displayList;
}



//get display list method for specific purpose (defined in DisplayType)
std::vector<Data>& DisplayStorage::getDisplayList(DisplayType type, std::string keyword){
	std::vector<Data> tempList = getListFromLocal();
	
	switch (type){
	case search:
		displaySearch(tempList, keyword);		
		break;
	
	case done:
		displayDone(tempList);
		break;

	case floating:
		displayFloat(tempList);
		break;
	}
	
	updateTaskNo();
	
	return displayList;
}

void DisplayStorage::clearList(){
	displayList.clear();
}

// !!unit testing done
//getting Data from the displayList taskNo
Data DisplayStorage::getData(int taskNo){
	Data desiredTask;
	desiredTask = displayList[taskNo-1];
	return desiredTask;
}

// !! unit test done
//API DataBase to get unique code of the data
int DisplayStorage::getUniqueCode(int taskNo){
	Data desiredTask = displayList[taskNo-1];
	return desiredTask.getUniqueCode();
}




//////////////////////////////////
// Start of Internal Helper methods

//helper method to get dataList from LocalStorage
std::vector<Data> DisplayStorage::getListFromLocal(){
	LocalStorage *localStorage;
	localStorage = LocalStorage::getInstance();
	std::vector<Data> tempList = localStorage->getDataList();
	return tempList;
}


// !!unit testing done
//helper method for getDisplayList()
//to update all taskNo in displayList vector
void DisplayStorage::enterDataToList(std::vector<long long> timePeriod){
	int endT;
	int startT;
	
	std::vector<Data> tempList = getListFromLocal();

	if(timePeriod.size() == 1){
		endT = startT = timePeriod[0];
	} else {
		endT = timePeriod[1];
		startT = timePeriod[0];
	}
	
	for (int i = startT; i <= endT; i++){
		//if task is not done
		if(tempList[i].getCompleteStatus()==false){
			displayList.push_back(tempList[i]);
		}
	}
}

void DisplayStorage::updateTaskNo(){
	int trackNo=1;
		
	for(int i = 0; i != displayList.size(); i++){
		if(displayList[i].getTaskNo() != trackNo){
			displayList[i].updateTaskNo(trackNo);
		}
		trackNo++;
	}
}

void DisplayStorage::displaySearch(std::vector<Data> tempList, std::string keyword){
	std::string taskDescription;
	size_t found;

	for(int i = 0; i != tempList.size(); i++){
		taskDescription = tempList[i].getDesc();
		found = taskDescription.find(keyword);
		if(found != std::string::npos){
			displayList.push_back(tempList[i]);
		}
	}
}

void DisplayStorage::displayDone(std::vector<Data> tempList){
	for(int i = 0; i != tempList.size(); i++){
		if(tempList[i].getCompleteStatus() == true){
			displayList.push_back(tempList[i]);
		}
	}
}

void DisplayStorage::displayFloat(std::vector<Data> tempList){
	for(int i = 0; i != tempList.size(); i++){
		if(tempList[i].getTimeMacroBeg().getDay() == "undefined"){
			displayList.push_back(tempList[i]);
		}
	}
}

//End of Internal Helper methods
////////////////////////////////