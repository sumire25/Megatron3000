//
// Created by msumi on 15/07/2024.
//

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "Rid.h"

template<typename T>
class BPlusTreeNode {
public:
    bool isLeaf;
    std::vector<T> keys;
    std::vector<BPlusTreeNode<T>*> children;
    BPlusTreeNode* next; // Puntero al siguiente nodo hoja
    std::vector<RID*> rids; // Vector de punteros a RIDs

    BPlusTreeNode(bool leaf);
};

template<typename T>
BPlusTreeNode<T>::BPlusTreeNode(bool leaf) : isLeaf(leaf), next(nullptr) {}

template<typename T>
class BPlusTree {
    BPlusTreeNode<T>* root;
    int degree;

    void insertInternal(T key, BPlusTreeNode<T>* actual, BPlusTreeNode<T>* child);
    void printTree(BPlusTreeNode<T>* actual);
    void deleteKey(BPlusTreeNode<T>* node, T key);
    void borrowFromLeft(BPlusTreeNode<T>* parent, BPlusTreeNode<T>* leftSibling, BPlusTreeNode<T>* node, int index);
    void borrowFromRight(BPlusTreeNode<T>* parent, BPlusTreeNode<T>* rightSibling, BPlusTreeNode<T>* node, int index);
    void mergeNodes(BPlusTreeNode<T>* parent, BPlusTreeNode<T>* leftNode, BPlusTreeNode<T>* rightNode, int index);
    BPlusTreeNode<T>* findParent(BPlusTreeNode<T>* root, BPlusTreeNode<T>* node);
    void updateInternalNodes(BPlusTreeNode<T>* node, T oldKey, T newKey); // Nueva función para actualizar nodos internos

public:
    BPlusTree(int degree);
    void insert(T key, RID* rid);
    void remove(T key);
    RID* search(T key);
    vector<RID*> searchRange(T l, T r);
    void printTree();
    void printLeaves();
    void genDotFile();
};

template<typename T>
BPlusTree<T>::BPlusTree(int degree) : root(nullptr), degree(degree) {}

template<typename T>
void BPlusTree<T>::insert(T key, RID* rid) {
    if (root == nullptr) { // arbol vacio
        root = new BPlusTreeNode<T>(true);
        root->keys.push_back(key);
        root->rids.push_back(rid);
    } else {
        BPlusTreeNode<T>* actual = root;
        BPlusTreeNode<T>* parent = nullptr;

        while (!actual->isLeaf) { // descender hasta la hoja
            parent = actual;
            auto it = std::upper_bound(actual->keys.begin(), actual->keys.end(), key);
            int index = std::distance(actual->keys.begin(), it);
            actual = actual->children[index];
        }
        // Insertar la clave y rid en la hoja
        int index = std::distance(actual->keys.begin(), std::upper_bound(actual->keys.begin(), actual->keys.end(), key));
        actual->keys.insert(actual->keys.begin() + index, key);
        actual->rids.insert(actual->rids.begin() + index, rid);

        if (actual->keys.size() > degree) {// si la hoja se llena
            // split node
            BPlusTreeNode<T>* newLeaf = new BPlusTreeNode<T>(true);
            int midIndex = (degree + 1) / 2;
            newLeaf->keys.assign(actual->keys.begin() + midIndex, actual->keys.end());
            newLeaf->rids.assign(actual->rids.begin() + midIndex, actual->rids.end());
            actual->keys.resize(midIndex);
            actual->rids.resize(midIndex);
            // Actualizar el puntero next
            newLeaf->next = actual->next;
            actual->next = newLeaf;

            // Copy up en el nodo padre
            if (actual == root) {
                BPlusTreeNode<T>* newRoot = new BPlusTreeNode<T>(false);
                newRoot->keys.push_back(newLeaf->keys.front());
                newRoot->children.push_back(actual);
                newRoot->children.push_back(newLeaf);
                root = newRoot;
            } else {
                insertInternal(newLeaf->keys.front(), parent, newLeaf);
            }
        }
    }
}

