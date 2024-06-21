//
// Created by msumi on 12/05/2024.
//

#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include <unordered_map>

#include "../Buffer/BufferManager.h"
#include "Schema.h"

class ExecutionEngine {
private:
  BufferManager* buffManRef;
  unordered_map<string, Schema*> schemas;
public:
  void setBuffManRef(BufferManager* buffManRef);
  void addSchema(vector<string>& relation, int blockId);
  void insertRecord(vector<string>& record);

  int getBlock(string& relName);//return header page del file de la relacion
  bool hasRelation(string& relName);
  string formatRecord(vector<string>& record);
  string fixedRecord(vector<string>& record, Schema* schema);
  string variableRecord(vector<string>& record, Schema* schema);

  //function which prints all the schemas
  void printSchemas();

  //POR IMPLEMENTAR
  void setDataDictionary();
  void addSchematoDisk(string& relName);
};



#endif //EXECUTIONENGINE_H
