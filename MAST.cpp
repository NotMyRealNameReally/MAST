
#include <iostream>
#include <string>
#include "Tree.h"

using namespace std;

int** createMatrix(int rows, int columns) {
	int** matrix = new int* [rows];
	for (int i = 0; i < rows; i++)
		matrix[i] = new int[columns];
	return matrix;
}

void deleteMatrix(int** matrix, int rows) {
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

	//przypadek w którym aktualny wierzchołek nie jest wiązany z żadnym innym
	int bestScore = associateChildren(matrix, firstChildren, secondChildren, firstAmount, secondAmount, current + 1);

	for (int i = 0; i < secondAmount; i++) {
		if (secondChildren[i] != 0) {
			int temp = secondChildren[i];
			secondChildren[i] = 0;

			int associateCurrent = matrix[firstChildren[current]][temp];
			int currentScore = associateCurrent + associateChildren(matrix, firstChildren, secondChildren, firstAmount, secondAmount, current + 1);
			bestScore = max(bestScore, currentScore);

			secondChildren[i] = temp;
		}
	}
	return bestScore;
}

int compareWithChildren(int** matrix, int first, int second, int* firstChildren, int* secondChildren, int firstAmount, int secondAmount) {
	int score = 0;
	for (int i = 0; i < secondAmount; i++)
		score = max(score, matrix[first][secondChildren[i]]);
	for (int i = 0; i < firstAmount; i++)
		score = max(score, matrix[firstChildren[i]][second]);
	return score;
}

void compareInner(Tree& first, Tree& second, int** matrix, int leavesAmount, int rows, int columns) {
	for (int i = rows - 1; i > leavesAmount; i--) {
		for (int j = columns - 1; j > leavesAmount; j--) {
			int firstAmount = first.countChildrenOf(i);
			int	secondAmount = second.countChildrenOf(j);
			int* firstChildren = first.getChildrenOf(i);
			int* secondChildren = second.getChildrenOf(j);

			int score = associateChildren(matrix, firstChildren, secondChildren, firstAmount, secondAmount, 0);
			score = max(score, compareWithChildren(matrix, i, j, firstChildren, secondChildren, firstAmount, secondAmount));
			matrix[i][j] = score;

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
	deleteMatrix(comparisonMatrix, rows);
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

