#include "matrix.h"
using namespace std;

Matrix::Matrix(std::size_t r , std::size_t c):rows(r),cols(c),m(rows){

    for(int i = 0; i < m.size(); ++i){
        m[i].resize(cols);
    }
    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            m[i][j] = 0;
        }
    }
}

Matrix::Matrix(std::string matrix){

}

Matrix::Matrix(const Matrix & rhs):rows(rhs.rows),cols(rhs.cols),m(rhs.rows) {
   
    for(int i = 0; i < m.size();++i){
        m[i].resize(cols);
    }

    for(int i = 0; i < rows; ++i){
        for(int j = 0; j < cols; ++j){
            m[i][j] = rhs.m[i][j];
        }
    }
    
}

Matrix::~Matrix(){
}

void Matrix::swap(Matrix & new_matrix) {
    std::swap(rows, new_matrix.rows);
    std::swap(cols, new_matrix.cols);

    m.resize(rows);
    for(std::size_t i = 0; i < rows; ++i){
        m[i].resize(cols);
        for(std::size_t j = 0; j < cols; ++j){
            m[i][j] = new_matrix.m[i][j];
        }
    }
}

std::size_t Matrix::getRows() const{
    return rows;
}

std::size_t Matrix::getCols() const{
    return cols;
}


void Matrix::display(void) const {
    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}




const std::vector<double> & Matrix::operator[](std::size_t index) const{
    //if(in_range(index))
    return this->m[index];
}

std::vector<double> & Matrix::operator[](std::size_t index){
    return const_cast<std::vector<double> &>(static_cast<const Matrix &>(*this)[index]);
}

Matrix & Matrix::operator=(const Matrix & rhs){
    if(this != &rhs){
        Matrix tmp(rhs);
        swap(tmp);
    }
    return *this;
}

Matrix & MatProps::multiply(const Matrix & lhs, const Matrix & rhs){
    Matrix * tmp = new Matrix(lhs.getRows(), rhs.getCols());
    double el;

    for(int i = 0; i < tmp->getRows(); ++i){
        for(int k = 0; k < rhs.getCols(); ++k){
            el = 0;
            for(int j = 0; j < rhs.getRows(); ++j){
                el += lhs[i][j] * rhs[j][k];
            }
            (*tmp)[i][k] = el;
        }
    }

    return *tmp;
}


Matrix & MatProps::multiply(const double slhs, const Matrix & rhs){
    Matrix * tmp = new Matrix(rhs);

    for(int i = 0; i < tmp->getRows(); ++i){
        for(int j = 0; j < tmp->getCols(); ++j){
            (*tmp)[i][j] *= slhs;
        }
    }

    return *tmp;


}

Matrix & MatProps::multiply(const Matrix & lhs, const double srhs){

    Matrix * tmp = new Matrix(lhs);

    for(int i = 0; i < tmp->getRows(); ++i){
        for(int j = 0; j < tmp->getCols(); ++j){
            (*tmp)[i][j] *= srhs;
        }
    }

    return *tmp;
}

Matrix & MatProps::add(const Matrix & lhs, const Matrix & rhs){
    Matrix * tmp = new Matrix(lhs);

    for(int i = 0; i < tmp->getRows(); ++i){
        for(int j = 0; j < tmp->getCols(); ++j){
            (*tmp)[i][j] += rhs[i][j];
        }
    }

    return *tmp;
}

Matrix & MatProps::operator*(const Matrix & lhs, const Matrix & rhs){
    return MatProps::multiply(lhs,rhs);
}

Matrix & MatProps::operator*(const double slhs, const Matrix & rhs){
    return MatProps::multiply(slhs,rhs);
}

Matrix & MatProps::operator*(const Matrix & lhs, const double srhs){
    return MatProps::multiply(lhs,srhs);
}

Matrix & MatProps::operator+(const Matrix & lhs, const Matrix & rhs){
    return MatProps::add(lhs,rhs);
}
