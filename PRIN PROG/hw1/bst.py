#!/usr/bin/env python3


class Node:
    def __init__(self, key):
        self.key = key
        self.right = None
        self.left = None


def search(root, key):
    key = int(key)
    if root is None:
        print("not found")
        return

    if root.key == key:
        print("found: root")
        return

    path = []
    node = root
    while node is not None:
        if node.key == key:
            path = ' '.join(map(str, path))
            print('found: ' + path)
            return
        if node.key > key:
            path.append('l')
            node = node.left
        elif node.key < key:
            path.append('r')
            node = node.right

    print("not found")
    return


def createNode(parent, key):
    key = int(key)
    temp = Node(key)
    if parent is None:
        return temp

    node = parent
    prev = 0
    while node is not None:
        prev = node
        if node.key > key:
            node = node.left
        elif node.key < key:
            node = node.right

    if prev.key > key:
        prev.left = temp
    elif prev.key < key:
        prev.right = temp

    return parent


def main():
    root = None
    while True:
        try:
            list = input()
            list = list.split()
            if list[0] == 'i':
                root = createNode(root, list[1])
            elif list[0] == 'q':
                search(root, list[1])
        except EOFError:
            return


if __name__ == "__main__":
    main()
