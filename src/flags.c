#include <stdio.h>
#include "../include/flags.h"

void flag_help(const char * const nome_do_programa)
{
	fprintf(stderr,
		"Usage: %s [OPTION]... [FILE]...\n\n"
		"  -f <FILE>     path to data file\n"
		"  -v            output version information and exit\n"
		"  -h            display this help and exit\n",
		nome_do_programa
	);
}

void flag_version(const char * const nome_do_programa)
{
	fprintf(stderr,
		"%s (c) 2026 %s, Inc.\n"
		"Compiled on %s at %s\n",
		nome_do_programa,
		nome_do_programa,
 		__DATE__,
		__TIME__
	);
}
