//solve matrix chain multiplying problem
//using DP
//zjr 11.26
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "timecount.h"

int p[32];		//subscripts of matrixes
int devide[32][32];     //devide points
int min[32][32];	//record minimum of A[i]*...*A[j]

//min[i,j]=min{min[i,k]+min[k,j]+p[i]*p[k]*p[j]}
void DP_Matrix_Chain(int N){
	int i,j,k,sum;
	for (i=0;i<N;++i){
		for (j=i+1;j<N;++j){
			min[i][j]=INT_MAX;	
			for (k=i+1;k<=j;++k){
				sum=min[i][k-1]+min[k][j]+p[i]*p[k]*p[j];
				if (sum<min[i][j]){
					min[i][j]=sum;
					devide[i][j]=k;
				}
			}//k for
		}//j for
	}//i for
}//DP_Matrix_Chain

int main(){
	int i;
	int scale[4]={5,10,20,30};
	//read numbers
	FILE *fp;
	fp=fopen("input.txt","r+");
	for (i=0;i<32;++i){
		fscanf(fp,"%d",&p[i]);
	}	
	fclose(fp);

	//calculate
	printf("**************CALCULATION START...****************\n");
	for (i=0;i<4;++i){
		memset(devide,0,32*32*sizeof(int));
		memset(min,0,32*32*sizeof(int));
		timestart();
		DP_Matrix_Chain(scale[i]);
		timeend();
		printf("\nN is %d:\n",scale[i]);
		outputtime();
	}
	printf("**************CALCULATION END**********************\n");
}
