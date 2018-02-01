#include "defines.h"

MAIN;
	ARGCHECK(1);

	int d;

	printf("switch ( %s )\n{\n",argv[1]);

	for( d=2; d < argc; d++ )
	{
printf("\tcase %d:\n\t\n\tbreak;\n\n",atoi(argv[d]));
	}

printf("}\n");

	RET;
END;