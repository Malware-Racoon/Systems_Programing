/**
 *
 * Gustave A Michel III
 * 02/04/15
 *
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h> //C99 bool type

#define CMD_BUFFER 20 //20 commands per input
#define TOKEN_BUFFER 20 //20 tokens per command
#define TOKEN_LENGTH 80 //80 char per token

struct Command {
	char tokens[TOKEN_BUFFER][TOKEN_LENGTH];
	bool pipes;
};

int parse_input(struct Command *cmd, int command_buffer, int token_buffer, int token_length);
bool has_command(struct Command cmd);
bool has_token(char* token);

struct Command cmds[CMD_BUFFER]; //Store each Cmd

int main(int argc, char *argv[])
{
	int i;
	int j;
	int k;

	while(true) //program loop
	{
		//clear Command Struct array
		memset(&cmds, 0, sizeof(struct Command)*CMD_BUFFER);

		//Prompt User
		//printf("%% ");
		printf("please enter a string: ");

		//Get input and parse into struct array
		if(parse_input(cmds, CMD_BUFFER, TOKEN_BUFFER, TOKEN_LENGTH) == 1)
		{
			return(1);
		}
		
		int num_cmds = 0;
		int num_tokens = 0;
		for(i = 0; i < CMD_BUFFER; i++)
		{
			if(has_command(cmds[i])) //Command contains at least one token
			{
				for(j = 0; j < CMD_BUFFER; j++)
				{
					if(has_token(cmds[i].tokens[j]))
					{
						num_tokens++;
						printf("%d: %s\n",num_tokens,cmds[i].tokens[j]);
					} else {
						break; //last token
					}
				}
			}
			else
			{
				num_cmds = i; //last command
				break;
			}
		}
		printf("Tokens: %d; Commands: %d;\n", num_tokens, num_cmds);
		for(i = 0; i < CMD_BUFFER; i++)
		{
			if(has_command(cmds[i])) //Command contains at least one token
			{
				printf("\"");
				for(j = 0; j < CMD_BUFFER; j++)
				{
					if(has_token(cmds[i].tokens[j]))
					{
						if(j != 0)
							printf(" ");
						printf("%s",cmds[i].tokens[j]);
					} else {
						break; //last token
					}
				}
				printf("\"\n");
			}
			else
			{
				break;
			}
		}
	}
}

// Parses line from Stdin into cmd struct array containing an array of the tokens,
// and weather the command pipes into the next command
int parse_input(struct Command *cmd, int command_buffer, int token_buffer, int token_length)
{
	int cmdin_buffer = 20;
	char cmdin[cmdin_buffer];
	
	//clear Command Input array
	memset(cmdin, 0, sizeof(char)*cmdin_buffer);
	fgets(cmdin, cmdin_buffer, stdin);

	int cmd_counter = 0; //current command (i)
	int cmd_token = 0; //current token in command (j)
	int cmd_token_pos = 0; //current string position in token (k)
	
	int i;
	for(i = 0; true; i++) //parse indivdual commands and tokens, and label pipes
	{
		//trims all whitespace before beginning of cmd
		while(cmd_token_pos == 0 && (cmdin[i] == ' ' || cmdin[i] == '	'))
			i++;
		char c = cmdin[i];
		if(c == '\n') //new line, end of input
			break;
		else if(c == '\0') //null, we probably have more to get
		{
			fgets(cmdin, cmdin_buffer, stdin);
			i = -1; //will incrament and start at zero
			continue;
		}

		switch(c)
		{
			case '|': //set pipe then treat as moving to next command
				cmd[cmd_counter].pipes = true; //This command pipes to the next
			case ';': //end of a command
				if(cmd_counter == command_buffer-1)
				{
					printf("Number of Commands Overflow\n");
					return(1);
				}
				cmd[cmd_counter].tokens[cmd_token][cmd_token_pos] = '\0'; //end last token
				cmd_counter++;
				cmd_token = 0;
				cmd_token_pos = 0;
				break;
			case '<': //Special Characters
			case '>':
			case '&':
			case '"':
			case ' ': //treat all whitespace delimiters the same
			case '	':
				if(cmd_token == token_buffer-1)
				{
					printf("Number of Tokens Overflow\n");
					return(1);
				}
				cmd[cmd_counter].tokens[cmd_token][cmd_token_pos] = '\0'; //end token
				cmd_token++;
				cmd_token_pos = 0;
				while(cmd_token_pos == 0 && (cmdin[i+1] == ' ' || cmdin[i+1] == '	')) i++; //remove remaining before next token
				break;

			default:
				if(cmd_token_pos == token_length) {
					cmd[cmd_counter].tokens[cmd_token][cmd_token_pos] = '\0'; //end token
					printf("Token Length Overflow\n");
					return(1);
				}
				cmd[cmd_counter].tokens[cmd_token][cmd_token_pos++] = c;
				break;
		}
	}
	cmd[cmd_counter].tokens[cmd_token][cmd_token_pos] = '\0'; //"close" last token
	return(0); //success!
}

bool has_command(struct Command cmd)
{
	return(cmd.tokens[0][0] != '\0'); //at least one token
}

bool has_token(char* token)
{
	return(token[0] != '\0'); //at least one char
}