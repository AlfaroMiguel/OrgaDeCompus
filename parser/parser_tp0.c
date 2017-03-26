/*
v1.0

	-¿Se puede cambiar went_wrong por {-declarar i afuera del for
									  -if(i<argc) no se pudo parsear todo (hubo un break)	
									} ????

*/

#include "parser_tp0.h"

#define VERSION1 "-V"
#define VERSION2 "--version"
#define HELP1 "-h"
#define HELP2 "--help"
#define INPUT1 "-i"
#define INPUT2 "--input"
#define OUTPUT1 "-o"
#define OUTPUT2 "--output"
#define ACTION1	"-a"
#define ACTION2 "--action"

//util

//define+declarations
#define UNKNOWN_CMD "\"%s\" is not a known command.\n"
#define INVALID_OPT	"\"%s\" is not a valid %s.\n"
#define EXPECTED_OPT "Expected an argument after \"%s\".\n"




void set_default(run_data_t* rd){
	rd->error_flag= 0;
	rd->is_decode = 0;
	rd->print_help = 0;
	rd->print_version = 0;
	rd->input=stdin;
	rd->output=stdout;
}

char set_action(run_data_t* rd, char* arg){
	if(!strcmp(arg,"encode")){
		rd->is_decode = 0;
		return 0;
	}
	if(!strcmp(arg,"decode")){
		rd->is_decode = 1;
		return 0;
	}
	return 1;
}

char set_input(run_data_t* rd, char* arg){
	FILE* aux_in = fopen(arg,"rb");
	if (aux_in == NULL) return 1;
	rd->input=aux_in;
	return 0;
}

char set_output(run_data_t* rd, char* arg){
	FILE* aux_out = fopen(arg,"wb");
	if (aux_out == NULL) return 1;
	rd->output=aux_out;
	return 0;
}

//end:util



void parse_cmd(run_data_t* rd, int argc, char** argv){
	char went_wrong=0;	
	for(int i = 1; i<argc; i++){	//parsing loop
		if(!strcmp(argv[i],VERSION1) || !strcmp(argv[i],VERSION2)){ //version
			rd->print_version=1;
			continue;
		}
		if(!strcmp(argv[i],HELP1) || !strcmp(argv[i],HELP2)){ //help
			rd->print_help=1;
			continue;
		}
		if(!strcmp(argv[i],ACTION1) || !strcmp(argv[i],ACTION2)){ //action
			if((i+1)==argc){
					fprintf(stderr,EXPECTED_OPT,argv[i]);
					went_wrong=1;
					break;
			}
			if(set_action(rd,argv[i+1])){
					fprintf(stderr,INVALID_OPT,argv[i+1],"action");
					went_wrong=1;
					break;
			}
			i++;
			continue;
		}
		if(!strcmp(argv[i],INPUT1) || !strcmp(argv[i],INPUT2)){ //input
			if((i+1)==argc){
					fprintf(stderr,EXPECTED_OPT,argv[i]);
					went_wrong=1;
					break;
			}
			if(set_input(rd,argv[i+1])){
					fprintf(stderr,INVALID_OPT,argv[i+1],"input");
					went_wrong=1;
					break;
			}
			i++;
			continue;
		}
		if(!strcmp(argv[i],OUTPUT1) || !strcmp(argv[i],OUTPUT2)){ //output
			if((i+1)==argc){
					fprintf(stderr,EXPECTED_OPT,argv[i]);
					went_wrong=1;
					break;
			}
			if(set_output(rd,argv[i+1])){
					fprintf(stderr,INVALID_OPT,argv[i+1],"output");
					went_wrong=1;
					break;
			}
			i++;
			continue;
		}
		//not recognized
		fprintf(stderr,UNKNOWN_CMD,argv[i]);
		went_wrong=1;
		break;
	}
	if(went_wrong){
		set_default(rd);
		rd->error_flag=1;		
		rd->print_help=1;
	}
}
