#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct vectors{
    char *name;
    int length;
    int *data;
};
struct matrices{
    char *name;
    int row;
    int column;
    int **data;
};
int findVector(char name[],int *sequence_vector, struct vectors **array){
    int i;
    for (i = 0; i <(*sequence_vector-1) ; ++i) {
        if(strcmp(name,array[i]->name)==0){
            return i;
        }
    }
    return -1;
}
int findMatrix(char name[],int *sequence_matrix, struct matrices **array){
    int i;
    for (i = 0; i <(*sequence_matrix-1) ; ++i) {
        if(strcmp(name,array[i]->name)==0){
            return i;
        }
    }
    return -1;
}
void Veczeros(char name[],char length[],int *sequence_of_vector,struct vectors *All_vectors){
    int i;
        All_vectors->name=malloc(sizeof(char)*strlen(name));
        for (i = 0;i  <strlen(name) ; ++i) {
            All_vectors->name[i]=name[i];
            printf("%c",All_vectors->name[i]);
        }

        All_vectors->name=atoi(length);
        All_vectors->name=(int *)malloc(sizeof(int)*(atoi(length)));
        for (i = 0; i <atoi(length) ; ++i) {
            All_vectors->name[i]=0;
        }
        *sequence_of_vector=*sequence_of_vector+1;


}
void Matzeros(char name[],char row[],char column[],int *sequence_of_matrices,struct matrices **All_matrices) {
    int i, j;
    if (findMatrix(name, sequence_of_matrices, All_matrices) != -1) {
        printf("ERROR-MATZEROS");
    }
    else {
        All_matrices = (struct matrices **) realloc(All_matrices, *sequence_of_matrices);
        All_matrices[*sequence_of_matrices-1] =(struct matrices *) malloc(sizeof(struct matrices*));
        All_matrices[*sequence_of_matrices - 1]->name = name;
        All_matrices[*sequence_of_matrices - 1]->row = atoi(row);
        All_matrices[*sequence_of_matrices - 1]->column = atoi(column);
        All_matrices[*sequence_of_matrices - 1]->data = (int **) malloc(sizeof(int *) * (atoi(row)));
        for (i = 0; i < atoi(row); ++i) {
            All_matrices[*sequence_of_matrices - 1]->data[i] = (int *) malloc(atoi(column) * sizeof(int));
            for (i = 0; i < atoi(row); ++i) {
                for (j = 0; j < atoi(column); ++j) {
                    All_matrices[*sequence_of_matrices - 1]->data[i][j] = 0;
                }
            }
        }
        *sequence_of_matrices = *sequence_of_matrices + 1;
    }
}
void Vecstack(char vec1[],char vec2[],char direction[],char new_matrix_name[],int *sequence_of_vector,int *sequence_matrix,struct vectors **array,struct matrices **array2){
    int i;
    if (findVector(vec1,sequence_of_vector,array)==-1){
        printf("ERROR-1-VECSTACK\n");
    }
    else if(findVector(vec2,sequence_of_vector,array)==-1){
        printf("ERROR-2-VECSTACK\n");
    }
    else if(findMatrix(new_matrix_name,sequence_matrix,array2)!=-1){
        printf("ERROR-3-VECSTACK\n");
    }
    else if (array[findVector(vec1,sequence_of_vector,array)]->length!=array[findVector(vec2,sequence_of_vector,array)]->length){
        printf("ERROR-4-VECSTACK\n");
    }
    else{

        array2 = (struct matrices **) realloc(array2, *sequence_matrix);
        array2[*sequence_matrix-1]=(struct matrices*)malloc(sizeof(struct matrices));
        array2[*sequence_matrix-1]->name=new_matrix_name;
        if(strcmp(direction,"row")==0){
            array2[*sequence_matrix-1]->row=2;
            array2[*sequence_matrix-1]->column=array[findVector(vec1,sequence_of_vector,array)]->length;
            array2[*sequence_matrix-1]->data=(int **)malloc(2* sizeof(int*));
            for (i = 0; i <2 ; ++i) {
                array2[*sequence_matrix-1]->data[i]=(int *)malloc((array2[*sequence_matrix-1]->column)* sizeof(int));
            }
            for (i = 0;  i<array2[*sequence_matrix-1]->column ; ++i) {
                array2[*sequence_matrix-1]->data[0][i]=array[findVector(vec1,sequence_of_vector,array)]->data[i];
            }
            for (i = 0;  i<array2[*sequence_matrix-1]->column ; ++i) {
                array2[*sequence_matrix-1]->data[1][i]=array[findVector(vec2,sequence_of_vector,array)]->data[i];
            }

        *sequence_matrix=*sequence_matrix+1;
        }
        else if (strcmp(direction,"column")==0) {
            array2[*sequence_matrix - 1]->row = array[findVector(vec1, sequence_of_vector, array)]->length;
            array2[*sequence_matrix - 1]->column = 2;
            array2[*sequence_matrix - 1]->data = (int **) malloc((array2[*sequence_matrix - 1]->row) * sizeof(int *));
            for (i = 0; i < (array2[*sequence_matrix - 1]->row); ++i) {
                array2[*sequence_matrix - 1]->data[i] = (int *) malloc(sizeof(int) * 2);
            }
            for (i = 0; i < (array2[*sequence_matrix - 1]->row); ++i) {
                array2[*sequence_matrix - 1]->data[i][0] = array[findVector(vec1, sequence_of_vector, array)]->data[i];
            }
            for (i = 0; i < (array2[*sequence_matrix - 1]->row); ++i) {
                array2[*sequence_matrix - 1]->data[i][1] = array[findVector(vec2, sequence_of_vector, array)]->data[i];
            }
            *sequence_matrix = *sequence_matrix + 1;
        }
    }
}
void Matstack(char line[],int *sequence_matrix,struct matrices **array) {
    int count = 9;
    int i,j;
    while (*(line + count) != ' ') {
        count++;
    }
    char *mat1 = (char *)malloc(sizeof(char) * (count - 8));
    for (i = 0; i < (count - 9); ++i) {
        mat1[i] = line[i + 9];
    }
    mat1[count - 9] = '\0';
    int count2 = count + 1;
    while (*(line + count2) != ' ') {
        count2++;
    }
    char *mat2 = (char *)malloc(sizeof(char) * (count2 - count));
    for (i = 0; i < (count2 - count - 1); ++i) {
        mat2[i] = line[count + 1 + i];
    }
    mat2[count2 - count - 1] = '\0';

    int count3 = count2 + 1;
    while (*(line + count3) != ' ') {
        count3++;
    }
    char *direction = (char *)malloc(sizeof(char) * (count3 - count2));
    for (i = 0; i < (count3 - count2 - 1); ++i) {
        direction[i] = line[count2 + 1 + i];
    }
    direction[count3 - count2 - 1] = '\0';
    if (findMatrix(mat1, sequence_matrix, array) == -1) {
        printf("ERROR--1--MATSTACK\n");
    }
    else if (findMatrix(mat2,sequence_matrix, array) == -1) {
        printf("ERROR--2--MATSTACK\n");
    }
    else{
        if (strcmp(direction,"d")==0){
            if (array[findMatrix(mat1,sequence_matrix,array)]->column!=array[findMatrix(mat2,sequence_matrix,array)]->column){
                printf("ERROR-Boyut1--MATSTACK\n");
            }
            else{
                array[findMatrix(mat1,sequence_matrix,array)]->data=(int **)realloc(array[findMatrix(mat1,sequence_matrix,array)]->data, sizeof(int *)*(array[findMatrix(mat1,sequence_matrix,array)]->row+array[findMatrix(mat2,sequence_matrix,array)]->row));
                for (i = array[findMatrix(mat1,sequence_matrix,array)]->row; i <(array[findMatrix(mat2,sequence_matrix,array)]->row+array[findMatrix(mat1,sequence_matrix,array)]->row) ; ++i) {
                    array[findMatrix(mat1,sequence_matrix,array)]->data[i]=(int *)malloc(array[findMatrix(mat2,sequence_matrix,array)*sizeof(int)]->column);
                }
                for (i = 0; i <array[findMatrix(mat2,sequence_matrix,array)]->row ; ++i) {
                    for (j = 0; j <array[findMatrix(mat2,sequence_matrix,array)]->column ; ++j) {
                        array[findMatrix(mat1,sequence_matrix,array)]->data[(i)+(array[findMatrix(mat1,sequence_matrix,array)]->row)][j]=array[findMatrix(mat2,sequence_matrix,array)]->data[i][j];
                    }
                }
                array[findMatrix(mat1,sequence_matrix,array)]->row=(array[findMatrix(mat1,sequence_matrix,array)]->row+array[findMatrix(mat2,sequence_matrix,array)]->row);
            }

        }
        else if (strcmp(direction,"r")==0){
            if (array[findMatrix(mat1,sequence_matrix,array)]->row!=array[findMatrix(mat2,sequence_matrix,array)]->row){
                printf("ERROR-Boyut2-MATSTACK\n");
            }
            else{
                for (i = 0; i < array[findMatrix(mat2,sequence_matrix,array)]->row ; ++i) {
                    array[findMatrix(mat1,sequence_matrix,array)]->data[i]=(int *) realloc(array[findMatrix(mat1,sequence_matrix,array)]->data[i],
                                                                                           sizeof(int)*(array[findMatrix(mat1,sequence_matrix,array)]->column+array[findMatrix(mat2,sequence_matrix,array)]->column));
                }
                for (i = 0;i  < array[findMatrix(mat1,sequence_matrix,array)]->row ; ++i) {
                    for (j = 0; j < (array[findMatrix(mat2,sequence_matrix,array)]->column) ; ++j) {
                        array[findMatrix(mat1,sequence_matrix,array)]->data[i][j+(array[findMatrix(mat1,sequence_matrix,array)]->column)]=array[findMatrix(mat2,sequence_matrix,array)]->data[i][j];
                    }
                }
                array[findMatrix(mat1,sequence_matrix,array)]->column = ((array[findMatrix(mat1,sequence_matrix,array)]->column+array[findMatrix(mat2,sequence_matrix,array)]->column));
            }
        }
    }
    free(mat1);
    free(mat2);
    free(direction);

}
void Mvstack(char line[],int *sequence_vector,int *sequence_matrix,struct vectors **All_vectors,struct matrices **All_matrices){
    int count = 8;
    int i,j;
    while (*(line + count) != ' ') {
        count++;
    }
    char *mat =(char *) malloc(sizeof(char) * (count - 7));
    for (i = 0; i < (count - 8); ++i) {
        mat[i] = line[i + 8];
    }
    mat[count - 8] = '\0';
    int count2 = count + 1;
    while (*(line + count2) != ' ') {
        count2++;
    }
    char *vec =(char *) malloc(sizeof(char) * (count2 - count));
    for (i = 0; i < (count2 - count - 1); ++i) {
        vec[i] = line[count + 1 + i];
    }
    vec[count2 - count - 1] = '\0';

    int count3 = count2 + 1;
    while (*(line + count3) != ' ') {
        count3++;
    }
    char *direction =(char *) malloc(sizeof(char) * (count3 - count2));
    for (i = 0; i < (count3 - count2 - 1); ++i) {
        direction[i] = line[count2 + 1 + i];
    }
    direction[count3 - count2 - 1] = '\0';

    if (findMatrix(mat, sequence_matrix, All_matrices) == -1) {

        printf("ERROR--1--MVSTACK\n");
    }
    else if (findVector(vec,sequence_matrix, All_vectors) == -1) {
        printf("ERROR--2--MVSTACK\n");
    }
    else{
        if (strcmp(direction,"d")==0){
            if (All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->column!=All_vectors[findVector(vec,sequence_vector,All_vectors)]->length){
                printf("ERROR-Boyut1--MVSTACK\n");
            }
            else{
                All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->data=(int **)realloc(All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->data,sizeof(int *)*All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->row+1);
                All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->data[All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->row]=(int *)malloc(sizeof(int)*(All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->column+1));
                for (i = 0; i <All_vectors[findVector(vec,sequence_vector,All_vectors)]->length ; ++i) {
                    All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->data[All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->row][i]=All_vectors[findVector(vec,sequence_vector,All_vectors)]->data[i];
                }
                All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->row=All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->row+1;
            }
        }
        else if (strcmp(direction,"r")==0){
            if (All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->row!=All_vectors[findVector(vec,sequence_vector,All_vectors)]->length){
                printf("ERROR-Boyut2--MVSTACK\n");
            }
            else{
                for (i = 0; i <All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->row ; ++i) {
                    All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->data[i]=(int *) realloc(All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->data[i],sizeof(int)*(All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->column+1));
                }
                for (i = 0; i <All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->row ; ++i) {
                    All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->data[i][All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->column]=All_vectors[findVector(vec,sequence_vector,All_vectors)]->data[i];
                }
                All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->column=All_matrices[findMatrix(mat,sequence_matrix,All_matrices)]->column+1;
            }
        }
    }
    free(mat);
    free(vec);
    free(direction);

}
void Pad(char line[],int *sequence_matrix,struct matrices **All_matrices){
    int count=4;
    int i,j,k,value;
    while(*(line+count)!=' '){
        count++;
    }
    char *mat=(char *)malloc(sizeof(char)*(count-3));
    for (i = 0; i < (count-4); ++i) {
        mat[i]=line[i+4];
    }
    mat[count-4]='\0';
    int index=findMatrix(mat,sequence_matrix,All_matrices);
    int count2=count+1;
    while(*(line+count2)!=' '){
        count2++;
    }
    char *new_row =(char *) malloc(sizeof(char)*(count2-count));

    for (i = 0; i <(count2-count-1) ; ++i) {
        new_row[i]=line[count+1+i];
    }
    new_row[count2-count-1]='\0';

    int count3=count2+1;
    while(*(line+count3)!=' '){
        count3++;
    }
    char *new_column=(char *)malloc(sizeof(char)*(count3-count2));

    for(i=0;i<(count3-count2-1);++i){
        new_column[i]=line[count2+1+i];
    }
    new_column[count3-count2-1]='\0';

    int count4=count3+1;
    while(*(line+count4)!='\0'){
        count4++;
    }
    char *mode=(char *)malloc(sizeof(char)*(count4-count3));

    for(i=0;i<(count4-count3-1);++i){
        mode[i]=line[count3+1+i];
    }

    mode[count4-count3-1]='\0';
    if (index ==-1){
        printf("ERROR-1");
    }
    else {
        if (strcmp(mode,"maximum")==0){
            All_matrices[index]->data = (int **) realloc(All_matrices[index]->data,sizeof(int*) * (All_matrices[index]->row + atoi(new_row)));
            for (i = All_matrices[index]->row;  i< All_matrices[index]->row+atoi(new_row); ++i) {
                All_matrices[index]->data[i]=(int *)malloc(sizeof(int )*All_matrices[index]->column+atoi(new_column));
            }
            for (i = 0; i <All_matrices[index]->column ; ++i) {
                value=All_matrices[index]->data[0][i];
                for (j = 0;j  < All_matrices[index]->row; ++j) {
                    if (All_matrices[index]->data[j][i]>value){
                        value=All_matrices[index]->data[j][i];
                    }
                }
                for (k = All_matrices[index]->row;k  <All_matrices[index]->row+atoi(new_row) ; ++k) {
                    All_matrices[index]->data[k][i]=value;
                }
            }
            for (i = 0;i<All_matrices[index]->row ; ++i) {
                value=All_matrices[index]->data[i][0];
                for (j = 0; j < All_matrices[index]->column; ++j) {
                    if ((All_matrices[index]->data[i][j]>value)){
                        value=All_matrices[index]->data[i][j];
                    }
                }
                for (k = All_matrices[index]->column; k <All_matrices[index]->column+atoi(new_column) ; ++k) {
                    All_matrices[index]->data[i][k]=value;
                }
            }
            for (i = All_matrices[index]->column; i <All_matrices[index]->column+atoi(new_column) ; ++i) {
                for (j = 0; j <All_matrices[index]->row ; ++j) {
                    if(All_matrices[index]->data[i][j]>value){
                        value=All_matrices[index]->data[j][i];
                    }
                }
                for (k = All_matrices[index]->row; k <All_matrices[index]->row+atoi(new_row) ; ++k) {
                    All_matrices[index]->data[k][i]=value;
                }
            }
            All_matrices[index]->row=All_matrices[index]->row+atoi(new_row);
            All_matrices[index]->column=All_matrices[index]->column+atoi(new_column);
        }
        if (strcmp(mode,"minimum")==0){

            All_matrices[index]->data = (int **) realloc(All_matrices[index]->data,sizeof(int*) * (All_matrices[index]->row + atoi(new_row)));

            for (i = All_matrices[index]->row;  i< All_matrices[index]->row+atoi(new_row); ++i) {
                All_matrices[index]->data[i]=(int *)malloc(sizeof(int )*All_matrices[index]->column+atoi(new_column));
            }
            for (i = 0; i <All_matrices[index]->column ; ++i) {
                value=All_matrices[index]->data[0][i];
                for (j = 0;j  < All_matrices[index]->row; ++j) {
                    if (All_matrices[index]->data[j][i]<value){
                        value=All_matrices[index]->data[j][i];
                    }
                }
                for (k = All_matrices[index]->row;k  <All_matrices[index]->row+atoi(new_row) ; ++k) {
                    All_matrices[index]->data[k][i]=value;
                }
            }
            for (i = 0;i<All_matrices[index]->row ; ++i) {
                value=All_matrices[index]->data[i][0];
                for (j = 0; j < All_matrices[index]->column; ++j) {
                    if ((All_matrices[index]->data[i][j]<value)){
                        value=All_matrices[index]->data[i][j];
                    }
                }
                for (k = All_matrices[index]->column; k <All_matrices[index]->column+atoi(new_column) ; ++k) {
                    All_matrices[index]->data[i][k]=value;
                }
            }
            for (i = All_matrices[index]->column; i <All_matrices[index]->column+atoi(new_column) ; ++i) {
                for (j = 0; j <All_matrices[index]->row ; ++j) {
                    if(All_matrices[index]->data[i][j]<value){
                        value=All_matrices[index]->data[j][i];
                    }
                }
                for (k = All_matrices[index]->row; k <All_matrices[index]->row+atoi(new_row) ; ++k) {
                    All_matrices[index]->data[k][i]=value;
                }
            }
            All_matrices[index]->row=All_matrices[index]->row+atoi(new_row);
            All_matrices[index]->column=All_matrices[index]->column+atoi(new_column);
        }
    }
    free(mat);
    free(new_row);
    free(new_column);
    free(mode);

}
void Padval(char line[],int *sequence_matrix,struct matrices **All_matrices){
    int count=7;
    int i,j;
    while(*(line+count)!=' '){
        count++;
    }
    char *mat=(char *)malloc(sizeof(char)*(count-6));
    for (i = 0; i < (count-7); ++i) {
        mat[i]=line[i+7];
    }
    mat[count-7]='\0';
    int index=findMatrix(mat,sequence_matrix,All_matrices);
    int count2=count+1;
    while(*(line+count2)!=' '){
        count2++;
    }

    char *new_row= (char *)malloc(sizeof(char)*(count2-count));
    for (i = 0; i <(count2-count-1) ; ++i) {
        new_row[i]=line[count+1+i];
    }
    new_row[count2-count-1]='\0';

    int count3=count2+1;
    while(*(line+count3)!=' '){
        count3++;
    }
    char *new_column=(char *)malloc(sizeof(char)*(count3-count2));
    for(i=0;i<(count3-count2-1);++i){
        new_column[i]=line[count2+1+i];
    }
    new_column[count3-count2-1]='\0';

    int count4=count3+1;

    while(*(line+count4)!='\0'){
        count4++;
    }

    char *value=(char *)malloc(sizeof(char)*(count4-count3));
    for(i=0;i<(count4-count3-1);++i){
        value[i]=line[count3+1+i];
    }
    value[count4-count3-1]='\0';
    int val=atoi(value);
    if (index==-1){
        printf("ERROR-1");
    }
    else{
        All_matrices[index]->data = (int **) realloc(All_matrices[index]->data,sizeof(int*) * (All_matrices[index]->row + atoi(new_row)));
        for (i = All_matrices[index]->row;  i< All_matrices[index]->row+atoi(new_row); ++i) {
            All_matrices[index]->data[i]=(int *)malloc(sizeof(int )*All_matrices[index]->column+atoi(new_column));
        }
        for (i = All_matrices[index]->column; i <All_matrices[index]->column+atoi(new_column) ; ++i) {
            for (j = 0;  j<All_matrices[index]->row ; ++j) {
                All_matrices[index]->data[j][i]=val;
            }
        }
        for (i = All_matrices[index]->row; i <All_matrices[index]->row+atoi(new_row) ; ++i) {
            for (j = 0;  j< All_matrices[index]->column+atoi(new_column); ++j) {
                All_matrices[index]->data[i][j]=val;
            }
        }
        All_matrices[index]->row=All_matrices[index]->row+atoi(new_row);
        All_matrices[index]->column=All_matrices[index]->column+atoi(new_column);
    }
    free(mat);
    free(new_row);
    free(new_column);
    free(value);

}
void Vecslice(char line[],int *sequence_vector,struct vectors **All_vectors){
    int count=9;
    int i;
    while(*(line+count)!=' '){
        count++;
    }
    char *vec=(char *)malloc(sizeof(char)*(count-8));
    for (i = 0; i < (count-9); ++i) {
        vec[i]=line[i+9];
    }
    vec[count-9]='\0';
    int index=findVector(vec,sequence_vector,All_vectors);
    int count2=count+1;
    while(*(line+count2)!=' '){
        count2++;
    }
    char *start =(char *) malloc(sizeof(char)*(count2-count));
    for (i = 0; i <(count2-count-1) ; ++i) {
        start[i]=line[count+1+i];
    }
    start[count2-count-1]='\0';
    int count3=count2+1;
    while(*(line+count3)!=' '){
        count3++;
    }
    char *stop=(char *)malloc(sizeof(char)*(count3-count2));
    for(i=0;i<(count3-count2-1);++i){
        stop[i]=line[count2+1+i];
    }
    stop[count3-count2-1]='\0';
    int count4=count3+1;
    while(*(line+count4)!='\0'){
        count4++;
    }

    char *new_name=(char *)malloc(sizeof(char)*(count4-count3));
    for(i=0;i<(count4-count3-1);++i){
        new_name[i]=line[count3+1+i];
    }
    new_name[count4-count3-1]='\0';
    int new_index=findVector(new_name,sequence_vector,All_vectors);

    if (index==-1){
        printf("ERROR--1--VECSLICE");
    }
    else if(new_index!=-1){
        printf("ERROR--2--VECSLICE");
    }
    else if (All_vectors[index]->length<=atoi(stop)){
        printf("ERROR--3--VECSLICE");
    }
    else{
        All_vectors = (struct vectors **) realloc(All_vectors, *sequence_vector);
        All_vectors[*sequence_vector - 1] =  malloc(sizeof(struct vectors*));
        All_vectors[*sequence_vector-1]->name=malloc(sizeof(char)*(count4-count3));
        for (i = 0; i < count4-count3-1; ++i) {
            All_vectors[*sequence_vector-1]->name[i]=new_name[i];
        }
        All_vectors[*sequence_vector -1]->name[count4-count3-1]='\0';

        All_vectors[*sequence_vector-1]->length=(atoi(stop)-atoi(start));

        All_vectors[*sequence_vector-1]->data=(int *)malloc(sizeof(int )*(atoi(stop)-atoi(start)));

        for (i = 0; i < All_vectors[*sequence_vector-1]->length; ++i) {
            All_vectors[*sequence_vector-1]->data[i]=0;
        }
        *sequence_vector=*sequence_vector+1;
    }
    free(vec);
    free(start);
    free(stop);
    free(new_name);
}
void Matslicecol(char line[],int *sequence_vector,int *sequence_matrice,struct vectors **All_vectors,struct matrices **All_matrices){

    int count=12;
    int i;
    while(*(line+count)!=' '){
        count++;
    }
    char *mat=(char *)malloc(sizeof(char)*(count-11));
    for (i = 0; i < (count-12); ++i) {
        mat[i]=line[i+12];
    }
    mat[count-12]='\0';

    int count2=count+1;
    while(*(line+count2)!=' '){
        count2++;
    }
    char *row =(char *) malloc(sizeof(char)*(count2-count));
    for (i = 0; i <(count2-count-1) ; ++i) {
        row[i]=line[count+1+i];
    }
    row[count2-count-1]='\0';
    int count3=count2+1;
    while(*(line+count3)!=' '){
        count3++;
    }
    char *start=(char *)malloc(sizeof(char)*(count3-count2));
    for(i=0;i<(count3-count2-1);++i){
        start[i]=line[count2+1+i];
    }
    start[count3-count2-1]='\0';
    int count4=count3+1;
    while(*(line+count4)!=' '){
        count4++;
    }
    char *stop=(char *)malloc(sizeof(char)*(count4-count3));
    for(i=0;i<(count4-count3-1);++i){
        stop[i]=line[count3+1+i];
    }
    stop[count4-count3-1]='\0';
    int count5=count4+1;
    while(*(line+count5)!='\0'){
        count5++;
    }
    char *new_vec=(char *)malloc(sizeof(char)*(count5-count4));
    for (i = 0;i  <(count5-count4-1) ; ++i) {
        new_vec[i]=line[count4+1+i];
    }
    new_vec[count5-count4-1]='\0';
    if (findMatrix(mat,sequence_matrice,All_matrices)==-1){
        printf("ERROR-1-MATSLICECOL");
    }
    else if(findVector(new_vec,sequence_matrice,All_vectors)!=-1){
        printf("ERROR-2-MATSLICECOL");
    }
    else if(All_matrices[(findMatrix(mat,sequence_matrice,All_matrices))]->row<=atoi(row)){
        printf("ERROR-3-MATSLICECOL");
    }
    else if(All_matrices[findMatrix(mat,sequence_matrice,All_matrices)]->column<=atoi(stop)){
        printf("ERROR-4-MATSLICECOL");
    }
    else{
        All_vectors = (struct vectors **) realloc(All_vectors, (*sequence_vector));
        All_vectors[*sequence_vector-1]=malloc(sizeof(struct vectors *));

        All_vectors[*sequence_vector-1]->name=malloc(sizeof(char)*(count5-count4));

        for (i = 0; i < count5-count4-1; ++i) {
            All_vectors[*sequence_vector-1]->name[i]=new_vec[i];
        }

        All_vectors[*sequence_vector-1]->name[count5-count4-1]='\0';

        All_vectors[*sequence_vector-1]->length=(atoi(stop)-atoi(start));
        All_vectors[*sequence_vector-1]->data=(int *)malloc(atoi(stop)-atoi(start));

        for (i = 0; i < (atoi(stop)-atoi(start)); ++i) {
            All_vectors[*sequence_vector-1]->data[i]=All_matrices[(findMatrix(mat,sequence_matrice,All_matrices))]->data[atoi(row)][i+atoi(start)];
        }

        *sequence_vector=*sequence_vector+1;
    }
}
void Matslicerow(char line[],int *sequence_vector,int *sequence_matrices,struct vectors **All_vectors,struct matrices **All_matrices){
    int count=12;
    int i;
    while(*(line+count)!=' '){
        count++;
    }
    char *mat=(char *)malloc(sizeof(char)*(count-11));
    for (i = 0; i < (count-12); ++i) {
        mat[i]=line[i+12];
    }
    mat[count-12]='\0';
    int count2=count+1;
    while(*(line+count2)!=' '){
        count2++;
    }
    char *row =(char *) malloc(sizeof(char)*(count2-count));
    for (i = 0; i <(count2-count-1) ; ++i) {
        row[i]=line[count+1+i];
    }
    row[count2-count-1]='\0';
    int count3=count2+1;
    while(*(line+count3)!=' '){
        count3++;
    }
    char *start=(char *)malloc(sizeof(char)*(count3-count2));
    for(i=0;i<(count3-count2-1);++i){
        start[i]=line[count2+1+i];
    }
    start[count3-count2-1]='\0';
    int count4=count3+1;
    while(*(line+count4)!=' '){
        count4++;
    }
    char *stop=(char *)malloc(sizeof(char)*(count4-count3));
    for(i=0;i<(count4-count3-1);++i){
        stop[i]=line[count3+1+i];
    }
    stop[count4-count3-1]='\0';
    int count5=count4+1;
    while(*(line+count5)!='\0'){
        count5++;
    }
    char *new_vec=(char *)malloc(sizeof(char)*(count5-count4));
    for (i = 0;i  <(count5-count4-1) ; ++i) {
        new_vec[i]=line[count4+1+i];
    }
    new_vec[count5-count4-1]='\0';

    int index=findMatrix(mat,sequence_matrices,All_matrices);
    int index2=findVector(new_vec,sequence_vector,All_vectors);
    if (index==-1){
        printf("ERROR-1-MATSLICEROW");
    }
    else if(index2!=-1){
        printf("ERROR-2-MATSLICEROW");
    }
    else if(All_matrices[index]->row<atoi(stop)){
        printf("ERROR-3-MATSLICEROW");
    }
    else if(All_matrices[index]->column<atoi(row)){
        printf("ERROR-4-MATSLICEROW");
    }
    else{

        All_vectors = (struct vectors **) realloc(All_vectors,*sequence_vector);
        All_vectors[*sequence_vector-1]=malloc(sizeof(struct vectors*));
        All_vectors[*sequence_vector-1]->name=(char *)malloc((count5-count4));

        for (i = 0; i < count5-count4-1; ++i) {
            All_vectors[*sequence_vector-1]->name[i]=new_vec[i];
        }

        All_vectors[*sequence_vector-1]->name[count5-count4-1]='\0';
        All_vectors[*sequence_vector-1]->length=(atoi(stop)-atoi(start));

        All_vectors[*sequence_vector-1]->data=(int *)malloc((atoi(stop)-atoi(start)));

        for (i = 0; i < All_vectors[*sequence_vector-1]->length; ++i) {
            All_vectors[*sequence_vector-1]->data[i]=All_matrices[(findMatrix(mat,sequence_matrices,All_matrices))]->data[atoi(row)][i+atoi(start)];
        }
        printf("%s",(All_matrices[0]->name));
        *sequence_vector=*sequence_vector+1;
    }
}
void Matslice(char line[],int *sequence_matrice,struct matrices **All_matrices){
    int count=9;
    int i,j;
    while(*(line+count)!=' '){
        count++;
    }
    char *mat=(char *)malloc(sizeof(char)*(count-8));
    for (i = 0; i < (count-9); ++i) {
        mat[i]=line[i+9];
    }
    mat[count-9]='\0';
    int count2=count+1;
    while(*(line+count2)!=' '){
        count2++;
    }
    char *x1 = (char *)malloc(sizeof(char)*(count2-count));
    for (i = 0; i <(count2-count-1) ; ++i) {
        x1[i]=line[count+1+i];
    }
    x1[count2-count-1]='\0';

    int count3=count2+1;
    while(*(line+count3)!=' '){
        count3++;
    }
    char *x2=(char *)malloc(sizeof(char)*(count3-count2));
    for(i=0;i<(count3-count2-1);++i){
        x2[i]=line[count2+1+i];
    }
    x2[count3-count2-1]='\0';
    int count4=count3+1;
    while(*(line+count4)!=' '){
        count4++;
    }
    char *y1=(char *)malloc(sizeof(char)*(count4-count3));
    for(i=0;i<(count4-count3-1);++i){
        y1[i]=line[count3+1+i];
    }
    y1[count4-count3-1]='\0';
    int count5=count4+1;
    while(*(line+count5)!=' '){
        count5++;
    }
    char*y2=(char *)malloc(sizeof(char)*(count5-count4));
    for (i = 0;i  <(count4-count3-1) ; ++i) {
        y2[i]=line[count4+1+i];
    }
    y2[count5-count4-1]='\0';
    int count6=count5+1;
    while (*(line+count6)!='\0'){
        count6++;
    }
    char *new_name=(char *)malloc(sizeof(char)*(count6-count5));
    for (i = 0; i <(count6-count5-1) ; ++i) {
        new_name[i]=line[count5+1+i];
    }
    new_name[count6-count5-1]='\0';
    int index=findMatrix(mat,sequence_matrice,All_matrices);
    int index2=findMatrix(new_name,sequence_matrice,All_matrices);
    if (index==-1){
        printf("ERROR-1-MATSLICE");
    }
    else if(index2!=-1){
        printf("ERROR-2-MATSLICE");
    }
    else if(All_matrices[index]->row <= atoi(x2)){
        printf("ERROR-3-MATSLICE");
    }
    else if (All_matrices[index]->column <= atoi(y2)){
        printf("ERROR-4-MATSLICE");
    }
    else{
        printf("%s",All_matrices[0]->name);
        All_matrices=(struct matrices **)realloc(All_matrices, *sequence_matrice);

        All_matrices[*sequence_matrice - 1] = (struct matrices *) malloc(sizeof(struct matrices*));

        All_matrices[*sequence_matrice-1]->row=atoi(x2)-atoi(x1);
        All_matrices[*sequence_matrice-1]->column=atoi(y2)-atoi(y1);

        for (i = 0;i  <All_matrices[*sequence_matrice-1]->row ; ++i) {

        }
    }
}
/*[],int *sequence_vector,struct vectors **All_vectors) {
    char *name = "vec1.vec";
    FILE *fileREADER;
    fileREADER = fopen(name, "r++");
    char *Rline[5000];
    char *pch;
    int array[10] = {};
    while (fgets(Rline, sizeof Rline, fileREADER) != NULL) {
        if ((strlen(Rline)) >= (1)) {
            printf("%s", Rline);
            pch = strtok(Rline, " ");
            int i = 0;
            while (pch != NULL) {
                printf("\n%d", atoi(pch));
                array[i] = atoi(pch);
                pch = strtok(NULL, " ");
                i = i + 1;
            }
        }
    }
}*/

