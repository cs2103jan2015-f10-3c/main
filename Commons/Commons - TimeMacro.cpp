//@author A0114002J

#include "Commons.h"
#include <assert.h>

const char TimeMacro::MONDAY[] = "Monday";
const char TimeMacro::TUESDAY[] = "Tuesday";
const char TimeMacro::WEDNESDAY[] = "Wednesday";
const char TimeMacro::THURSDAY[] = "Thursday";
const char TimeMacro::FRIDAY[] = "Friday";
const char TimeMacro::SATURDAY[] = "Saturday";
const char TimeMacro::SUNDAY[] = "Sunday";
const char TimeMacro::UNDEFINED[] = "undefined";
const int TimeMacro::DEFAULT_TIME_MACRO_VALUE = 0;
const int TimeMacro::MAX_MONTH_BOUNDARY = 12;
const int TimeMacro::MAX_DATE_BOUNDARY = 31;
const int TimeMacro::MAX_YEAR_BOUNDARY = 2100;
const int TimeMacro::MIN_YEAR_BOUNDARY = 1900;

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
	assert (inDay == MONDAY || inDay == TUESDAY || 
		inDay == WEDNESDAY || inDay == THURSDAY || 
		inDay == FRIDAY || inDay == SATURDAY || 
		inDay == SUNDAY || inDay == UNDEFINED);

			day = inDay;
}

void TimeMacro::updateDate(int inDate){
	assert (inDate >= DEFAULT_TIME_MACRO_VALUE && inDate <= MAX_DATE_BOUNDARY);
		date = inDate;
}

void TimeMacro::updateMonth(int inMonth){
	assert (inMonth >= DEFAULT_TIME_MACRO_VALUE && inMonth <= MAX_MONTH_BOUNDARY);
		month = inMonth;
}

void TimeMacro::updateYear(int inYear){
	assert (inYear > MIN_YEAR_BOUNDARY && inYear < MAX_YEAR_BOUNDARY || inYear == DEFAULT_TIME_MACRO_VALUE);
		year = inYear;
}