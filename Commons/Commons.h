#ifndef COMMONS_H_
#define COMMONS_H_

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
	//default is day("undefined"), date(00), month(00), year(0000)
	//if it's default it means, there is no input
	//UI should not display default
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

	//update methods
	//return true for succesful operation
	//return false for failed operation
	bool updateDay(std::string inDay);
	bool updateDate(int inDate);
	bool updateMonth(int inMonth);
	bool updateYear (int inYear);

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
	//return true for succesful operation
	//return false for failed operation
	bool updateHour(int inHour);
	bool updateMin(int inMin);
};


class Data {
public:
	//private attribute of internal working
	bool completeStatus; 
	int taskNo;
	int uniqueCode;
	long long psedoDate;

	//main attribute for Data
	std::string desc;
	TimeMacro macroTimeBeg;
	TimeMacro macroTimeEnd;
	TimeMicro microTimeBeg;
	TimeMicro microTimeEnd;


public:

	//constructors
	//constructor for custom Data
	Data () {} 
	// constructor for activities that start and end at different days
	Data (TimeMacro inMacroBeg, TimeMacro inMacroEnd, TimeMicro inMicroBeg, 
		TimeMicro inMicroEnd, std::string inDesc) : 
		macroTimeBeg(inMacroBeg), macroTimeEnd(inMacroEnd), microTimeBeg(inMicroBeg), 
		microTimeEnd(inMicroEnd), desc(inDesc) {} 
	//constructor for activities that start and end at the same time
	Data (TimeMacro inMacro, TimeMicro inMicroBeg, TimeMicro inMicroEnd, std::string inDesc) :
		macroTimeBeg(inMacro), microTimeBeg(inMicroBeg), microTimeEnd(inMicroEnd), desc(inDesc) {}
	//constructor for activities that only have a deadline
	Data (TimeMacro inMacro, std::string inDesc) :
		macroTimeBeg(inMacro), desc(inDesc) {}
	//constructor for floating task
	Data (std::string inDesc) : 
		desc(inDesc) {}
	

	//getter methods
	bool getCompleteStatus();
	int getTaskNo();
	int getUniqueCode();
	long long getPsedoDate();

	std::string getDesc();
	TimeMacro getTimeMacroBeg();
	TimeMacro getTimeMacroEnd();
	TimeMicro getTimeMicroBeg();
	TimeMicro getTimeMicroEnd();



	//update methods
	//return true for succesful operation
	//return false for failed operation
	void updateTaskNo(int no);
	void updateUniqueCode(int no);
	void updateCompleteStatus(bool status);
	void updatePsedoDate(long long sDate);

	void updateDesc(std::string inDesc);
	void updateTimeMacroBeg(TimeMacro inMacroBeg);
	void updateTimeMacroEnd(TimeMacro inMacroEnd);
	void updateTimeMicroBeg(TimeMicro inMicroBeg);
	void updateTimeMicroEnd(TimeMicro inMicroEnd);



};



#endif