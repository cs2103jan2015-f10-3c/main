#ifndef OPERATIONCENTER_H
#define OPERATIONCENTER_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include "Parser.h"
#include "DataStorage.h"

using namespace std;

class OperationCenter{

public:

	void executeCommand(string command, string item);

};
#endif