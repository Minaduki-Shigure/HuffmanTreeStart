#pragma once

#include<stdio.h>
#include<stdlib.h>

typedef int TElemType;

typedef struct{
	int weight;
	TElemType data;
	HuffmanTNode *Parent;
	HuffmanTNode *LeftChild;
	HuffmanTNode *RightChild;
}HuffmanTNode;

int statistics[127] = { 0 };