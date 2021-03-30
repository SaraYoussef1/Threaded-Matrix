
#include <pthread.h>

struct Data2{
    struct Matrix matrix;
    int row;
    int col;
    int *c_pt;
};

void* mul_element(void* args){
    //extracting sent data
    struct Data2 *my_arg;
    my_arg = (struct Data2*) args;
    struct Matrix mat_ab = my_arg->matrix;
    int i = my_arg->row;
    int j = my_arg->col;
    int *C_pt = my_arg->c_pt;
    int sum = 0;
    //calculate element at row i, colomn j
    for(int k=0; k<mat_ab.size_b[0]; k++)
        sum = sum + mat_ab.mat_a[i][k] * mat_ab.mat_b[k][j];
    C_pt[i*mat_ab.size_b[1]+j] = sum;
}

struct timeval creat_threads2(struct Matrix mat_ab){
    int *C_pt;
    //array saving multiplication output
    int C [mat_ab.size_a[0]*mat_ab.size_b[1]];
    C_pt = C;
    struct Data2 *args;
    //making array of threads
    int num_threads = mat_ab.size_a[0]*mat_ab.size_b[1];
    pthread_t threads[num_threads];
    for(int i=0; i<mat_ab.size_a[0]; i++){
        for(int j=0; j<mat_ab.size_b[1]; j++){
            args = malloc(sizeof(struct Data2));
            args->matrix = mat_ab;      //it holds matrixxx A&B in addition to their dimensions
            args->row = i;              //output row number that is the same as thread number
            args->col = j;              //output colomn number
            args->c_pt = C_pt;          //pointer to output array
            //create threads
            pthread_create(&threads[i], NULL, mul_element, (void *) args);
        }
    }
    //waiting for all threads
    for(int i=0; i<num_threads; i++)
        pthread_join(threads[i], NULL);

    //saving threads finish time
    struct timeval stop;
    gettimeofday(&stop, NULL);
    write_C(mat_ab, C_pt);
    return stop;

}


