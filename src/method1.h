#include <pthread.h>

struct Data{
    struct Matrix matrix;
    int row;
    int *c_pt;
};

void* mul_row(void* args){

    //extracting sent data
    struct Data *my_arg;
    my_arg = (struct Data*) args;
    int i = my_arg->row;
    struct Matrix mat_ab = my_arg->matrix;
    int *C_pt = my_arg->c_pt;

    int m = mat_ab.size_b[0];
    int n = mat_ab.size_b[1];  //number of colomn
    int sum = 0;
    //calculate row i elements
        for(int j=0; j<n; j++){
            for(int k=0; k<m; k++)
                sum = sum + mat_ab.mat_a[i][k] * mat_ab.mat_b[k][j];
            C_pt[i*n+j] = sum;
            sum = 0;
        }
}

struct timeval creat_threads1(struct Matrix mat_ab ){

    //array saving multiplication output
    int C [mat_ab.size_a[0]*mat_ab.size_b[1]];
    int *C_pt;
    C_pt = C;
    struct Data *args;
    //making array of threads
    int num_threads = mat_ab.size_a[0];
    pthread_t threads[num_threads];
    for(int i=0; i<num_threads; i++){
        args = malloc(sizeof(struct Data));
        args->matrix = mat_ab;  //it holds matrixxx A&B in addition to their dimensions
        args->row = i;          //output row number that is the same as thread number
        args->c_pt = C_pt;      //pointer to output array
        //create threads
        pthread_create(&threads[i], NULL, mul_row, (void *) args);
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






