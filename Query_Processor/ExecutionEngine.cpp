//
// Created by msumi on 12/05/2024.
//

#include "ExecutionEngine.h"

void ExecutionEngine::insertRecord(string relName, vector<string> &record) {
  string newRecord = formatRecord(record);
  int blockId = getBlock(relName);
  //write record to disk
}

void ExecutionEngine::setDataDictionary() {
  vector<string> metadata = {"Relation_metadata","Fixed","relationName","char","20","numAttributes","int","8","recordType","char","8","location","int","8"};
  addSchema(metadata,1);
  metadata = {"Attribute_metadata","Fixed","relationName","char","20","attributeName","char","20","type","char","5","pos","int","8","length","int","8"};
  addSchema(metadata,11);
  //save schema to disk
}

bool ExecutionEngine::hasRelation(string &relName) {
  if (schemas.find(relName) != schemas.end())
    return 1;
  return 0;
}

void ExecutionEngine::addSchema(vector<string> &relation, int blockId) {
  schemas[relation[0]] = new Schema(relation);
  schemas[relation[0]]->location = blockId;
  addSchematoDisk(relation[0]);
}

void ExecutionEngine::addSchematoDisk(string &relName) {
  vector<string> register_ = {relName,to_string(schemas[relName]->numAttributes),schemas[relName]->recordType,to_string(schemas[relName]->location)};
  //save register to disk

  for(auto &attribute : schemas[relName]->attributes) {
    register_ = {relName,attribute.first,get<0>(attribute.second),to_string(get<1>(attribute.second)),to_string(get<2>(attribute.second))};
    //save register to disk
  }
}

string ExecutionEngine::formatRecord(vector<string> &record) {
  auto& schema = schemas[record[0]];
  if(schema->recordType == "Fixed") {
    return fixedRecord(record, schema);
  } else {
    return variableRecord(record, schema);
  }
}

string ExecutionEngine::fixedRecord(vector<string> &record, Schema *schema) {
  string newRecord;
  tuple<string,int,int> attrInfo;
  for(auto& attribute : schema->attributes) {
    attrInfo = attribute.second;
    if(get<0>(attrInfo) == "int")
      newRecord += myFunc::padString(record[get<1>(attrInfo)+1],get<2>(attrInfo));
    else if(get<0>(attrInfo) == "float")
      newRecord += myFunc::padString(record[get<1>(attrInfo)+1],get<2>(attrInfo));
    else
      newRecord += myFunc::padString(record[get<1>(attrInfo)+1], get<2>(attrInfo));
  }
  return newRecord;
}

string ExecutionEngine::variableRecord(vector<string> &record, Schema *schema) {
  return "";
}

int ExecutionEngine::getBlock(string &relName) {
  auto& schema = schemas[relName];
  return schema->location;
}
