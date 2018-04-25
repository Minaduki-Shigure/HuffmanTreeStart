#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
	int weight;
	char data;
	int Parent;
	int *LeftChild;
	int *RightChild;
	char code[10];
}HuffmanTNode, *HuffmanTree;

int statistics[127] = { 0 };

void FileStatistic(FILE *fp);
void TakeSmallestWeight(HuffmanTree tree, int end, int *s1, int *s2);
HuffmanTree HuffmanTreeInit(void);