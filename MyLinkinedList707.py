class Node:
    def __init__(self, val=-1):
        self.val = val
        self.next = None


class MyLinkedList:

    def __init__(self):
        self.prevHead = Node()
        self.tail = None
        self.cnt = 0

    def get(self, index: int) -> int:
        if index < 0 or index >= self.cnt:
            return -1
        curr = self.prevHead.next
        for _ in range(index):
            curr = curr.next
        return curr.val

    def addAtHead(self, val: int) -> None:
        rest = self.prevHead.next
        self.prevHead.next = Node(val)
        self.prevHead.next.next = rest
        self.cnt += 1

    def findTail(self):
        if self.tail:
            return
        curr = self.prevHead.next
        while curr.next:
            prev = prev.next
            curr = curr.next
        self.tail = curr

    def addAtTail(self, val: int) -> None:
        if self.cnt == 0:
            self.addAtHead(val)
            return
        self.findTail()
        self.tail.next = Node(val)
        self.tail = self.tail.next
        self.cnt += 1

    def addAtIndex(self, index: int, val: int) -> None:
        if index < 0 or index > self.cnt:
            return
        if index == 0:
            self.addAtHead(val)
            return
        if index == self.cnt:
            self.addAtTail(val)
            return
        prev = self.prevHead
        curr = prev.next
        for _ in range(index):
            prev = prev.next
            curr = curr.next
        prev.next = Node(val)
        prev.next.next = curr
        self.cnt += 1

    def deleteAtIndex(self, index: int) -> None:
        if index < 0 or index >= self.cnt:
            return
        prev = self.prevHead
        curr = prev.next
        for _ in range(index):
            prev = prev.next
            curr = curr.next
        prev.next = curr.next

        if index == self.cnt - 1:  # If deleting the last element
            self.tail = prev  # Update tail to the new last element

        if self.cnt == 1:  # If the list is now empty
            self.tail = None

        self.cnt -= 1

    def __str__(self):
        values = []
        current = self.prevHead.next  # Start from the first actual node
        while current:
            values.append(str(current.val))  # Convert each value to string
            current = current.next
        print(f"size: {len(values)}")
        return " -> ".join(values)


if __name__ == "__main__":
    operations = ["addAtHead", "addAtTail", "addAtTail", "get", "get", "addAtTail", "addAtIndex", "addAtHead", "addAtHead", "addAtTail", "addAtTail", "addAtTail", "addAtTail", "get", "addAtHead", "addAtHead", "addAtIndex", "addAtIndex", "addAtHead", "addAtTail", "deleteAtIndex", "addAtHead", "addAtHead", "addAtIndex", "addAtTail", "get", "addAtIndex", "addAtTail", "addAtHead", "addAtHead", "addAtIndex", "addAtTail", "addAtHead", "addAtHead", "get", "deleteAtIndex", "addAtTail", "addAtTail", "addAtHead", "addAtTail", "get", "deleteAtIndex", "addAtTail", "addAtHead", "addAtTail", "deleteAtIndex", "addAtTail", "deleteAtIndex",
                  "addAtIndex", "deleteAtIndex", "addAtTail", "addAtHead", "addAtIndex", "addAtHead", "addAtHead", "get", "addAtHead", "get", "addAtHead", "deleteAtIndex", "get", "addAtHead", "addAtTail", "get", "addAtHead", "get", "addAtTail", "get", "addAtTail", "addAtHead", "addAtIndex", "addAtIndex", "addAtHead", "addAtHead", "deleteAtIndex", "get", "addAtHead", "addAtIndex", "addAtTail", "get", "addAtIndex", "get", "addAtIndex", "get", "addAtIndex", "addAtIndex", "addAtHead", "addAtHead", "addAtTail", "addAtIndex", "get", "addAtHead", "addAtTail", "addAtTail", "addAtHead", "get", "addAtTail", "addAtHead", "addAtTail", "get", "addAtIndex"]
    parameters = [[84], [2], [39], [3], [1], [42], [1, 80], [14], [1], [53], [98], [19], [12], [2], [16], [33], [4, 17], [6, 8], [37], [43], [11], [80], [31], [13, 23], [17], [4], [10, 0], [21], [73], [22], [24, 37], [14], [97], [8], [6], [17], [50], [28], [76], [79], [18], [30], [5], [9], [83], [3], [40], [26], [20, 90], [30], [
        40], [56], [15, 23], [51], [21], [26], [83], [30], [12], [8], [4], [20], [45], [10], [56], [18], [33], [2], [70], [57], [31, 24], [16, 92], [40], [23], [26], [1], [92], [3, 78], [42], [18], [39, 9], [13], [33, 17], [51], [18, 95], [18, 33], [80], [21], [7], [17, 46], [33], [60], [26], [4], [9], [45], [38], [95], [78], [54], [42, 86]]
    linked_list = MyLinkedList()  # Create an instance of MyLinkedList
    results = []

    for op, params in zip(operations, parameters):
        print(f"{op} {params}")
        method = getattr(linked_list, op)  # Get the method by name
        result = method(*params)  # Call the method with unpacked parameters
        results.append(result)
        print(linked_list)

    # Print or process the results as needed
    print(results)
