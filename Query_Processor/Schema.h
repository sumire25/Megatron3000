//
// Created by msumi on 12/05/2024.
//

#ifndef SCHEMA_H
#define SCHEMA_H
gi
#include "../Util/myFunc.h"

struct Attribute {
	string name;
	string type;
	int size;
};
class Schema {
public:
	string relationName;
	int numAttr = 0;
	bool isVarLength = false;
	int headerPageId;

	vector<Attribute> attributes;
	/**
	 * @author Chullunquia Alonso
	 */
	Schema(const vector<string>& createQuery);
};

#endif //SCHEMA_H
