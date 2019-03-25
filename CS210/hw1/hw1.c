
/*
Conor Williams
2/19/2018
Dr. Wilder
Homework 1
*/
#include <stdio.h>
#include <string.h>
void comment(char CCXfile[]);
void identifier(char CCXfile[]);
void string(char CCXfile[]);
void keyword(char CCXfile[]);
void characterliteral(char CCXfile[]);
void operator(char CCXfile[]);
void numericliteral(char CCXfile[]);
void unk(char CCXfile[]);
int checkkeyword(char CCXfile[]); 
int i;

int main(int argc, char *argv[])
{
	char CCXfile[20000];
	if (argc == 1) //make sure command line took arguments
        {
                printf("No Command Line Argument. Exiting program...\n");
                return -1;
        }
	FILE *fIn = fopen(argv[1], "r");
	
    	if(fIn == 0)
	{
	    printf("File did not open.\n");
	    return -2;
	}
    	i=0;
	while((CCXfile[i]=fgetc(fIn))!=EOF)
	{
		i++;
	}  
    
	i=0;
	while(CCXfile[i] != '\0')
	{
		if(CCXfile[i] == '/' && CCXfile[i+1] == '*')
        	{
         		comment(CCXfile);
        	}
        	else if(CCXfile[i] == '.' || CCXfile[i] == '<' || CCXfile[i] == '>' || CCXfile[i] == '(' || CCXfile[i] == ')' || CCXfile[i] == '+' || CCXfile[i] == '-' || CCXfile[i] == '*' || CCXfile[i] == '/' || CCXfile[i] == '|' || CCXfile[i] == '&' || CCXfile[i] == ';' || CCXfile[i] == ',' || CCXfile[i] == ':' || CCXfile[i] == '=' || CCXfile[i] == '[' || CCXfile[i] == ']' || CCXfile[i] == '{' || CCXfile[i] == '}'|| CCXfile[i] == '!' || CCXfile[i] == '#' || CCXfile[i] == '@' || CCXfile[i] == '$') 
       		{
        		operator(CCXfile);
        	}
       		else if(CCXfile[i] == '"')
        	{
        		string(CCXfile);
        	}
        	else if(checkkeyword(CCXfile) == 1)
        	{
        		keyword(CCXfile);
        	}
        	else if(CCXfile[i] == '\'')
        	{
        		characterliteral(CCXfile);
		}
        	else if(CCXfile[i] >= 'A' && CCXfile[i] <= 'Z' || CCXfile[i] >= 'a' && CCXfile[i] <= 'z' )
        	{
        		identifier(CCXfile);
        	}
        	else if(CCXfile[i] >= '0' && CCXfile[i] <= '9')
        	{
        		numericliteral(CCXfile);
        	}
        	else
        	{
        		unk(CCXfile);
        	}
	}

	return 0;
}

void comment(char CCXfile[]) //prints comment to the screen and updates array index
{
	for (i; CCXfile[i] != '\0'; i++)
	{
	        printf("%c", CCXfile[i]);
	        if(CCXfile[i] == '*' && CCXfile[i+1] == '/')
	        {
			i++;
			printf("%c", CCXfile[i]);
		        break;
        	}
    	}
    	printf("%s\n", " (comment)");
	i++;

}

void identifier(char CCXfile[]) //prints identifier to screen and updates index
{
	//if(CCXfile[i-2] == '.')
	//{
       // printf("%c", CCXfile[i-1]);
	//}
	for(i; CCXfile[i] >= 'A' && CCXfile[i] <= 'Z' || CCXfile[i] >= 'a' && CCXfile[i] <= 'z' || CCXfile[i] >= '0' && CCXfile[i] <= '9' || CCXfile[i] == '_' ; i++)
    	{
    		printf("%c", CCXfile[i]);
    	}
    	printf(" (identifier)");
    	printf("\n");
}

void string(char CCXfile[]) //prints string to screen and updates index
{
	printf("%c", CCXfile[i]);
	i++;
   	for(i; CCXfile[i] != '"'; i++)
    	{
        printf("%c", CCXfile[i]);
    	}
	printf("%c", CCXfile[i]);
    	i++;
	printf(" (string)\n");
}

void keyword(char CCXfile[]) //prints keyword to screen and updates index
{
	for(i; CCXfile[i] >= 'a' && CCXfile[i] <= 'z'; i++)
	{
        	printf("%c", CCXfile[i]);
    	}
    	printf("%s\n", " (keyword)");
}

