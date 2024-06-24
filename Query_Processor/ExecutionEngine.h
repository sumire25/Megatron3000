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
  /**
   *@author Suni Yanira
   */
private:
  BufferManager* buffManRef;
  DiskManager* diskManRef;
  unordered_map<string, Schema*> schemas;

  //Insercion de registros
  void insertVariableRecord(vector<string>& record);
  void insertFixedRecord(vector<string>& record);
  //Formateo de registros
  string formatRecord(vector<string>& record);
  string fixedRecord(vector<string>& record, Schema* schema);
  string variableRecord(vector<string> record,const Schema& schema);
  //helpers
  int getBlock(string& relName);//return header page del file de la relacion
  bool hasVarRecords(string& relName);
  string schemaToString(Schema* schema);
  vector<string> stringToVector(string &schemaStr, int &pageId);
public:
  /**
   *@author Chullunquia Alonso
   */
  ~ExecutionEngine();
  void setBuffManRef(BufferManager* buffManRef);
  void setDiskManRef(DiskManager* diskManRef);
  void readSchemasFromFile();
  void writeSchemasToFile();

  void addSchema(vector<string>& relation, int blockId);//crea y agrega un esquema a la tabla de esquemas
  void insertRecord(vector<string>& record);
  string getPageContent(int& blockId);
  bool hasRelation(string& relName);

  //function which prints all the schemas
  void printSchemas();

  //POR IMPLEMENTAR
  void setDataDictionary();
  void addSchematoDisk(string& relName);
};



#endif //EXECUTIONENGINE_H
