#!/usr/bin/env python3
# This Source code can be used to Find the Functions in .C(Dot C) Files, using Command Prompt cmd.exe
# Command Line Arguments in Python is given below:
# python "C:\Users\91638\PycharmProjects\Function_reader\C_File_Functions_Reader_11_12_2022.py" C:\Users\91638\PycharmProjects\Function_reader\drv_adc.c
# imported Modules/Library
import re
import sys
import glob
import os


# read file (new way)
# print("Output #140: ")
# input_file = sys.argv[1]
# with open(input_file, 'r', newline='') as filereader:
# for row in filereader:
# print("{}".format(row.strip()))


# Read multiple files (glob, os import)
# print("Output #141: ")
# inputPath = sys.argv[1]
# for input_file in glob.glob(os.path.join(inputPath, '*.txt')):
# with open(input_file, 'r', newline='') as filereader:
# for row in filereader:
# print("{}".format(row.strip()))


#Stack operation is given below

class Stack(list):
    def __init__(self):
        self.stack = []

    def Push(self, a_data):
        self.stack.append(a_data)

    def Pop(self):
        if self.isEmpty():
            return -1
        return self.stack.pop()

    def Peak(self):
        return self.stack[-1]

    def isEmpty(self):
        if len(self.stack) == 0:
            return True
        return False


# Read a file and create a list of function names
f = sys.argv[1]
# with open(f, 'r', newline='') as filereader:
with open(f, 'r') as fileReader:
    # for line in fileReader:
    # print(line)

    codeListTemp = fileReader.readlines()
    codeList = codeListTemp
    # print("{}".format(line.strip()))
    fileLen = len(codeListTemp)

    stackAnno = Stack()
    stackBracket = Stack()
    # stackFunc = Stack()
    listFunc = list()

    for i in range(0, fileLen - 1):
        codeList[i] = codeListTemp[i].rstrip("\n")

        if '{' in codeList[i]:
            if '}' not in codeList[i]:
                stackBracket.Push(i + 1)
                # print('Line {}: {{ -> Push      {}'.format(i+1, stackBracket.stack))
            else:
                temp = stackBracket.Pop()
                # print('Line {}: }} -> Pop {}    {}'.format(i+1, temp, stackBracket.stack))
        elif '}' in codeList[i]:
            temp = stackBracket.Pop()
            # print('Line {}: }} -> Pop {}   {}'.format(i+1, temp, stackBracket.stack))
            if stackBracket.isEmpty() == True:
                listFunc.append(temp)
        else:
            continue

    # print(listFunc)
    for i in range(0, len(listFunc)):
        temp = codeList[listFunc[i] - 2].find('(')
        codeList[listFunc[i] - 2] = codeList[listFunc[i] - 2][:temp]
        codeList[listFunc[i] - 2] = codeList[listFunc[i] - 2].split(' ')
        print(codeList[listFunc[i] - 2][-1])

    # print(codeList.count('/*!'))