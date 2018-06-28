#pragma once

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

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
void EnCode(const char *s);

void NextByte(int a, char *b);
void NextByte_2(int a, char *c);
void verify(char *output);
void Output(HuffmanTree &T, FILE *pr, int n, char *output);
void DeCode(const char*s);