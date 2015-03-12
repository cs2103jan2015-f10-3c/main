#include "DataStorage.h"

//return the DataBase list 
//to be accessed by data Processor
//for command such as search
std::vector<Data> DataBase::getDataList() {
	return dataList;
}

//for add command to update the dataList
//it allocates uniqueCode into Data
//and also automaticallly sort dataList and update taskNo 
//the added Data inside dataList will be ready for printing
//return the data that was added in the form of Data
Data DataBase::addData(Data inData){

	History::updateLatestData(inData); //store for undo
	allocateUniqueCode(inData);
	dataList.push_back(inData);
	sortDataList();
	updateTaskNo();

	return inData;
}

//for clear command
//return a Data that shows the time period
//contain startTime and endTime in TimeMacroBeg and TimeMacro End
Data DataBase::clearData(TimeMacro startTime, TimeMacro endTime){

	searchPeriod(startTime , endTime);
	History::updateLatestVector(); //update for undo
	dataList.erase(IterStorage::getIterBeg(),IterStorage::getIterEnd()+1);
	updateTaskNo();

	//for returning the time frame
	Data period;
	period.updateTimeMacroBeg(startTime);
	period.updateTimeMacroEnd(endTime);

	return period;
}

//method for delete command
//input the taskno of the display list to be deleted
//return the Data that was deleted
Data DataBase::deleteData(int taskNo){
	int uniqueNo = DisplayStorage::getUniqueCode(taskNo);
	History::updateLatestData(*getData(uniqueNo)); //store in History
	dataList.erase(getData(uniqueNo));
	updateTaskNo();

	return DisplayStorage::getData(taskNo);
}

//method for edit command
//input the taskno of the displayList and the updatedData
//return Data that was edited
Data DataBase::editData(int taskNo, Data updatedData){
	History::updateLatestData(updatedData); // store for undo
	deleteData(taskNo);
	addData(updatedData);

	return DisplayStorage::getData(taskNo);
}

//helper method for deleteData and editData
//input int uniqueCode
//return iterator to be modified/deleted
std::vector<Data>::iterator DataBase::getData(int uniqueNo){
	std::vector<Data>::iterator iter;
	for(iter=dataList.begin(); iter < dataList.end(); iter++){
		if(iter->getUniqueCode()==uniqueNo){
			return iter;
		}
	}
	return;// !! figure out how to return error here
}







//allocate uniqueCode to each Data
//For internal working
void DataBase::allocateUniqueCode(Data inData){
	uniqueNo++;
	inData.updateUniqueCode(uniqueNo);
	
}

//to update all taskNo in dataList vector
//after sorting or adding
void DataBase::updateTaskNo(){
	std::vector<Data>::iterator iter;
	int TrackNo=1;

	for(iter = dataList.begin(); iter < dataList.end(); iter++){
		if(iter->getTaskNo() != TrackNo){
			iter->updateTaskNo(TrackNo);
		}
	}
	TrackNo++;

}


//sorting dataList for maintenance
//use radix sorting algorithm
//allocation of psedoDate is done here. to help sorting
//for internal working
void DataBase::sortDataList(){
	std::vector<Data>::iterator iter;
	allocatePsedoDate();

	int i;
	int power = 1;
	std::queue<Data> digitQueue[10];

	for (i=0; i<8; i++) {
		radixDistribute(digitQueue, power);
		radixCollect(digitQueue);
		power *= 10;
	}

}

//helper method for radix sort
//organise items into groups using digit indicated by the power
void DataBase::radixDistribute(std::queue<Data> digitQ[], int power){
	int digit;
	std::vector<Data>::iterator iter;
	
	for(iter = dataList.begin(); iter < dataList.end(); iter++){
		int sDate = iter->getPsedoDate();
		digit = (sDate / power ) % 10; //extract digit
		digitQ[digit].push(*iter);

	}
}

//helper method for radix sort
//put Data back into dataList
void DataBase::radixCollect(std::queue<Data> digitQ[]){
	std::vector<Data>::iterator iter;
	iter = dataList.begin();
	int digit;

	for(digit = 0 ; digit < 10; digit++){
		while (!digitQ[digit].empty()) {
			*iter = digitQ[digit].front();
			digitQ[digit].pop();
	
			iter++;
		}
	}
}


//allocate psedoDate for all Data in dataList
//used for sorting purposes
//for internal working
void DataBase::allocatePsedoDate(){

	std::vector<Data>::iterator iter;
	for(iter = dataList.begin(); iter < dataList.end(); iter++){
		TimeMacro time = iter->getTimeMacroBeg;
		
		int year = time.getYear();
		int month = time.getMonth();
		int date = time.getDate();

		int sDate = year*10000 + month*100 + date;
	
		iter->updatePsedoDate(sDate);

	}

}



//helper method for search Data from a specific period
//to be pass to DisplayStorage
//updates IterStorage to contain the relevant iteration
void DataBase::searchPeriod(TimeMacro startTime, TimeMacro endTime){

	std::vector<Data>::iterator iter;
	
	bool marker = false;

	for(iter = dataList.begin(); marker == false || iter < dataList.end(); iter++){
		TimeMacro time = iter->getTimeMacroBeg();

		if(time.getDate() >= startTime.getDate() &&
			time.getMonth() >= startTime.getMonth() &&
			time.getYear() >= startTime.getYear()) {
				marker = true;
				IterStorage::updateIterBeg(iter);
		}
	}

	for(iter = dataList.end()-1; marker == true || iter <= dataList.begin(); iter--){
		TimeMacro time = iter->getTimeMacroBeg();

		if(time.getDate() <= endTime.getDate() &&
			time.getMonth() <= endTime.getMonth() &&
			time.getYear() <= endTime.getYear()) {
				marker = false;
				IterStorage::updateIterEnd(iter);
		}
	}
}