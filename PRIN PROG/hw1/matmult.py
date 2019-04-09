#!/usr/bin/env python3
class Matrix:
    def __init__(self, m, n, entries):
        self.m = m
        self.n = n
        self.entries = entries


def printmatrix(matrix):
    for i in range(matrix.m):
        print(*matrix.entries[i])


def createMatrix():
    list = input()
    list = list.split()
    entries = []
    for _ in range(int(list[0])):
        row_entries = input().split()
        row_entries = [float(i) for i in row_entries]
        entries.append(row_entries)

    matrix = Matrix(int(list[0]), int(list[1]), entries)
    return matrix


def matmult(A, B):
    if A.n != B.m:
        print("invalid input")
        raise SystemExit

    Sum = 0
    R = []
    result = []
    for i in range(A.m):
        for j in range(B.n):
            for k in range(A.n):
                Sum += A.entries[i][k] * B.entries[k][j]
            R.append(Sum)
            Sum = 0
        result.append(R)
        R = []

    return(Matrix(A.m, B.n, result))


def main():
    matrixA = createMatrix()
    matrixB = createMatrix()
    matrixR = matmult(matrixA, matrixB)
    printmatrix(matrixR)


if __name__ == "__main__":
    main()