template<typename T>
void BPlusTree<T>::insertInternal(T key, BPlusTreeNode<T>* actual, BPlusTreeNode<T>* child) {
    if (actual->keys.size() < degree) {
        auto it = std::upper_bound(actual->keys.begin(), actual->keys.end(), key);
        int index = std::distance(actual->keys.begin(), it);
        actual->keys.insert(it, key);
        actual->children.insert(actual->children.begin() + index + 1, child);
    } else {
        BPlusTreeNode<T>* newInternal = new BPlusTreeNode<T>(false);
        std::vector<T> tempKeys(actual->keys);
        std::vector<BPlusTreeNode<T>*> tempChildren(actual->children);

        auto it = std::upper_bound(tempKeys.begin(), tempKeys.end(), key);
        int index = std::distance(tempKeys.begin(), it);
        tempKeys.insert(it, key);
        tempChildren.insert(tempChildren.begin() + index + 1, child);

        int midIndex = (degree + 1) / 2;
        actual->keys.assign(tempKeys.begin(), tempKeys.begin() + midIndex);
        actual->children.assign(tempChildren.begin(), tempChildren.begin() + midIndex + 1);

        newInternal->keys.assign(tempKeys.begin() + midIndex + 1, tempKeys.end());
        newInternal->children.assign(tempChildren.begin() + midIndex + 1, tempChildren.end());

        if (actual == root) {
            BPlusTreeNode<T>* newRoot = new BPlusTreeNode<T>(false);
            newRoot->keys.push_back(tempKeys[midIndex]);
            newRoot->children.push_back(actual);
            newRoot->children.push_back(newInternal);
            root = newRoot;
        } else {
            insertInternal(tempKeys[midIndex], actual, newInternal);
        }
    }
}

template<typename T>
void BPlusTree<T>::updateInternalNodes(BPlusTreeNode<T>* node, T oldKey, T newKey) {
    BPlusTreeNode<T>* parent = findParent(root, node);
    while (parent != nullptr) {
        for (int i = 0; i < parent->keys.size(); i++) {
            if (parent->keys[i] == oldKey) {
                parent->keys[i] = newKey;
                return;
            }
        }
        parent = findParent(root, parent);
    }
}

template<typename T>
void BPlusTree<T>::deleteKey(BPlusTreeNode<T>* node, T key) {
    BPlusTreeNode<T>* actual = node;
    BPlusTreeNode<T>* parent = nullptr;
    int parentIndex = 0;

    while (!actual->isLeaf) {
        auto it = std::upper_bound(actual->keys.begin(), actual->keys.end(), key);
        int index = std::distance(actual->keys.begin(), it);
        parent = actual;
        parentIndex = index;
        actual = actual->children[index];
    }

    auto it = std::lower_bound(actual->keys.begin(), actual->keys.end(), key);
    if (it != actual->keys.end() && *it == key) {
        T oldKey = actual->keys.front();
        int idx = std::distance(actual->keys.begin(), it);
        actual->keys.erase(it);
        // delete actual->rids[idx];
        actual->rids.erase(actual->rids.begin() + idx);
        if (actual == root) {
            if (actual->keys.empty()) {
                delete root;
                root = nullptr;
            }
            return;
        }
        if (actual->keys.size() >= (degree + 1) / 2) {
            T newKey = actual->keys.front();
            if (parent != nullptr && parent->keys[parentIndex] == key) {
                parent->keys[parentIndex] = newKey;
                updateInternalNodes(parent, oldKey, newKey);
            }
            return;
        }

        if (parent != nullptr && parent->keys[parentIndex] == key) {
            parent->keys[parentIndex] = actual->keys.front();
            updateInternalNodes(parent, oldKey, parent->keys.front());
        }

        BPlusTreeNode<T>* grandParent = findParent(root, parent);
        int index = std::distance(parent->children.begin(), std::find(parent->children.begin(), parent->children.end(), actual));

        //PRIEMR CASO
        if (index > 0 && parent->children[index - 1]->keys.size() > (degree + 1) / 2) {
            borrowFromLeft(parent, parent->children[index - 1], actual, index - 1);
        //SEGUNDO CASO
        } else if (index < parent->children.size() - 1 && parent->children[index + 1]->keys.size() > (degree + 1) / 2) {
            borrowFromRight(parent, parent->children[index + 1], actual, index);
        } else {
            if (index > 0) {
                mergeNodes(parent, parent->children[index - 1], actual, index - 1);
            } else {
                mergeNodes(parent, actual, parent->children[index + 1], index);
            }
        }
    }
}
                                     //padre 15 21  //nodo del que se presta //nodo actual24 24//poisicion del hijo
