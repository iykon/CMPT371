/*
CMPT371 project1
name: Weida Pan
student number: 301295773
problem: DHT
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

/*
because all hosts are a circle, handle the situation where index is smaller than 0 or larger than total number of hosts
 */
int loop(int S,int n){
	if(n>=S)
		n-=S;
	else if(n<0)
		n+=S;
	return n;
}

/*
 * build the finger table of a node
 */
void buildfingertable(int S,int size, int suc[], int node){
	int i, interval;
	//build hash table
	interval = S;
	for(i=0;i<size;++i){
		interval/=2;
		hashnode[node].fingertable[i] = suc[loop(S,node+interval)];
	}
		
}

/*
 * join a node to the existing circle of nodes
 */
void nodejoin(int node,int S,int size,int suc[]){
	int i,rnode,interval;
	rnode = node;

	//update successor
	for(i=0;i<S;++i){
		if(suc[rnode]==rnode)
			break;
		suc[rnode] = node;
		rnode = loop(S,rnode-1);
	}
	
	return;
}

/*
because of the circle, when the beginning node is n, use this function to change those value smaller than n ,written as m, to m+S to make sure the algorithm will not search more than one circle
 */
int relativevalue(int S, int begin, int node){
	if(node<begin)
		return node+S;
	else 
		return node;
}

/*
 * use recursive function to query the exact file 
 */
int query(int beginner,int node,int key,int S,int suc[]){
	//printf("in query: %d %d %d\n",beginner,node,key);
	int i,interval;
	for(i=0;i<hashnode[node].files;++i)
		if(hashnode[node].filetable[i]==key)
			return 0;
	if(relativevalue(S,beginner,node) >= relativevalue(S,beginner,key))
		return 0;
	interval = S/2;
	while(relativevalue(S,beginner,node+interval)>relativevalue(S,beginner,key))
		interval/=2;
	return 1+query(beginner,suc[loop(S,node+interval)],key,S,suc);
}

int main(int argc, char **argv){
	//declare
	FILE *fpin,*fpout;
	int i,j;
	char comma;
	int S,N,M,node,key,tablesize;//tablesize = log2(S) which is the number of fingers
	int successor[MAXNODE],joined[MAXNODE];//successor stores the successor of a node

	//parameters error handling
	if(argc != 3){
		printf("usage: chord source_file target_file\n");
		return 0;
	}
	
	//read data from file
	fpin = fopen("chord.in","r");
	fpout = fopen("chord.out","w");
	fscanf(fpin,"%d %d %d",&S,&N,&M);
	++S;
	tablesize = (int)(log(S)/log(2));//this is equal to log2(S)

	//initialization
	for(i=0;i<S;++i){
		successor[i] = -1;
	}
	for(i=0;i<N;++i){
		fscanf(fpin,"%d%c",joined+i,&comma);
		nodejoin(joined[i],S,tablesize,successor);
	}
	for(j=0;j<N;++j){
		buildfingertable(S,tablesize,successor,joined[j]);
	}

	//read keys
	for(j=0;j<M;++j){
		fscanf(fpin,"%d%c",&key,&comma);
		hashnode[successor[key]].filetable[hashnode[successor[key]].files++] = key;
	}

	//read queries
	while(1){
		fscanf(fpin,"%d%c%d",&key,&comma,&node);
		if(node==-1)
			break;
		fprintf(fpout,"%d\n",query(node,node,key,S,successor));
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}
