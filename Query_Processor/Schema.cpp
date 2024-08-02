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
	//agregar indice en el atributo 0
	if(attributes[3].type == "int") {
		indexes[attributes[3].name] = new BPlusTree<int>(BPLUSTREE_DEGREE);
	} else if(attributes[3].type == "float") {
		indexes[attributes[3].name] = new BPlusTree<float>(BPLUSTREE_DEGREE);
	} else {
		indexes[attributes[3].name] = new BPlusTree<string>(BPLUSTREE_DEGREE);
		cerr<<"bptree: string"<<endl;
	}
}

int Schema::recordSize() const {
	int recordSize = 0;
	for(const auto& attr : attributes) {
		recordSize += attr.size;
	}
	return recordSize;
}

string Schema::attributeType(string &attrName) const {
	string type;
	for(const auto& attr : attributes) {
		if(attr.name == attrName) {
			type = attr.type;
			break;
		}
	}
	return type;
}
