#include "OperationCenter.h"

using namespace std;

const string Logic::ADD_COMMAND = "add";
const string Logic::DELETE_COMMAND = "delete";
const string Logic::DISPLAY_COMMAND = "display";
const string Logic::CLEAR_COMMAND = "clear";
const string Logic::SORT_COMMAND = "sort";
const string Logic::SEARCH_COMMAND = "search";
const string Logic::EDIT_COMMAND = "edit";
const string Logic::UNDO_COMMAND = "undo";
const string Logic::EXIT_COMMAND = "exit";
const string Logic::EMPTY_RESPONSE = "";
const string Logic::IVALID_COMMAND_MESSAGE = "Invalid Command";


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

