#include "InternalStoring.h"

//Magic string definition
const char LocalStorage::LOGGING_MESSAGE_1[] = "Exception is caught in LocalStorage Class";
const char LocalStorage::LOGGING_MESSAGE_2[] = "Esception is thrown from LocalStorage Class";
const char LocalStorage::LOGGING_MESSAGE_3[] = "LocalStorage is initiated";
const char LocalStorage::LOGGING_MESSAGE_4[] = "Adding data in storage is succesful";
const char LocalStorage::LOGGING_MESSAGE_5[] = "Editing data in storage is succesful";
const char LocalStorage::LOGGING_MESSAGE_6[] = "Clearing data in storage is succesful";
const char LocalStorage::LOGGING_MESSAGE_7[] = "Deleting data in storage is succesful";
const char LocalStorage::ADD[] = "add";
const char LocalStorage::EDIT[] = "edit";
const char LocalStorage::DELETE_WORD[] = "delete";
const char LocalStorage::CLEAR[] = "clear";
const int LocalStorage::TIME_MICRO_DEFAULT = -1;
const int LocalStorage::TIME_MACRO_DEFAULT = 0;
const int LocalStorage::TIME_MICRO_ADJUSTMENT = 2359;
const int LocalStorage::NO_OF_DIGITS = 10;
const int LocalStorage::LENGTH_OF_PSEDODATE =8;
const int LocalStorage::ZERO = 0;
const int LocalStorage::TEN_THOUSAND = 10000;
const int LocalStorage::ONE_MILLION = 1000000;
const int LocalStorage::HUNDRED_MILLION = 100000000;

///////////////////////////////////////
//Singleton Definition / Implementation

LocalStorage* LocalStorage::instance = NULL;

