#include "Commons.h"

int TimeMicro::getHour(){
	return hour;
}

int TimeMicro::getMin(){
	return minute;
}

void TimeMicro::updateHour(int inHour){
	_ASSERT (inHour >= 0 && inHour <= 24);
		hour = inHour;
		
}

void TimeMicro::updateMin(int inMin){
	_ASSERT (inMin >= 0 && inMin <= 59);
		minute = inMin;
}

