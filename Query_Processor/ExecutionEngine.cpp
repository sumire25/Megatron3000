#include "ExecutionEngine.h"

void ExecutionEngine::setBuffManRef(BufferManager *buffManRef) {
  this->buffManRef = buffManRef;
}

void ExecutionEngine::insertRecord(vector<string> &record) {
  RID* rid;
  if(hasVarRecords(record[0]))
    rid = insertVariableRecord(record);
  else
    rid = insertFixedRecord(record);
  buffManRef->printRequestQueue();
  buffManRef->printPageTable();
  buffManRef->printReplacer();
  addIndexEntry(record, rid);

}

string ExecutionEngine::getPageContent(int &blockId) {
  if(!buffManRef->pinPage(blockId, RequestType::READ)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return "";
  }
  Page* page = buffManRef->getPage(blockId);
  string content = *page->data;
  buffManRef->unpinPage(blockId);
  return content;
}

RID* ExecutionEngine::insertVariableRecord(vector<string> &record) {
  RID* rid = nullptr;
  string newRecord = formatRecord(record);
  cerr<<"newRecord: '"<<newRecord<<"'"<<endl;
  int recordSize = newRecord.size();
  //solicitar headerPage
  int headerBlockId = getBlock(record[0]);
  if(!buffManRef->pinPage(headerBlockId, RequestType::WRITE)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return rid;
  }
  Page* header = buffManRef->getPage(headerBlockId);
  //buscar pagina con espacio disponible
  bool allocated = false;
  int freePage = pageEdit::getAndUpdateFreePage(*(header->data),recordSize,true);
  if(freePage == -1) {
    freePage = buffManRef->allocNextBlock(headerBlockId);
    allocated = true;
  }
  //solicitar pagina con espacio disponible, y añadir registro
  if(!buffManRef->pinPage(freePage, RequestType::WRITE)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return rid;
  }
  Page* pageToWrite = buffManRef->getPage(freePage);
  if(allocated) {
    *(pageToWrite->data) = pageEdit::setNewSlotted(PAGE_SIZE);
    int freeSpace = PAGE_SIZE - (NUM_RECORDS_SIZE+VAR_OFFSET_SIZE) - (VAR_OFFSET_SIZE+VAR_LENGTH_SIZE) - recordSize;
    pageEdit::addNewPageToDirectory(*(header->data),freePage,freeSpace);
  }
  int slot = pageEdit::insertSlotted(*(pageToWrite->data),newRecord);
  buffManRef->setDirtyFlag(freePage);
  buffManRef->unpinPage(freePage);
  //actualizar headerPage y liberarla
  buffManRef->setDirtyFlag(headerBlockId);
  buffManRef->unpinPage(headerBlockId);

  rid =  new RID(freePage,slot);
  cerr<<"RID: "<<rid->GetPageId()<<", "<<rid->GetSlotNum()<<endl;
  return rid;
}

RID* ExecutionEngine::insertFixedRecord(vector<string> &record) {
  RID* rid = nullptr;
  string newRecord = formatRecord(record);
  int recordSize = newRecord.size();
  cerr<<"newRecord: '"<<newRecord<<"'"<<endl;
  //solicitar headerPage
  int headerBlockId = getBlock(record[0]);
  if(!buffManRef->pinPage(headerBlockId, RequestType::WRITE)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return rid;
  }
  Page* header = buffManRef->getPage(headerBlockId);
  cout<< "page header antes:"<<*(header->data) <<endl;
  //buscar pagina con espacio disponible
  bool allocated = false;
  int freePage = pageEdit::getAndUpdateFreePage(*(header->data),recordSize,false);
  if(freePage == -1) {
    freePage = buffManRef->allocNextBlock(headerBlockId);
    allocated = true;
  }
  //solicitar pagina con espacio disponible, y añadir registro
  if(!buffManRef->pinPage(freePage, RequestType::WRITE)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return rid;
  }
  Page* pageToWrite = buffManRef->getPage(freePage);
  cout<< "freepage antes:"<<*(pageToWrite->data) <<endl;
  if(allocated) {
    pageEdit::setNewUnpacked(*(pageToWrite->data),recordSize);
    int freeSpace = PAGE_SIZE - (recordSize+1) - NUM_RECORDS_SIZE - 1;
    pageEdit::addNewPageToDirectory(*(header->data),freePage,freeSpace);
  }
  cout<< "page header despues:"<<*(header->data) <<endl;
  int slot = pageEdit::insertUnpacked(*(pageToWrite->data),newRecord);
  cout<< "freepage después:"<<*(pageToWrite->data) <<endl;
  buffManRef->setDirtyFlag(freePage);
  buffManRef->unpinPage(freePage);
  //actualizar headerPage y liberarla
  buffManRef->setDirtyFlag(headerBlockId);
  buffManRef->unpinPage(headerBlockId);
  //create Rid;
  rid =  new RID(freePage,slot);
  cerr<<"RID: "<<rid->GetPageId()<<", "<<rid->GetSlotNum()<<endl;
  return rid;
}

