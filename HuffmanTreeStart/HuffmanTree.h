#pragma once

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define NAMESIZE 500

typedef struct {
	unsigned long weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree, *HTree;

typedef char** HuffmanCode;

void StrCopy(char *str, const char *c);
void WeightSelect(HuffmanTree T, int n, int &l, int &r);
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
void HuffmanCodeOutput(HuffmanCode C, int* s, int n);
void Rewin(HuffmanTree &T, char *s, int *x, int n, int &m);
void EnCode(const char *s);
void DeCode(const char *s);