template<typename T>
void BPlusTree<T>::borrowFromLeft(BPlusTreeNode<T>* parent, BPlusTreeNode<T>* leftSibling, BPlusTreeNode<T>* node, int index) {
    node->keys.insert(node->keys.begin(), parent->keys[index]);
    if(node->isLeaf) {//move rid from left to right
        node->rids.insert(node->rids.begin(), leftSibling->rids.back());
        leftSibling->rids.pop_back();
    }
    if (!node->isLeaf) {
        node->children.insert(node->children.begin(), leftSibling->children.back());
        leftSibling->children.pop_back();
    }
    node->keys[index-1]= leftSibling->keys.back();//actualiza el hijo
    parent->keys[index] = leftSibling->keys.back();
    leftSibling->keys.pop_back();
}

template<typename T>
void BPlusTree<T>::borrowFromRight(BPlusTreeNode<T>* parent, BPlusTreeNode<T>* rightSibling, BPlusTreeNode<T>* node, int index) {
    node->keys.push_back(parent->keys[index]);
    if(node->isLeaf) {//move rid from right to left
        node->rids.push_back(rightSibling->rids.front());
        rightSibling->rids.erase(rightSibling->rids.begin());
    }
    if (!node->isLeaf) {
        node->children.push_back(rightSibling->children.front());
        rightSibling->children.erase(rightSibling->children.begin());
    }
    rightSibling->keys.erase(rightSibling->keys.begin());
    parent->keys[index] = rightSibling->keys.front();//cambio
}

template<typename T>
void BPlusTree<T>::mergeNodes(BPlusTreeNode<T>* parent, BPlusTreeNode<T>* leftNode, BPlusTreeNode<T>* rightNode, int index) {
    // Mover todas las claves del nodo derecho al nodo izquierdo
    leftNode->keys.insert(leftNode->keys.end(), rightNode->keys.begin(), rightNode->keys.end());
    leftNode->rids.insert(leftNode->rids.end(), rightNode->rids.begin(), rightNode->rids.end());

    // Mover todos los hijos del nodo derecho al nodo izquierdo
    if (!leftNode->isLeaf) {
        leftNode->children.insert(leftNode->children.end(), rightNode->children.begin(), rightNode->children.end());
    }

    // Ajustar el puntero next del nodo izquierdo
    leftNode->next = rightNode->next;

    // Eliminar la clave del padre y el puntero al nodo derecho
    parent->keys.erase(parent->keys.begin() + index);
    parent->children.erase(parent->children.begin() + index + 1);

    delete rightNode;

    // Si el padre era la raíz y ahora está vacío, hacer del nodo izquierdo la nueva raíz
    if (parent == root && parent->keys.empty()) {
        root = leftNode;
        delete parent;
    }
}

template<typename T>
BPlusTreeNode<T>* BPlusTree<T>::findParent(BPlusTreeNode<T>* root, BPlusTreeNode<T>* node) {
    if (root == nullptr || root->isLeaf) {
        return nullptr;
    }

    for (auto child : root->children) {
        if (child == node) {
            return root;
        } else {
            BPlusTreeNode<T>* parent = findParent(child, node);
            if (parent != nullptr) {
                return parent;
            }
        }
    }
    return nullptr;
}

template<typename T>
void BPlusTree<T>::remove(T key) {
    if (root == nullptr) {
        std::cout << "Tree is empty." << std::endl;
        return;
    }
    deleteKey(root, key);
}

