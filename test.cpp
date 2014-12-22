#include <iostream>
#include <math.h>
#include "matrix.h"
using namespace MatProps;

int main() {

	std::cout << pow((-1),3) << std::endl;
    Matrix mat(3,3);

    for(std::size_t i = 0; i < mat.getRows(); ++i){
        for(std::size_t j = 0; j < mat.getCols(); ++j){
            mat[i][j] = i+j;
        }
    }
    display(mat);



    Matrix mat2(3,3);
    mat2 = mat2 + mat;

    display(mat2);

    mat2 * 2;
    display(mat2);

    mat2 = mat2 * 2;

    display(mat2);

    (mat * 5).display();

    Matrix mat3("[1.0 2.5 3.0:1.1 2.3 3.4:1.1 2.5 3.3]");
    display(mat3);

    Matrix mat4("[-1 -2 -3:-1 -2 -3:-1 -2 -3]");

    mat4 = mat4 * mat3;
    display(mat4);

    mat4 = mat4/3;
    display(mat4);

    Matrix mat5("[1 0 0:0 1 0:0 0 1]");
    display(mat5);
    std::cout << mat5.det() << std::endl;
    

    return 0;
}