//LAST WORK: TO MAKE PERSISTENT DB
void ExecutionEngine::setDataDictionary() {
  vector<string> metadata = {"Relation_metadata","Fixed","relationName","char","20","numAttributes","int","8","recordType","char","8","location","int","8"};
  //addSchema(metadata,1);
  metadata = {"Attribute_metadata","Fixed","relationName","char","20","attributeName","char","20","type","char","5","pos","int","8","length","int","8"};
  //addSchema(metadata,11);
  //printSchemas();
}

bool ExecutionEngine::hasRelation(string &relName) {
  if (schemas.find(relName) != schemas.end())
    return 1;
  return 0;
}

void ExecutionEngine::printSchemas() {
  // imprimir todos los esquemas
  for(auto& schema : schemas) {
    //cout << schemaToString(schema.second) << endl;
    cout << "-----------------------------------" << endl;
    cout << "Relation: " << schema.second->relationName << endl;
    cout << "IsVarLength: " << schema.second->isVarLength << endl;
    cout << "HeaderPageId: " << schema.second->headerPageId << endl;
    cout << "Attributes: " << endl;
    for(auto& attr : schema.second->attributes) {
      cout << "Name: " << attr.name << " Type: " << attr.type << " Size: " << attr.size << endl;
    }
    cout << "-----------------------------------" << endl;
  }
}

bool ExecutionEngine::hasVarRecords(string &relName) {
  auto& schema = schemas[relName];
  return schema->isVarLength;
}

void ExecutionEngine::addSchema(vector<string> &relation) {
  int headerPageId = buffManRef->allocRandomBlock();
  loadSchema(relation, headerPageId);
  if(!buffManRef->pinPage(headerPageId, RequestType::WRITE)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return;
  }
  // extrae y edita el contenido de la pagina header
  Page* header = buffManRef->getPage(headerPageId);
  pageEdit::setNewPageHeader(*(header->data));
  // liberar la pagina
  buffManRef->setDirtyFlag(headerPageId);
  buffManRef->unpinPage(headerPageId);
}
void ExecutionEngine::loadSchema(vector<string> &createQuery, int headerPageId) {
  schemas[createQuery[0]] = new Schema(createQuery);
  schemas[createQuery[0]]->headerPageId = headerPageId;
}

void ExecutionEngine::addSchematoDisk(string &relName) {
}

