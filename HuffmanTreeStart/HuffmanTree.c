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

HuffmanTNode *HuffmanTreeInit(void)
{
	//int i, j, m, s1, s2, start;
	int i = 0, n = 0;
	for (i == 0; i < 128; i++)
	{
		if (statistics[i])
		{
			n++;
			HuffmanTNode* node = NewNode();
			node->data = i;
			node->weight = statistics[i];
		}
	}

}