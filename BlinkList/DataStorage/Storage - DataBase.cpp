#include "DataStorage.h"


/*
std::vector<Data> DataBase::getDataList() {
	return dataList;
}*/

//add command update the dataList
//it allocates uniqueCode into Data
//and also automaticallly sort dataList and update taskNo 
//the added Data inside dataList will be ready for printing
void DataBase::addData(Data inData){

	allocateUniqueCode(inData);
	dataList.push_back(inData);
	sortDataList();
	updateTaskNo();

}

//sorting dataList for maintenance
//use radix sorting algorithm
//allocation of psedoDate is done here. to help sorting
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

//allocate uniqueCode to each Data
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


void DataBase::deleteData(int uniqueCode){

}

void DataBase::clearData(TimeMacro startTime, TimeMacro endTime){

	searchPeriod(startTime , endTime);
	dataList.erase(IterStorage::iterBeg,IterStorage::iterEnd+1);

}

IterStorage DataBase::searchPeriod(TimeMacro startTime, TimeMacro endTime){

	std::vector<Data>::iterator iter;
	
	bool marker = false;

	for(iter = dataList.begin(); marker == false || iter < dataList.end(); iter++){
		TimeMacro time = iter->getTimeMacroBeg();

		if(time.getDate() == startTime.getDate() &&
			time.getMonth() == startTime.getMonth() &&
			time.getYear() == startTime.getYear()) {
				marker = true;
				IterStorage::iterBeg = iter;
		}
	}

	for(iter = dataList.end()-1; marker == true || iter <= dataList.begin(); iter--){
		TimeMacro time = iter->getTimeMacroBeg();

		if(time.getDate() == endTime.getDate() &&
			time.getMonth() == endTime.getMonth() &&
			time.getYear() == endTime.getYear()) {
				marker = false;
				IterStorage::iterEnd = iter;
		}
	}
}