string ExecutionEngine::selectRecord(vector<string> &selectQuery) {
  //verificar si esiste la relacion
  if(!hasRelation(selectQuery[0])) {
    cerr<<"No existe la relacion"<<endl;
    return "";
  }
  auto& schema = schemas[selectQuery[0]];
  if(schema->indexes.find(selectQuery[1]) != schema->indexes.end()) {
    string type = schema->attributeType(selectQuery[1]);
    RID* rid = nullptr;
    if(type == "int") {
      rid = std::get<BPlusTree<int>*>(schema->indexes[selectQuery[1]])->search(stoi(selectQuery[2]));
    }
    else if(type == "float") {
      rid = std::get<BPlusTree<float>*>(schema->indexes[selectQuery[1]])->search(stof(selectQuery[2]));
    }
    else {
      rid = std::get<BPlusTree<string>*>(schema->indexes[selectQuery[1]])->search(selectQuery[2]);
    }
    if(!rid) {
      cerr<<"No se encontro el registro"<<endl;
      return "";
    }
    //print rid
    cerr<<"RID: "<<rid->GetPageId()<<", "<<rid->GetSlotNum()<<endl;
    if(!buffManRef->pinPage(rid->GetPageId(), RequestType::READ)) {
      cerr<<"Error al pinnear pagina"<<endl;
      return "";
    }
    Page* page = buffManRef->getPage(rid->GetPageId());
    string record = "";
    if(!schema->isVarLength)
      record = pageEdit::selectRecordUnpacked(*(page->data),rid->GetSlotNum(), schema->recordSize());
    else {
      record = pageEdit::obtenerContenidoRegistro(*(page->data),rid->GetSlotNum());
    }
    //imprimir página
    cout<<"<"<<*(page->data)<<">"<<endl;
    buffManRef->unpinPage(rid->GetPageId());
    buffManRef->printRequestQueue();
    buffManRef->printPageTable();
    buffManRef->printReplacer();
    return record;
  }
  cerr << "No existe un indice sobre el atributo" << endl;
  return "";
}

void ExecutionEngine::addIndexEntry(vector<string> &record, RID *rid) {
  auto& schema = schemas[record[0]];//extrayendo el esquema de la relacion
  //recorrer todos los atributos de la relacion, y verificar si tiene un indice
  for(int i=0; i<schema->numAttr; i++) {
    if(schema->indexes.find(schema->attributes[i].name) != schema->indexes.end()) {
      string type = schema->attributeType(schema->attributes[i].name);
      if(type == "int") {
        std::get<BPlusTree<int>*>(schema->indexes[schema->attributes[i].name])->insert(stoi(record[i+1]), rid);
      }
      else if(type == "float") {
        std::get<BPlusTree<float>*>(schema->indexes[schema->attributes[i].name])->insert(stof(record[i+1]), rid);
      }
      else {
        std::get<BPlusTree<string>*>(schema->indexes[schema->attributes[i].name])->insert(record[i+1], rid);
      }
    }
  }
}

void ExecutionEngine::deleteIndexEntry(vector<string> &deleteQuery) {
  auto& schema = schemas[deleteQuery[0]];
  //buscar indice en el atributo
  if(schema->indexes.find(deleteQuery[1]) != schema->indexes.end()) {
    string type = schema->attributeType(deleteQuery[1]);
    if(type == "int") {
      std::get<BPlusTree<int>*>(schema->indexes[deleteQuery[1]])->remove(stoi(deleteQuery[2]));
    }
    else if(type == "float") {
      std::get<BPlusTree<float>*>(schema->indexes[deleteQuery[1]])->remove(stof(deleteQuery[2]));
    }
    else {
      std::get<BPlusTree<string>*>(schema->indexes[deleteQuery[1]])->remove(deleteQuery[2]);
    }
  }
}

void ExecutionEngine::deleteRecord(vector<string> &deleteQuery) {
  //verificar si esiste la relacion
  if(!hasRelation(deleteQuery[0])) {
    cerr<<"No existe la relacion"<<endl;
    return;
  }
  auto& schema = schemas[deleteQuery[0]];
  if(schema->indexes.find(deleteQuery[1]) != schema->indexes.end()) {
    string type = schema->attributeType(deleteQuery[1]);
    RID* rid = nullptr;
    if(type == "int") {
      rid = std::get<BPlusTree<int>*>(schema->indexes[deleteQuery[1]])->search(stoi(deleteQuery[2]));
    }
    else if(type == "float") {
      rid = std::get<BPlusTree<float>*>(schema->indexes[deleteQuery[1]])->search(stof(deleteQuery[2]));
    }
    else {
      rid = std::get<BPlusTree<string>*>(schema->indexes[deleteQuery[1]])->search(deleteQuery[2]);
    }
    if(!rid) {
      cerr<<"No se encontro el registro"<<endl;
      return;
    }
    if(!buffManRef->pinPage(rid->GetPageId(), RequestType::WRITE)) {
      cerr<<"Error al pinnear pagina"<<endl;
      return;
    }
    Page* page = buffManRef->getPage(rid->GetPageId());
    cerr << "Before: <"<<*(page->data)<<">"<<endl;
    if(!schema->isVarLength)
      pageEdit::deleteRecordUnpacked(*(page->data),rid->GetSlotNum(), schema->recordSize());
    else {
      pageEdit::eliminarRegistro(*(page->data),rid->GetSlotNum());
    }
    cerr << "After: <"<<*(page->data)<<">"<<endl;
    buffManRef->setDirtyFlag(rid->GetPageId());
    buffManRef->unpinPage(rid->GetPageId());
    deleteIndexEntry(deleteQuery);

    buffManRef->printRequestQueue();
    buffManRef->printPageTable();
    buffManRef->printReplacer();
    return;
  }
  cerr << "No existe un indice sobre el atributo" << endl;
}