LocalStorage* LocalStorage::getInstance(){
	if(instance == NULL){
		instance = new LocalStorage;

		Logger log;
		log.logging(LOGGING_MESSAGE_3); //write in log
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
	allocatePsedoDate(); //allocating psedoDate to ensure all data have psedoDates

	//allocate startTime & endTime into psedoDate format
	long long pStartTime = allocateTimeMacroToPsedoDate(startTime);
	long long pEndTime = allocateTimeMacroToPsedoDate(endTime);

	return searchRelevantDates(pStartTime,pEndTime);
}

//return the list containing all tasks
//in internal storage
std::vector<Data>& LocalStorage::getDataList() {
	return dataList;
}

//clearing all tasks from internal storage
void LocalStorage::clearDataList(){
	History::updateLatestCommand(CLEAR); //store for undo
	History::updateLatestVector();
	dataList.clear();

	Logger log;
	log.logging(LOGGING_MESSAGE_6); //log a message
}

//for add command to update the dataList
//it allocates uniqueCode into Data
//and also automaticallly sort dataList
void LocalStorage::addData(Data& inData){
	Logger log;
	log.logging(LOGGING_MESSAGE_4); //log a message

	int uniqueNo = allocateUniqueCode(uniqueCodeStore); //get unique code
	inData.updateUniqueCode(uniqueNo);// assign unique code to Data
	
	dataList.push_back(inData);
	sortDataList(); //automatic sorting of list chronologically

	History::updateLatestCommand(ADD); //store for undo
	History::updateLatestData(inData);
}


//method for delete command
//input the taskno of the display list to be deleted
Data LocalStorage::deleteData(int taskNo){
	DisplayStorage *display = DisplayStorage::getInstance();
	try{
		checkTaskNoValidity(taskNo);
	}
	catch(int errorNo){
		Logger log;
		log.logging(LOGGING_MESSAGE_1);
		throw errorNo; 
	}

	int uniqueCode = display->getUniqueCode(taskNo);
	dataList = deleteDataOfUniqueCode(uniqueCode);

	History::updateLatestCommand(DELETE_WORD); //store for undo
	Logger log;
	log.logging(LOGGING_MESSAGE_7);
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

	try{
		checkTaskNoValidity(taskNo);

	}
	catch (int errorNo){
		Logger log;
		log.logging(LOGGING_MESSAGE_2);
		throw errorNo;
	}

	int uniqueNo = display->getUniqueCode(taskNo);
	Data dataToEdit = getData(uniqueNo);

	dataToEdit = updateData(dataToEdit, updatedData);

	deleteData(taskNo);
	addData(dataToEdit);

	History::updateLatestCommand(EDIT); //Store for undo
	Logger log;
	log.logging(LOGGING_MESSAGE_5);
	
	return display->getData(taskNo);
}

std::string LocalStorage::checkPathName(){
	PrewrittenData prewrittenData;
	std::string directory;
	if (prewrittenData.getPath() != EMPTY_STRING){
		directory = prewrittenData.getPath();
		return directory;
	} else {
		return EMPTY_STRING;
	}
}

//End of API implementation
////////////////////////////////////

/////////////////////////////////////
//Helper methods for internal working


//helper method for deleteData and editData
//check whether input no is within the boundary
//throw exception otherwise
void LocalStorage::checkTaskNoValidity(int taskNo){
	DisplayStorage *display = DisplayStorage::getInstance();
	int listSize = display->getListSize();

	if(taskNo <= ZERO || taskNo > listSize){
		Logger log;
		log.logging(LOGGING_MESSAGE_2);
		throw 1;
	} 
}

//helper method for undoAdd and deleteData
//delete data that have a certain unique code
std::vector<Data> LocalStorage::deleteDataOfUniqueCode(int uniqueCode){
	std::vector<Data> listAfterDeletion;
	for(int i = ZERO; i != dataList.size(); i++){
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
long long LocalStorage::allocateTimeMacroToPsedoDate(TimeMacro time){
	long long pTime;
	long long tempMonth;
	long long tempDate = TEN_THOUSAND;

	//Allocate all components systematically to pTime
	//addition is done slowly to prevent memory loss
	//from changing type;
	pTime= HUNDRED_MILLION;
	pTime= time.getYear()*pTime;
	tempMonth = ONE_MILLION;
	tempMonth = tempMonth * time.getMonth();
	pTime = pTime + tempMonth;
	tempDate = tempDate * time.getDate();
	pTime = pTime + tempDate;

	return pTime;
}

//allocate TimeMicro in addition of TimeMacro to psedodate
long long LocalStorage::allocateTimeMicroToPsedoDate(long long time, TimeMicro tMicro){
	//extract HH/MM
	int hour = tMicro.getHour();
	int min = tMicro.getMin();

	//qualify default hour
	if(hour == TIME_MICRO_DEFAULT){
		hour = ZERO;
		}
	
	//qualify default min
	if(min == TIME_MICRO_DEFAULT){
		min =ZERO;
	}

	time += hour*100 + min; //update psedoData

	return time;
}

//helper method for searchPeriod
//to look for relevant dates
std::vector<long long> LocalStorage::searchRelevantDates(long long pStartTime, long long pEndTime){
	std::vector<long long> saveNo;
	bool marker = false;
	long long time;
	Data copyTask;

	//find first relevant date
	for(int i = ZERO; marker == false && i != dataList.size(); i++){
		copyTask = dataList[i];
		time = copyTask.getPsedoDate();
		if(time >= pStartTime && time <= pEndTime + TIME_MICRO_ADJUSTMENT){
			marker = true;
			saveNo.push_back(i);
		}
	}

	//find last relevant date
	for(int i = dataList.size()-1; marker == true && i != ZERO; i--){
		if(dataList[i].getPsedoDate() <= pEndTime + TIME_MICRO_ADJUSTMENT ) {
			marker = false;
			saveNo.push_back(i);
		}
	}
	return saveNo;
}

//helper method for deleteData and editData
Data LocalStorage::getData(int uniqueNo){
	Data desiredTask;
	for(int i = ZERO; i != dataList.size(); i++){
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
	int i;
	int power = 1;
	std::queue<Data> digitQueue[NO_OF_DIGITS];
	
	allocatePsedoDate();

	for (i=0; i < LENGTH_OF_PSEDODATE; i++) {
		radixDistribute(digitQueue, power);
		radixCollect(digitQueue);
		power *= NO_OF_DIGITS;
	}

}

//helper method for radix sort
//organise items into groups using digit indicated by the power
void LocalStorage::radixDistribute(std::queue<Data> digitQ[], int power){
	int digit;

	for(int i = 0; i != dataList.size(); i++){
		long long sDate = dataList[i].getPsedoDate();
		digit = (sDate / power ) % NO_OF_DIGITS; //extract digit
		digitQ[digit].push(dataList[i]);

	}
}

//helper method for radix sort
//put Data back into dataList
void LocalStorage::radixCollect(std::queue<Data> digitQ[]){
	int digit;
	int i=0;

	for(digit = 0 ; digit < NO_OF_DIGITS; digit++){
		while (!digitQ[digit].empty()) {
			dataList[i] = digitQ[digit].front();
			digitQ[digit].pop();
	
			i++;
		}
	}
}

//allocate psedoDate for all Data in dataList
//for sorting purposes
void LocalStorage::allocatePsedoDate(){
	int i=0;
	long long pDate;

	while(i != dataList.size()){
		TimeMacro tMacro = dataList[i].getTimeMacroBeg();
		pDate = allocateTimeMacroToPsedoDate(tMacro);
				
		TimeMicro tMicro = dataList[i].getTimeMicroBeg();
		pDate = allocateTimeMicroToPsedoDate(pDate, tMicro);

		dataList[i].updatePsedoDate(pDate);
		
		i++;
	}
}

//helper method for edit Data
//go through Data components
//to change what needed
Data LocalStorage::updateData(Data dataToEdit, Data updatedData){
	//update description when there is a change
	if (!updatedData.getDesc().empty()){
		dataToEdit.updateDesc(updatedData.getDesc());
	}

	//update TimeMacro begin when there is a change
	if (updatedData.getTimeMacroBeg().getDate() != TIME_MACRO_DEFAULT 
		&& updatedData.getTimeMacroBeg().getMonth() != TIME_MACRO_DEFAULT
		&& updatedData.getTimeMacroBeg().getYear() != 0) {
			dataToEdit.updateTimeMacroBeg(updatedData.getTimeMacroBeg());
	}

	//update TimeMacro End when there is a change
	if (updatedData.getTimeMacroEnd().getDate() != TIME_MACRO_DEFAULT 
		&& updatedData.getTimeMacroEnd().getMonth() != TIME_MACRO_DEFAULT
		&& updatedData.getTimeMacroEnd().getYear() != TIME_MACRO_DEFAULT) {
			dataToEdit.updateTimeMacroEnd(updatedData.getTimeMacroEnd());
	}

	//update TimeMicro begin when there is a change
	if (updatedData.getTimeMicroBeg().getHour() != TIME_MICRO_DEFAULT
		&& updatedData.getTimeMicroBeg().getMin() != TIME_MICRO_DEFAULT) {
			dataToEdit.updateTimeMicroBeg(updatedData.getTimeMicroBeg());
			dataToEdit.updateTimeMicroEnd(updatedData.getTimeMicroEnd());
	}

	//update AlarmMacro when there is a change
	//alarm is not a supported feature of the software at submission time
	if (updatedData.getAlarmMacro().getDate() != TIME_MACRO_DEFAULT 
		&& updatedData.getAlarmMacro().getMonth() != TIME_MACRO_DEFAULT
		&& updatedData.getAlarmMacro().getYear() != TIME_MACRO_DEFAULT) {
			dataToEdit.updateAlarmMacro(updatedData.getAlarmMacro());
	}
	
	//update AlarmMicro when there is a change
	//alarm is not a supported feature of the software at submission time
	if (updatedData.getAlarmMicro().getHour() != TIME_MICRO_DEFAULT
		&& updatedData.getAlarmMicro().getMin() != TIME_MICRO_DEFAULT) {
			dataToEdit.updateAlarmMicro(updatedData.getAlarmMicro());
	}

	//update complete status when there is a change
	if (updatedData.getCompleteStatus() != dataToEdit.getCompleteStatus()){
		dataToEdit.updateCompleteStatus(updatedData.getCompleteStatus());
	}
	return dataToEdit;
}
//End of Helper Methods for internal working
////////////////////////////////////////////
