#include "Commons.h"

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

bool TimeMacro::updateDay(std::string inDay){
	if (inDay == "Monday" || inDay == "Tuesday" || 
		inDay == "Wednesday" || inDay == "Thrusday" || 
		inDay == "Friday" || inDay == "Saturday" || 
		inDay == "Sunday"){
			day = inDay;
			return true;
	} else return false;
}

bool TimeMacro::updateDate(int inDate){
	if (inDate > 0 && inDate < 32){
		date = inDate;
		return true;
	} else return false;
}

bool TimeMacro::updateMonth(int inMonth){
	if (inMonth >0 && inMonth < 12){
		month = inMonth;
		return true;
	} else return false;
}

bool TimeMacro::updateYear(int inYear){
	if (inYear > 1900 && inYear < 2100){
		year = inYear;
		return true;
	} else return false;
}