#include "InternalStoring.h"


///////////////////////////////////////
//Singleton Definition / Implementation

LocalStorage* LocalStorage::instance = NULL;

LocalStorage* LocalStorage::getInstance(){
	if(instance == NULL){
		instance = new LocalStorage;
	}
	return instance;
}


//End of Singleton Definition
///////////////////////////////////////



///////////////////////////////
//API implementation

//API for DisplayStorage
//to search for two dates from a specific period
std::vector<long long> LocalStorage::searchPeriod(TimeMacro startTime, TimeMacro endTime){
	allocatePsedoDate();

	//allocate startTime & endTime into psedoDate format
	long long pStartTime = allocateTimeToPsedoDate(startTime);
	long long pEndTime = allocateTimeToPsedoDate(endTime);

	return searchRelevantDates(pStartTime,pEndTime);
}

//return the list containing all tasks
//in internal storage
std::vector<Data>& LocalStorage::getDataList() {
	return dataList;
}

//clearing all tasks from internal storage
void LocalStorage::clearDataList(){
	History::updateLatestCommand("clear"); //store for undo
	dataList.clear();
}

//for add command to update the dataList
//it allocates uniqueCode into Data
//and also automaticallly sort dataList
void LocalStorage::addData(Data& inData){
	int uniqueNo = allocateUniqueCode(uniqueCodeStore); //get unique code
	inData.updateUniqueCode(uniqueNo);// assign unique code to Data
	
	dataList.push_back(inData);
	sortDataList(); //automatic sorting of list chronologically

	History::updateLatestCommand("add"); //store for undo
	History::updateLatestData(inData);
}


//method for delete command
//input the taskno of the display list to be deleted
Data LocalStorage::deleteData(int taskNo){
	History::updateLatestCommand("delete"); //store for undo
	
	DisplayStorage *display = DisplayStorage::getInstance();
	int uniqueCode = display->getUniqueCode(taskNo);

	dataList = deleteDataOfUniqueCode(uniqueCode);

	return display->getData(taskNo);
}

//API to help undo add
void LocalStorage::undoAdd(){
	int uniqueCode;
	uniqueCode = History::getLatestData().getUniqueCode();

	dataList = deleteDataOfUniqueCode(uniqueCode);
}

//method for edit command
//input the taskno of the displayList and the updatedData
//return Data that was edited
Data LocalStorage::editData(int taskNo, Data updatedData){
	History::updateLatestVector(); //Store for undo
	
	DisplayStorage *display = DisplayStorage::getInstance();
	int uniqueNo = display->getUniqueCode(taskNo);
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
		&& updatedData.getTimeMicroBeg().getMin() != -1) {
			dataToEdit.updateTimeMicroBeg(updatedData.getTimeMicroBeg());
			dataToEdit.updateTimeMicroEnd(updatedData.getTimeMicroEnd());
	}

	if (updatedData.getAlarmMacro().getDate() != 0 
		&& updatedData.getAlarmMacro().getMonth() != 0
		&& updatedData.getAlarmMacro().getYear() != 0) {
			dataToEdit.updateAlarmMacro(updatedData.getAlarmMacro());
	}

	if (updatedData.getAlarmMicro().getHour() != -1
		&& updatedData.getAlarmMicro().getMin() != -1) {
			dataToEdit.updateAlarmMicro(updatedData.getAlarmMicro());
	}

	if (updatedData.getCompleteStatus() != false){
		dataToEdit.updateCompleteStatus(true);
	}//exception is for undone

	deleteData(taskNo);
	addData(dataToEdit);


	History::updateLatestCommand("edit"); //Store for undo

	return display->getData(taskNo);
}

//End of API implementation
////////////////////////////////////

/////////////////////////////////////
//Helper methods for internal working

//helper method for undoAdd and deleteData
//delete data that have a certain unique code
std::vector<Data> LocalStorage::deleteDataOfUniqueCode(int uniqueCode){
	std::vector<Data> listAfterDeletion;
	for(int i = 0; i != dataList.size(); i++){
		if(uniqueCode != dataList[i].getUniqueCode()){
				listAfterDeletion.push_back(dataList[i]);
		} else {
			History::updateLatestData(dataList[i]); //store for undo
		}
	}
	return listAfterDeletion;
}


//helper method for searchPeriod
//to change time type
//from TimeMacro to psedoDate
long long LocalStorage::allocateTimeToPsedoDate(TimeMacro time){
	long long pTime;
	long long tempMonth;
	long long tempDate = 10000;

	pTime= 100000000;
	pTime= time.getYear()*pTime;
	tempMonth = 1000000;
	tempMonth = tempMonth * time.getMonth();
	pTime = pTime + tempMonth;
	tempDate = tempDate * time.getDate();
	pTime = pTime + tempDate;

	return pTime;
}

//helper method for searchPeriod
//to look for relevant dates
std::vector<long long> LocalStorage::searchRelevantDates(long long pStartTime, long long pEndTime){
	std::vector<long long> saveNo;

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

//helper method for deleteData and editData
Data LocalStorage::getData(int uniqueNo){
	Data desiredTask;
	for(int i = 0; i != dataList.size(); i++){
		if(dataList[i].getUniqueCode() == uniqueNo){
			desiredTask = dataList[i];
		}
	}
	return desiredTask;
}



// !! unit testing done
//allocate uniqueCode to each Data
int LocalStorage::allocateUniqueCode(int& uniqueNo){
	uniqueNo++;
	return uniqueNo;
}


//sorting dataList for maintenance
//use radix sorting algorithm
void LocalStorage::sortDataList(){
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
void LocalStorage::radixDistribute(std::queue<Data> digitQ[], int power){
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
void LocalStorage::radixCollect(std::queue<Data> digitQ[]){
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
//for sorting purposes
void LocalStorage::allocatePsedoDate(){
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

//End of Helper Methods for internal working
////////////////////////////////////////////
