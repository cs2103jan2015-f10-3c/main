#pragma once

#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>
#include <vector>
#include <fstream>


class TimeMacro{
private:
	static const char MONDAY[10];
	static const char TUESDAY[10];
	static const char WEDNESDAY[10];
	static const char THURSDAY[10];
	static const char FRIDAY[10];
	static const char SATURDAY[10];
	static const char SUNDAY[10];
	static const char UNDEFINED[10];
	static const int DEFAULT_TIME_MACRO_VALUE;
	static const int MAX_MONTH_BOUNDARY;
	static const int MAX_DATE_BOUNDARY;
	static const int MAX_YEAR_BOUNDARY;
	static const int MIN_YEAR_BOUNDARY;

	//private attributes
	std::string day;
	int date;
	int month;
	int year;

public:

	//constructors 
	TimeMacro () :
		day(UNDEFINED), date(DEFAULT_TIME_MACRO_VALUE), month(DEFAULT_TIME_MACRO_VALUE), year(DEFAULT_TIME_MACRO_VALUE) {}
	TimeMacro (int inDate, int inMonth, int inYear) :
		day(UNDEFINED), date(inDate), month(inMonth), year(inYear) {}
	TimeMacro (std::string inDay):
		day(inDay), date(DEFAULT_TIME_MACRO_VALUE), month(DEFAULT_TIME_MACRO_VALUE), year(DEFAULT_TIME_MACRO_VALUE) {}
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
	static const int DEFAULT_TIME_MICRO_VALUE;
	static const int MAX_HOUR_BOUNDARY;
	static const int MIN_TIME_MICRO_BOUNDARY;
	static const int MAX_MIN_BOUNDARY;

	int hour;
	int minute;

public:

	//constructors
	TimeMicro () :
		hour(DEFAULT_TIME_MICRO_VALUE),minute(DEFAULT_TIME_MICRO_VALUE) {}

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
private:
	static const char NONE[10];
	static const char LOW[10];
	static const char MEDIUM[10];
	static const char HIGH[10];

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
	completeStatus(false), priority(NONE) {} 

	// constructor for activities that start and end at different days
	Data (TimeMacro inMacroBeg, TimeMacro inMacroEnd, TimeMicro inMicroBeg, 
		TimeMicro inMicroEnd, std::string inDesc) : 
		macroTimeBeg(inMacroBeg), macroTimeEnd(inMacroEnd), microTimeBeg(inMicroBeg), 
		microTimeEnd(inMicroEnd), desc(inDesc), completeStatus(false), priority (NONE) {} 

	//constructor for activities that start and end at the same time
	Data (TimeMacro inMacro, TimeMicro inMicroBeg, TimeMicro inMicroEnd, std::string inDesc) :
		macroTimeBeg(inMacro), microTimeBeg(inMicroBeg), microTimeEnd(inMicroEnd), 
		desc(inDesc), completeStatus(false), priority(NONE) {}

	//constructor for activities that only have a deadline
	Data (TimeMacro inMacro, std::string inDesc) :
		macroTimeBeg(inMacro), desc(inDesc), completeStatus(false), priority(NONE) {}

	//constructor for floating task
	Data (std::string inDesc) : 
		desc(inDesc), completeStatus(false), priority(NONE) {}
	

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

class log{
private: 
	std::ofstream writeLog;
	std::string directory;

public:
	void logging(std::string inputMessage){
		std::string directory = "log.txt";
		writeLog.open(directory.c_str() , std::ofstream::app);
		writeLog << inputMessage;
	}

	void deleteLogContent(){
		std::string directory = "log.txt";
		writeLog.open(directory.c_str() , std::ofstream::app);
	}

};
