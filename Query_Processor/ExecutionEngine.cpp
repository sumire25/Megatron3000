//
// Created by msumi on 12/05/2024.
//

#include "ExecutionEngine.h"

void ExecutionEngine::setBuffManRef(BufferManager *buffManRef) {
  this->buffManRef = buffManRef;
}

void ExecutionEngine::insertRecord(vector<string> &record) {
  string newRecord = formatRecord(record);
  //imprime registro// cerr << "Record: " << newRecord << "\n";
  int blockId = getBlock(record[0]);
  if(!buffManRef->pinPage(blockId, RequestType::WRITE)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return;
  }
  Page* header = buffManRef->getPage(blockId);
  header->data->append(newRecord);
  buffManRef->setDirtyFlag(blockId);
  buffManRef->unpinPage(blockId);
  buffManRef->printPageTable();
  buffManRef->printReplacer();
  //write record to disk
}

//LAST WORK: TO MAKE PERSISTENT DB
void ExecutionEngine::setDataDictionary() {
  vector<string> metadata = {"Relation_metadata","Fixed","relationName","char","20","numAttributes","int","8","recordType","char","8","location","int","8"};
  addSchema(metadata,1);
  metadata = {"Attribute_metadata","Fixed","relationName","char","20","attributeName","char","20","type","char","5","pos","int","8","length","int","8"};
  addSchema(metadata,11);
  //printSchemas();
}

bool ExecutionEngine::hasRelation(string &relName) {
  if (schemas.find(relName) != schemas.end())
    return 1;
  return 0;
}

void ExecutionEngine::addSchema(vector<string> &relation, int blockId) {
  schemas[relation[0]] = new Schema(relation);
  schemas[relation[0]]->location = blockId;
  addSchematoDisk(relation[0]);//añadir relacion a las tablas de metadata
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

  //imprimiendo el vector
  /*for(const auto& str : record) {
    std::cout << str <<"; ";
  }
  cout<<endl;*/

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

void ExecutionEngine::printSchemas() {
  for (const auto& pair : schemas) {
    std::cout << "Schema Name: " << pair.first << std::endl;
    Schema* schema = pair.second;
    for (const auto& attribute : schema->attributes) {
      std::cout << "Attribute Name: " << attribute.first << std::endl;
      std::cout << "Type: " << std::get<0>(attribute.second) << std::endl;
      std::cout << "Position: " << std::get<1>(attribute.second) << std::endl;
      std::cout << "Length: " << std::get<2>(attribute.second) << std::endl;
    }
    std::cout << "Location: " << schema->location << std::endl;
    std::cout << "------------------------" << std::endl;
  }
}
