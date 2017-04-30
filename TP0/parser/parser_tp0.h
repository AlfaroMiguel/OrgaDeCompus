#include <stdio.h>
#include <string.h>
struct run_data {
	char is_decode;
	char print_help;
	char print_version;
	char error_flag;	
	char* input;
	char* output;
};

typedef struct run_data run_data_t;

//Set default values on given run_data_t ref
void set_default(run_data_t* rd);

//Try to set action according to arg, if succesful returns 0.
char set_action(run_data_t* rd, char* arg);

//Parse options given from cmd line
//Should an error occur, prints it to stderr and sets print_help with stdout as output
void parse_cmd(run_data_t* rd, int argc, char* argv[]);
