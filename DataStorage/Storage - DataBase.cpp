#include "DataStorage.h"

//std::vector<Data>::iterator IterStorage::iterBeg;
//std::vector<Data>::iterator IterStorage::iterEnd;


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

	std::vector<long long> timePeriod;
	timePeriod = searchPeriod(startTime , endTime);
	//History::updateLatestVector(); //update for undo
	
	int endT;
	endT = timePeriod.back();
	int startT;
	startT = timePeriod.front();
	std::vector<Data> temp;
	int i=0;
		
		while(i<startT){
			temp.push_back(dataList[i]);
			i++;
		}
		while(i >= startT && i <= endT){
			dataList.pop_back();
			i++;
		}
		while(i > endT && i < dataList.size()){
			temp.push_back(dataList[i]);
			i++;
		}

		dataList=temp;
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
	//std::vector<Data>::iterator iter;
	for(int i = 0; i != dataList.size(); i++){
	//for(iter = dataList.begin(); iter < dataList.end(); iter++){
		long long sDate = dataList[i].getPsedoDate();
		digit = (sDate / power ) % 10; //extract digit
		digitQ[digit].push(dataList[i]);

	}
}

// !!test done by processor
//helper method for radix sort
//put Data back into dataList
void DataBase::radixCollect(std::queue<Data> digitQ[]){
	//std::vector<Data>::iterator iter;
	//iter = dataList.begin();
	int digit;
	int i=0;
	for(digit = 0 ; digit < 10; digit++){
		while (!digitQ[digit].empty()) {
			dataList[i] = digitQ[digit].front();
			digitQ[digit].pop();
	
			i++;
		}
	}
}


//!! test done by processing
//allocate psedoDate for all Data in dataList
//used for sorting purposes
//for internal working
void DataBase::allocatePsedoDate(){
	int i=0;
	long long sDate;
	while(i != dataList.size()){

		TimeMacro time = dataList[i].getTimeMacroBeg();
		int year = time.getYear();
		int month = time.getMonth();
		int date = time.getDate();
		
		TimeMicro time1 = dataList[i].getTimeMicroBeg();
		int hour = time1.getHour();
		int min = time1.getMin();

		if(hour == -1){
			hour = 0;
		}

		if(min == -1){
			min = 0;
		}
		sDate = 100000000;
		sDate = year*sDate;
		long long tempMonth;
		tempMonth = 1000000;
		tempMonth = month*tempMonth;
		sDate = tempMonth + sDate;
		long long tempDate;
		tempDate = 10000;
		tempDate = date*tempDate;
		sDate = sDate + tempDate + hour*100 + min;
		dataList[i].updatePsedoDate(sDate);
		
		i++;

	}



}



//helper method for search Data from a specific period
//to be pass to DisplayStorage
//updates IterStorage to contain the relevant iteration
std::vector<long long> DataBase::searchPeriod(TimeMacro startTime, TimeMacro endTime){
	allocatePsedoDate();
	std::vector<long long> saveNo;

	long long pStartTime;
	pStartTime= 100000000;
	pStartTime= startTime.getYear()*pStartTime;
	long long tempMonth;
	tempMonth = 1000000;
	tempMonth = tempMonth * startTime.getMonth();
	pStartTime = pStartTime + tempMonth;
	pStartTime = pStartTime + startTime.getDate();

	long long pEndTime;
	pEndTime= 100000000;
	pEndTime= endTime.getYear()*pEndTime;
	long long tempMonth1;
	tempMonth1 = 1000000;
	tempMonth1 = tempMonth1 * endTime.getMonth();
	pEndTime = pEndTime + tempMonth1;
	pEndTime = pEndTime + endTime.getDate();


	bool marker = false;
	long long time;
	Data copyTask;
	for(int i = 0; marker == false && i != dataList.size(); i++){
		copyTask = dataList[i];
		time = copyTask.getPsedoDate();
		if(time >= pStartTime && time <= pEndTime + 2359){
			marker = true;
			saveNo.push_back(i);
		}
		
	}

	for(int i = dataList.size()-1; marker == true && i != 0; i--){
		if(dataList[i].getPsedoDate() <= pEndTime+2359 ) {
			marker = false;
			saveNo.push_back(i);
		}
	}
	return saveNo;
}