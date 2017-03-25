#include <stdio.h>
#include <string.h>
#include "parser_tp0.h"

void set_expected(run_data_t* rd, char is_d, char prt_h, char prt_v, char err_flag, FILE* in, FILE* out){
	rd->error_flag= err_flag;
	rd->is_decode = is_d;
	rd->print_help = prt_h;
	rd->print_version = prt_v;
	rd->input=in;
	rd->output=out;
}

enum CMP_DIFF {NO_ERROR,ACTION,HELP,VERSION,ERR_FLAG,INPUT,OUTPUT};

//Returns first difference found between rd1 and rd2, 0 (==NO_ERROR) if none.  
enum CMP_DIFF rd_cmp(run_data_t* rd1,run_data_t* rd2){
	if (rd1->error_flag != rd2->error_flag) return ERR_FLAG;
	if (rd1->is_decode != rd2->is_decode) return ACTION;
	if (rd1->print_help != rd2->print_help) return HELP;
	if (rd1->print_version != rd2->print_version) return VERSION;
	if (rd1->input != rd2->input) return INPUT;		//puede ser que no anden estos 2 ultimos?
	if (rd1->output != rd2->output) return OUTPUT;	//para probar este solo voy a usar stdout
	return NO_ERROR;
} 

void test_rd(run_data_t* rd1,run_data_t* rd2,char* msg){
	switch(rd_cmp(rd1,rd2)){
		case (int)NO_ERROR:
			strcpy(msg,"no error");break;
		case (int)ACTION:
			strcpy(msg,"failed at action");break;
		case (int)HELP:
			strcpy(msg,"failed at help");break;
		case (int)VERSION:
			strcpy(msg,"failed at version");break;
		case (int)ERR_FLAG:
			strcpy(msg,"failed at error_flag");break;
		case (int)INPUT:
			strcpy(msg,"failed at input");break;
		case (int)OUTPUT:
			strcpy(msg,"failed at output");break;
		default:
			strcpy(msg,"UNEXPECTED");break;
	}
}
/* DEPRECATED
int main(){
	run_data_t rd1,rd2;
	char msg[20]="";
	printf("TESTING:\n");

	//fail on dummies 1
	set_expected(&rd1,0,0,0,0,stdin,stdout);
	set_expected(&rd2,0,0,1,0,stdin,stdout);

	printf("\nComparing dummy rd1 and rd2 (1)\n");
	printf("Expected: failed at version\n");
	test_rd(&rd1,&rd2,msg);
	printf("Gives: %s\n",msg);
	strcpy(msg,"");

	//fail on dummies 2
	set_expected(&rd1,1,1,0,0,stdin,stdout);
	set_expected(&rd2,0,0,0,0,stdin,stdout);

	printf("\nComparing dummy rd1 and rd2 (2)\n");
	printf("Expected: failed at action\n");
	test_rd(&rd1,&rd2,msg);
	printf("Gives: %s\n",msg);
	strcpy(msg,"");
	
	//no fail on dummies
	set_expected(&rd1,0,0,0,0,stdin,stdout);
	set_expected(&rd2,0,0,0,0,stdin,stdout);

	printf("\nComparing dummy rd1 and rd2 (3)\n");
	printf("Expected: no error\n");
	test_rd(&rd1,&rd2,msg);
	printf("Gives: %s\n",msg);
	strcpy(msg,"");

	//parse cmd 1
	set_expected(&rd1,0,0,0,0,stdin,stdout);
	char aux[5][20]={"tp0"};
	char** rgv = aux;	
	int rgc = 1;
	parse_cmd(&rd2,rgc,rgv);
	
	printf("\nComparing dummy rd1 and parsed rd2 (1)\n");
	printf("Expected: no error\n");
	test_rd(&rd1,&rd2,msg);
	printf("Gives: %s\n",msg);
	strcpy(msg,"");

	//parse cmd 2
	set_expected(&rd1,1,0,1,0,stdin,stdout);
	char aux2[5][20]={"tp0","-a","decode","-V"};
	rgv = aux2;	
	rgc = 4;
	parse_cmd(&rd2,rgc,rgv);
		printf("TODO BIEN0\n");//DEBUG
	printf("\nComparing dummy rd1 and parsed rd2 (2)\n");
	printf("Expected: no error\n");
	test_rd(&rd1,&rd2,msg);
	printf("TODO BIEN1\n");//DEBUG
	printf("Gives: %s\n",msg);
	printf("TODO BIEN2\n");//DEBUG
	strcpy(msg,"");



	return 0;

}*/
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


