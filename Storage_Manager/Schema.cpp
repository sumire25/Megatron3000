//
// Created by msumi on 12/05/2024.
//

#include "Schema.h"

Schema::Schema(vector<string>& relation) {
	int idx;
	bool isFixed = true;
	numAttributes = (relation.size()-1) / 3;
	for (idx=0; idx<numAttributes; idx++) {
		if (relation[3*idx + 3] == "0")
			isFixed = false;
		attributes[relation[3*idx + 1]] = make_tuple(relation[3*idx + 2], idx, stoi(relation[3*idx + 3]));
	}
	if (isFixed)
		recordType = "Fixed";
	else
		recordType = "Variable";
}
