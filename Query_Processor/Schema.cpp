//
// Created by msumi on 12/05/2024.
//

#include "Schema.h"

Schema::Schema(vector<string>& relation) {
	//layout:relName,recordType,attr1Name,attr1Type,attr1Size,attr2Name,attr2Type,attr2Size,....
	recordType = relation[1];
	int idx;
	for (idx=2; idx<relation.size(); idx=idx+3) {
		cout<<relation[idx]<<relation[idx+1]<<relation[idx+2]<<endl;
		attributes[relation[idx]] = make_tuple(relation[idx + 1], (idx-2)/3, stoi(relation[idx + 2]));
	}
}
