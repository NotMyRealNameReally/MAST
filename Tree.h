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
	Node root;
	int leaves = 0;
	int innerVertices = 1;

	Node* createChildOf(Node* parent);
	Node* createSiblingOf(Node* previous);
public:
	Tree(std::string newick);
	//void createTree(std::string newick);
};

