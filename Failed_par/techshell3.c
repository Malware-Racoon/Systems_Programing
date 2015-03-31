#include <stdio.h>

char string[80];
int i = 0;
int token = 0;
int command = 1;
int count = 1;

main()
{
	printf("Please enter a string: ");
	char *a = fgets(string,80,stdin);
	while(a[i] !=0)
	{
		printf("%s\n",a[i] );
		i++;
		/*switch(*i)
		{
			case ' ' || '	':
				printf( "\n" );
				token++;
				break;
			case'|':
				command++;
				break;
			default:
				printf("%s", i);
				break;		
		}*/
	}
	printf("there are %d tokens, %d command \n",token,command);
	printf("%s\n", string);

}