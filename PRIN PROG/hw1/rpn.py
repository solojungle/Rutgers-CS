#!/usr/bin/env python3


class Stack:
    def __init__(self):
        self.items = []

    def push(self, item):
        self.items.append(item)

    def pop(self):
        return self.items.pop()

    def peek(self):
        return self.items[len(self.items) - 1]

    def size(self):
        return len(self.items)

    def isEmpty(self):
        return self.items == []


def isoperator(op):
    if op == '+':
        return 0
    elif op == '-':
        return 1
    elif op == '*':
        return 2
    elif op == '/':
        return 3
    elif op == '~':
        return 4
    else:
        return -1


def handleOperator(op, stack):
    if op == -1:
        return

    if op == 4:
        # negation
        y = stack.pop()
        stack.push(y * -1)
        return

    if stack.size() < 2:
        print("invalid operator")
        return

    y = stack.pop()
    x = stack.pop()

    if op == 0:
        # addition
        stack.push(x + y)
        return
    elif op == 1:
        stack.push(x - y)
        # subtraction
        return
    elif op == 2:
        stack.push(x * y)
        # multiplication
        return
    elif op == 3:
        stack.push(x / y)
        # division
        return

    return


def main():
    stack = Stack()
    while True:
        try:
            operation = input()
            if operation[0].isdigit():
                stack.push(int(operation))
            elif isoperator(operation) > -1:
                if stack.size() < 1:
                    print("invalid operator")
                else:
                    handleOperator(isoperator(operation), stack)
            print(stack.peek())
        except EOFError:
            return
    return


if __name__ == "__main__":
    main()
