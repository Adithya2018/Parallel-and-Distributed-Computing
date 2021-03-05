#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <sys/time.h>
#define n 100000
typedef struct arr{
    int *a1;
    int *a2;
}arr;

pthread_t tid[4];

void *sum(void* p)
{
    int *s=(int*) calloc(1,sizeof(int));
    arr *q=(arr*)p;
    for(int i=0;i<n;++i)
        s[0]+=q->a1[i];
    pthread_exit(s);
}

void *largest(void* p)
{
    int *max=(int*) calloc(1,sizeof(int));
    arr *q=(arr*)p;
    max[0]=INT_MIN;
    for(int i=0;i<n;++i){
        int m;
        m=(q->a1[i]>q->a2[i])?q->a1[i]:q->a2[i];
        if(m>max[0]){
            max[0]=m;
        }
        /*if(q->a1[i]>max[0])
            max[0]=q->a1[i];*/
    }
    pthread_exit(max);
}

void *difference(void *p)
{
    //int *d=(int*)calloc(10000000,sizeof(int));
    arr *q=(arr*)p;
    for(int i=0;i<n;++i)
        printf("a[%d]-b[%d]=%d\n",i,i,q->a1[i]-q->a2[i]);
    pthread_exit(NULL);
}

int main()
{   
    struct timeval t0, t1, t2;
    gettimeofday(&t0, NULL);
    //static memory allocation
    /*
    int a[n];
    int b[n];*/

    //dynamic memory allocation
    int *a=(int*)calloc(n,sizeof(int));
    int *b=(int*)calloc(n,sizeof(int));
    for(int i=0;i<n;++i)
    {
        a[i]=rand()%70;
        b[i]=rand()%70;
    }
    printf("a[]: ");
    for(int i=0;i<n;++i)
        printf("%i ",a[i]);
    printf("\n");
    printf("b[]: ");
    for(int i=0;i<n;++i)
        printf("%i ",b[i]);
    printf("\n");
    arr d;
    d.a1 = a;
    d.a2 = b;
    gettimeofday(&t1, NULL);
    pthread_create(&tid[0],NULL,sum,&a);
    pthread_create(&tid[1],NULL,sum,&b);
    pthread_create(&tid[2],NULL,largest,&d);
    pthread_create(&tid[3],NULL,difference,&d);
    int *s1,*s2,*max;
    pthread_join(tid[0],(void**)&s1);
    pthread_join(tid[1],(void**)&s2);
    pthread_join(tid[2],(void**)&max);
    pthread_join(tid[3],NULL);
    gettimeofday(&t2, NULL);
    printf("sum = %d \n",*s1+*s2);
    printf("max = %d \n",*max);
    printf("time for calculation = %lf seconds\n",(double)((t2.tv_sec-t1.tv_sec)*1000000+t2.tv_usec-t1.tv_usec)/1000000);
    printf("program execution time = %lf seconds\n",(double)((t2.tv_sec-t0.tv_sec)*1000000+t2.tv_usec-t0.tv_usec)/1000000);
    return 0;
}
