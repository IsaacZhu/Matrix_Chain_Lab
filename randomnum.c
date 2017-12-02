#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int i;
	FILE *fp;
	fp=fopen("input.txt","w+");
	srand(time(0));
	printf("Making some random numbers...\n");
	for (i=1;i<=32;++i){
		fprintf(fp,"%d",(int)rand()%256+1);
		fprintf(fp,"\n");		
	}
	printf("Success!\n");
	fclose(fp);
}
