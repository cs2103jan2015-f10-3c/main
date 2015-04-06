#include "Commons.h"

const char Logger::LOG_FILE_NAME[] = "log.txt";

void Logger::logging(std::string inputMessage){
	std::string directory = LOG_FILE_NAME;
	writeLog.open(directory.c_str() , std::ofstream::app);
	writeLog << inputMessage << '\n';
}

void Logger::deleteLogContent(){
	std::string directory = LOG_FILE_NAME;
	writeLog.open(directory.c_str() , std::ofstream::app);
}