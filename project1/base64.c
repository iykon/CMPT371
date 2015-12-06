/*
CMPT371 project1
name: Weida Pan
student number: 301295773
problem: base 64 decoding
programming language: C
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//base 64 decoding table
int b64dt[128]={  0,0,0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,0,0,
				  0,0,0,0,0,0,0,0,0,0,
				  0,0,0,62,0,0,0,63,52,53,
				  54,55,56,57,58,59,60,61,0,0,
				  0,0,0,0,0,0,1,2,3,4,
				  5,6,7,8,9,10,11,12,13,14,
				  15,16,17,18,19,20,21,22,23,24,
				  25,0,0,0,0,0,0,26,27,28,
				  29,30,31,32,33,34,35,36,37,38,
				  39,40,41,42,43,44,45,46,47,48,
				  49,50,51,0,0,0,0,0};

int main(int argc, char **argv){
	//declare
	FILE *fpin,*fpout;
	int decode[3];// a group of 3 output decoded characters
	char encode[4];//a group of 4 input characters
	
	//parameters error handling
	if(argc != 3){
		printf("usage: base64decode source_file target_file\n");
		return 0;
	}

	fpin = fopen(argv[1],"r");
	fpout = fopen(argv[2],"w");

	while((encode[0]=fgetc(fpin))!=EOF){
		//read a group of input data
		encode[1]=fgetc(fpin);
		encode[2]=fgetc(fpin);
		encode[3]=fgetc(fpin);
		//using bit operations to decode and produce 3 characters
		decode[0]=(b64dt[encode[0]]<<2)+(b64dt[encode[1]]>>4);
		decode[1]=((b64dt[encode[1]]&15)<<4)+(b64dt[encode[2]]>>2);
		decode[2]=((b64dt[encode[2]]&3)<<6)+(b64dt[encode[3]]);
		fprintf(fpout,"%c",decode[0]);
		//special case where there is one '=' or two '='
		if(encode[2]=='='){}
		else if(encode[3]=='=')
			fprintf(fpout,"%c",decode[1]);
		else{
			fprintf(fpout,"%c",decode[1]);
			fprintf(fpout,"%c",decode[2]);
		}
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}

