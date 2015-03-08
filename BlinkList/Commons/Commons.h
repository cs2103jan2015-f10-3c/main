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
	TimeMacro () :
		day("undefined"), date(99), month(99), year(9999) {}
	TimeMacro (int inDate, int inMonth, int inYear) :
		day("undefined"), date(inDate), month(inMonth), year(inYear) {}
	TimeMacro (std::string inDay):
		day(inDay), date(99), month(99), year(9999) {}
	TimeMacro (std::string inDay, int inDate, int inMonth, int inYear) :
		day(inDay), date(inDate), month(inMonth), year(inYear) {}

	//getter methods
	int getDate();
	std::string getDay();
	int getMonth();
	int getYear();

	//update methods
	//return true for succesful operation
	//return false for failed operation
	bool updateDate(int inDate);
	bool updateDay(std::string inDay);
	bool updateMonth(int inMonth);
	bool updateYear (int inYear);

};

class TimeMicro{
private:
	int hourBeg;
	int minuteBeg;
	int hourEnd;
	int minuteEnd;

public:

	//constructors
	TimeMicro ();
	TimeMicro (int inHourbeg, int inMinBeg, int inHourEnd, int inMinEnd);

	//getter methods
	int getHourBeg();
	int getHourEnd();
	int getMinBeg();
	int getMinEnd();

	//update methods
	//return true for succesful operation
	//return false for failed operation
	bool updateHourBeg(int inHour);
	bool updateHourEnd(int inHour);
	bool updateMinBeg(int inMin);
	bool updateMinEnd(int inMin);
};


class Data {
private:
	bool completeStatus;
	int taskNo;
	std::string desc;
	TimeMacro macroTime;
	TimeMicro microTime;


public:

	//constructors
	Data ();
	Data (TimeMacro inMacro, TimeMicro inMicro, std::string inDesc);
	Data (std::string inDesc); //constructor for floating task

	//getter methods
	bool getCompleteStatus();
	int getTaskNo();
	std::string getDesc();
	TimeMacro getTimeMacro();
	TimeMicro getTimeMicro();

	//update methods
	//return true for succesful operation
	//return false for failed operation
	bool updateCompleteStatus();
	bool updateDesc(std::string inDesc);
	bool updateTimeMacro(TimeMacro inMacro);
	bool updateTimeMicro(TimeMicro inMicro);



};



#endif