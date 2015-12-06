/*
CMPT371 project1
name: Weida Pan
student number: 301295773
programming language: C
 */
#include <stdio.h>
#include <math.h>
#define MAXNODE 10000
#define MAXTABLE 20

//a struct defines the content of each node
struct DHT{
	int fingertable[MAXTABLE];// finger table
	int filetable[MAXNODE];// file table
	int files;// the number of files locally
}hashnode[MAXNODE];

int S,tablesize;

/*
because all hosts are a circle, handle the situation where index is smaller than 0 or larger than total number of hosts
 */
int loop(int n){
	if(n>=S)
		n-=S;
	else if(n<0)
		n+=S;
	return n;
}

void buildhashtable(int node){
	int i, interval;
	//build hash table
	interval = S;
	for(i=0;i<tablesize;++i){
		interval/=2;
		hashnode[node].fingertable[i] = loop(node+interval);
	}
		
}

void nodejoin(int node,int suc[]){
	int i,rnode,interval;
	rnode = node;

	//update successor
	for(i=0;i<S;++i){
		if(suc[rnode]==rnode)
			break;
		suc[rnode] = node;
		rnode = loop(rnode-1);
	}
	
	return;
}

/*
because of the circle, when the beginning node is n, use this function to change those value smaller than n ,written as m, to m+S to make sure the algorithm will not search more than one circle
 */
int relativevalue(int begin, int node){
	if(node<begin)
		return node+S;
	else 
		return node;
}

/*
 * use recursive function to query the exact file 
 */
int query(int beginner,int node,int key,int suc[]){
	printf("in query: %d %d %d\n",beginner,node,key);
	int i,interval;
	for(i=0;i<hashnode[node].files;++i)
		if(hashnode[node].filetable[i]==key)
			return 0;
	if(relativevalue(beginner,node) >= relativevalue(beginner,key))
		return 0;
	/*interval = S/2;
	while(relativevalue(S,beginner,node+interval)>relativevalue(S,beginner,key))
		interval/=2;
	return 1+query(beginner,suc[loop(S,node+interval)],key,S,suc);
		*/
	i=0;
	while(relativevalue(beginner,hashnode[node].fingertable[i])>relativevalue(beginner,key))
		++i;
	return 1+query(beginner,suc[loop(hashnode[node].fingertable[i])],key,suc);
}

int main(){
	//definition
	FILE *fpin,*fpout;
	int i,j;
	char comma;
	int N,M,node,key;
	int successor[MAXNODE],joined[MAXNODE];

	//read data from file
	fpin = fopen("chord.in","r");
	fpout = fopen("chord.out","w");
	fscanf(fpin,"%d %d %d",&S,&N,&M);
	++S;
	tablesize = (int)(log(S)/log(2));
	//printf("tablesize: %d\n",tablesize);

	//initialization
	for(i=0;i<S;++i){
		successor[i] = -1;
	}
	for(i=0;i<N;++i){
		fscanf(fpin,"%d%c",joined+i,&comma);
		//printf("nodes: ");
		//printf("%d ",joined[i]);
		nodejoin(joined[i],successor);
	}
	for(j=0;j<N;++j){
		buildhashtable(joined[j]);
	}

	//printf("\n");

	/*for(i=0;i<N;++i){
		printf("%d ",successor[i]);
	}*/
	//printf("\n");
	/*for(i=0;i<N;++i){
		printf("%d:",joined[i]);
		for(j=0;j<tablesize;++j)
			printf("%d ",hashnode[joined[i]].fingertable[j]);
		//printf("\n");
	}*/

	//read keys
	//printf("keys:\n");
	for(j=0;j<M;++j){
		fscanf(fpin,"%d%c",&key,&comma);
		hashnode[successor[key]].filetable[hashnode[successor[key]].files++] = key;
		//printf("%d ",key);
	}
	//printf("end of keys\n");

	//read queries
	while(1){
		fscanf(fpin,"%d%c%d",&key,&comma,&node);
		//printf("%d %d\n",node,key);
		if(node==-1)
			break;
		fprintf(fpout,"%d\n",query(node,node,key,successor));
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}

