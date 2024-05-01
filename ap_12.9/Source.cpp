#include <iostream>
#include <fstream>
#include <limits.h>
#include <iomanip>
using namespace std;

typedef int Info;

struct Node {
    Node* left,
        * right;
    Info info;
};

void PrintTree(Node* root, int level) {
    if (root != NULL) {
        PrintTree(root->right, level + 1);
        for (int i = 1; i <= level; i++)
            cout << " ";
        cout << root->info << endl;
        PrintTree(root->left, level + 1);
    }
}

Node* BinarySearchInsert(Node*& root, Info value, bool& found) {
    if (root == NULL) {
        root = new Node;
        root->info = value;
        root->left = NULL;
        root->right = NULL;
        found = false;
        return root;
    }
    else if (value == root->info) {
        found = true;
        return root;
    }
    else if (value < root->info) {
        return BinarySearchInsert(root->left, value, found);
    }
    else {
        return BinarySearchInsert(root->right, value, found);
    }
}

Node* FindMax(Node* root) {
    if (root->right != NULL)
        return FindMax(root->right);
    else
        return root;
}

void RightRotation(Node*& root) {
    Node* tmp1 = root->left;
    Node* tmp2 = tmp1->right;
    tmp1->right = root;
    root->left = tmp2;
    root = tmp1;
}

void LeftRotation(Node*& root) {
    Node* tmp1 = root->right;
    Node* tmp2 = tmp1->left;
    tmp1->left = root;
    root->right = tmp2;
    root = tmp1;
}

int Height(Node* root) {
    if (root == NULL)
        return 0;
    int hL = Height(root->left);
    int hR = Height(root->right);
    return (hL > hR ? hL : hR) + 1;
}

int BFactor(Node* root) {
    return Height(root->right) - Height(root->left);
}

void BalanceHeight(Node*& root) {
    if (root != NULL) {
        while (BFactor(root) >= 2) {
            if (BFactor(root->right) < 0)
                RightRotation(root->right);
            LeftRotation(root);
        }
        while (BFactor(root) <= -2) {
            if (BFactor(root->left) > 0)
                LeftRotation(root->left);
            RightRotation(root);
        }
        BalanceHeight(root->left);
        BalanceHeight(root->right);
    }
}

void insert(Node** root, int value) {
    if (*root == nullptr) {
        *root = new Node;
        (*root)->info = value;
        (*root)->left = (*root)->right = nullptr;
        return;
    }
    if (value < (*root)->info) {
        insert(&(*root)->left, value);
    }
    else {
        insert(&(*root)->right, value);
    }
}

void PrefixOrderWithMax(Node* root, Node*& maxNode) {
    if (root != NULL) {
        if (maxNode == NULL || root->info > maxNode->info) {
            maxNode = root;
        }
        PrefixOrderWithMax(root->left, maxNode);
        PrefixOrderWithMax(root->right, maxNode);
    }
}

void PrintTreeWithHighlight(Node* root, int highlight_value) {
    if (root == NULL) {
        return;
    }

    if (root->left != NULL) {
        PrintTreeWithHighlight(root->left, highlight_value);
    }

    if (root->right != NULL) {
        PrintTreeWithHighlight(root->right, highlight_value);
    }

    if (root->info == highlight_value) {
        cout << "[" << root->info << "] ";
    }
    else {
        cout << root->info << " ";
    }
}

void FindFirstMax(Node* root) {
    Node* maxNode = NULL;
    PrefixOrderWithMax(root, maxNode);

    if (maxNode != NULL) {
        cout << "First node with maximum value is: " << maxNode->info << endl;
        PrintTreeWithHighlight(root, maxNode->info);
    }
    else {
        cout << "Binary tree is empty" << endl;
    }
}

void PostfixOrder(Node* root) {
    if (root != NULL) {
        PostfixOrder(root->left);
        PostfixOrder(root->right);
        cout << root->info << " ";
    }
}

int main() {
    int N;
    cout << "Nodes count: "; cin >> N;
    Node* root = NULL;
    Info value;
    bool found = false;
    for (int i = 0; i < N; i++) {
        cout << "value: "; cin >> value;
        BinarySearchInsert(root, value, found);
    }
    cout << endl;
    PrintTree(root, 0);
    cout << endl;
    BalanceHeight(root);
    cout << endl;
    PrintTree(root, 0);
    char answer;
    do {
        int value;
        cout << "Enter value to insert: ";
        cin >> value;
        insert(&root, value);
        PrintTree(root, 0);
        cout << "Do you want to add another node? (y/n): ";
        cin >> answer;
    } while (answer == 'y');

    FindFirstMax(root);
    cout << endl;


    return 0;
}
