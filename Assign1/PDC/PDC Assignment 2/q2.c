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
    #pragma omp for// schedule(dynamic,1) 
    for (int i=0; i< N; i++) {
        local_sum += a[i]; 
        printf("thread with id is ​ %d ​ is executing the iteration with index %d\n",omp_get_thread_num(),i);
    }

    //each thread calculated its local_sum. ALl threads have to add to
    //the global sum. It is critical that this operation is atomic.

    //omitting the critical construct below
    //causes the final result of sum to be 
    //an incorrect value. Same thing happens 
    //if the statement is not omitted because
    //critical is not optimized for handling 
    //simple operations. This can be solved 
    //by using the atomic constuct which is 
    //more optimized.

    #pragma omp atomic
    sum += local_sum;
    } 

    printf("sum=%d should be %d\n", sum, N*(N-1)/2);
    printf("My name is Adithya Suresh and my roll num is AM.EN.U4CSE18102\n");
    return 0;
}

