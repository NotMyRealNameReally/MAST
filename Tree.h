#pragma once

#include <string>

struct Node {
	Node* parent;
	Node* sibling;
	Node* child;
	int label;
};

class Tree {
private:
	Node** nodes;
	int leaves = 0;
	int innerVertices = 0;

	Node* createChildOf(Node* parent);
	Node* createSiblingOf(Node* previous);
	void countVertices(std::string newick);
public:
	Tree(std::string newick);
	~Tree();
	bool isAncestor(int ancestorLabel, int descendantLabel);
	int getVerticesAmount() {
		return leaves + innerVertices;
	}
	int getLeavesAmount() {
		return leaves;
	}
	int countChildrenOf(int label);
	int* getChildrenOf(int label);
};

