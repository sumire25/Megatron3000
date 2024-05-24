//
// Created by msumi on 12/05/2024.
//

#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include <unordered_map>

#include "../Util/myFunc.h"
#include "Schema.h"

class ExecutionEngine {
private:
  unordered_map<string, Schema*> schemas;
public:
  void insertRecord(string relName, vector<string>& record);
  void setDataDictionary();
  bool hasRelation(string& relName);
  void addSchema(vector<string>& relation, int blockId);
  void addSchematoDisk(string& relName);
  string formatRecord(vector<string>& record);
  string fixedRecord(vector<string>& record, Schema* schema);
  string variableRecord(vector<string>& record, Schema* schema);

  int getBlock(string& relName);
};



#endif //EXECUTIONENGINE_H
