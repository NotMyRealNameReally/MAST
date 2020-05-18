#include "Tree.h"

using namespace std;

Tree::Tree(string newick) {
	for (char& character : newick) {
		if (isdigit(character))
			leaves++;
	}
	innerVertices = leaves + 1;
	root.parent = NULL;
	root.sibling = NULL;
	root.label = innerVertices++;
	Node* current = &root;

	for (char& character : newick) {
		Node node;

		//assign label to a leaf
		if (isdigit(character))
			current->label = character - '0';
		else {
			switch (character) {
			//create child
			case '(':
				if (current->label == NULL)
					current->label = innerVertices++;
				node.parent = current;
				current->child = &node;
				current = &node;
				break;
			//create sibling
			case ',':
				node.parent = current->parent;
				current->sibling = &node;
				node.label = NULL;
				break;
			//go back to parent
			case')':
				current = current->parent;
			}
		}
	}
	innerVertices -= leaves;
}
