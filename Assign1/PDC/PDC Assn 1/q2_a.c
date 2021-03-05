#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

#define n 2000

int A[n][n];
int B[n][n];
int C[n][n];


int main()
{
    struct timeval t0, t1, t2, t3, t4;
    gettimeofday(&t0, NULL);
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            A[i][j] = rand() %10;
            B[i][j] = rand() %10;
        }
    }
    gettimeofday(&t1, NULL);

    printf("a[][]\n");
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            printf("%i ",A[i][j]);
        printf("\n");
    }
    printf("\n");
    
    printf("\nb[][]\n");
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            printf("%i ",B[i][j]);
        printf("\n");
    }
    printf("\n");

    gettimeofday(&t2, NULL);
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            C[i][j]=A[i][j]+B[i][j];
    }

    gettimeofday(&t3, NULL);
    printf("\nc[][]\n");
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++)
            printf("%i ",C[i][j]);
        printf("\n");
    }

    gettimeofday(&t4, NULL);
    printf("time for array initialization = %lf seconds\n",(double)((t1.tv_sec-t0.tv_sec)*1000000+t1.tv_usec-t0.tv_usec)/1000000);
    printf("time for calculation = %lf seconds\n",(double)((t3.tv_sec-t2.tv_sec)*1000000+t3.tv_usec-t2.tv_usec)/1000000);
    printf("time for printing the result = %lf seconds\n",(double)((t4.tv_sec-t3.tv_sec)*1000000+t4.tv_usec-t3.tv_usec)/1000000);
    printf("program execution time = %lf seconds\n",(double)((t4.tv_sec-t0.tv_sec)*1000000+t4.tv_usec-t0.tv_usec)/1000000);
    return 0;
}