void characterliteral(char CCXfile[]) //prints character literal to screen and updates index
{
	printf("%c", CCXfile[i]);
	i++;
	for(i; CCXfile[i] != '\''; i++)
	{
		printf("%c", CCXfile[i]);
	}
	printf("%c %s\n", CCXfile[i], " (character literal)");
	i++;
	
}

void operator(char CCXfile[]) // prints operator to screen and updates index
{
	printf("%c", CCXfile[i]);
	i++;
	if(CCXfile[i] == '=' || CCXfile[i] == '.' || CCXfile[i] == '<' || CCXfile[i] == '>'  || CCXfile	[i] == '*' || CCXfile[i] == ':')
    	{
        	printf("%c", CCXfile[i]);
		i++;
    	}
    	printf(" (operator)\n");
}

void numericliteral(char CCXfile[]) //prints numeric literal to screen and updates index
{
	for(i; CCXfile[i] >= '0' && CCXfile[i] <= '9' || CCXfile[i] >= 'A' && CCXfile[i] <= 'F' || CCXfile[i] >= 'a' && CCXfile[i] <= 'f' || CCXfile[i] == '_' || CCXfile[i] == '.' || CCXfile[i] == '#'; i++)
	{
		printf("%c", CCXfile[i]);
    	}
    	printf(" (numeric literal)\n");
}

void unk(char CCXfile[])
{
	if(CCXfile[i] == '\n' || CCXfile[i] == ' ')
	{
        	i++;
    	}
    	else
    	{
        if(CCXfile[i] == '\377')
        {
       		exit(0);
     	}
        printf("%c", CCXfile[i]);
        printf(" (unk)\n");
        exit(0);
    	}
}
int checkkeyword(char CCXfile[]) //checks to see if 10 characters in input array are a keyword
//returns 1 if it finds a keyword and 0 if it does not
{
	int tmp = i;
	char str[10];
	for (int h = 0; h < 10; h++)
		str[h] = '\0';
	int g = 0;
	while(CCXfile[tmp] != '\0' && g < 10)
	{
		if (CCXfile[tmp] == ' ')
		{
			break;
		}
		str[g] = CCXfile[tmp];
		tmp++;
		g++;
	}
	if (strcmp(str, "accessor") == 0)
		return 1;
	if (strcmp(str, "and") == 0)
		return 1;
	if (strcmp(str, "array") == 0)
		return 1;
	if (strcmp(str, "bool") == 0)
		return 1;
	if (strcmp(str, "case") == 0)
		return 1;
	if (strcmp(str, "character") == 0)
		return 1;
	if (strcmp(str, "constant") == 0)
		return 1;
	if (strcmp(str, "else") == 0)
		return 1;
	if (strcmp(str, "elsif") == 0)
		return 1;
	if (strcmp(str, "end") == 0)
		return 1;
	if (strcmp(str, "exit") == 0)
		return 1;
	if (strcmp(str, "float") == 0)
		return 1;
	if (strcmp(str, "func") == 0)
		return 1;
	if (strcmp(str, "if") == 0)
		return 1;
	if (strcmp(str, "ifc") == 0)
		return 1;
	if (strcmp(str, "in") == 0)
		return 1;
	if (strcmp(str, "integer") == 0)
		return 1;
	if (strcmp(str, "is") == 0)
		return 1;
	if (strcmp(str, "mutator") == 0)
		return 1;
	if (strcmp(str, "natural") == 0)
		return 1;
	if (strcmp(str, "null") == 0)
		return 1;
	if (strcmp(str, "of") == 0)
		return 1;
	if (strcmp(str, "or") == 0)
		return 1;
	if (strcmp(str, "others") == 0)
		return 1;
	if (strcmp(str, "out") == 0)
		return 1;
	if (strcmp(str, "pkg") == 0)
		return 1;
	if (strcmp(str, "positive") == 0)
		return 1;
	if (strcmp(str, "proc") == 0)
		return 1;
	if (strcmp(str, "ptr") == 0)
		return 1;
	if (strcmp(str, "range") == 0)
		return 1;
	if (strcmp(str, "subtype") == 0)
		return 1;
	if (strcmp(str, "then") == 0)
		return 1;
	if (strcmp(str, "type") == 0)
		return 1;
	if (strcmp(str, "when") == 0)
		return 1;
	if (strcmp(str, "while") == 0)
		return 1;
	else
		return 0;
}











