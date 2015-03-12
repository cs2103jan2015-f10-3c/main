#include "Commons.h"

int TimeMicro::getHour(){
	return hour;
}

int TimeMicro::getMin(){
	return minute;
}

bool TimeMicro::updateHour(int inHour){
	if(inHour >= 0 && inHour <= 24){
		hour = inHour;
		return true;
	} else return false;
}

bool TimeMicro::updateMin(int inMin){
	if(inMin >= 0 && inMin <= 59){
		minute = inMin;
		return true;
	} return false;
}

