#include "DataStorage.h"

std::vector<Data>::iterator IterStorage::iterBeg;
std::vector<Data>::iterator IterStorage::iterEnd;


std::vector<Data> DataBase::dataList;


// !!test done by data processing
//return the DataBase list 
//to be accessed by data Processor
//for command such as search
std::vector<Data> DataBase::getDataList() {
	return dataList;
}

void DataBase::clearDataList(){
	dataList.clear();
}

// !!test done by processing
//for add command to update the dataList
//it allocates uniqueCode into Data
//and also automaticallly sort dataList and update taskNo 
//the added Data inside dataList will be ready for printing
//return the data that was added in the form of Data
Data DataBase::addData(Data inData){

	History::updateLatestData(inData); //store for undo
	int tempNo = allocateUniqueCode();
	inData.updateUniqueCode(tempNo);
	dataList.push_back(inData);
	sortDataList();

	return inData;
}

//for clear command
//return a Data that shows the time period
//contain startTime and endTime in TimeMacroBeg and TimeMacro End
Data DataBase::clearData(TimeMacro startTime, TimeMacro endTime){

	searchPeriod(startTime , endTime);
	History::updateLatestVector(); //update for undo
	dataList.erase(IterStorage::getIterBeg(),IterStorage::getIterEnd()+1);

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
	// !! figure out how to return error here
}






// !! unit testing done
//allocate uniqueCode to each Data
//For internal working
int DataBase::allocateUniqueCode(){
	static int UniqueNo = 0;
	UniqueNo++;
	return UniqueNo;
	
}


// !!test done by processor
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

// !!test done by processor
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

// !!test done by processor
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


//!! test done by processing
//allocate psedoDate for all Data in dataList
//used for sorting purposes
//for internal working
void DataBase::allocatePsedoDate(){

	std::vector<Data>::iterator iter;
	for(iter = dataList.begin(); iter < dataList.end(); iter++){
		TimeMacro time = iter->getTimeMacroBeg();
		
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
	allocatePsedoDate();
	std::vector<Data>::iterator iter;

	int pStartTime = startTime.getYear()*10000 + startTime.getMonth()*100 + startTime.getDate();
	int pEndTime = endTime.getYear()*10000 + endTime.getMonth()*100 + endTime.getDate();

	bool marker = false;

	for(iter = dataList.begin(); marker == false || iter < dataList.end(); iter++){
		if(iter->getPsedoDate() >= pStartTime){
			marker = true;
			IterStorage::updateIterBeg(iter);
		}
	}

	for(iter = dataList.end()-1; marker == true || iter <= dataList.begin(); iter--){
		if(iter->getPsedoDate() <= pEndTime) {
			marker = false;
			IterStorage::updateIterEnd(iter);
		}
	}
}