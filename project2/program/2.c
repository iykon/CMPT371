/*
 * author: Weida Pan
 * student number: 301295773
 * project: 2
 * course: CMPT 371
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int usr,len,bit;
int code[9][17];
int data[9][9];

/*
 * function: isvalid
 * description: check all codes to see if they are orthogonal to each other
 * return value: for valid code, 1 is returned, for invalid code, 0 is returned
 * */
int isvalid(){
	int i,j,k;
	int sum;
	for(i = 1; i < usr; ++i){
		for(j = 0; j < i; ++j){
			sum = 0;
			for(k = 0; k < len; ++k)
				sum += code[i][k]*code[j][k];
			if(sum != 0)
				return 0;
		}
	}
	return 1;
}

int main(int argc, char **argv){
	int i, j, k, encode;
	char fn[10];
	FILE *fp;

	printf("please input the input file name.\n");
	scanf("%s",fn);
	if(access(fn,F_OK) == -1){
		printf("File %s not found.\n",fn);
		return 1;
	}
	fp = fopen(fn, "r+");
	fscanf(fp, "%d", &usr);
	fscanf(fp, "%d", &len);
	fscanf(fp, "%d", &bit);
	for(i = 0; i < usr; ++i)
		for(j = 0; j < len; ++j)
			fscanf(fp, "%d", code[i]+j);
	for(i = 0; i < usr; ++i)
		for(j = 0; j < bit; ++j)
			fscanf(fp, "%d", data[i]+j);
	if(isvalid()){
		printf("Yes\n");
		for(i = 0; i < bit; ++i){
			for(j = 0; j < len; ++j){
				encode = 0;
				for(k = 0; k < usr; ++k)
					encode += code[k][j]*data[k][i];
				printf("%d ",encode);
			}
			printf("\n");
		}
	}
	else{
		printf("no\n");
		return 0;
	}
	
	return 0;
}
