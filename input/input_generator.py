"""
Program to generate random input files for sorting algorithms
"""

import getopt
import random
import sys

def main():
    if len(sys.argv) < 3:
        print("Usage: python sorting_input_generator.py <number of elements> <output file>")
        sys.exit(1)

    n = int(sys.argv[1])

    f = open(sys.argv[2], 'w')

    opts, args = getopt.getopt(sys.argv[3:], 'pad', ['pos', 'asc', 'desc'])

    positive = False
    ascending = False
    descending = False

    for opt, arg in opts:
        if opt in ('-p', '--pos'):
            positive = True
        elif opt in ('-a', '--asc'):
            ascending = True
        elif opt in ('-d', '--desc'):
            descending = True

    f.write(str(n) + '\n')
    if ascending:
        for i in range(n):
            f.write(str(i) + ' ')
    elif descending:
        for i in range(n):
            f.write(str(n - i) + ' ')
    else:
        for i in range(n):
            f.write(str(random.randint(0 if positive else -1000000, 1000000)) + ' ')

    f.close()

if __name__ == '__main__':
    main()