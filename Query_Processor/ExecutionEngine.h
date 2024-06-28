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
    /**
 * Referencia al administrador de búfer.
 */
  BufferManager* buffManRef;

    /**
 * Referencia al administrador de disco.
 */
  DiskManager* diskManRef;

    /**
 * Tabla hash que almacena los esquemas de las relaciones.
 * La clave es el nombre de la relación y el valor es un puntero al esquema correspondiente.
 */
  unordered_map<string, Schema*> schemas;

    /**
   * Inserta un registro de longitud variable en un bloque (slotted page).
   * @param record: vector de strings que representa el registro.
   */
  void insertVariableRecord(vector<string>& record);

    /**
     * Inserta un registro de longitud fija en un bloque (unpacked).
     * @param record: vector de strings que representa el registro.
     */
  void insertFixedRecord(vector<string>& record);


    /**
     * Devuelve un string con el formato indicado para un registro, ya sea de longitud variable o fija.
     * @param record: vector de strings que representa el registro.
     * @return string con el registro formateado.
     */
  string formatRecord(vector<string>& record);

    /**
    * Da el formato para un registro de longitud fija.
    * @param record: vector de strings que representa el registro.
    * @param schema: esquema de la relación.
    * @return string con el registro formateado.
    */
  string fixedRecord(vector<string>& record, Schema* schema);

    /**
 * Da el formato para un registro de longitud variable.
 * @param record: vector de strings que representa el registro.
 * @param schema: esquema de la relación.
 * @return string con el registro formateado.
 */
  string variableRecord(vector<string> record,const Schema& schema);

    /**
 * Obtiene el bloque de encabezado de la relación.
 * @param relName: nombre de la relación.
 * @return ID del bloque de encabezado.
 */
  int getBlock(string& relName);

    /**
 * Verifica si existen registros de longitud variable en la relación.
 * @param relName: nombre de la relación.
 * @return true si la relación tiene registros de longitud variable, false en caso contrario.
 */
  bool hasVarRecords(string& relName);

    /**
  * Convierte un esquema a una cadena.
  * @param schema: puntero al esquema.
  * @return string que representa el esquema.
  */
  string schemaToString(Schema* schema);

  /**
 * Convierte una cadena en un esquema.
 * @param schemaStr: cadena que representa el esquema.
 * @param pageId: referencia al ID de la página.
 * @return vector de strings que representa el esquema.
 */
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
