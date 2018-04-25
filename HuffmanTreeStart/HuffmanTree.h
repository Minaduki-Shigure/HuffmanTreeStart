#pragma once

#include<stdio.h>
#include<stdlib.h>

typedef struct{
	int weight;
	char data;
	HuffmanTNode *Parent;
	HuffmanTNode *LeftChild;
	HuffmanTNode *RightChild;
}HuffmanTNode;

int statistics[127] = { 0 };

void FileStatistic(FILE *fp);
HuffmanTNode* NewNode(void);
