#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void eulerTour(struct Node* root) {
    if (root == NULL) return;

    printf("%d ", root->data);  
    eulerTour(root->left);
    printf("%d ", root->data);
    eulerTour(root->right); 
}

void computeParent(struct Node* root, int parent) {
    if (root == NULL) return;

    printf("Vértice %d tem pai %d\n", root->data, parent);

    computeParent(root->left, root->data);
    computeParent(root->right, root->data);
}

int main() {
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);

    printf("Percurso de Euler: ");
    eulerTour(root);
    printf("\n");

    printf("\nComputando o pai de cada vértice:\n");
    computeParent(root, -1);

    return 0;
}