int main() {
    int i;
    int sequence_vector = 1;
    int sequence_matrice = 1;
    struct vectors **All_vectors = (struct vectors **) malloc(sizeof(struct vectors *) * (sequence_vector));
    struct matrices **All_matrices = (struct matrices **) malloc(sizeof(struct matrices *) * (sequence_matrice));
    All_vectors[sequence_vector - 1] = (struct vectors *) malloc(sizeof(struct vectors));
    All_matrices[sequence_matrice - 1] = (struct matrices *) malloc(sizeof(struct matrices));
    char line[] = "veczeros vector1 5";
    int counter = 0;
    char *p = strtok(line, " ");
    if (strcmp(p, "veczeros") == 0) {
        char **array = (char **) malloc(sizeof(char *) * 1);
        while (p != NULL) {
            array = realloc(array, counter + 1);
            array[counter++] = p;
            p = strtok(NULL, " ");
            printf("%d--",counter-1);
            printf("%s\n",array[counter-1]);
        }
        if (findVector(array[1],&sequence_vector,All_vectors)!=-1){
            printf("ERROR");
        }
        else{
            All_vectors=(struct vectors **)realloc(All_vectors,sequence_vector);
            All_vectors[sequence_vector-1]=malloc(sizeof(struct vectors *));

            Veczeros("vector2","5",&sequence_vector,&All_vectors[sequence_vector-1]);
            printf("%s\n",All_vectors[0]->name);
            Veczeros(array[1],array[2],&sequence_vector,&All_vectors[sequence_vector-1]);
            printf("%s",All_vectors[1]->name);
        }



    } else if (strcmp(p, "matzeros") == 0) {
        char **array = (char **) malloc(sizeof(char *) * 1);
        while (p != NULL) {
            array = realloc(array, counter + 1);
            array[counter++] = p;
            p = strtok(NULL, " ");
            printf("%d--",counter-1);
            printf("%s\n",array[counter-1]);
        }

        Matzeros(array[1],array[2],array[3],&sequence_matrice,&All_matrices);

    } else if (strcmp(p, "vecread") == 0) {

    } else if (strcmp(p, "matread") == 0) {

    } else if (strcmp(p, "vecstack") == 0) {
        char **array = (char **) malloc(sizeof(char *) * 1);
        while (p != NULL) {
            array = realloc(array, counter + 1);
            array[counter++] = p;
            p = strtok(NULL, " ");
            printf("%d--",counter-1);
            printf("%s\n",array[counter-1]);
        }

    } else if (strcmp(p, "matstack") == 0) {
        Matstack(line, &sequence_matrice, All_matrices);
    } else if (strcmp(p, "mvstack") == 0) {
        Mvstack(line, &sequence_vector, &sequence_matrice, All_vectors, All_matrices);
    } else if (strcmp(p, "pad") == 0) {
        Pad(line, &sequence_matrice, All_matrices);
    } else if (strcmp(p, "padval") == 0) {
        Padval(line, &sequence_matrice, All_matrices);
    } else if (strcmp(p, "vecslice") == 0) {

    } else if (strcmp(p, "matslicecol") == 0) {

    } else if (strcmp(p, "matslicerow") == 0) {

    } else if (strcmp(p, "matslice") == 0) {

    } else if (strcmp(p, "add") == 0) {

    } else if (strcmp(p, "multiply") == 0) {

    } else if (strcmp(p, "subtract") == 0) {

    } else {
        printf("ERROR");
    }
}
