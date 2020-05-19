#include "Tree.h"

using namespace std;

Tree::Tree(string newick) {
	countVertices(newick);

	nodes = new Node*[leaves + innerVertices];
	int innerLabel = leaves;

	//create root
	Node* current = new Node;
	current->parent = NULL;
	current->sibling = NULL;
	current->label = ++innerLabel;
	nodes[innerLabel - 1] = current;

	Node* node;
	bool previousWasDigit = false;
	string tmp;

	for (char character : newick) {
		if (isdigit(character)) {
			tmp.push_back(character);
			previousWasDigit = true;
		}
		else {
			if (previousWasDigit) {
				int leafLabel = stoi(tmp);
				tmp.clear();
				current->label = leafLabel;
				previousWasDigit = false;

				nodes[leafLabel - 1] = current;
			}
			switch (character) {
			case '(':
				if (current->label == NULL) {
					current->label = ++innerLabel;

					nodes[innerLabel - 1] = current;
				}
				node = createChildOf(current);
				current = node;
				break;
			case ',':
				node = createSiblingOf(current);
				current = node;
				break;
			case')':
				current = current->parent;
			}
		}
	}
}

Node* Tree::createChildOf(Node* parent) {
	Node* node = new Node;

	node->parent = parent;
	node->child = NULL;
	node->sibling = NULL;
	node->label = NULL;
	parent->child = node;
	return node;
}

Node* Tree::createSiblingOf(Node* previous) {
	Node* node = new Node;

	node->parent = previous->parent;
	node->child = NULL;
	node->sibling = NULL;
	node->label = NULL;
	previous->sibling = node;
	return node;
}

void Tree::countVertices(std::string newick) {
	bool previousWasDigit = false;

	for (char& character : newick) {
		if (isdigit(character) && !previousWasDigit) {
			leaves++;
			previousWasDigit = true;
		} else {
			previousWasDigit = false;
			if (character == '(')
				innerVertices++;
		}
	}
}

Tree::~Tree() {
	for (int i = 0; i < (leaves + innerVertices); i++) {
		delete nodes[i];
	}
	delete[] nodes;
}
