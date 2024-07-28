//
// Created by msumi on 12/05/2024.
//

#ifndef SCHEMA_H
#define SCHEMA_H
#include <variant>
#include <unordered_map>
#include "../Util/myFunc.h"
#include "BPlusTree.h"

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

	using BPlusTreeVariant = std::variant<BPlusTree<int>*, BPlusTree<float>*, BPlusTree<string>*>;
    unordered_map<string, BPlusTreeVariant> indexes;
	/**
	 * @author Chullunquia Alonso
	 */
	Schema(const vector<string>& createQuery);
	/**
	 * Devuelve el tamaño total de un registro.
	 * @return tamaño total del registro.
	 */
	int recordSize() const;
	/**
	 * Devuelve el tipo de un atributo, se asunme que el atributo existe.
	 * @param attrName: nombre del atributo.
	 * @return tipo del atributo.
	 */
	string attributeType(string& attrName) const;
};

#endif //SCHEMA_H
