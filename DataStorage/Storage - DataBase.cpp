#include "DataStorage.h"

std::vector<Data> DataBase::dataList;
int DataBase::uniqueCodeStore;

//return the DataBase list 
//for command such as search
std::vector<Data> & DataBase::getDataList() {
	return dataList;
}

void DataBase::clearDataList(){
	dataList.clear();
}

//for add command to update the dataList
//it allocates uniqueCode into Data
//and also automaticallly sort dataList
void DataBase::addData(Data& inData){


	int tempNo = allocateUniqueCode(uniqueCodeStore);
	inData.updateUniqueCode(tempNo);
	dataList.push_back(inData);
	sortDataList();
	History::updateLatestCommand("add");
	History::updateLatestData(inData); //store for undo

}

//for clear command
//return a Data that shows the time period
//contain startTime and endTime in TimeMacroBeg and TimeMacro End
Data DataBase::clearData(TimeMacro startTime, TimeMacro endTime){

	std::vector<long long> timePeriod;
	timePeriod = searchPeriod(startTime , endTime);
	History::updateLatestCommand("clear");
	History::updateLatestVector(); //update for undo
	
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

		dataList = temp;

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

	History::updateLatestCommand("delete");
		int uniqueCode = DisplayStorage::getUniqueCode(taskNo);

	std::vector<Data> listTofacilitateDeletion;
	for(int i = 0; i != dataList.size(); i++){
		if(uniqueCode != dataList[i].getUniqueCode()){
				listTofacilitateDeletion.push_back(dataList[i]);
		}else
		{
			History::updateLatestData(dataList[i]); //store in History
		}
	}
	dataList = listTofacilitateDeletion;
	return DisplayStorage::getData(taskNo);
}


//method for deleting the latest Data added
//helper for undo function
void DataBase::undoData(int uniqueNo){
	
	std::vector<Data> listTofacilitateDeletion;
	for(int i = 0; i != dataList.size(); i++){
		if(uniqueNo != dataList[i].getUniqueCode()){
				listTofacilitateDeletion.push_back(dataList[i]);
		}
	}
	dataList = listTofacilitateDeletion;
}
//method for edit command
//input the taskno of the displayList and the updatedData
//return Data that was edited
Data DataBase::editData(int taskNo, Data updatedData){
	
	History::updateLatestVector(); //Store for undo
	int uniqueNo = DisplayStorage::getUniqueCode(taskNo);
	Data dataToEdit = getData(uniqueNo);

	if (!updatedData.getDesc().empty()){
		dataToEdit.updateDesc(updatedData.getDesc());
	}

	if (updatedData.getTimeMacroBeg().getDate() != 0 
		&& updatedData.getTimeMacroBeg().getMonth() != 0
		&& updatedData.getTimeMacroBeg().getYear() != 0) {
			dataToEdit.updateTimeMacroBeg(updatedData.getTimeMacroBeg());
	}

	if (updatedData.getTimeMacroEnd().getDate() != 0 
		&& updatedData.getTimeMacroEnd().getMonth() != 0
		&& updatedData.getTimeMacroEnd().getYear() != 0) {
			dataToEdit.updateTimeMacroEnd(updatedData.getTimeMacroEnd());
	}

	if (updatedData.getTimeMicroBeg().getHour() != -1
		&& updatedData.getTimeMicroBeg().getHour() != -1) {
			dataToEdit.updateTimeMicroBeg(updatedData.getTimeMicroBeg());
	}

	if (updatedData.getTimeMicroEnd().getHour() != -1
		&& updatedData.getTimeMicroEnd().getHour() != -1) {
			dataToEdit.updateTimeMicroEnd(updatedData.getTimeMicroEnd());
	}

	deleteData(taskNo);
	addData(dataToEdit);
	History::updateLatestCommand("edit"); //Store for undo

	return DisplayStorage::getData(taskNo);
}

//helper method for deleteData and editData
//input int uniqueCode
//return Data to be modified/deleted
Data DataBase::getData(int uniqueNo){
	Data desiredTask;
	for(int i = 0; i != dataList.size(); i++){
		if(dataList[i].getUniqueCode() == uniqueNo){
			desiredTask = dataList[i];
		}
	}
	return desiredTask;

	// !! figure out how to return error here
}






// !! unit testing done
//allocate uniqueCode to each Data
//For internal working
int DataBase::allocateUniqueCode(int& uniqueNo){
	uniqueNo++;
	return uniqueNo;
	
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

	for(int i = 0; i != dataList.size(); i++){
		long long sDate = dataList[i].getPsedoDate();
		digit = (sDate / power ) % 10; //extract digit
		digitQ[digit].push(dataList[i]);

	}
}

// !!test done by processor
//helper method for radix sort
//put Data back into dataList
void DataBase::radixCollect(std::queue<Data> digitQ[]){
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

		//extract YYYY/MM/DD
		TimeMacro time = dataList[i].getTimeMacroBeg();
		int year = time.getYear();
		int month = time.getMonth();
		int date = time.getDate();
		
		//extract HH/MM
		TimeMicro time1 = dataList[i].getTimeMicroBeg();
		int hour = time1.getHour();
		int min = time1.getMin();

		//qualify default hour
		if(hour == -1){
			hour = 0;
		}
		
		//qualify default min
		if(min == -1){
			min = 0;
		}

		//store psedoDate in long long type
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
//return vector<long long> with two psedoDates inside 
std::vector<long long> DataBase::searchPeriod(TimeMacro startTime, TimeMacro endTime){
	allocatePsedoDate();
	std::vector<long long> saveNo;

	//allocate startTime into psedoDate format
	long long pStartTime;
	pStartTime= 100000000;
	pStartTime= startTime.getYear()*pStartTime;
	long long tempMonth;
	tempMonth = 1000000;
	tempMonth = tempMonth * startTime.getMonth();
	pStartTime = pStartTime + tempMonth;
	long long tempDate = 10000;
	tempDate = tempDate * startTime.getDate();
	pStartTime = pStartTime + tempDate;

	//allocate endTime into psedoDate format
	long long pEndTime;
	pEndTime= 100000000;
	pEndTime= endTime.getYear()*pEndTime;
	long long tempMonth1;
	tempMonth1 = 1000000;
	tempMonth1 = tempMonth1 * endTime.getMonth();
	pEndTime = pEndTime + tempMonth1;
	long long tempDate1 = 10000;
	tempDate1 = tempDate1 * endTime.getDate();
	pEndTime = pEndTime + tempDate1;

	//find first relevant date
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

	//find last relevant date
	for(int i = dataList.size()-1; marker == true && i != 0; i--){
		if(dataList[i].getPsedoDate() <= pEndTime+2359 ) {
			marker = false;
			saveNo.push_back(i);
		}
	}

	return saveNo;
}