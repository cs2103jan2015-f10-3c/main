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
	//private attribute of internal working
	bool completeStatus; 
	int taskNo;
	int uniqueCode;
	int psedoDate;

	//main attribute for Data
	std::string desc;
	TimeMacro macroTimeBeg;
	TimeMacro macroTimeEnd;
	TimeMicro microTime;


public:

	//constructors
	Data ();
	Data (TimeMacro inMacroBeg, TimeMacro inMacroEnd, TimeMicro inMicro, std::string inDesc);
	Data (std::string inDesc); //constructor for floating task

	//getter methods
	bool getCompleteStatus();
	int getTaskNo();
	int getUniqueCode();
	int getPsedoDate();

	std::string getDesc();
	TimeMacro getTimeMacroBeg();
	TimeMacro getTimeMacroEnd();
	TimeMicro getTimeMicro();



	//update methods
	//return true for succesful operation
	//return false for failed operation
	bool updateTaskNo(int no);
	bool updateUniqueCode(int no);
	bool updateCompleteStatus(bool status);
	bool updatePsedoDate(int sDate);

	bool updateDesc(std::string inDesc);
	bool updateTimeMacroBeg(TimeMacro inMacroBeg);
	bool updateTimeMacroEnd(TimeMacro inMacroEnd);
	bool updateTimeMicro(TimeMicro inMicro);



};



#endif