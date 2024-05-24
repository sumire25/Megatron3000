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
	// <attributeName, <attributeType, offset, length>>
	unordered_map<string,tuple<string,int,int>> attributes;

	Schema(vector<string>& relation);

	// Attribute access
	tuple<string, int, int> getAttribute(const string& attributeName);
	tuple<string, int, int> getAttribute(int index);

	// Record conversion
	string recordToString(const unordered_map<string, string>& record);
	unordered_map<string, string> stringToRecord(const string& recordString);

	// Search
	vector<unordered_map<string, string>> searchRecords(const string& condition);
};



#endif //SCHEMA_H
