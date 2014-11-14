#include "matrix_properties.h"
#include <stdio.h>
#include <ctype.h>

int rows(struct Matrix * mat){
    return mat->rows;

}

int cols(struct Matrix * mat){
    return mat->cols;
}


int** mallocA_i(int size_r, int size_c){
    int **ip;
	if(!(ip = (int **) malloc(size_r * sizeof(int *)))){
        fprintf(stderr, "Error: malloc failed, out of memory.\n");
        return NULL;
    }

	int i;
    int recover = 0;
	for(i = 0; i < size_r; ++i){
		if(!(ip[i] = malloc(size_c * sizeof(int)))){
            fprintf(stderr, "Error: malloc failed, out of memory.\n");
            recover = 1;
            break;
        }
	}

    //Free anything already allocated
    if(recover){
        for(recover = 0; recover <= i; ++recover){
            free(ip[recover]);
            ip[recover] = NULL;
        }
        free(ip);
        ip = NULL;
    }

    return ip;
}

void freeA_i(int ** ip, int size){
	int i;
	for(i = 0; i < size; ++i){
		free(ip[i]);
	}
	free(ip);
}

struct Matrix * mallocM(){
    struct Matrix * mat;

    mat = malloc(sizeof(struct Matrix));
    return mat;
}

void destroy_matrix(struct Matrix * mat){
    if (mat != NULL) {
        freeA_i(mat->mat,mat->rows);
        free(mat);    
    }
    
}

void print_matrix(struct Matrix * mat){
    int i;
    int j;

    if (mat == NULL)
        return;

    fprintf(stdout,"[");
    for(i = 0; i < mat->rows; ++i){
        for(j = 0; j < mat->cols; ++j){
            fprintf(stdout,"%d ",mat->mat[i][j]);
        }
        if(i < mat->rows -1)
            fprintf(stdout,":");
        else
            fprintf(stdout,"]");
    }
    fprintf(stdout,"\n");
}

struct Matrix  * mat_mult(struct Matrix * m1, struct Matrix * m2){
    if(m1->cols != m2->rows){
        fprintf(stderr, "Error: matrix dimensions do not match.\n");
        return NULL;
    }

    struct Matrix * result = zeroes(m1->rows,m2->cols);
    if(result == NULL){
        return NULL;
    }

    int i,j,k;
    for(i = 0; i < m1->rows; ++i){
        for(k = 0; k < m2->cols; ++k){
            for(j = 0; j < m1->cols; ++j){
                result->mat[i][k] += m1->mat[i][j] * m2->mat[j][k];
            }
        }
    }

    return result;
}

struct Matrix * mat_add(struct Matrix * m1, struct Matrix * m2){
    if(m1 == NULL || m2 == NULL){
        fprintf(stderr, "Error: null pointer sent to mat_add\n");
        return NULL;
    }

    if(m1->rows != m2->rows && m1->cols != m2->cols){
        fprintf(stderr, "Error: matrix dimensions do not match\n");
        return NULL;
    }

    struct Matrix * result = zeroes(m1->rows, m1->cols);
    if(result == NULL){
        return NULL;
    }

    int i,j;


    for(i = 0; i < m1->rows; ++i)
        for(j = 0; j < m1->cols; ++j)
            result->mat[i][j] = m1->mat[i][j] + m2->mat[i][j];

    return result;
}

struct Matrix * init_matrix(char * mat) {
    int rows = 0;
    int cols = 0;

    struct Matrix * m = mallocM();
    

    if(m == NULL){
        fprintf(stderr, "Error: Out of memory in init_matrix()\n");
        return NULL;
    }

    struct TokenNode * matTokens = matrix_tokenize(mat);

    struct TokenNode * walkTokens = matTokens;
    walkTokens=walkTokens->next->next;
    while(strcmp(walkTokens->name,":")){
        ++cols;
        walkTokens=walkTokens->next;
    }
    walkTokens = matTokens;
    while(walkTokens){
        if(walkTokens->type == ROWEND || walkTokens->type == RBRACKET)
            ++rows;

        walkTokens = walkTokens->next;
    }

    m->mat = mallocA_i(rows,cols);
    m->rows = rows;
    m->cols = cols;

    int c = 0;
    int r = 0;

    walkTokens = matTokens;

    for(r = 0;r < rows; ++r){
        for(c = 0;c < cols; ++c){
            while(walkTokens->type != VALUE){
                walkTokens=walkTokens->next;
            }
            if((walkTokens->name)[0] == '-'){
                m->mat[r][c] = -1 * atoi((walkTokens->name + 1));
            }
            else
                m->mat[r][c] = atoi(walkTokens->name);

            
            walkTokens = walkTokens->next;
        }
    }

    return m;


}



struct Matrix * zeroes(int rows, int cols){
    struct Matrix * result = NULL;
    result = mallocM();
    if (result == NULL){
        fprintf(stderr, "Error: Out of Memory during zeroes()\n");
        return result;
    }
    result->rows = rows;
    result->cols = cols;
    result->mat = mallocA_i(result->rows,result->cols);

    if(result->mat == NULL){
        fprintf(stderr, "Error: Out of Memory during zeroes()\n");
        free(result);
        result = NULL;
    } else {
        int i,j;
        for(i = 0; i < rows; ++i)
            for(j = 0; j < cols; ++j)
                result->mat[i][j] = 0;
    }
    
    return result;
    
}
