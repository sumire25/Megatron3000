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

  //Insercion de registros de longitud variable en bloque (slotted page)
  void insertVariableRecord(vector<string>& record);
  //Insercion de registros de longitud fija en bloque (unpacked)
  void insertFixedRecord(vector<string>& record);
  //formatRecord devuelte un string ya con el formato indicado ya sea registro de longitud variable o registro de longitud fija
  string formatRecord(vector<string>& record);
  //Da el formato para registo de longitud fija
  string fixedRecord(vector<string>& record, Schema* schema);
  //Da el formato para registo de longitud variable
  string variableRecord(vector<string> record,const Schema& schema);
  //helpers
  int getBlock(string& relName);//return header page del file de la relacion
  bool hasVarRecords(string& relName); //verifica si existe regustros de longitud variable en la relacion
  string schemaToString(Schema* schema); //del objeto schema convierte a string
  vector<string> stringToVector(string &schemaStr, int &pageId); //de un string convierte en un schema
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
