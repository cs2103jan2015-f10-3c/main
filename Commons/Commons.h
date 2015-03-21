#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <vector>

class TimeMacro{
private:

	//private attributes
	std::string day;
	int date;
	int month;
	int year;

	

public:

	//constructors 
	TimeMacro () :
		day("undefined"), date(00), month(00), year(0000) {}
	TimeMacro (int inDate, int inMonth, int inYear) :
		day("undefined"), date(inDate), month(inMonth), year(inYear) {}
	TimeMacro (std::string inDay):
		day(inDay), date(00), month(00), year(0000) {}
	TimeMacro (std::string inDay, int inDate, int inMonth, int inYear) :
		day(inDay), date(inDate), month(inMonth), year(inYear) {}

	//getter methods
	std::string getDay();
	int getDate();
	int getMonth();
	int getYear();

	//setter methods
	void updateDay(std::string inDay);
	void updateDate(int inDate);
	void updateMonth(int inMonth);
	void updateYear (int inYear);

};

class TimeMicro{
private:
	int hour;
	int minute;

public:

	//constructors
	TimeMicro () :
		hour(-1),minute(-1) {}

	TimeMicro (int inHourBeg, int inMinBeg) :
		hour(inHourBeg), minute(inMinBeg){}

	//getter methods
	int getHour();
	int getMin();

	//update methods
	void updateHour(int inHour);
	void updateMin(int inMin);
};


class Data {
public:
	//private attributes of internal working
	int taskNo;
	int uniqueCode;
	long long psedoDate;

	//private attributes for User
	std::string desc;
	TimeMacro macroTimeBeg;
	TimeMacro macroTimeEnd;
	TimeMicro microTimeBeg;
	TimeMicro microTimeEnd;
	bool completeStatus; 
	std::string priority;
	TimeMacro alarmMacro;
	TimeMicro alarmMicro;


public:

	//constructors
	//constructor for custom Data
	Data () :
	completeStatus(false), priority("None") {} 

	// constructor for activities that start and end at different days
	Data (TimeMacro inMacroBeg, TimeMacro inMacroEnd, TimeMicro inMicroBeg, 
		TimeMicro inMicroEnd, std::string inDesc) : 
		macroTimeBeg(inMacroBeg), macroTimeEnd(inMacroEnd), microTimeBeg(inMicroBeg), 
		microTimeEnd(inMicroEnd), desc(inDesc), completeStatus(false), priority ("None") {} 

	//constructor for activities that start and end at the same time
	Data (TimeMacro inMacro, TimeMicro inMicroBeg, TimeMicro inMicroEnd, std::string inDesc) :
		macroTimeBeg(inMacro), microTimeBeg(inMicroBeg), microTimeEnd(inMicroEnd), 
		desc(inDesc), completeStatus(false), priority("None") {}

	//constructor for activities that only have a deadline
	Data (TimeMacro inMacro, std::string inDesc) :
		macroTimeBeg(inMacro), desc(inDesc), completeStatus(false), priority("None") {}

	//constructor for floating task
	Data (std::string inDesc) : 
		desc(inDesc), completeStatus(false), priority("None") {}
	

	//getter methods
	int getTaskNo();
	int getUniqueCode();
	long long getPsedoDate();

	std::string getDesc();
	TimeMacro getTimeMacroBeg();
	TimeMacro getTimeMacroEnd();
	TimeMicro getTimeMicroBeg();
	TimeMicro getTimeMicroEnd();
	bool getCompleteStatus();
	std::string getPriority();
	TimeMacro getAlarmMacro();
	TimeMicro getAlarmMicro();


	//update methods
	void updateTaskNo(int no);
	void updateUniqueCode(int no);
	void updatePsedoDate(long long sDate);

	void updateDesc(std::string inDesc);
	void updateTimeMacroBeg(TimeMacro inMacroBeg);
	void updateTimeMacroEnd(TimeMacro inMacroEnd);
	void updateTimeMicroBeg(TimeMicro inMicroBeg);
	void updateTimeMicroEnd(TimeMicro inMicroEnd);
	void updateCompleteStatus(bool status);
	void updatePriority(std::string inPriority);
	void updateAlarmMacro(TimeMacro inAlarm);
	void updateAlarmMicro(TimeMicro inAlarm);


};
