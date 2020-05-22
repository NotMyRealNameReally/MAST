#include "Tree.h"

using namespace std;

Tree::Tree(string newick){
	countVertices(newick);

	nodes = new Node*[leaves + innerVertices + 1];
	int innerLabel = leaves;

	//create root
	Node* current = new Node;
	current->parent = NULL;
	current->sibling = NULL;
	current->label = ++innerLabel;
	nodes[innerLabel] = current;

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

				nodes[leafLabel] = current;
			}
			switch (character) {
			case '(':
				if (current->label == NULL) {
					current->label = ++innerLabel;

					nodes[innerLabel] = current;
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

bool Tree::isAncestor(int ancestorLabel, int descendantLabel) const {
	Node* ancestor = nodes[ancestorLabel];
	Node* descendant = nodes[descendantLabel];

	while (descendant->parent != NULL) {
		if (descendant->parent == ancestor)
			return true;
		descendant = descendant->parent;
	}
	return false;
}

int Tree::countChildrenOf(int label) const {
	Node* node = nodes[label];
	if (node->child == NULL)
		return 0;
	node = node->child;
	int count = 1;

	while (node->sibling != NULL) {
		node = node->sibling;
		count++;
	}
	return count;
}

int* Tree::getChildrenOf(int label) {
	int amount = countChildrenOf(label);
	int* arr = new int[amount];
	Node* node = nodes[label]->child;

	for (int i = 0; i < amount; i++) {
		arr[i] = node->label;
		node = node->sibling;
	}
	return arr;
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
	for (int i = 1; i < (leaves + innerVertices + 1); i++) {
		delete nodes[i];
	}
	delete[] nodes;
}
