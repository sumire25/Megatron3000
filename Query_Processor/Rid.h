//
// Created by msumi on 15/07/2024.
//

#ifndef RID_H
#define RID_H

#include <cstdint>
#include <sstream>
#include <string>

#include "pageEdit.h"
#include "../Util/myFunc.h"

// Clase que representa un identificador de registro, compuesto por un identificador de página y un número de slot.
class RID {
 public:
  RID() = default;
  RID(int page_id, int slot_num) : page_id_(page_id), slot_num_(slot_num) {}

	/**
	 * Constructor a partir de un string con formato de tamaño fijo.
	 * @author Marko
	 */
	RID(string rid) {
	  page_id_ = stoi(rid.substr(0, PAGEID_SIZE));
  	slot_num_ = stoi(rid.substr(PAGEID_SIZE, SLOTNUM_SIZE));
  }
  int GetPageId() const { return page_id_; }
  int GetSlotNum() const { return slot_num_; }
  void Set(int page_id, int slot_num) {
    page_id_ = page_id;
    slot_num_ = slot_num;
  }
	/**
	 * Retorna string con formato de tamaño fijo.
	 * @return "pageID slotnum".
	 * @author Marko
	 */
  std::string ToString() const{
		std::string str = myFunc::padString(to_string(page_id_), PAGEID_SIZE);
  	str = str + myFunc::padString(to_string(slot_num_), SLOTNUM_SIZE);
  	return str;
  }

 private:
  int page_id_;
  int slot_num_;  // logical offset from 0, 1...
};

#endif //RID_H
