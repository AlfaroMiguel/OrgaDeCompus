#include "parser/parser_tp0.h"
#include "base64/base64.h"
#include <stdlib.h>
#include <stdio.h>

#define HELP_FILE "help.txt"
#define VERSION "2.1.3"
#define STDIN_FD 0
#define STDOUT_FD 1

#define SOURCE_CODE_SIZE_ENCODE 3
#define RESULT_SIZE_ENCODE 4

#define SOURCE_CODE_SIZE_DECODE 4
#define RESULT_SIZE_DECODE 3

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
	return fopen(input, "rb");
}

FILE* get_output_file(char* output){
	if (!output || !strcmp(output, "-"))
		return stdout;
	return fopen(output, "wb");
}

void close_files(FILE* input, FILE* output){
	if (input != stdin)
		fclose(input);
	if (output != stdout)
		fclose(output);
}

void encode(char* input, char* output){
	FILE* input_file = get_input_file(input);
	FILE* output_file = get_output_file(output);
	unsigned char source_code[SOURCE_CODE_SIZE_ENCODE];
	unsigned char result[RESULT_SIZE_ENCODE];
	int i, char_to_encode;
	int c = fgetc(input_file);
	while (c != EOF){
		i = 0;
        char_to_encode = 0;
		while (i < 3){
			source_code[i] = c;
			i++;
            char_to_encode++;
			c = fgetc(input_file);
            if(c == EOF) break;
		}
		while (i < 3){
			source_code[i] = '\0';
			i++;
		}
		base64_encode(source_code, result, char_to_encode);
		fwrite(result, 1, 4, output_file);
	}

	if(ferror(input_file))
		fprintf(stderr, "ERROR READING FILE %s", input);


	close_files(input_file, output_file);
}

void decode(char* input, char* output){
	FILE* input_file = get_input_file(input);
	FILE* output_file = get_output_file(output);
	unsigned char source_code[SOURCE_CODE_SIZE_DECODE];
	unsigned char result[RESULT_SIZE_DECODE];
	int i, write;
	int c = fgetc(input_file);
	while (c != EOF){
		i = 0;
		while (i < 4){
			source_code[i] = c;
			i++;
			c = fgetc(input_file);
            if(c == EOF) break;
		}
		while (i < 4){
			source_code[i] = '=';
			i++;
		}
		bool success = base64_decode(source_code, result, &write);
		if (!success){
			fprintf(stderr, "Decoding Error\n");
			return;
		}
        fwrite(result, 1, write, output_file);
	}

	if(ferror(input_file))
		fprintf(stderr, "ERROR READING FILE %s", input);


	close_files(input_file, output_file);
}

int main(int argc, char* argv[]){
	run_data_t* rd = malloc(sizeof(run_data_t));
	parse_cmd(rd, argc, argv);
	if (rd->print_help)
		print_help();
	if (rd->print_version){
		print_version();
		return 0;
		}
	if (rd->is_decode){
		decode(rd->input, rd->output);
	}
	else if(!rd->error_flag){
		encode(rd->input, rd->output);
	}
	else fprintf(stderr, "Argument Error\n");
	free(rd);
	return 0;
}
