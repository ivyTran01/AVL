#ifndef AVLTREE_H
#define AVLTREE_H
#include<iostream>
#include"KeyNotFoundException.h"
#include"EmptyTreeException.h"

class AVLTree
{
public:
	class Node
	{
	private:
		int key;
		int height;
		Node* left;
		Node* right;
		Node* parent;
	public:
		Node();
		std::string toString() const;
		bool operator==(const Node& x) const; 
		friend class AVLTree;
	};
private:
	Node* root;
	int count;
	Node end;

	//utilities
	bool isExternal(Node* v) const;
	static int max(int a, int b) ;
	Node* expandExternal(Node* v, int k);
	Node* rotateLeft(Node* v);
	Node* rotateRight(Node* v);
	Node* searchSpotForInsert(int k) const;
	int balanceFactor(Node* v) const;
	bool isBalanced(Node* v) const;
	Node* lookUp(int k) const;
	Node* removeAboveExternal(Node* v);
	Node* findMinNode(Node* v) const;
	void print(Node* v) const;
	void indent(int n) const;
	void printPreorder(Node* v, int n=0) const;
public:
	AVLTree();
	~AVLTree();
	Node find(int k) const;
	Node put(int k);
	void erase(int k);
	int size() const;
	bool empty() const;
	Node getEnd() const;
	void print() const;
};

#endif
