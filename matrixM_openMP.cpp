#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

void showMatrix(int ** M, int size){
	  for (int i=0; i<2 ;i++)
        for (int j=0; j<2; j++)
          printf(" %d ",M[i][j]);
}

void iniMatrix(int **V, int size){
	for (int i = 0 ; i < size ; i++)
		for(int j = 0 ; j < size ; j++)
		V[i][j] = 1 + i;
	}
void matrixM_s(int **A, int **B, int **C, int n) 
{	
	int i, j, k;
	for (i = 0; i < n; i++) { 
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				C[i][j]= C[i][j] + A[i][k]*B[k][j];
			} 
		}
	}
}
int main(){
	int x;
	int const size = 1000;
	int **A = new int*[size]();
	int **B = new int*[size]();
	int **C = new int*[size]();
	for(int i = 0 ; i < size ; i++){
		A[i] = new int[size];
		B[i] = new int[size];
		C[i] = new int[size];
	}
    iniMatrix(A,size);
	iniMatrix(B,size);
    for (int i=0; i<size; i++)
      for (int j=0; j<size; j++){
		 C[i][j] = 0;
	  }

	//show part of matrix
    showMatrix(A,2);
	omp_set_num_threads(4);// create number of openMP threads
	/* Parallel region begins here */
	double start = omp_get_wtime();
	printf("\n time start = %d \n",start);
	double end;
	int i,j,k;
#pragma omp parallel
{

    int ID = omp_get_thread_num();
	int nTreads = omp_get_num_threads();
	printf("\n threads num = %d \n",omp_get_num_threads());
#pragma omp for
	for (i = 0 ; i < size ; i = i + 1)
		for(j = 0 ; j < size ; j++)
			for( k = 0 ; k < size ; k++)
		      C[i][j] = C[i][j] + A[i][k] * B[k][j];
    
}
    end = omp_get_wtime();
    printf("\n time end = %d \n",end);
    printf("\ntotal time openMP is %1f \n",end-start);

		//show part of matrix
	showMatrix(C,2);
	// reinilize matrix C for serial computation
    for(int i = 0 ; i < size ; i++)
		for (int j = 0 ; j < size ; j++)
			C[i][j] = 0;

	//serial computation
	matrixM_s(A,B,C,size);

	printf("\n");
	end = omp_get_wtime();
	printf("\ntotal time Serial is %1f \n",end-start);
		//show part of matrix
    showMatrix(C,2);
	scanf("inset x ",x);
}
