//
// Created by msumi on 15/07/2024.
//

#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename T> class BPlusTree {
public:
	// structure to create a node
	struct Node {
		bool isLeaf;
		vector<T> keys;
		vector<Node*> children;
		Node* next;

		Node(bool leaf = false)
				: isLeaf(leaf)
				, next(nullptr)
		{
		}
	};

	Node* root;
	// Minimum degree (defines the range for the number of keys)
	int t;

	// Function to split a child node
	void splitChild(Node* parent, int index, Node* child);

	// Function to insert a key in a non-full node
	void insertNonFull(Node* node, T key);

	// Function to remove a key from a node
	void remove(Node* node, T key);

	// Function to borrow a key from the previous sibling
	void borrowFromPrev(Node* node, int index);

	// Function to borrow a key from the next sibling
	void borrowFromNext(Node* node, int index);

	// Function to merge two nodes
	void merge(Node* node, int index);

	// Function to print the tree
	void printTree(Node* node, int level);

public:
	BPlusTree(int degree) : root(nullptr), t(degree) {}

	void insert(T key);
	bool search(T key);
	void remove(T key);
	vector<T> rangeQuery(T lower, T upper);
	void printTree();
};



#endif //BPLUSTREE_H
