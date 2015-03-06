#include "Parser.h"

vector<string> Parser::parseInput(string userInput){
	
	vector<string> returnInput;
	int commandPosition = userInput.find_first_of(" ");
	returnInput.push_back(userInput.substr(0, commandPosition));
	returnInput.push_back(userInput.substr(commandPosition+1, userInput.length()));

	return returnInput;

}//test