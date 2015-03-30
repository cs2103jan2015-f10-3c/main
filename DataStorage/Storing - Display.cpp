#include "InternalStoring.h"

/////////////////////////////
//Definition of Static Method

std::vector<Data> DisplayStorage::displayList;

//End of Definition
/////////////////////////////


//get display list method for a time frame
std::vector<Data>& DisplayStorage::getDisplayList(TimeMacro startTime, TimeMacro endTime){
	std::vector<long long> timePeriod;
	timePeriod = LocalStorage::searchPeriod(startTime,endTime);
	
	if(!timePeriod.empty()){
		enterDataToList(timePeriod);
		updateTaskNo();
	}
	return displayList;
}

//get display list method for specific purpose (defined in DisplayType)
std::vector<Data>& DisplayStorage::getDisplayList(DisplayType type, std::string keyword= ""){
	switch (type){
	case search:
		displaySearch(keyword);		
		break;
	
	case done:
		displayDone();
		break;

	case floating:
		displayFloat();
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


// !!unit testing done
//helper method for getDisplayList()
//to update all taskNo in displayList vector
void DisplayStorage::enterDataToList(std::vector<long long> timePeriod){
	int endT;
	int startT;

	if(timePeriod.size() == 1){
		endT = startT = timePeriod[0];
	} else {
		endT = timePeriod[1];
		startT = timePeriod[0];
	}
	
	for (int i = startT; i <= endT; i++){
		//if task is not done
		if(LocalStorage::dataList[i].getCompleteStatus()==false){
			displayList.push_back(LocalStorage::dataList[i]);
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

void DisplayStorage::displaySearch(std::string keyword){
	std::string taskDescription;
	size_t found;

	for(int i = 0; i != LocalStorage::dataList.size(); i++){
		taskDescription = LocalStorage::dataList[i].getDesc();
		found = taskDescription.find(keyword);
		if(found != std::string::npos){
			displayList.push_back(LocalStorage::dataList[i]);
		}
	}
}

void DisplayStorage::displayDone(){
	for(int i = 0; i != LocalStorage::dataList.size(); i++){
		if(LocalStorage::dataList[i].getCompleteStatus() == true){
			displayList.push_back(LocalStorage::dataList[i]);
		}
	}
}

void DisplayStorage::displayFloat(){
	for(int i = 0; i != LocalStorage::dataList.size(); i++){
		if(LocalStorage::dataList[i].getTimeMacroBeg().getDay() == "undefined"){
			displayList.push_back(LocalStorage::dataList[i]);
		}
	}
}

//End of Internal Helper methods
////////////////////////////////