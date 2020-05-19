#include "Tree.h"

using namespace std;

Tree::Tree(string newick) {
	bool previousWasDigit = false;
	for (char& character : newick) {
		if (isdigit(character)) {
			leaves++;
			if (previousWasDigit)
				leaves--;
			previousWasDigit = true;
		} else
			previousWasDigit = false;
	}
	innerVertices = leaves;
	root.parent = NULL;
	root.sibling = NULL;
	root.label = ++innerVertices;
	Node* current = &root;
	Node* node;
	string label;

	for (char character : newick) {
		if (isdigit(character)) {
			label.push_back(character);
			previousWasDigit = true;
		}
		//current->label = character - '0';
		else {
			if (previousWasDigit) {
				current->label = stoi(label);
				label.clear();
				previousWasDigit = false;
			}
			switch (character) {
			case '(':
				if (current->label == NULL)
					current->label = ++innerVertices;
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
	innerVertices -= leaves;
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
