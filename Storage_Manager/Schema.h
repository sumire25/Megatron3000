//
// Created by msumi on 12/05/2024.
//

#ifndef SCHEMA_H
#define SCHEMA_H

#include <unordered_map>

#include "../Util/myFunc.h"

class Schema {
public:
	int numAttributes;
	int location;
	string recordType;
	unordered_map<string,tuple<string,int,int>> attributes;

	Schema(vector<string>& relation);
};



#endif //SCHEMA_H
