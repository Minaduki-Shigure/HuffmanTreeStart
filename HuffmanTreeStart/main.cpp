#include "HuffmanTree.h"

int main(int argc, char *argv[])
{
	const char *opt;
	const char *str;
	opt = argv[1];
	str = argv[2];
	if (argc > 0)
	{
		if (strcmp(opt, "-e") == 0)
			EnCode(str);
		else if (strcmp(opt, "-d") == 0)
			DeCode(str);
	}
	return 0;
}