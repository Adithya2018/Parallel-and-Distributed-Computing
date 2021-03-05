#include<stdio.h>
#include<omp.h>
int main (int argc, char *argv[]) {
    //int th_id, nthreads;
    int c=0;
    #pragma omp parallel shared(c)
    {
        printf("hello world\n");
        #pragma omp atomic
        ++c;
    }
    printf("No. of threads = %d\n",c);
    printf("My name is Adithya Suresh and my roll num is AM.EN.U4CSE18102\n");
    return 0;
}

