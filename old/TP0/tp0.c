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

#define VERSION_MSG "Version %s\n"
#define ARGUMENT_ERROR_MSG "ARGUMENT ERROR\n"
#define DECODING_ERROR_MSG "DECODING ERROR\n"
#define INPUT_OPENING_ERROR_MSG "ERROR OPENING INPUT FILE \n"
#define OUTPUT_OPENING_ERROR_MSG "ERROR OPENING OUTPUT FILE \n"
#define FILE_WRITING_ERROR_MSG "ERROR WRITING IN FILE\n"
#define FILE_READING_ERROR_MSG "ERROR READING FROM FILE\n"

#define STD_FILE_SYMBOL "-"

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
	printf(VERSION_MSG, VERSION);
}

FILE* get_input_file(char* input){
	if (!input || !strcmp(input, STD_FILE_SYMBOL))
		return stdin;
	return fopen(input, "rb");
}

FILE* get_output_file(char* output){
	if (!output || !strcmp(output, STD_FILE_SYMBOL))
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
	if (! input_file) {
		fprintf(stderr, INPUT_OPENING_ERROR_MSG);
		return;
	}
	FILE* output_file = get_output_file(output);
	if (! output_file) {
		fprintf(stderr, OUTPUT_OPENING_ERROR_MSG);
		close_files(input_file, output_file);
		return;
	}
	unsigned char source_code[SOURCE_CODE_SIZE_ENCODE];
	unsigned char result[RESULT_SIZE_ENCODE];
	int i, char_to_encode, bytes_written;
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
		bytes_written = fwrite(result, 1, 4, output_file);
		if (bytes_written == 0){
			fprintf(stderr, FILE_WRITING_ERROR_MSG);
			break;
		}
	}

	if(ferror(input_file))
		fprintf(stderr, FILE_READING_ERROR_MSG);
	close_files(input_file, output_file);
}

void decode(char* input, char* output){
	FILE* input_file = get_input_file(input);
	if (! input_file) {
		fprintf(stderr, INPUT_OPENING_ERROR_MSG);
		return;
	}
	FILE* output_file = get_output_file(output);
	if (! output_file) {
		fprintf(stderr, OUTPUT_OPENING_ERROR_MSG);
		close_files(input_file, output_file);
		return;
	}
	unsigned char source_code[SOURCE_CODE_SIZE_DECODE];
	unsigned char result[RESULT_SIZE_DECODE];
	int i, write, bytes_written;
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
			fprintf(stderr, DECODING_ERROR_MSG);
			break;
		}
        bytes_written = fwrite(result, 1, write, output_file);
        if (bytes_written == 0){
			fprintf(stderr, FILE_WRITING_ERROR_MSG);
			break;
		}
	}

	if(ferror(input_file))
		fprintf(stderr, FILE_READING_ERROR_MSG);
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
	else fprintf(stderr, ARGUMENT_ERROR_MSG);
	free(rd);
	return 0;
}
