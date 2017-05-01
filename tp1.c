#define _POSIX_C_SOURCE 1

#include "parser/parser_tp0.h"
#include "base64/base64.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
#define INPUT_OPENING_ERROR_MSG "ERROR OPENING INPUT FILE \n"
#define OUTPUT_OPENING_ERROR_MSG "ERROR OPENING OUTPUT FILE \n"

#define STD_FILE_SYMBOL "-"

#define NO_ERROR_CODE 0
#define DECODING_ERROR_CODE 1
#define FILE_WRITING_ERROR_CODE 2
#define FILE_READING_ERROR_CODE 3

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

int encode(int input_file, int output_file){
	unsigned char source_code[SOURCE_CODE_SIZE_ENCODE];
	unsigned char result[RESULT_SIZE_ENCODE];
	int i, char_to_encode, bytes_written;
	char buffer[1];
	int bytes_read = read(input_file, buffer, 1);
	while (buffer[0] != EOF){
		i = 0;
        char_to_encode = 0;
		while (i < 3){
			source_code[i] = buffer[0];
			i++;
            char_to_encode++;
			bytes_read = read(input_file, buffer, 1);
            if(buffer[0] == EOF) break;
		}
		while (i < 3){
			source_code[i] = '\0';
			i++;
		}
		base64_encode(source_code, result, char_to_encode);
		bytes_written = write(output_file, result, 4);
		if (bytes_written == 0) return FILE_WRITING_ERROR_CODE;
	}

	if(bytes_read == -1) return FILE_READING_ERROR_CODE; 
	return NO_ERROR_CODE;
}

int decode(int input_file, int output_file){
	unsigned char source_code[SOURCE_CODE_SIZE_DECODE];
	unsigned char result[RESULT_SIZE_DECODE];
	int i, bytes_write, bytes_written;
	char buffer[1];
	int bytes_read = read(input_file, buffer, 1);
	while ((int)buffer[0] != EOF){
		i = 0;
		while (i < 4){
			source_code[i] = (int)buffer[0];
			i++;
			bytes_read = read(input_file, buffer, 1);
            if((int)buffer[0] == EOF) break;
		}
		while (i < 4){
			source_code[i] = '=';
			i++;
		}
		bool success = base64_decode(source_code, result, &bytes_write);
		if (!success) return DECODING_ERROR_CODE;
        bytes_written = write(output_file, result, bytes_write);
        if (bytes_written == 0) return FILE_WRITING_ERROR_CODE;
	}

	if(bytes_read == -1) return FILE_READING_ERROR_CODE;
	return NO_ERROR_CODE;
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
	FILE* input_file = get_input_file(rd->input);
	if (! input_file) {
		fprintf(stderr, INPUT_OPENING_ERROR_MSG);
		return 0;
	}
	FILE* output_file = get_output_file(rd->output);
	if (! output_file) {
		fprintf(stderr, OUTPUT_OPENING_ERROR_MSG);
		close_files(input_file, output_file);
		return 0;
	}
	int res;
	if (rd->is_decode) res = decode(fileno(input_file), fileno(output_file));
	else if(!rd->error_flag) res = encode(fileno(input_file), fileno(output_file));
	else fprintf(stderr, ARGUMENT_ERROR_MSG);
	if (res != 0) fprintf(stderr, "%s", errmsg[res-1]);
	close_files(input_file, output_file);
	free(rd);
	return 0;
}
