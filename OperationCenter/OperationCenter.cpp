#include "OperationCenter.h"

using namespace std;


void OperationCenter::executeInput(string input){
	Logic::executeInput(input);
}

void OperationCenter::saveData(){
	Logic::saveData();
}

void OperationCenter::loadData(bool& status){
	Logic::loadData(status);
}

string OperationCenter::showWelcomeMessage(bool status){
	return Logic::showWelcomeMessage(status);
}

string OperationCenter::getDisplay(){
	return Feedback::getDisplay();
}

string OperationCenter::getResponse(){
	return Feedback::getResponse();
}

