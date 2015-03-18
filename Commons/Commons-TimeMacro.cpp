#include "Commons.h"
#include <assert.h>

std::string TimeMacro::getDay(){
	return day;
}

int TimeMacro::getDate(){
	return date;
}

int TimeMacro::getMonth(){
	return month;
}

int TimeMacro::getYear(){
	return year;
}

void TimeMacro::updateDay(std::string inDay){
	assert (inDay == "Monday" || inDay == "Tuesday" || 
		inDay == "Wednesday" || inDay == "Thursday" || 
		inDay == "Friday" || inDay == "Saturday" || 
		inDay == "Sunday");
			day = inDay;
}

void TimeMacro::updateDate(int inDate){
	assert (inDate > 0 && inDate < 32);
		date = inDate;
}

void TimeMacro::updateMonth(int inMonth){
	assert (inMonth >0 && inMonth <= 12);
		month = inMonth;
}

void TimeMacro::updateYear(int inYear){
	assert (inYear > 1900 && inYear < 2100);
		year = inYear;
}