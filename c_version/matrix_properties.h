#ifndef MATRIX_PROPERTIES_H
#define MATRIX_PROPERTIES_H

#include <stdio.h>
#include <stdlib.h>
#include "matrix_tokenizer.h"

struct Matrix {
	int ** mat;
	int rows,cols;
};

struct ParseNode {
	int val;
	struct ParseNode * next;
};


//Helper Methods for initializing a matrix
int** mallocA_i(int size_r,int size_c);
struct Matrix * mallocM();
void freeA_i(int **ip, int size);

//Constructor and Destructor
struct Matrix * zeroes(int rows, int cols);
struct Matrix * init_matrix(char * mat);
void destroy_matrix(struct Matrix * m1);

//Operations performed on a matrix
void print_matrix(struct Matrix * mat);
struct Matrix * mat_mult(struct Matrix * m1, struct Matrix * m2);
struct Matrix * mat_add(struct Matrix * m1, struct Matrix * m2);
struct Matrix * scalar_mult(struct Matrix * m, int s);

//Get parameters of the matrix
int getRows(struct Matrix* mat);
int getCols(struct Matrix* mat);

#endif
