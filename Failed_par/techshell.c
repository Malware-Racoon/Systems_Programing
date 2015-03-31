#include <stdio.h>

char string[80];
char * i;
int token = 0;
int command = 1;
int count = 1;

main()
{
	printf("Please enter a string: ");
	char *a = fgets(string,80,stdin);
	for(i=a; *i; i++)
	{
		if(*i == '|')
		{
			command++;
		}
	}
	char *tokens;
	char *array[80];
	int j = 0;
	tokens = strtok(string, "|, ,	,>");
	while(tokens != NULL)
	{
		if(*tokens != '|')
		{
			printf("%d: %s\n",count, tokens);
			count++;
			token++;
		}
		array[j] = tokens;
		tokens = strtok(NULL, " ,	" );
		j++;
	}

	printf("there are %d tokens, %d command \n",token,command);
	int k=0;
	while(k < j)
	{
		if(*array[k] == '|')
		{
			printf("\n");
		}
		else
		{
			printf("%s ", array[k]);
		}
		k++;
	}

}