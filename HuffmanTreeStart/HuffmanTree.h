#pragma once

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

#define NAMESIZE 500
#define INIT1 50000
#define INIT2 400000
#define INCREASE1 10000
#define INCREASE2 80000

typedef struct {
	unsigned long weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree, *HTree;

typedef char** HuffmanCode;

void StrCopy(char *str, const char *c);
void WeightSelect(HuffmanTree T, int n, int &l, int &r);
void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n);
void HuffmanCodeOutput(HuffmanCode C, int* s, int n);
void ReSync(HuffmanTree &T, char *s, int *x, int n, long long int &m);
void EnCode(const char *s);
void DeCode(const char *s);