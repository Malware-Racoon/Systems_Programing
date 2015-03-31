#include <unistd.h>
#include <stdio.h>

char opt;
int tokens = 0;
int commands = 0;
main(int argc, char* argv[])
{
	while ((opt = getopt(argc, argv, "|") != -1))
	{
		switch(opt)
		{
			case ' ' | '	':
				break;
			case'|':
				commands++;
				break;
			default:
				printf("%s\n", opt );
				tokens++;
				break;
		}
	}
	printf("%s\n", opt );
}