#include "parser/parser_tp0.h"
#include "base64/base64.h"
#include <stdlib.h>
#include <stdio.h>

#define HELP_FILE "help.txt"
#define VERSION "2.1.3"
#define STDIN_FD 0
#define STDOUT_FD 1


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

FILE* get_input_file(char* input){
	if (!input || !strcmp(input, "-"))
		return stdin;
	return fopen(input, "r");
}

FILE* get_output_file(char* output){
	if (!output || !strcmp(output, "-"))
		return stdout;
	return fopen(output, "w");
}

void encode(char* input, char* output){
	FILE* input_file = get_input_file(input);
	FILE* output_file = get_output_file(output);
	char* source_code = malloc(sizeof(char)*4);
	char* result = malloc(sizeof(char)*5);
	int i;
	char c;
	while (true){
		i = 0;
		while (i < 3){
			c = fgetc(input_file);
			source_code[i] = c;
			i++;
		}
	
		while (i < 3){
			source_code[i] = '\0';
			i++;
		}
		printf("%s\n", source_code);
		base64_encode(source_code, result);
		fwrite(result, 1, 4, output_file);
		if (c == EOF) break;
	}
}

void decode(char* input, char* output){
	FILE* input_file = get_input_file(input);
	FILE* output_file = get_output_file(output);
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
		encode(rd->input, rd->output);
	}
	free(rd);
	return 0;
}