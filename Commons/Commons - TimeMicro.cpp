//@author A0114002J

#include "Commons.h"
#include <assert.h>

const int TimeMicro::DEFAULT_TIME_MICRO_VALUE = -1;
const int TimeMicro::MAX_HOUR_BOUNDARY = 24;
const int TimeMicro::MIN_TIME_MICRO_BOUNDARY = 0;
const int TimeMicro::MAX_MIN_BOUNDARY = 59;

int TimeMicro::getHour(){
	return hour;
}

int TimeMicro::getMin(){
	return minute;
}

void TimeMicro::updateHour(int inHour){
	assert (inHour >= MIN_TIME_MICRO_BOUNDARY && inHour <= MAX_HOUR_BOUNDARY || inHour == DEFAULT_TIME_MICRO_VALUE);
		hour = inHour;
		
}

void TimeMicro::updateMin(int inMin){
	assert (inMin >= MIN_TIME_MICRO_BOUNDARY && inMin <= MAX_MIN_BOUNDARY || inMin == DEFAULT_TIME_MICRO_VALUE);
		minute = inMin;
}

