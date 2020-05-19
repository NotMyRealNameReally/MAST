#include "Tree.h"

using namespace std;

Tree::Tree(string newick) {
	countVertices(newick);
	int inner = leaves;

	root.parent = NULL;
	root.sibling = NULL;
	root.label = ++inner;
	Node* current = &root;
	Node* node;

	bool previousWasDigit = false;
	string label;

	for (char character : newick) {
		if (isdigit(character)) {
			label.push_back(character);
			previousWasDigit = true;
		}
		else {
			if (previousWasDigit) {
				current->label = stoi(label);
				label.clear();
				previousWasDigit = false;
			}
			switch (character) {
			case '(':
				if (current->label == NULL)
					current->label = ++inner;
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
