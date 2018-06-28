#include"HuffmanTree.h"

void StrCopy(char *str, const char *c)
{
	char *s = str;
	while (*c != '\0')
		*s++ = *c++;
	*s = '\0';
	return;
}

void WeightSelect(HuffmanTree T, int n, int &l, int &r)
{
	HuffmanTree p = T + 1;
	int a = 0, b = 0;
	for (int i = 1; i <= n; ++i, ++p)
	{
		if (!p->parent)
		{
			if (!a)
			{
				l = i;
				a = 1;
			}
			else if (!b)
			{
				r = i;
				b = 1;
			}
			else if (p->weight < (T + l)->weight || p->weight < (T + r)->weight)
			{
				if ((T + l)->weight <= (T + r)->weight)
					r = i;
				else
					l = i;
			}
		}
	}
	return;
}

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, int *w, int n)
{
	int f, c, start, m1, m2, i, m = 2 * n - 1;
	HuffmanTree p;
	HT = (HuffmanTree)malloc(sizeof(HTNode)*(m + 1));
	if (!HT)
	{
		printf("Out of memory!\n");
		exit(-1);
	}
	for (p = HT + 1, i = 1; i <= n; ++i, ++w, ++p)
	{
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (i = n + 1; i <= m; ++i, ++p)
	{
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (i = n + 1, p = HT + i; i <= m; ++i, ++p)
	{
		WeightSelect(HT, i - 1, m1, m2);
		p->weight = (HT + m1)->weight + (HT + m2)->weight;
		p->lchild = m1;
		p->rchild = m2;
		(HT + m1)->parent = i;
		(HT + m2)->parent = i;
	}
	HC = (HuffmanCode)malloc(sizeof(char*)*(n + 1));
	if (!HC)
	{
		printf("Out of memory!");
		exit(-1);
	}
	char *cd = (char*)malloc(sizeof(char)*n);
	cd[n - 1] = '\0';
	for (i = 1; i <= n; ++i)
	{
		start = n - 1;
		for (f = HT[i].parent, c = i; f != 0; c = f, f = HT[f].parent)
		{
			if (HT[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		HC[i] = (char*)malloc(sizeof(char)*(n - start));
		StrCopy(HC[i], cd + start);
	}
	free(cd);
	return;
}

void HuffmanCodeOutput(HuffmanCode C, int* s, int n)
{
	char *p;
	for (int i = 1; i <= n; ++i)
	{
		printf("Weight:%3d��Code:", s[i - 1]);
		p = C[i];
		while (*p != '\0')
			printf("%c", *p++);
		printf("\n");
	}
	return;
}

void EnCode(const char *s)
{
	FILE *pr, *pw;
	char cmd1[50] = "copy ";
	const char cmd2[] = " buffer";
	strcat(cmd1, s);
	strcat(cmd1, cmd2);
	char del[] = "del buffer";
	system(cmd1);
	int a, i = 0, weight[256] = { 0 }, j, n = 256, m = 2 * n - 1;
	HuffmanTree HT;
	HuffmanCode HC, hc;
	char CodedName[NAMESIZE], c = ' ';
	while (s[i] != '.')
	{
		CodedName[i] = s[i];
		i++;
	}
	CodedName[i] = '.';
	CodedName[1 + i] = 'e';
	CodedName[2 + i] = 'n';
	CodedName[3 + i] = 'c';
	CodedName[4 + i] = '\0';
	pr = fopen("buffer", "rb");
	if (!pr)
	{
		printf("Failed to open the file!\n");
		exit(-1);
	}
	a = fgetc(pr);
	while (!feof(pr))
	{
		weight[a]++;
		a = fgetc(pr);
	}
	fclose(pr);
	pr = fopen("buffer", "ab");
	fprintf(pr, "////////Powered by MINADUKI Technologies 2018. All rights reserved.////////");
	fclose(pr);
	HuffmanCoding(HT, HC, weight, 256);
	pw = fopen(CodedName, "wb");
	//��д��ԭ��չ�� ��ռ4���ֽڡ� ����4���ÿո���;��
	j = 0;
	while (s[++i])
	{
		fwrite(s + i, 1, 1, pw);
		j++;
	}
	while (j++ < 4)
		fwrite(&c, 1, 1, pw);
	for (i = n + 1; i <= m; i++)
	{
		fwrite(&((HT + i)->lchild), 2, 1, pw);
		fwrite(&((HT + i)->rchild), 2, 1, pw);
	}
	pr = fopen("buffer", "rb");
	a = fgetc(pr);
	i = 0;
	int b = 0;
	hc = HC;
	char *p = *(hc + a + 1);
	while (!feof(pr) || *p != '\0')
	{
		for (i = 0; i < 8; i++)
		{
			if (*p == '\0')
			{
				a = fgetc(pr);
				if (a >= 0)
					p = hc[a + 1];
				else
				{
					int h = 1;
					for (j = 0; j < 8 - i; j++)
						h = h * 2;
					b = b * h;
					break;
				}
			}
			int h = 1;
			for (j = 0; j < 7 - i; j++)
				h = h * 2;
			b = b + (*p - 48)*h;
			++p;
		}
		fwrite(&b, 1, 1, pw);
		b = 0;
	}
	printf("EnCoding finished!\n");
	fclose(pr);
	fclose(pw);
	system(del);
	return;
}