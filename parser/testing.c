#include <stdio.h>
#include <string.h>
#include "parser_tp0.h"

int main(int argc, char** argv){
	run_data_t rd;
	set_default(&rd);

	parse_cmd(&rd,argc,argv);

	printf("\nState of parsed cmd:\n");
	printf("Error flag is: %d\n",rd.error_flag);
	printf("Is_decode is: %d\n",rd.is_decode);
	printf("Print_help is: %d\n",rd.print_help);
	printf("Print version is: %d\n",rd.print_version);
	printf("Input file* is: %p\n",rd.input);
	printf("Output file* is: %p\n",rd.output);
}


