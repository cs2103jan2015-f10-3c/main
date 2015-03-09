#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <iostream>
#include <cstdio>
#include <sstream>
#include <string>
#include <vector>
#include "Commons.h"


class DataBase {
private:
	
public: 
	DataBase (){
		std::vector<Data> dataList;
	}

	static DataBase getDataList();
	static bool addData();	
	



};



#endif