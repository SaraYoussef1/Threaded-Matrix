
#define MAX 100
#include<stdio.h>
struct Matrix{
    //containing matrix A, B, their dimensions and selected method
    int mat_a[MAX][MAX];
    int size_a[2];
    int mat_b[MAX][MAX];
    int size_b[2];
    char out_file[MAX];
    int method;
    int threads_num;
};

struct Matrix open(){
    struct Matrix *mat_pt, mat_ab;
    mat_pt = &mat_ab;
    char file1[MAX];
    char file2[MAX];
    char file_out[MAX];
    int method_num;

    //reading files name from user
    printf("Enter first matrix file path, 'enter' for default\n");
    fgets(file1, MAX, stdin);
    printf("Enter second matrix file path, 'enter' for default\n");
    fgets(file2, MAX, stdin);
    printf("Enter OUTPUT file path, 'enter' for default\n");
    fgets(file_out, MAX, stdin);
    printf("Method of matrices multiplication:\n 1--> thread for each row\n 2--> thread for each element\n");
    scanf("%d",&method_num);
    //if user enterd invalid input
    while(method_num != 1 && method_num != 2){
        printf("unvalid Method number!!!\n");
        printf("Method of matrices multiplication:\n 1--> thread for each row\n 2--> thread for each element\n");
        scanf("%d",&method_num);
    }
    mat_pt->method = method_num;

    //handle files names to open them
    remove_enter(mat_pt, file1, 1);
    remove_enter(mat_pt, file2, 2);
    remove_enter(mat_pt, file_out, 3);


    if (method_num == 1)
        mat_pt->threads_num = mat_ab.size_a[0];
    else
        mat_pt->threads_num = mat_ab.size_a[0]*mat_ab.size_b[1];

    return mat_ab;
}

void remove_enter(struct Matrix *mat_pt, char str[], int n){
    char str2[MAX];
    int i = 0;
    while(str[i] != '\n'){
        str2[i] = str[i];
        i++;
    }
    str2[i] = '\0';
    //open files
    get_matrix(mat_pt, str2, n);
}

void get_matrix(struct Matrix *mat_pt, char file[], int n){
    FILE *fp;
    fp = fopen(file, "r");
    //unexisted files to read from
    //open default files
    if (fp == NULL){
        if(n == 1)
            fp = fopen("a.txt", "r");
        if(n == 2)
            fp = fopen("b.txt", "r");
        if(n == 3){
            strncpy(mat_pt->out_file, "c.txt", MAX);
            }
    }
    //save output file distenation
    else if(n == 3)
        strncpy(mat_pt->out_file, file, MAX);
    //open files to read from
    if(n != 3){
        extract(mat_pt, fp, n);
        fclose(fp);
    }

}

void extract(struct Matrix *mat_pt, FILE *fp, int n){
    int row = 0;
    char str[MAX];
    fgets(str, MAX, fp);

    //read first row in file to get matrix dimensions
    get_dimensions(mat_pt, str, n);
    while (fgets(str, MAX, fp) != NULL){
        if(*str != '\n'){
            //read each line in file and extract numbers
            get_elements(mat_pt, str, n, row);
            row++;
        }
    }
}

void get_dimensions(struct Matrix *mat_pt, char str[], int n){
    int i = 0, f = 0, temp = 0;
    while (str[i] != '\0' && str[i] != '\n'){
        if(str[i] == '='){
            i++;
            while(str[i] != ' ' && str[i] != '\n'){
                temp = temp * 10 + (str[i] - '0');
                i++;
            }
            if (f == 0){
                if(n == 1)
                    mat_pt->size_a[0] = temp;
                else
                    mat_pt->size_b[0] = temp;
                f = 1;
            }
            else{
                if(n == 1)
                    mat_pt->size_a[1] = temp;
                else
                    mat_pt->size_b[1] = temp;
            }
            temp = 0;
        }
        i++;
    }
}

void get_elements(struct Matrix *mat_pt, char str[], int n, int row){
    int i = 0, neg = 0, temp = 0, column = 0;
    while (str[i] != '\0' && str[i] != '\n'){
        if(str[i] != ' '){
            if(str[i] == '-'){
                i++;
                neg = 1;
            }
            while((str[i] != ' ') && (str[i] != '\n') && (str[i] != '\0')){
                temp = temp * 10 + (str[i] - '0');
                i++;
            }
            if(neg == 1)
                temp = temp * -1;
            if(n == 1)
                mat_pt->mat_a[row][column] = temp;
            if(n == 2)
                mat_pt->mat_b[row][column] = temp;
            temp = 0;
            neg = 0;
            column ++;
        }
        i++;
    }
}

