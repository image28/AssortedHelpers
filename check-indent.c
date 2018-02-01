#include "defines.h"

int main(int argc, char *argv[])
{
ARGCHECK(1);
	INPUT_FILE;
	int tabs=0;
	UCHAR line[1001];
	int count=1;
	int d=0;
	int next=0;
	int pos=0;
	int tabs2=0;
	int errorcount=0;	

	input=fopen(argv[1],"r");

	while ( ! feof(input) )
	{

		fread(&line[0],1,1,input);
		

		// SCAN LINE FOR BRACES ( OPEN/CLOSE )
		while ( ( line[count-1] != '\n' ) && ( ! feof(input) ) )
		{

			
			if ( ! feof(input) )
			{
				fread(&line[count],1,1,input);
			}
	
			if ( line[count-1] == '{' ) 
			{
				tabs++;
				next=1;
				count++;
			}
			else if ( line[count-1] == '}' ) 
			{ 
				tabs--;
				count++;
			}
			else if ( line[count-1] == '\t' )
			{
				//line[count-1]=line[count];
				tabs2++;
			}
			else if ( line[count-1] != '\t' )
			{
				count++;
			}

		}

		if ( line[count-1] == '{' ) 
		{ 
			tabs++;
			next=1;	
		}
		else if ( line[count-1] == '}' ) 
		{ 
			tabs--;
		}

		if ( tabs2 == tabs )
		{
			printf("Line %d has the correct number of tabs\n",pos);
		}else{
			printf("Line %d has a incorrect number of tabs\n",pos);
			errorcount++;
		}

		pos++;
		count=1;
		next=0;
		tabs2=0;
	}

	if ( tabs == 0 )
		printf("Correct number of open/close braces found\n");
	else
		printf("Incorrect number of open/close braces found\n");

	printf("Total errors : %d\n",errorcount+tabs);

	RET;
}