void ExecutionEngine::graficarArbol(vector<string> & query) {
  auto& schema = schemas[query[0]];//extrayendo el esquema de la relacion
  for(int i=0; i<schema->numAttr; i++) {
    if(schema->indexes.find(schema->attributes[i].name) != schema->indexes.end()) {
      string type = schema->attributeType(schema->attributes[i].name);
      if(type == "int") {
        std::get<BPlusTree<int>*>(schema->indexes[schema->attributes[i].name])->genDotFile();
      }
      else if(type == "float") {
        std::get<BPlusTree<float>*>(schema->indexes[schema->attributes[i].name])->genDotFile();
      }
      else {
        std::get<BPlusTree<string>*>(schema->indexes[schema->attributes[i].name])->genDotFile();
      }
    }
  }
}

string ExecutionEngine::formatRecord(vector<string> &record) {
  auto& schema = schemas[record[0]];
  if(!schema->isVarLength) {
    return fixedRecord(record, schema);
  } else {
    return variableRecord(record, *schema);
  }
}

string ExecutionEngine::fixedRecord(vector<string> &recordQuery, Schema *schema) {
  //recordQuery: {relName,val1,val2,...}
  string newRecord;
  for(int i=0; i<schema->numAttr; i++) {
    if(recordQuery[1+i] == "NULL")
      newRecord += string(schema->attributes[i].size, ' ');
    else
      newRecord += myFunc::padString(recordQuery[i+1],schema->attributes[i].size);
  }
  return newRecord;
}

string ExecutionEngine::variableRecord(vector<string> record, const Schema &schema) {
  vector<Attribute> atributos = schema.attributes;

    // eliminando el primer elemento del vector (relationName)
    record.erase(record.begin());

    std::string convertedRecord;
    // encontrar el tamaño de la parte fija (atributos de longitud fija, offset y length de los atributos de longitud variable)
    int fixedPartSize = 0;
    for (int i = 0; i < record.size(); ++i) {
        if(record[i] == "NULL") {
            continue;
        }
       if(atributos[i].type != "VARCHAR" && atributos[i].type != "char") {
           fixedPartSize += atributos[i].size;
       }else {
           fixedPartSize += OFFSET_SIZE + LENGTH_SIZE;
       }
    }

    // se le suma el nullbitmap = size
    int endOfRecord = fixedPartSize + record.size();
    convertedRecord = std::string(fixedPartSize, ' '); //la parte de tamaño fijo se incializa con espacios en blanco

    //actualizar datos para cada atributo

    int stringIndex = 0; //indice a recorrer en el string record
    std::string nullbitmap = "";
    for (int i = 0; i < record.size(); ++i) {

        //actualizar el nullbitmap
        if(record[i] == "NULL") {
            nullbitmap += "1";
            continue;
        }else{
            nullbitmap += "0";
        }

        // verifica si es un atributo de longitud variable y oepra
        //   añade el valor al final
        //   añade ubicación y tamaño
        if (atributos[i].type== "VARCHAR" || atributos[i].type == "char"){
            // Añadiendo Offset
            convertedRecord.replace(stringIndex,OFFSET_SIZE,myFunc::padString(to_string(endOfRecord),OFFSET_SIZE));
            // Añadiendo Length
            int token_size = static_cast<int>(record[i].size());
            convertedRecord.replace(stringIndex+OFFSET_SIZE,LENGTH_SIZE,myFunc::padString(to_string(token_size),LENGTH_SIZE) );
            // Actualizando final del registro
            endOfRecord += token_size;
            // Añadiendolo al final de la cadena
            convertedRecord += record[i];
            // Actualizando Index
            stringIndex += OFFSET_SIZE + LENGTH_SIZE;
        }

        // Inserta el valor fijo directamente en el registro
         else {

            // Reemplazamos solo el tamaño del token porque por defecto el resto está con espacios en blanco
            convertedRecord.replace(stringIndex,static_cast<int>(record[i].size()), record[i]);
            // Actualizando Index
            stringIndex += atributos[i].size;
        }

    }
    convertedRecord = nullbitmap + convertedRecord;
    return convertedRecord;
}

