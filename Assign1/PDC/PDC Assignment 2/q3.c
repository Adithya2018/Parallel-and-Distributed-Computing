#include<stdio.h>
#include<omp.h>
int main(){

    const int N=20; 
    int a[N]; 

//initialize 
    for (int i=0; i < N; i++){
        a[i] = i; 
    }

//compute sum 
    int local_sum, sum; 
    #pragma omp parallel private(local_sum) shared(sum) 
    { 
        local_sum = 0; 
    
    //the array is distributde statically between threads
    #pragma omp for schedule(static,1) 
    for (int i=0; i< N; i++) {
        local_sum += a[i]; 
        printf("thread with id is ​ %d ​ is executing the iteration with index %d\n",omp_get_thread_num(),i);
    }

    //each thread calculated its local_sum. ALl threads have to add to
    //the global sum. It is critical that this operation is atomic.

    /*
    Output:
    static-equal no. of threads are created for each thread ID.
    dynamic-different no. of threads are created for each thread dynamically, in this case unequally.
    Another example: If the chunk size was 10 then only two threads would be running.
    default-chunk size differs for each thread; since it decided by the compiler.
    */

    #pragma omp atomic
    sum += local_sum;
    } 

    printf("sum=%d should be %d\n", sum, N*(N-1)/2);
    printf("My name is Adithya Suresh and my roll num is AM.EN.U4CSE18102\n");
    return 0;
}

