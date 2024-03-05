from typing import Optional


class Node:
    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def treeToDoublyList(self, root: 'Optional[Node]') -> 'Optional[Node]':
        print(root.val)
        if not root:
            return None
        if not root.left and not root.right:
            root.left = root.right = root
            return root
        l = self.treeToDoublyList(root.left)
        if l:
            ltail = l.left
            ltail.right = root
            root.left = ltail
            l.left = root
            root.right = l
        r = self.treeToDoublyList(root.right)
        if not l:
            root.left = root.right = root
            l = root
        if r:
            ltail = l.left
            rtail = r.left
            ltail.right = r
            r.left = ltail
            l.left = rtail
            rtail.right = l
        return l


if __name__ == "__main__":
    head = Node(2, Node(1), Node(3))
    sol = Solution()
    dlist = sol.treeToDoublyList(head)
    ptr = head
    while ptr != head:
        print(ptr.val)
        ptr = ptr.right
