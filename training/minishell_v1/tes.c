// Program to print binary tree in 2D
#include <stdlib.h>
#include <stdio.h>
#define COUNT 10

// A binary tree node
struct Node {
	int data;
	struct Node *left, *right;
};

// Helper function to allocates a new node
struct Node* newNode(int data)
{
	struct Node* node
		= (struct Node*)malloc(sizeof(struct Node));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(struct Node* root, int space)
{
	// Base case
	if (root == NULL)
		return;

	// Increase distance between levels
	space += COUNT;

	// Process right child first
	print2DUtil(root->right, space);

	// Print current node after space
	// count
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->data);

	// Process left child
	print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D(struct Node* root)
{
	// Pass initial space count as 0
	print2DUtil(root, 0);
}

// Driver program to test above functions
int main()
{
	struct Node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);

	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(7);

	root->left->left->left = newNode(8);
	root->left->left->right = newNode(9);
	root->left->right->left = newNode(10);
	root->left->right->right = newNode(11);
	root->right->left->left = newNode(12);
	root->right->left->right = newNode(13);
	root->right->right->left = newNode(14);
	root->right->right->right = newNode(15);
	root->right->right->left->left = newNode(-1);
	root->right->right->left->right = newNode(-2);
	print2D(root);

	return 0;
}
