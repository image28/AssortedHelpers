//---------------------------------------------------------------------------
// This program auto-corrects some spacing problems with assignments before
// submitting them, it's not finished or perfect but it works....
//
// There is a small bug that prints one } at the end of the file.
//---------------------------------------------------------------------------
// By Image
//---------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma hdrstop

// Program Checks
// DONE 1. [2] should be [ 2 ]
// DONE 2. (2) should be ( 2 )
// 3. Tabs/Spaces Should be 3
// 4. spaces before and after = + - / * % (DONE == >= <= ) != += -=

#define TRUE 1
#define FALSE 0

#pragma argsused
int main(int argc, char* argv[])
{
        FILE *input;
        FILE *output;

        unsigned char inbyte='\0';
        unsigned char nextbyte='\0';
        unsigned char SPACE=32;
        unsigned char space=0;
        unsigned char outfile[1000];
        unsigned int errors=0;
        unsigned int open=0;
        unsigned char equal='=';
	unsigned long filesize=0;
	unsigned long pos=0;

        strcpy(outfile,argv[1]);
        strcat(outfile,".corrected");

        if ( ( input=fopen(argv[1],"r") ) == NULL ) exit(-1);
        if ( ( output=fopen(outfile,"w") ) == NULL ) exit(-2);

	fseek(input,0L,SEEK_END);
	filesize=ftell(input);
	fseek(input,0L,SEEK_SET);

        while ( ! feof(input) )
        {

                fread(&inbyte,1,1,input);

                switch(inbyte)
                {
			case '#':
				fwrite(&inbyte,1,1,output);
				fread(&inbyte,1,1,input);
				if ( inbyte == 'i' )
				{
					fwrite(&inbyte,1,1,output);
					fread(&inbyte,1,1,input);
					fwrite(&inbyte,1,1,output);

					while( inbyte != '>' )
					{
						fread(&inbyte,1,1,input);
						fwrite(&inbyte,1,1,output);
					}
				}else{
					fwrite(&inbyte,1,1,output);
				}
			break;

                        case '[':
                                // check next byte for space
                                fread(&nextbyte,1,1,input);
				pos++;

                                if ( nextbyte == 32 )
                                {
                                        fwrite(&inbyte,1,1,output);
                                        fwrite(&nextbyte,1,1,output);
                                }else{
                                        printf("Found 1 Error, [2 should be [ 2\n");
                                        errors++;
                                        fwrite(&inbyte,1,1,output);
                                        fwrite(&SPACE,1,1,output);
                                        fwrite(&nextbyte,1,1,output);
                                }

                                open = TRUE;
                        break;

                        case ']':
                                // check if previous byte was a space
                                if ( space )
                                {
                                        fwrite(&inbyte,1,1,output);
                                }else{
                                        printf("Found 1 Error, 2] should be 2 ]\n");
                                        errors++;
                                        fwrite(&SPACE,1,1,output);
                                        fwrite(&inbyte,1,1,output);
                                }

                                space = FALSE;
                                open = FALSE;
                        break;

                        case '(':
                                // check next byte for space
                                fread(&nextbyte,1,1,input);
				pos++;

                                if ( nextbyte == 32 )
                                {
                                        fwrite(&inbyte,1,1,output);
                                        fwrite(&nextbyte,1,1,output);
                                }else{
                                        printf("Found 1 Error, (2 should be ( 2\n");
                                        errors++;
                                        fwrite(&inbyte,1,1,output);
                                        fwrite(&SPACE,1,1,output);
                                        fwrite(&nextbyte,1,1,output);
                                }

                                open = TRUE;

                        break;

                        case ')':
                                // check previous byte for space
                                if ( space )
                                {
                                        fwrite(&inbyte,1,1,output);
                                }else{
                                        printf("Found 1 Error, 2) should be 2 )\n");
                                        errors++;
                                        fwrite(&SPACE,1,1,output);
                                        fwrite(&inbyte,1,1,output);
                                }

                                open = FALSE;
                                space = FALSE;
                        break;

			case '>':
				fread(&inbyte,1,1,input);	
				if ( inbyte == '>' )
				{
					fwrite(&inbyte,1,1,output);
					fwrite(&inbyte,1,1,output);
				}else{

				fseek(input,-3,SEEK_CUR);
				
				fread(&inbyte,1,1,input);

				if ( inbyte == 32 )
				{
					//fwrite(&inbyte,1,1,output);
					// write equal
					fread(&inbyte,1,1,input);
					fwrite(&inbyte,1,1,output);
					// check for equal after
					fread(&inbyte,1,1,input);
					// check for space after
					if ( inbyte == 32 )
					{
						fwrite(&inbyte,1,1,output);
					}else{	
						if ( inbyte == '=' )
						{
							fwrite(&equal,1,1,output);
							fread(&inbyte,1,1,input);
							if ( inbyte == 32 )
							{	
								fwrite(&inbyte,1,1,output);
							}else{
								printf("Found 1 Error, inbyte==2 should be inbyte == 2\n");
                                       				errors++;
								fwrite(&SPACE,1,1,output);
								fwrite(&inbyte,1,1,output);
							}
						}else{
							printf("Found 1 Error, inbyte=2 should be inbyte = 2\n");
                                       			errors++;
							fwrite(&SPACE,1,1,output);
							fwrite(&inbyte,1,1,output);
						}
					}
				}else{
					
					fwrite(&SPACE,1,1,output);
					fwrite(&inbyte,1,1,output);
					
					fread(&inbyte,1,1,input);
					if ( inbyte == 32 )
					{
						fwrite(&inbyte,1,1,output);
					}else{	
						if ( inbyte == '=' )
						{
							fwrite(&equal,1,1,output);
							fread(&inbyte,1,1,input);
							if ( inbyte == 32 )
							{	
								fwrite(&inbyte,1,1,output);
							}else{
								printf("Found 1 Error, inbyte==2 should be inbyte == 2\n");
                                       				errors++;
								fwrite(&SPACE,1,1,output);
								fwrite(&inbyte,1,1,output);
							}
						}else{
							printf("Found 1 Error, inbyte=2 should be inbyte = 2\n");
                                       			errors++;
							fwrite(&SPACE,1,1,output);
							fwrite(&inbyte,1,1,output);
						}
					}
				}
				}
			break;

			case '<':
				fread(&inbyte,1,1,input);	
				if ( inbyte == '<' )
				{
					fwrite(&inbyte,1,1,output);
					fwrite(&inbyte,1,1,output);
				}else{

				fseek(input,-3,SEEK_CUR);
				
				fread(&inbyte,1,1,input);

				if ( inbyte == 32 )
				{
					//fwrite(&inbyte,1,1,output);
					// write equal
					fread(&inbyte,1,1,input);
					fwrite(&inbyte,1,1,output);
					// check for equal after
					fread(&inbyte,1,1,input);
					// check for space after
					if ( inbyte == 32 )
					{
						fwrite(&inbyte,1,1,output);
					}else{	
						if ( inbyte == '=' )
						{
							fwrite(&equal,1,1,output);
							fread(&inbyte,1,1,input);
							if ( inbyte == 32 )
							{	
								fwrite(&inbyte,1,1,output);
							}else{
								printf("Found 1 Error, inbyte==2 should be inbyte == 2\n");
                                       				errors++;
								fwrite(&SPACE,1,1,output);
								fwrite(&inbyte,1,1,output);
							}
						}else{
							printf("Found 1 Error, inbyte=2 should be inbyte = 2\n");
                                       			errors++;
							fwrite(&SPACE,1,1,output);
							fwrite(&inbyte,1,1,output);
						}
					}
				}else{
					
					fwrite(&SPACE,1,1,output);
					fread(&inbyte,1,1,input);
					fwrite(&inbyte,1,1,output);
					
					fread(&inbyte,1,1,input);
					if ( inbyte == 32 )
					{
						fwrite(&inbyte,1,1,output);
					}else{	
						if ( inbyte == '=' )
						{
							fwrite(&equal,1,1,output);
							fread(&inbyte,1,1,input);
							if ( inbyte == 32 )
							{	
								fwrite(&inbyte,1,1,output);
							}else{
								printf("Found 1 Error, inbyte==2 should be inbyte == 2\n");
                                       				errors++;
								fwrite(&SPACE,1,1,output);
								fwrite(&inbyte,1,1,output);
							}
						}else{
							printf("Found 1 Error, inbyte=2 should be inbyte = 2\n");
                                       			errors++;
							fwrite(&SPACE,1,1,output);
							fwrite(&inbyte,1,1,output);
						}
					}
				}
				}
			break;

			case '!':
				fseek(input,-2,SEEK_CUR);
				
				fread(&inbyte,1,1,input);

				if ( inbyte == 32 )
				{
					//fwrite(&inbyte,1,1,output);
					// write equal
					fread(&inbyte,1,1,input);
					fwrite(&inbyte,1,1,output);
					// check for equal after
					fread(&inbyte,1,1,input);
					// check for space after
					if ( inbyte == 32 )
					{
						fwrite(&inbyte,1,1,output);
					}else{	
						if ( inbyte == '=' )
						{
							fwrite(&equal,1,1,output);
							fread(&inbyte,1,1,input);
							if ( inbyte == 32 )
							{	
								fwrite(&inbyte,1,1,output);
							}else{
								printf("Found 1 Error, inbyte==2 should be inbyte == 2\n");
                                       				errors++;
								fwrite(&SPACE,1,1,output);
								fwrite(&inbyte,1,1,output);
							}
						}else{
							printf("Found 1 Error, inbyte=2 should be inbyte = 2\n");
                                       			errors++;
							fwrite(&SPACE,1,1,output);
							fwrite(&inbyte,1,1,output);
						}
					}
				}else{
					
					fwrite(&SPACE,1,1,output);
					fread(&inbyte,1,1,input);
					fwrite(&inbyte,1,1,output);
					
					fread(&inbyte,1,1,input);
					if ( inbyte == 32 )
					{
						fwrite(&inbyte,1,1,output);
					}else{	
						if ( inbyte == '=' )
						{
							fwrite(&equal,1,1,output);
							fread(&inbyte,1,1,input);
							if ( inbyte == 32 )
							{	
								fwrite(&inbyte,1,1,output);
							}else{
								printf("Found 1 Error, inbyte==2 should be inbyte == 2\n");
                                       				errors++;
								fwrite(&SPACE,1,1,output);
								fwrite(&inbyte,1,1,output);
							}
						}else{
							printf("Found 1 Error, inbyte=2 should be inbyte = 2\n");
                                       			errors++;
							fwrite(&SPACE,1,1,output);
							fwrite(&inbyte,1,1,output);
						}
					}
				}
			break;

			case '=':
				fseek(input,-2,SEEK_CUR);
				
				fread(&inbyte,1,1,input);

				if ( inbyte == 32 )
				{
					//fwrite(&inbyte,1,1,output);
					// write equal
					fread(&inbyte,1,1,input);
					fwrite(&inbyte,1,1,output);
					// check for equal after
					fread(&inbyte,1,1,input);
					// check for space after
					if ( inbyte == 32 )
					{
						fwrite(&inbyte,1,1,output);
					}else{	
						if ( inbyte == '=' )
						{
							fwrite(&equal,1,1,output);
							fread(&inbyte,1,1,input);
							if ( inbyte == 32 )
							{	
								fwrite(&inbyte,1,1,output);
							}else{
								printf("Found 1 Error, inbyte==2 should be inbyte == 2\n");
                                       				errors++;
								fwrite(&SPACE,1,1,output);
								fwrite(&inbyte,1,1,output);
							}
						}else{
							printf("Found 1 Error, inbyte=2 should be inbyte = 2\n");
                                       			errors++;
							fwrite(&SPACE,1,1,output);
							fwrite(&inbyte,1,1,output);
						}
					}
				}else{
					
					fwrite(&SPACE,1,1,output);
					fread(&inbyte,1,1,input);
					fwrite(&inbyte,1,1,output);
					
					fread(&inbyte,1,1,input);
					if ( inbyte == 32 )
					{
						fwrite(&inbyte,1,1,output);
					}else{	
						if ( inbyte == '=' )
						{
							fwrite(&equal,1,1,output);
							fread(&inbyte,1,1,input);
							if ( inbyte == 32 )
							{	
								fwrite(&inbyte,1,1,output);
							}else{
								printf("Found 1 Error, inbyte==2 should be inbyte == 2\n");
                                       				errors++;
								fwrite(&SPACE,1,1,output);
								fwrite(&inbyte,1,1,output);
							}
						}else{
							printf("Found 1 Error, inbyte=2 should be inbyte = 2\n");
                                       			errors++;
							fwrite(&SPACE,1,1,output);
							fwrite(&inbyte,1,1,output);
						}
					}
				}
			break;

                        default:
                                // write byte normaly if open store if is a space
                                if ( open )
                                {
                                        if ( inbyte == 32 )
                                        {
                                                space = TRUE;
                                        }
                                }else{
                                        space = FALSE;
                                }

				if ( inbyte != 32 )
					space = FALSE;

                                fwrite(&inbyte,1,1,output);
                        break;
                }

		pos++;

        }

        printf("%d Errors Found and Corrected\n",errors);

        fclose(input);
        fclose(output);
        
        return 0;
}
