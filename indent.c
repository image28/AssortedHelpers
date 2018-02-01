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
	int casecount=0;
	int ccount=0;
	int acount=0;
	int scount=0;
	int ecount=0;
	int semicount=0;	
	int bcount=0;
	int rcount=0;
	int kcount=0;

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
				next=0;
			}
			else if ( line[count-1] == '\t' )
			{
				line[count-1]=line[count];
			}
			else if ( line[count-1] == 'c' )
			{
				ccount++;
				count++;
			}
			else if ( line[count-1] == 'a' )
			{
				acount++;
				count++;
			}
			else if ( line[count-1] == 's' )
			{
				scount++;
				count++;
			}
			else if ( line[count-1] == 'e' )
			{
				ecount++;
				count++;
			}
			else if ( line[count-1] == ':' )
			{
				semicount++;
				count++;
			}
			else if ( line[count-1] == 'b' )
			{
				bcount++;
				count++;
			}
			else if ( line[count-1] == 'r' )
			{
				rcount++;
				count++;
			}
			else if ( line[count-1] == 'k' )
			{
				kcount++;
				count++;
			}
			else if ( line[count-1] != '\t' )
			{
				count++;
			}

			//printf("case: %d\tbreak: %d\n",casecount,breakcount);
			
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
		else if ( line[count-1] == ':' )
		{
			semicount++;
		}

		if ( ccount >= 1 )
		{
			if ( acount >= 1 )
			{
				if ( scount >= 1 )
				{
					if ( ecount >= 1 )
					{
						if ( semicount == 1 )
						{
							tabs++;
							next=1;
							casecount++;
						}
					}
				}
			}
		}

		if ( casecount >= 1 )
		{
			if ( bcount == 1 )
			{
				if ( rcount == 1 )
				{
					if ( ecount == 1 )
					{
						if ( acount == 1 )
						{
							if ( kcount == 1 )
							{
								tabs--;
								casecount--;
							}
						}
					}
				}
			}
		}

		for(d=next; d < tabs; d++)
			printf("\t");

		for(d=0; d < count; d++)
			printf("%c",line[d]);

		ccount=0;
		acount=0;
		ecount=0;
		scount=0;
		bcount=0;
		rcount=0;
		kcount=0;
		semicount=0;
		count=1;
		next=0;
	}

	RET;
}
