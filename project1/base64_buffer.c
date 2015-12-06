#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLENGTH 500000

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
	char *buf;
	int i,length;
	
	//parameters error handling
	if(argc != 3){
		printf("usage: base64decode source_file target_file\n");
		return 0;
	}
	
	//read data
	fpin = fopen(argv[1],"r");
	fpout = fopen(argv[2],"w");
	buf = (char *)malloc(MAXLENGTH*sizeof(char));
	fscanf(fpin,"%s",buf);
	length = strlen(buf);
	printf("%d\n",length);
	i = 0;
	while(i<length-4){
		printf("%d %d %d %d\n",b64dt[buf[i]],b64dt[buf[i+1]],b64dt[buf[i+2]],b64dt[buf[i+3]]);
		printf("%d\n",(b64dt[buf[i+1]]&15)<<4);
		printf("%d ",(b64dt[buf[i]]<<2)+(b64dt[buf[i+1]]>>4));
		printf("%d ",((b64dt[buf[i+1]]&15)<<4)+(b64dt[buf[i+2]]>>2));
		printf("%d ",((b64dt[buf[i+2]]&3)<<6)+(b64dt[buf[i+3]]));
		printf("\n%c",0);
		fprintf(fpout,"%c",(b64dt[buf[i]]<<2)+(b64dt[buf[i+1]]>>4));
		fprintf(fpout,"%c",((b64dt[buf[i+1]]&15)<<4)+(b64dt[buf[i+2]]>>2));
		fprintf(fpout,"%c",((b64dt[buf[i+2]]&3)<<6)+(b64dt[buf[i+3]]));
		i+=4;
	}
	fprintf(fpout,"%c",(b64dt[buf[i]]<<2)+(b64dt[buf[i+1]]>>4));
	if(buf[i+2]=='='){}
	else if(buf[i+3]=='=')
		fprintf(fpout,"%c",(b64dt[buf[i]]<<2)+(b64dt[buf[i+1]]>>4));
	else
		fprintf(fpout,"%c",((b64dt[buf[i+2]]&3)<<6)+(b64dt[buf[i+3]]));

	free(buf);
	fclose(fpin);
	fclose(fpout);
	return 0;
}
