//author A0114002J

#include "Commons.h"

const char Data::NONE[] = "None";
const char Data::LOW[] = "Low";
const char Data::MEDIUM[] = "Med";
const char Data::HIGH[] = "High";

////////////////////////////////
//getter methods implementations
////////////////////////////////


std::string Data::getDesc(){
	return desc;
}

bool Data::getCompleteStatus(){
	return completeStatus;
}

int Data::getTaskNo(){
	return taskNo;
}

int Data::getUniqueCode(){
	return uniqueCode;
}

long long Data::getPsedoDate(){
	return psedoDate;
}

TimeMacro Data::getTimeMacroBeg(){
	return macroTimeBeg;
}

TimeMacro Data::getTimeMacroEnd(){
	return macroTimeEnd;
}

TimeMicro Data::getTimeMicroBeg(){
	return microTimeBeg;
}

TimeMicro Data::getTimeMicroEnd(){
	return microTimeEnd;
}

std::string Data::getPriority(){
	return priority;
}

TimeMacro Data::getAlarmMacro(){
	return alarmMacro;
}

TimeMicro Data::getAlarmMicro(){
	return alarmMicro;
}


////////////////////////////////
//setter methods implementations
////////////////////////////////

void Data::updateTaskNo(int no){
	taskNo = no;
}

void Data::updateUniqueCode(int no){
	uniqueCode = no;
}

void Data::updateCompleteStatus(bool status){
	completeStatus = status;
}

void Data::updatePsedoDate(long long sDate){
	psedoDate = sDate;
}

void Data::updateDesc(std::string inDesc){
	desc = inDesc;
}

void Data::updateTimeMacroBeg(TimeMacro inMacroBeg){
	macroTimeBeg = inMacroBeg;
}

void Data::updateTimeMacroEnd(TimeMacro inMacroEnd){
	macroTimeEnd = inMacroEnd;
}

void Data::updateTimeMicroEnd(TimeMicro inMicroEnd){
	microTimeEnd = inMicroEnd;
}

void Data::updateTimeMicroBeg(TimeMicro inMicroBeg){
	microTimeBeg = inMicroBeg;
}

//@author A0114002J - unused
//Priority and Alarm is not supported by other components
//for this version
void Data::updatePriority(std::string inPriority){
	_ASSERTE ( inPriority == LOW || inPriority == MEDIUM ||
				inPriority == HIGH || inPriority == NONE );

	priority = inPriority;
}

void Data::updateAlarmMacro(TimeMacro inAlarm){
	alarmMacro = inAlarm;
}

void Data::updateAlarmMicro(TimeMicro inAlarm){
	alarmMicro = inAlarm;
}
