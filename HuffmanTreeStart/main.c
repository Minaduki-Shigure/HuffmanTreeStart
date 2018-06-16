#include"HuffmanTree.h"

int main(void)
{
	char input[20] = "";
	char output[20] = "";
	scanf("%s", input);
	scanf("%s", output);
	HuffmanTree tree;
	FILE *in = fopen(input, "r");
	FILE *out = fopen(output, "w");
	if (in == NULL)
	{
		printf("File open process retured with a failure!\n");
		system("pause");
		exit(-1);
	}
	FileStatistic(in);
	tree = HuffmanTreeInit();
	for (int j = 0; j < 128; j++)
		printf("%d %s\n", tree[j].data, tree[j].code);
	EnCode(tree, in, out);
	system("pause");
	return 0;
}