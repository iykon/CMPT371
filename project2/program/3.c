/*
 * author: Weida Pan
 * student number: 301295773
 * project: 2
 * course: CMPT 371
 * */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char node[27];
int n;
int dist[27][27];
int sdist[27];

/*
 * function: LS
 * description: use Dijsktra’s algorithm to calculate shortest path from start node to other nodes
 * argument: int start: start node
 * return value: none
 * */
void LS(int start){
	int i, j, mind, minn;
	int set[27];

	for(i = 0; i < n; ++i)
		set[i] = 0;
	// put start node into set
	set[start] = 1;
	for(i = 0; i < n; ++i)
		sdist[i] = dist[start][i];
	for(i = 1; i < n; ++i){
		mind = -1;
		// get a node that is not in S and has the minimum distance to start node
		for(j = 0; j < n; ++j){
			if(set[j] == 0 && sdist[j] != -1){
				if(mind == -1 || sdist[j] < mind){
					mind = sdist[j];
					minn = j;
				}
			}
		}
		//update current shortest path to other nodes
		if(mind >0){
			set[minn] = 1;
			for(j = 0; j < n; ++j)
				if(set[j] == 0 && (sdist[j] == -1 || (sdist[j] > sdist[minn] + dist[minn][j] && dist[minn][j] > 0)) )
					sdist[j] = sdist[minn] + dist[minn][j];
		}
		else
			break;
	}
	return;
}

int main(int argc, char **argv){
	char fn[10];
	FILE *fp;
	int i,j,k;

	printf("please type the input file name: ");
	scanf("%s", fn);
	if(access(fn, F_OK) == -1 ){
		printf("File %s not found.\n", fn);
		return 1;
	}
	fp = fopen(fn, "r+");
	fscanf(fp, "%d", &n);
	//printf("%d\n",n);
	for(i = 0; i < n; ++i){
		fscanf(fp, "%d", &j);
		fscanf(fp, "%c", node+i);
		//printf("i:%c\n", node[i]);
	}
	//for(i = 0; i < n; ++i)
	//	printf("%c ", node[i]);
	//printf("\n");
	for(i = 0; i < n; ++i)
		for(j = 0; j < n; ++j)
			fscanf(fp, "%d", dist[i]+j);
	/*for(i = 0; i < n; ++i){
		for(j = 0; j < n; ++j)
			printf("%d ", dist[i][j]);
		printf("\n");
	}
	*/
	LS(0);
	for(i = 1; i < n; ++i)
		printf("%c %d\n", node[i], sdist[i]);
	return 0;
}
