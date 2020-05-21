
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

int max(int a, int b) {
	return a > b ? a : b;
}

int associateChildren(int** matrix, int* firstChildren, int* secondChildren, int firstAmount, int secondAmount, int current) {
	if (current == firstAmount)
		return 0;

	int bestScore = associateChildren(matrix, firstChildren, secondChildren, firstAmount, secondAmount, current + 1);
	for (int i = 0; i < secondAmount; i++) {
		if (secondChildren[i] != 0) {
			int temp = secondChildren[i];
			secondChildren[i] = 0;
			int currentScore = matrix[firstChildren[current]][temp] + associateChildren(matrix, firstChildren, secondChildren, firstAmount, secondAmount, current + 1);
			secondChildren[i] = temp;
			bestScore = bestScore > currentScore ? bestScore : currentScore;
		}
	}
	return bestScore;
}

int compareWithChildren(int** matrix, int first, int second, int* firstChildren, int* secondChildren, int firstAmount, int secondAmount) {
	int value = 0;
	for (int i = 0; i < secondAmount; i++)
		value = max(value, matrix[first][secondChildren[i]]);
	for (int i = 0; i < firstAmount; i++)
		value = max(value, matrix[firstChildren[i]][second]);
	return value;
}

void compareInner(Tree& first, Tree& second, int** matrix, int leavesAmount, int rows, int columns) {
	for (int i = rows - 1; i > leavesAmount; i--) {
		for (int j = columns - 1; j > leavesAmount; j--) {
			int firstAmount = first.countChildrenOf(i);
			int	secondAmount = second.countChildrenOf(j);
			int* firstChildren = first.getChildrenOf(i);
			int* secondChildren = second.getChildrenOf(j);

			int value = associateChildren(matrix, firstChildren, secondChildren, firstAmount, secondAmount, 0);
			value = max(value, compareWithChildren(matrix, i, j, firstChildren, secondChildren, firstAmount, secondAmount));
			matrix[i][j] = value;

			delete[] firstChildren;
			delete[] secondChildren;
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
	compareInner(first, second, comparisonMatrix, leavesAmount, rows, columns);

	int result = leavesAmount - comparisonMatrix[leavesAmount + 1][leavesAmount + 1];
	deleteMatrix(comparisonMatrix, rows, columns);
	return result;
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

