//
// Created by msumi on 12/05/2024.
//

#include "Schema.h"

Schema::Schema(const vector<string>& createQuery) {

	//layout:relName,recordType,attr1Name,attr1Type,attr1Size,attr2Name,attr2Type,attr2Size,....

	relationName = createQuery[0];
	if(createQuery[1] == "Variable")
		isVarLength = true;
	numAttr = (createQuery.size()-2) / 3;
	int idx;
	for(int i = 0; i < numAttr; i++) {
		idx = 2 + i*3;
		attributes.push_back({createQuery[idx],createQuery[idx+1],stoi(createQuery[idx+2])});
	}
}
