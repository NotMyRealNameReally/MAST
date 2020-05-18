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
public:
	Tree(std::string newick);
};

