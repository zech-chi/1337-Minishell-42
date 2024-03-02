   
# Python3 Program to print binary tree in 2D
COUNT = [10]
 
# Binary Tree Node
""" utility that allocates a newNode 
with the given key """
 
 
class newNode:
 
    # Construct to create a newNode
    def __init__(self, key):
        self.val = key
        self.left = None
        self.right = None
 
# Function to print binary tree in 2D
# It does reverse inorder traversal
 
 
def print2DUtil(root, space):
 
    # Base case
    if (root == None):
        return
 
    # Increase distance between levels
    space += COUNT[0]
 
    # Process right child first
    print2DUtil(root.right, space)
 
    # Print current node after space
    # count
    print()
    for i in range(COUNT[0], space):
        print(end=" ")
    print(root.val)
 
    # Process left child
    print2DUtil(root.left, space)
 
# Wrapper over print2DUtil()
 
 
def print2D(root):
 
    # space=[0]
    # Pass initial space count as 0
    print2DUtil(root, 0)