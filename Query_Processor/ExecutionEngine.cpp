#include "ExecutionEngine.h"

void ExecutionEngine::setBuffManRef(BufferManager *buffManRef) {
  this->buffManRef = buffManRef;
}

void ExecutionEngine::insertRecord(vector<string> &record) {
  if(hasVarRecords(record[0]))
    insertVariableRecord(record);
  else
    insertFixedRecord(record);
  buffManRef->printRequestQueue();
  buffManRef->printPageTable();
  buffManRef->printReplacer();
  /*string newRecord = formatRecord(record);
  cerr << "Record: " << newRecord << "\n";
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
  //write record to disk*/
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

void ExecutionEngine::insertVariableRecord(vector<string> &record) {
  string newRecord = formatRecord(record);
  cerr<<"newRecord: '"<<newRecord<<"'"<<endl;
  int recordSize = newRecord.size();
  //solicitar headerPage
  int headerBlockId = getBlock(record[0]);
  if(!buffManRef->pinPage(headerBlockId, RequestType::WRITE)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return;
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
    return;
  }
  Page* pageToWrite = buffManRef->getPage(freePage);
  if(allocated) {
    *(pageToWrite->data) = pageEdit::setNewSlotted(PAGE_SIZE);
    int freeSpace = PAGE_SIZE - (NUM_RECORDS_SIZE+VAR_OFFSET_SIZE) - (VAR_OFFSET_SIZE+VAR_LENGTH_SIZE) - recordSize;
    pageEdit::addNewPageToDirectory(*(header->data),freePage,freeSpace);
  }
  *(pageToWrite->data) = pageEdit::insertSlotted(*(pageToWrite->data),newRecord);
  buffManRef->setDirtyFlag(freePage);
  buffManRef->unpinPage(freePage);
  //actualizar headerPage y liberarla
  buffManRef->setDirtyFlag(headerBlockId);
  buffManRef->unpinPage(headerBlockId);
}

void ExecutionEngine::insertFixedRecord(vector<string> &record) {
  string newRecord = formatRecord(record);
  int recordSize = newRecord.size();
  cerr<<"newRecord: '"<<newRecord<<"'"<<endl;
  //solicitar headerPage
  int headerBlockId = getBlock(record[0]);
  if(!buffManRef->pinPage(headerBlockId, RequestType::WRITE)) {
    cerr<<"Error al pinnear pagina"<<endl;
    return;
  }
  Page* header = buffManRef->getPage(headerBlockId);
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
    return;
  }
  Page* pageToWrite = buffManRef->getPage(freePage);
  if(allocated) {
    pageEdit::setNewUnpacked(*(pageToWrite->data),recordSize);
    int freeSpace = PAGE_SIZE - (recordSize+1) - NUM_RECORDS_SIZE - 1;
    pageEdit::addNewPageToDirectory(*(header->data),freePage,freeSpace);
  }
  int slot = pageEdit::insertUnpacked(*(pageToWrite->data),newRecord);
  buffManRef->setDirtyFlag(freePage);
  buffManRef->unpinPage(freePage);
  //actualizar headerPage y liberarla
  buffManRef->setDirtyFlag(headerBlockId);
  buffManRef->unpinPage(headerBlockId);
  //create Rid;
  RID* rid =  new RID(freePage,slot);
  cerr<<"RID: "<<rid->GetPageId()<<", "<<rid->GetSlotNum()<<endl;
  postIndex->insert(stoi(record[1]), rid);
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

string ExecutionEngine::selectPost(int postId) {
  RID* rid = postIndex->search(postId);
  if(!rid) {
    cerr<<"null rid"<<endl;
    return "";
  }
  if(!buffManRef->pinPage(rid->GetPageId(), RequestType::READ)) {
    cerr<<"Error al pinnear pagina"<<endl;
  }
  Page* page = buffManRef->getPage(rid->GetPageId());
  Schema* schema = schemas["Post"];
  string record = pageEdit::getRecord(*(page->data),rid->GetSlotNum(), schema->recordSize());
  buffManRef->unpinPage(rid->GetPageId());
  return record;
}

string ExecutionEngine::formatRecord(vector<string> &record) {
  auto& schema = schemas[record[0]];

  //imprimiendo el vector
  /*for(const auto& str : record) {
    std::cout << str <<"; ";
  }
  cout<<endl;*/

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
  postIndex = new BPlusTree<int>(4);
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
