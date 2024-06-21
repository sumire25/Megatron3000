//
// Created by msumi on 10/06/2024.
//

#ifndef REPLACER_H
#define REPLACER_H

#include <list>
#include <iostream>
using namespace std;

//Clase abstracta para las politicas de reemplazo
class Replacer {
protected:
	tuple<bool, int, bool>* frameInfo;// referencia a la informacion de los frames en el bufferManager
	int numFrames;// numero de frames en el bufferManager
public:
	/**
	* Constructor: crea un reemplazador con referencia al frameInfo y el numero de frames
	* @param fi: puntero a frameInfo
	* @param nf: numero de frames
	* @author Marko
	*/
	Replacer(tuple<bool, int, bool>* fi, int nf) : frameInfo(fi), numFrames(nf) {}
	/**
	* Ejecuta la busqueda del victimFrameId segun la politica de reemplazo
	* @return id del frame a reemplazar, -1 si no hay ningun frame a reemplazar
	* @author Marko
	*/
	virtual int getVictim() = 0;
	/**
	* Actualiza la politica de reemplazo cuando se pinea un frame
	* @param frameId: id del frame que se ha pineado
	* @author Marko
	*/
	virtual void handlePinning(int frameId) = 0;
	/**
	* Actualiza la politica de reemplazo cuando se despinea un frame
	* @param frameId: id del frame que se ha despineado
	* @author Marko
	*/
	virtual void handleUnpinning(int frameId) = 0;	/**
	* Imprime la informacion de la politica de reemplazo
	* @author Marko
	*/
	virtual void print() = 0;
};

//Clase que implementa la politica de reempalzo LRU
class LruReplacer : public Replacer {
private:
	list<int> LRUqueue;//cola de frames segun su uso reciente
public:
	LruReplacer(tuple<bool, int, bool>* fi, int nf) : Replacer(fi, nf) {
		for(int i=0; i<nf; i++) {
			LRUqueue.push_back(i);
		}
	}
	int getVictim() override {
		if(!LRUqueue.empty())
			return LRUqueue.front();
		return -1;
	}
	void handlePinning(int frameId) override {
		if(get<1>(frameInfo[frameId]) == 1) {//si no estaba pineado
			for (auto it = LRUqueue.begin(); it != LRUqueue.end(); ++it) {
				if (*it == frameId) {
					LRUqueue.erase(it);
					break;
				}
			}
		}
	}
	void handleUnpinning(int frameId) override {
		LRUqueue.push_back(frameId);
	}
	void print() override {
		for (const int& item : LRUqueue) {
			cout << "( " << item << " ) <- ";
		}
		cout << "end\n" << endl;
	}
};

class ClockReplacer : public Replacer {
private:
	bool* refBit;
	int hand;
public:
	ClockReplacer(tuple<bool, int, bool>* fi, int nf) : Replacer(fi, nf) {
		refBit = new bool[nf];
		for(int i=0; i<nf; i++) {
			refBit[i] = false;
		}
		hand = 0;
	}
	int getVictim() override {
		bool existUnpinned = false;
		for(int i=0; i<numFrames; i++) {
			if(get<1>(frameInfo[i]) == 0 && get<2>(frameInfo[i]) == false)
				existUnpinned = true;
		}
		if(existUnpinned) {//si algun frame en frameInfo esta unpinned
			while(true) {
				if(get<1>(frameInfo[hand]) == 0 && get<2>(frameInfo[hand]) == false) {
					if(refBit[hand] == false) break;
					refBit[hand] = false;
				}
				hand = (hand + 1) % numFrames;
			}
			int temp = hand;
			hand = (hand + 1) % numFrames;
			return temp;
		}
		return -1;
	}
	void handlePinning(int frameId) override {
		refBit[frameId] = true;
	}
	void handleUnpinning(int frameId) override {}
	//print where the hand is pointing in a circular way
	void print() override {
		int temp = hand;
		cout << "hand ";
		cout << "-> | " << temp << " | ";
		temp = (temp + 1) % numFrames;
		while(temp != hand) {
			cout << "-> | " << temp << " | ";
			temp = (temp + 1) % numFrames;
		}
		cout << endl;
		//then print the refBit array in a circular way
		temp = hand;
		cout << "refBit: ";
		cout << "| " << refBit[temp] << " | ";
		temp = (temp + 1) % numFrames;
		while(temp != hand) {
			cout << "   | " << refBit[temp] << " | ";
			temp = (temp + 1) % numFrames;
		}
		cout << endl;
	}
};

#endif //REPLACER_H
