#include "HuffmanTree.h"

void NextByte(int a, char *b)
{
	int i = 0;
	for (i = 0; i < 8; i++)
		if (a)
		{
			b[7 - i] = 48 + a % 2;
			a = a / 2;
		}
		else b[7 - i] = '0';
		b[8] = '#';
}

void NextByte_2(int a, char *c)
{
	char b[8];
	int i = 0;
	for (i = 0; i < 8; i++)
	{
		if (a)
		{
			b[7 - i] = 48 + a % 2;
			a = a / 2;
		}
		else
			break;
	}
	for (int k = 0; k < i; k++)
		c[k] = b[8 - i + k];
	c[i] = '#';
	c[i + 1] = '#';
}

void verify(char *output)
{
	char cmd1[50] = "copy ";
	const char cmd2[] = " buffer";
	strcat(cmd1, output);
	strcat(cmd1, cmd2);
	char del[] = "del buffer";
	system(cmd1);
	FILE *fr = fopen("buffer", "rb");
	FILE *fw = fopen(output, "wb");
	char cpr[46] = "///////Powered by MINADUKI Technologies 2018.";
	char key[46];
	char buf;
	while (1)
	{
		buf = fgetc(fr);
		if (buf == 47)
		{
			printf("/ is found!\n");
			fread(key, sizeof(key) - 1, 1, fr);
			key[45] = '\0';
			if (strcmp(key, cpr) == 0)
			{
				printf("Flag is found!\n");
				fclose(fr);
				fclose(fw);
				system(del);
				return;
			}
		}
		fputc(buf, fw);
		if (buf == EOF)
			return;
	}
	fclose(fr);
	fclose(fw);
	system(del);
	return;
}

void Output(HuffmanTree &T, FILE *pr, int n, char *output)
{
	char c[9], *s;
	HuffmanTree p = T + 2 * n - 1;
	int a = fgetc(pr), w = 0;
	if (!feof(pr))
		NextByte(a, c);
	else
		NextByte_2(a, c);
	s = c;
	FILE *pw = fopen(output, "wb");
	while (!feof(pr))
	{
		if (*s == '0'&&p->lchild)
			p = T + p->lchild;
		else if (*s == '1'&&p->rchild)
			p = T + p->rchild;
		if (!p->lchild && !p->rchild)
		{
			if (*s == '0')
			{
				w = (T + p->parent)->lchild - 1;
				fwrite(&w, 1, 1, pw);
			}
			else
			{
				w = (T + p->parent)->rchild - 1;
				fwrite(&w, 1, 1, pw);
			}
			p = T + 2 * n - 1;
		}
		s++;
		if (*s == '#')
		{
			a = fgetc(pr);
			if (!feof(pr))
				NextByte(a, c);
			else
				NextByte_2(a, c);
			s = c;
		}
	}
	fclose(pw);
	verify(output);
	return;
}

void DeCode(const char*s)
{
	printf("Starting the decode process!\n");
	FILE *pr = fopen(s, "rb");
	if (!pr)
	{
		printf("Failed to open the file!\n");
		exit(1);
	}
	char sname[NAMESIZE];
	int a, i = 0, j, n = 256, m = 2 * n - 1;
	HuffmanTree HT;
	char output[NAMESIZE];
	i = 0;
	while (s[i] != '.')
		i++;
	i--;
	j = 0;
	while (s[i] != 92 && i >= 0)
		sname[j++] = s[i--];
	i = 0;
	while (--j >= 0)
	{
		output[i] = sname[j];
		i++;
	}
	output[i] = '.';
	i++;
	j = 0;
	a = fgetc(pr);
	while (j < 4)
	{
		output[i] = a;
		if (j < 3)
			a = fgetc(pr);
		j++;
		i++;
	}
	output[i] = '\0';
	HT = (HuffmanTree)malloc(sizeof(HTNode)*(m + 1));
	HT[0].weight = 0;
	HT[0].parent = 0;
	HT[0].lchild = 0;
	HT[0].rchild = 0;
	for (i = 1; i <= n; i++)
	{
		HT[i].weight = 0;//反正用不到就设0吧。 
		HT[i].lchild = 0;
		HT[i].rchild = 0;
	}
	for (i = n + 1; i <= m; i++)
	{
		HT[i].weight = 0;
		fread(&a, 2, 1, pr);
		HT[i].lchild = a;
		HT[a].parent = i;
		fread(&a, 2, 1, pr);
		HT[i].rchild = a;
		HT[a].parent = i;
	}
	HT[m].parent = 0;
	Output(HT, pr, n, output);
	fclose(pr);
	printf("Finished！\n");
	return;
}