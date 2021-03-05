#include<stdio.h>
#include<omp.h>
int main (int argc, char *argv[]) {
    int th_id, nthreads;
    #pragma omp parallel private(th_id)
    {
        th_id = omp_get_thread_num();
        printf("Hello World from thread %d\n", th_id);
    //#pragma omp barrier        //<----------- master waits until all threads finish before printing 
    //if the barrier is removed the print statement below may get executed... 
    //during every other thread executes the print statement above
        if (th_id==0 ){
            nthreads = omp_get_num_threads();
            printf("There are %d threads\n",nthreads);
        }
    }
    printf("My name is Adithya Suresh and my roll num is AM.EN.U4CSE18102\n");
    return 0;
}

