#ifndef OPERATIONCENTER_H
#define OPERATIONCENTER_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include "Commons.h"
#include "DataProcessor.h"
#include "Parser.h"
#include "DataStorage.h"

using namespace std;
class OperationCenter{


public:

	OperationCenter();
	string executeInput (string input);

};

#endif