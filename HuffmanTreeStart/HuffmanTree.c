#include"HuffmanTree.h"

void FileStatistic(FILE *fp)
{
	char buff;
	buff = fgetc(fp);
	while (buff != EOF)
	{
		statistics[(int)buff]++;
		buff = fgetc(fp);
	}
	return;
}

HuffmanTNode* NewNode(void)
{
	HuffmanTNode *newnode = (HuffmanTNode*)malloc(sizeof(HuffmanTNode));
	newnode->data = 0;
	newnode->weight = 0;
	newnode->Parent = NULL;
	newnode->LeftChild = NULL;
	newnode->RightChild = NULL;
	return newnode;
}

HuffmanTNode *HuffmanTreeInit(int n)
{
	int i, j, m, s1, s2, start;
	if (n == 1)
		exit(-1);

}