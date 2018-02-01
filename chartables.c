#include "defines.h"

MAIN;
	if ( argc < 4 )
		printf("Incorrect number of arguments\n Usage : %s [number of tables] [table height] [table width] [fill with char]\n");
	
	int x,y,tabs;

	for(tabs=0; tabs < atoi(argv[1]); tabs++)
	{
		for(y=0; y < atoi(argv[2]); y++)
		{
			for(x=0; x < atoi(argv[3]); x++)
			{
				if (( y == 0 ) || ( x == 0 ) || ( y == atoi(argv[2])-1) || ( x == atoi(argv[3])-1 )) 	
					printf("1");
				else
					printf("%s",argv[4]);
			}EL;
		}EL;EL;
	}

	RET;

END;