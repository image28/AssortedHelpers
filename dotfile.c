#include "defines.h"

MAIN;
	//ARGCHECK(3);
	
	int d,e,n;

	long dots_wide=strtol(argv[1],NULL,10);
	long dots_down=strtol(argv[2],NULL,10);
	long grids=strtol(argv[3],NULL,10);

	for(d=0; d<grids; d++)
	{

		for(e=0; e < dots_down; e++)
		{

			for(n=0; n < dots_wide; n++)
			{
				printf(".");
			}printf("\n");
		}printf("\n");
	}

	RET;
END;
	