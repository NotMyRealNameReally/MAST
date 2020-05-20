
#include <iostream>
#include <string>
#include "Tree.h"
using namespace std;


/*
(4,(8,1,(5,3)),(9,2,(10,(7,6))))
(10,(8,(9,(5,4)),(6,2,3)),(7,1))
*/

int** createMatrix(int rows, int columns) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++)
		matrix[i] = new int[columns];
	return matrix;
}

void deleteMatrix(int** matrix, int rows, int columns) {
	for (int i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void fillLeaves(int** matrix, int amount) {
	for (int i = 1; i <= amount; i++) {
		for (int j = 1; j <= amount; j++) {
			if (i == j)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
		}
	}
}

void compareInnerWithLeaves(Tree& first, Tree& second, int** matrix, int leavesAmount, int rows, int columns) {
	for (int leaf = 1; leaf <= leavesAmount; leaf++) {
		for (int inner = leavesAmount + 1; inner < rows; inner++) {
			matrix[inner][leaf] = first.isAncestor(inner, leaf) ? 1 : 0;
		}
		for (int inner = leavesAmount + 1; inner < columns; inner++) {
			matrix[leaf][inner] = second.isAncestor(inner, leaf) ? 1 : 0;
		}
	}
}

int compareTrees(Tree& first, Tree& second) {
	int rows = first.getVerticesAmount() + 1;
	int columns = second.getVerticesAmount() + 1;
	int** comparisonMatrix = createMatrix(rows, columns); // macierz porównawcza indeksuje od 1
	int leavesAmount = first.getLeavesAmount(); //oba drzewa mają tyle samo liści
	fillLeaves(comparisonMatrix, leavesAmount);
	compareInnerWithLeaves(first, second, comparisonMatrix, leavesAmount, rows, columns);


	deleteMatrix(comparisonMatrix, rows, columns);
	return 1;
}

int main() {
	int amount;
	string* trees;
	cin >> amount;
	trees = new string[amount];

	for (int i = 0; i < amount; i++) {
		string tree;
		cin >> tree;
		trees[i] = tree;
	}
	for (int i = 0; i < amount - 1; i++) {
		Tree first(trees[i]);
		for (int j = i + 1; j < amount; j++) {
			Tree second(trees[j]);
			cout << compareTrees(first, second) << endl;
		}
	}
	delete[] trees;
}

