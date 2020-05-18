
#include <iostream>
#include <string>
#include "Tree.h"
using namespace std;



int main()
{
    int amount;
    string* trees;
    cin >> amount;
    trees = new string[amount];

    for (int i = 0; i < amount; i++) {
        string tree;
        cin >> tree;
        cout << tree;
        trees[i] = tree;
    }
    for (int i = 0; i < amount - 1; i++) {
        Tree first(trees[i]);
        for (int j = i + 1; j < amount; j++) {
            Tree second(trees[j]);
            //cout << compareTrees(root1, root2) << endl;
        }
    }
    delete[] trees;
}