template<typename T>
RID* BPlusTree<T>::search(T key) {
    BPlusTreeNode<T>* actual = root;
    // Buscar la hoja donde debería estar la clave
    if(actual == nullptr) return nullptr;
    while (!actual->isLeaf) {
        auto it = std::upper_bound(actual->keys.begin(), actual->keys.end(), key);
        int index = std::distance(actual->keys.begin(), it);
        actual = actual->children[index];
    }
    // Buscar la clave en la hoja
    auto it = std::lower_bound(actual->keys.begin(), actual->keys.end(), key);
    if (it != actual->keys.end() && *it == key) {
        int index = std::distance(actual->keys.begin(), it);
        return actual->rids[index];
    }
    return nullptr;
}

template<typename T>
vector<RID *> BPlusTree<T>::searchRange(T l, T r) {
    BPlusTreeNode<T>* actual = root;
    vector<RID*> rids;
    // Buscar la hoja donde debería estar la clave minima dentor del rango
    if(actual == nullptr) return rids;
    while (!actual->isLeaf) {
        auto it = std::upper_bound(actual->keys.begin(), actual->keys.end(), l);
        int index = std::distance(actual->keys.begin(), it);
        actual = actual->children[index];
    }
    // Buscar la clave en la hoja
    auto it = std::lower_bound(actual->keys.begin(), actual->keys.end(), l);
    int index;
    while(true){
        if(it == actual->keys.end()){
            if(actual->next == nullptr)
                break;
            actual = actual->next;
            it = actual->keys.begin();
        }
        else if(*it <= r) {
            index = std::distance(actual->keys.begin(), it);
            rids.push_back(actual->rids[index]);
            it++;
        }
        else break;
    }

    return rids;
}

template<typename T>
void BPlusTree<T>::printTree() {
    if (root == nullptr) return;

    std::queue<BPlusTreeNode<T>*> nodesQueue;
    nodesQueue.push(root);

    while (!nodesQueue.empty()) {
        int levelSize = nodesQueue.size();
        while (levelSize > 0) {
            BPlusTreeNode<T>* node = nodesQueue.front();
            nodesQueue.pop();

            for (T key : node->keys) {
                std::cout << key << " ";
            }
            std::cout << "| ";

            if (!node->isLeaf) {
                for (BPlusTreeNode<T>* child : node->children) {
                    nodesQueue.push(child);
                }
            }
            levelSize--;
        }
        std::cout << std::endl;
    }
}

template<typename T>
void BPlusTree<T>::printLeaves() {
    if (root == nullptr) return;

    BPlusTreeNode<T>* current = root;
    while (!current->isLeaf) {
        current = current->children[0];
    }

    while (current != nullptr) {
        for (int key : current->keys) {
            std::cout << key << " ";
        }
        std::cout << "| ";
        current = current->next;
    }
    std::cout << std::endl;
}

template<typename T>
void BPlusTree<T>::genDotFile() {
    std::ofstream file("../bplustreee.dot");
    file << "digraph G {" << std::endl;
    file << "node [shape=record];" << std::endl;

    std::queue<BPlusTreeNode<T>*> nodesQueue;
    if (root == nullptr)
        return;
    nodesQueue.push(root);

    while (!nodesQueue.empty()) {
        BPlusTreeNode<T>* node = nodesQueue.front();
        nodesQueue.pop();

        file << "node" << node << " [label=\"";
        for (T key : node->keys) {
            file << "<f" << key << ">" << "|" << key << "|";
        }
        file << "<f" << node->keys.back() << "_"<< ">" << "\"];" << std::endl;

        if (!node->isLeaf) {
            int i = 0;
            for (BPlusTreeNode<T>* child : node->children) {
                if(child == node->children.back()) {
                    file << "node" << node << ":f" << node->keys.back() << "_ -> node" << child << ";" << std::endl;
                }
                else {
                    file << "node" << node << ":f" << node->keys[i] << " -> node" << child << ";" << std::endl;
                }
                nodesQueue.push(child);
                i++;
            }
        }
    }
    file << "}" << std::endl;
    file.close();
    system("dot -Tpng ../bplustreee.dot -o ../bplustreee.png");
    system("xdg-open ../bplustreee.png");
}

#endif //BPLUSTREE_H
