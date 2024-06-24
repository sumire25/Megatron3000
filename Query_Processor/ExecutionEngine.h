//
// Created by msumi on 12/05/2024.
//

#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include <unordered_map>

#include "../Buffer_Manager/BufferManager.h"
#include "../Util/myFunc.h"
#include "pageEdit.h"
#include "Schema.h"

class ExecutionEngine {
private:
  BufferManager* buffManRef;
  DiskManager* diskManRef;
  unordered_map<string, Schema*> schemas;
public:
  void setBuffManRef(BufferManager* buffManRef);
  void setDiskManRef(DiskManager* diskManRef);
  void addSchema(vector<string>& relation, int blockId);
  void insertRecord(vector<string>& record);
  void insertVariableRecord(vector<string>& record);
  void insertFixedRecord(vector<string>& record);

  int getBlock(string& relName);//return header page del file de la relacion
  bool hasRelation(string& relName);
  bool hasVarRecords(string& relName);
  string formatRecord(vector<string>& record);
  string fixedRecord(vector<string>& record, Schema* schema);
  string variableRecord(vector<string> record,const Schema& schema);

  //function which prints all the schemas
  void printSchemas();
  string schemaToString(Schema* schema);
  void writeSchemasToFile();
  void readSchemasFromFile();
  vector<string> readSchemaFromFile();

  //POR IMPLEMENTAR
  void setDataDictionary();
  void addSchematoDisk(string& relName);
};



#endif //EXECUTIONENGINE_H
