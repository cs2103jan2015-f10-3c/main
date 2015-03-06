#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "DataStorage.h"

using namespace std;

DataStorage::DataStorage(){
}

void DataStorage::addItem(string item)
{
	setRecentInput("add", item);
	itemList.push_back(item);
	cout <<item<<" added"<<endl;
}

void DataStorage::displayList()
{
	if(!itemList.empty()){
		vector<string>::iterator iter;
		int itemNumber=1;
		for(iter=itemList.begin(); iter!=itemList.end(); ++iter){
		cout << itemNumber << "." << *iter << endl;
		++itemNumber;
		}
	}
	else{
		cout << "There is no task in your list" << endl;
	}
}

void DataStorage::setRecentInput(string command, string item){

	recentInput.push_back(command);
	recentInput.push_back(item);

}

vector<string> DataStorage::getRecentInput(){
	return recentInput;
}

void DataStorage::executeUndo(){
	string command = recentInput[0];
	string item = recentInput[1];
	if(command == "add"){
		itemList.pop_back();
		cout << "\"" << item << "\"" << " is deleted from the list" << endl;
	}
	else if(command == "delete"){
		itemList.push_back(item);
	}

}