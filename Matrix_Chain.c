//solve matrix chain multiplying problem
//using DP
//zjr 11.26
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "timecount.h"

int p[32];		//subscripts of matrixes
int devide[32][32];     //devide points
long int min[32][32];	//record minimum of A[i]*...*A[j]

//min[i,j]=min{min[i,k]+min[k,j]+p[i]*p[k]*p[j]}
void DP_Matrix_Chain(int N){
	int i,j,k,length;
	long int sum;
	for (length=1;length<N;++length){
		j=length;
		for (i=0;i<N-length;++i){
			min[i][j]=INT_MAX;							//inatialize every min[i][j] to be unlimit
			for (k=i+1;k<=j;++k){						//looking for devide point
				sum=min[i][k-1]+min[k][j]+p[i]*p[k]*p[j+1]; 
				if (sum<min[i][j]){
					min[i][j]=sum;
					devide[i][j]=k;
				}
			}//k for
			++j;
		}//i for
	}//length for
}//DP_Matrix_Chain

void printresult(FILE **fpr,int i,int j){
	if (i==j){
		fprintf(*fpr,"A%d",i);
		return;
	}
	else if (i==(j-1)){
		fprintf(*fpr,"(A%d,A%d)",i,j);
		return;
	}
	int k;
	k=devide[i][j];
	fprintf(*fpr,"(");
	printresult(fpr,i,k-1);
	fprintf(*fpr,",");
	printresult(fpr,k,j);
	fprintf(*fpr,")");
}

int main(){
	int i,j,k;
	int scale[4]={5,10,20,30};
	//read numbers
	FILE *fp,*fpr;
	fp=fopen("input.txt","r+");
	for (i=0;i<32;++i){
		fscanf(fp,"%d",&p[i]);
	}	
	fclose(fp);

	
	fp=fopen("output.txt","w+");
	fpr=fopen("result.txt","w+");
	fprintf(fp,"********result*********\n");
	fprintf(fpr,"********result*********\n");

	//calculate
	printf("**************CALCULATION START...****************\n");
	for (i=0;i<4;++i){
		memset(devide,0,32*32*sizeof(int));
		memset(min,0,32*32*sizeof(long int));
		timestart();
		DP_Matrix_Chain(scale[i]);				//calculate
		timeend();
		printf("\nN is %d:\n",scale[i]);
		//output result
		fprintf(fp,"\nN:%d min is %ld\n",scale[i],min[0][scale[i]-1]);
		fprintf(fp,"\tdevide:\n");
		for (j=0;j<scale[i];++j){
			fprintf(fp,"\t");
			for (k=0;k<scale[i];++k){
				if (devide[j][k]>=10) fprintf(fp,"%d ",devide[j][k]);	
				else fprintf(fp,"%d  ",devide[j][k]);
			}
			fprintf(fp,"\n");
		}
		outputtime();
		fprintf(fpr,"\nN:%d min is %ld\n",scale[i],min[0][scale[i]-1]);
		printresult(&fpr,0,scale[i]-1);
	}
	printf("\n**************CALCULATION END**********************\n");
	fclose(fp);
	fclose(fpr);
}
