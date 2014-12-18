#include <iostream>
#include "matrix.h"
using namespace MatProps;

int main() {
    Matrix mat(3,3);

    for(std::size_t i = 0; i < mat.getRows(); ++i){
        for(std::size_t j = 0; j < mat.getCols(); ++j){
            mat[i][j] = i+j;
        }
    }
    mat.display();
    std::cout << std::endl;

    Matrix mat2(3,3);
    mat2 = mat2 + mat;

    mat2.display();
    std::cout << std::endl;

    mat2 * 2;
    mat2.display();
    std::cout << std::endl;

    mat2 = mat2 * 2;

    mat2.display();
    std::cout << std::endl;

    (mat * 5).display();
    

    return 0;
}
