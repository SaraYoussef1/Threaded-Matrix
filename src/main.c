#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include "read.h"
#include "method1.h"
#include "method2.h"
#include "write.h"
#define MAXCHAR 1000

int main() {
    struct timeval start, stop;
    struct Matrix mat_ab;
    //open assigned files and extract A,B and their dimensions
    mat_ab = open();
    //second dimension of first matrix is different from first dimension of second matrix
    if(mat_ab.size_a[1] != mat_ab.size_b[0]){
        printf("Invalid Dimensions!!!\n");
        return 1;
    }
    //one thread for each row
    if(mat_ab.method == 1){
        gettimeofday(&start, NULL);
        stop = creat_threads1(mat_ab);
        }
    else{ //one thread for each element
        gettimeofday(&start, NULL);
        stop = creat_threads2(mat_ab);
        }

    printf("\nUsing method number %d:\n", mat_ab.method);
    printf("Number of created threads is: %d\n", mat_ab.threads_num);
    printf("Microseconds taken by threads to perform multiplication: %lu\n", stop.tv_usec - start.tv_usec);
    pthread_exit(NULL);
    return 0;
}
