#include"HuffmanTree.h"

void FileStatistic(FILE *fp)
{
	char buffer;
	buffer = fgetc(fp);
	while (buffer != EOF)
	{
		statistics[(int)buffer]++;
		buffer = fgetc(fp);
	}
	return;
}

void TakeSmallestWeight(HuffmanTree tree, int end, int *s1, int *s2)
{
	*s1 = 1;
	*s2 = 1;
	int buffer[127] = { 0 };
	int i = 0;
	int a = 1;
	for (i = 1; i <= end; i++)
		buffer[i] = tree[i].weight;
	for (i = 1; i <= end; i++)
	{
		if (buffer[i] <= buffer[*s1])
			*s1 = i;
	}
	for (i = 1; i <= end; i++)
	{
		if (i != *s1&&buffer[i] <= buffer[*s2])
			*s2 = i;
	}
	return;
}

HuffmanTree HuffmanTreeInit(void)
{
	HuffmanTree tree;
	//int i, j, m, s1, s2, start;
	int i = 0, n = 0;
	for (i = 0; i < 128; i++)
	{
		if (statistics[i])
			n++;
	}
	int m = 2 * n - 1;
	tree = (HuffmanTree)malloc((m + 1) * sizeof(HuffmanTNode));
	int a = 1;
	for (i = 0; i < 128; i++)
	{
		if (statistics[i])
		{
			tree[a].data = i;
			tree[a].weight = statistics[i];
			tree[a].Parent = 0;
			tree[a].LeftChild = 0;
			tree[a].RightChild = 0;
			a++;
		}
	}
	for (i = a; i <= m; i++)
	{
		tree[i].data = 0;
		tree[i].weight = 0;
		tree[i].Parent = 0;
		tree[i].LeftChild = 0;
		tree[i].RightChild = 0;
	}
	int s1, s2;
	for (i = n + 1; i <= m; i++)
	{
		TakeSmallestWeight(tree, i - 1, &s1, &s2);
		tree[s1].Parent = i;
		tree[s2].Parent = i;
		tree[i].LeftChild = s1;
		tree[i].RightChild = s2;
		tree[i].weight = tree[s1].weight + tree[s2].weight;
	}
	char *cd;
	int start;
	unsigned int c, f;
	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = tree[i].Parent; f != 0; c = f, f = tree[f].Parent)
		{
			if (tree[f].LeftChild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		strcpy(tree[i].code, &cd[start]);
	}
	free(cd);
	return tree;
}