#ifndef EXECUTIONENGINE_H
#define EXECUTIONENGINE_H

#include <unordered_map>
#include <limits>
#include "../Buffer_Manager/BufferManager.h"
#include "../Util/myFunc.h"
#include "pageEdit.h"
#include "Schema.h"
#include "Rid.h"
#include "BPlusTree.h"

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
 * Tabla hash que almacena los esquemas de las relaciones.
 * La clave es el nombre de la relación y el valor es un puntero al esquema correspondiente.
 * @author Suni Yanira
 */
  unordered_map<string, Schema*> schemas;

    /**
   * Inserta un registro de longitud variable en un bloque (slotted page).
   * @param record: vector de strings que representa el registro.
   * @author Suni Yanira
   */
  RID* insertVariableRecord(vector<string>& record);

    /**
     * Inserta un registro de longitud fija en un bloque (unpacked).
     * @param record: vector de strings que representa el registro.
     * @author Suni Yanira
     */
  RID* insertFixedRecord(vector<string>& record);


    /**
     * Devuelve un string con el formato indicado para un registro, ya sea de longitud variable o fija.
     * @param record: vector de strings que representa el registro.
     * @return string con el registro formateado.
     * @author Suni Yanira
     */
  string formatRecord(vector<string>& record);

    /**
    * Da el formato para un registro de longitud fija.
    * @param record: vector de strings que representa el registro.
    * @param schema: esquema de la relación.
    * @return string con el registro formateado.
    * @author Suni Yanira
    */
  string fixedRecord(vector<string>& record, Schema* schema);

    /**
 * Da el formato para un registro de longitud variable.
 * @param record: vector de strings que representa el registro.
 * @param schema: esquema de la relación.
 * @return string con el registro formateado.
 * @author Suni Yanira
 */
  string variableRecord(vector<string> record,const Schema& schema);

    /**
 * Obtiene el bloque de encabezado de la relación.
 * @param relName: nombre de la relación.
 * @return ID del bloque de encabezado.
 * @author Suni Yanira
 */
  int getBlock(string& relName);

    /**
 * Verifica si existen registros de longitud variable en la relación.
 * @param relName: nombre de la relación.
 * @return true si la relación tiene registros de longitud variable, false en caso contrario.
 * @author Suni Yanira
 */
  bool hasVarRecords(string& relName);

    /**
  * Convierte un esquema a una cadena.
  * @param schema: puntero al esquema.
  * @return string que representa el esquema.
  * @author Suni Yanira
  */
  string schemaToString(Schema* schema);

  /**
 * Convierte una cadena en un esquema.
 * @param schemaStr: cadena que representa el esquema.
 * @param pageId: referencia al ID de la página.
 * @return vector de strings que representa el esquema.
 * @author Suni Yanira
 */
  vector<string> stringToVector(string &schemaStr, int &pageId);
public:
	ExecutionEngine();
    /**
   * Destructor de la clase ExecutionEngine.
   * Escribe los esquemas en un archivo al destruir el objeto.
   */
  ~ExecutionEngine();


    /**
     * Establece la referencia al BufferManager.
     * @param buffManRef: puntero al BufferManager.
     * @author Alonso
     */
  void setBuffManRef(BufferManager* buffManRef);

    /**
 * Lee los esquemas desde un archivo y los carga en la tabla de esquemas.
 * @author Alonso
 */
  void readSchemasFromFile();

    /**
* Escribe los esquemas cargados en memoria a su archivo.
* @author Alonso
*/
  void writeSchemasToFile();

    /**
   * Crea y agrega un esquema a la tabla de esquemas.
   * @param relation: vector de strings que representa la relación.
   * @param headerPageId: el headerPageId de la relación.
* @author Alonso
   */
  void addSchema(vector<string>& relation);

  /**
   * CARGA un esquema en la tabla de esquemas.
   * @param relation vector de strings que representa la relación con su metadata.
   * @param headerPageId el headerPageId de la relación.
* @author Alonso
   */
  void loadSchema(vector<string> &relation, int headerPageId);

    /**
 * Inserta un registro en la relación correspondiente.
 * @param record: vector de strings que representa el registro.
 * relName,Val1,Val2,...ValN
* @author Alonso
 */
  void insertRecord(vector<string>& record);

    /**
 * Obtiene el contenido de una página en el buffer.
 * @param blockId: ID del bloque.
 * @return string con el contenido de la página.
* @author Alonso
 */
  string getPageContent(int& blockId);

    /**
 * Verifica si existe una relación con el nombre dado.
 * @param relName: nombre de la relación.
 * @return true si la relación existe, false en caso contrario.
* @author Alonso
 */
  bool hasRelation(string& relName);

    /**
     * Imprime todos los esquemas almacenados.
* @author Alonso
     */
  void printSchemas();

    /**
     * @brief Crea una nueva relación en el motor de ejecución.
     *
     * Esta función añade un nuevo esquema a la colección de esquemas.
     * Si la relación especificada no existe, se asigna un nuevo bloque de cabecera para almacenar
     * los datos de la relación y se inicializa la cabecera de la página correspondiente.
     * Si la relación ya existe, la función no realiza ninguna acción adicional.
     *
     * @param relation Un vector de strings que contiene el nombre de la relación seguido de los detalles de sus atributos.
     *                 Por ejemplo: {"nombreRelacion", "tipoAtributo1", "nombreAtributo1", "tipoAtributo2", "nombreAtributo2", ...}.
     * @param blockId El identificador del bloque en el disco donde se almacenará la cabecera de la nueva relación.
     * @author  Suni Yanira
     */
  void createRelation(vector<string> &relation);

  //POR IMPLEMENTAR
  // funciones para crear un diccionario correctamente
  void setDataDictionary();
  void addSchematoDisk(string& relName);

  string selectRecord(vector<string> & selectQuery);
	vector<string> selectRangeRecords(vector<string> & selectQuery);
    void addIndexEntry(vector<string> & record, RID* rid);
    void deleteIndexEntry(vector<string> & deleteQuery);
  void deleteRecord(vector<string> & deleteQuery);
  void graficarArbol(vector<string> & query);
};



#endif //EXECUTIONENGINE_H