int ExecutionEngine::getBlock(string &relName) {
  auto& schema = schemas[relName];
  return schema->headerPageId;
}

void ExecutionEngine::readSchemasFromFile() {
  // leer cada linea del archivo y añadirlo al schema
  ifstream file(SCHEMA_PATH);
  if(!file.is_open()) {
    cerr<<"Error al abrir el archivo"<<endl;
    return;
  }
  string line;
  while(getline(file, line)) {
    int pageId;
    vector<string> schemaVec = stringToVector(line, pageId);

    loadSchema(schemaVec, pageId);//ERROR: se aplica el seteo a cero de la cantidad de paginas en el header page
  }
  file.close();
  printSchemas();
}

string ExecutionEngine::schemaToString(Schema *schema) {
  // tiene la forma:
  // relationName isVarLength headerPageId attr1Name attr1Type attr1Size ... attrNName attrNType attrNSize
  // A partir de un esquema se genera un string con la información de los atributos
  string schemaStr = schema->relationName + ",";
  if(schema->isVarLength)
    schemaStr += "Variable,";
  else
    schemaStr += "Fixed,";

  // añadir headerPageId
  schemaStr += to_string(schema->headerPageId) + ",";
  for (int i = 0; i < schema->numAttr-1; ++i) {
    schemaStr += schema->attributes[i].name + "," + schema->attributes[i].type + "," + to_string(schema->attributes[i].size) + ",";
  }
  schemaStr += schema->attributes[schema->numAttr-1].name + "," + schema->attributes[schema->numAttr-1].type + "," + to_string(schema->attributes[schema->numAttr-1].size);
  return schemaStr;
}

void ExecutionEngine::writeSchemasToFile() {
  ofstream file(SCHEMA_PATH);
  if(!file.is_open()) {
    cerr<<"Error al abrir el archivo"<<endl;
    return;
  }
  for(auto& schema : schemas) {
    file << schemaToString(schema.second) << endl;
  }
  file.close();
}

vector<string> ExecutionEngine::stringToVector(string &schemaStr, int &pageId) {
  // leer un string formado por schemaToString y convertirlo a un vector de strings de la forma:
  //relName,recordType,attr1Name,attr1Type,attr1Size,attr2Name,attr2Type,attr2Size,....
  vector<string> schemaVec;
  stringstream ss(schemaStr);
  string token;
  int i = 0;
  while(getline(ss, token, ',')) {
    if( i == 2) {
      // al ser el headerPageId no se añade a schemaVec
      pageId = stoi(token);
      i++;
      continue;
    }
    schemaVec.push_back(token);
    i++;
  }
  return schemaVec;
}

ExecutionEngine::ExecutionEngine() {
}

void ExecutionEngine::createRelation(vector<string> &relation) {
  if (!hasRelation(relation[0])) {
    addSchema(relation);
  } else {
    cerr << "Relacion ya existente" << endl;
  }
  printSchemas();
}

ExecutionEngine::~ExecutionEngine() {
  writeSchemasToFile();
}
