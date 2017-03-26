#include "parser/parser_tp0.h"
#include <stdlib.h>

#define HELP_FILE "help.txt"
#define VERSION "2.1.3"

void print_help(){
	FILE* help_file = fopen(HELP_FILE, "r");
	char c = fgetc(help_file);
	while (c != EOF){
		printf("%c", c);
		c = fgetc(help_file);
	}
	printf("\n");
	fclose(help_file);
}

void print_version(){
	printf("Version %s\n", VERSION);
}

void encode(char* input, char* output){
	// bool stdin = false;
	// bool stdout = false;
	// if (!input)
	// 	stdin = true;
	// if (!output)
	// 	stdout = true;
	// if (!stdin)
	// 	FILE* input_file = fopen(input, "rb");
}
int main(int argc, char* argv[]){
	run_data_t* rd = malloc(sizeof(run_data_t));
	parse_cmd(rd, argc, argv);
	if (rd->print_help)
		print_help();
	if (rd->print_version)
		print_version();
	if (rd->is_decode){
		//hacer decode
	}
	else if(!rd->error_flag){
		//encode(rd->input, rd->output);
	}
	free(rd);
	return 0;
}