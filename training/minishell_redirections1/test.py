from test2 import print2D


#class Solution:

#    def __init__(self):
#        self.priority = {
#            '(': 1,
#            '&': 2,
#            '>': 3,
#            '|': 3,
#        }

#    def expTree(self, s: str) -> 'Node':
#        ops = [] # not Node yet
#        stack = [] # already Node

#        for ch in s:
#            if ch == '(':
#                ops.append(ch)
#            elif ch.isdigit():
#                stack.append(Node(ch)) # assumption: only single digit for each node
#            elif ch == ')':
#                while ops[-1] != '(':
#                    self.combine(ops, stack)
#                ops.pop() # pop left '('
#            else: # then operator
#                # @note: must be >=, for test case "1+2+3+4+5"
#                while ops and self.priority.get(ops[-1], 0) >= self.priority[ch]:
#                    self.combine(ops, stack)

#                ops.append(ch)

#        while len(stack) > 1: # eg input, '1+2'
#            self.combine(ops, stack)

#        return stack[0]

#    def combine(self, ops: list, stack: list) -> None:
#        root = Node(ops.pop())
#        # right first, then left, since it's a stack
#        root.right = stack.pop()
#        root.left = stack.pop()

#        stack.append(root)


class Node:

    def __init__(self, val: str):
        self.val = val
        self.left = None
        self.right = None

class TreeNode:
    def __init__(self, val='', left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def __init__(self):
        self.precedence = {'>': 3,  '|': 3, '&': 2}

    def buildTree(self, expression: str) -> TreeNode:
        postfix = self.infixToPostfix(expression)
        stack = []
        for char in postfix:
            if char.isdigit():
                node = TreeNode(char)
                stack.append(node)
            else:
                right = stack.pop()
                left = stack.pop()
                node = TreeNode(char, left, right)
                stack.append(node)
        return stack.pop()

    # converts infix to postfix
    def infixToPostfix(self, expression):
        postfix = []
        operator_stack = []
        i = 0
        while i < len(expression):
            if expression[i].isdigit():
                j = i
                while j < len(expression) and expression[j].isdigit():
                    j += 1
                postfix.append(expression[i:j])
                i = j
            elif expression[i] in self.precedence:
                while operator_stack and operator_stack[-1] != '(' and self.precedence[operator_stack[-1]] >= self.precedence[expression[i]]:
                    postfix.append(operator_stack.pop())
                operator_stack.append(expression[i])
                i += 1
            elif expression[i] == '(':
                operator_stack.append(expression[i])
                i += 1
            elif expression[i] == ')':
                while operator_stack and operator_stack[-1] != '(':
                    postfix.append(operator_stack.pop())
                operator_stack.pop()
                i += 1
            else:
                i += 1
        while operator_stack:
            postfix.append(operator_stack.pop())
        return postfix
    



treee = Solution().buildTree(input())
print2D(treee)