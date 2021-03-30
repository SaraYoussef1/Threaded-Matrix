
#include<stdio.h>

void write_C(struct Matrix mat_ab, int* C_pt){
    FILE *fp;
    //open file
    fp = fopen(mat_ab.out_file, "w+");
    //write dimentions of calculated matrix
    fprintf(fp, "row=%d col=%d\n",mat_ab.size_a[0],mat_ab.size_b[1]);
    //write content of calculated matrix in the out file
    for(int i=0; i<mat_ab.size_a[0]; i++){
        for(int j=0; j<mat_ab.size_b[1]; j++)
            fprintf(fp, "%d ", C_pt[i*mat_ab.size_b[1]+j]);
        fprintf(fp,"\n");
    }
    fclose(fp);
}

