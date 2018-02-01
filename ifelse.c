#include "defines.h"

MAIN;
	ARGCHECK(1);

	int d;

	printf("if ( %s )\n{\n",argv[1]);

	for( d=2; d < argc; d++ )
	{
printf("}\nelse if ( %s )\n{\t\n",argv[d]);
	}

printf("}\n");

	RET;
END;