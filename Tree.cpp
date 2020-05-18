#include "Tree.h"

using namespace std;

Tree::Tree(string newick) {
	for (char& character : newick) {
		if (isdigit(character))
			leaves++;
	}
	innerVertices = leaves;
	root.parent = NULL;
	root.sibling = NULL;
	root.label = ++innerVertices;
	Node* current = &root;
	Node* node;

	for (char& character : newick) {
		if (isdigit(character))
			current->label = character - '0';
		else {
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
