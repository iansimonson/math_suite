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

Matrix::Matrix(std::string matrix):rows(0),cols(0),m(){
    m = parseMatrix(matrix);
    rows = m.size();
    cols = m[0].size();
}

Matrix::Matrix(const std::vector<std::vector<double> > & mrhs):rows(mrhs.size()),cols(0),m(mrhs){
    if(rows != 0){
        cols = m[0].size();
    }
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

    std::vector<std::vector<double> > tmp = m;
    m = new_matrix.m;
    new_matrix.m = tmp;
}

std::vector<std::vector<double> > Matrix::parseMatrix(const std::string & input) const{

    std::vector<std::vector<double> > * tmp;
    std::size_t r = countRows(input);
    std::size_t c = countCols(input);

    //Create the matrix of size rxc
    tmp = new std::vector<std::vector<double> >(r);
    for(std::size_t i = 0; i < tmp->size(); ++i){
        (*tmp)[i].resize(c);
    }

    int state = 0;
    double curEl = 0.0;
    int mult = 1;
    std::size_t rr = 0, cc = 0;
    std::size_t pos = 0;

    while(pos != input.size()){
        if(state == 0){
            if(input[pos] == '['){
                ++pos;
                rr = 0;
                cc = 0;
                state = 1;
            } else {
                ++pos;
                continue;
            }
        } else if(state == 1){
            mult = 1;
            if(isdigit(input[pos])){
                state = 2;
            } else if(input[pos] == '-'){
                mult = -1;
                state = 2;
                ++pos;
            } else {
                ++pos;
            }
        } else if(state == 2){
            std::size_t iend = input.find_first_of(" :]",pos);
            curEl = mult * std::stod(input.substr(pos,iend));
            (*tmp)[rr][cc] = curEl;
            
            char c = input[iend];
            pos = iend;
            while(c == ' '){
                ++pos;
                c = input[pos];
            }
            ++cc;

            if(c == ':'){
                ++rr;
                cc = 0;
            } else if(c == ']'){
                break;
            }
            state = 1;
        }
    }

    return *tmp;


}

std::size_t Matrix::countRows(const std::string & input) const {
    std::size_t r = 0;
    std::size_t pos = 0;


    while(pos != input.size()){
        pos = input.find_first_of(":]",pos);
        if(pos != std::string::npos){
            ++r;
            ++pos;
        }
    }

    return r;
}

std::size_t Matrix::countCols(const std::string & input) const {
    std::size_t c = 0;
    std::size_t pos = 0;


    while(pos != input.size()){
        if((pos = input.find_first_of("0123456789:",pos)) != input.size()){
            if(input[pos] == ':'){
                break;
            } else {
                ++c;
                pos = input.find_first_of(" :",pos);
                if(input[pos] == ':'){
                    break;
                }
                ++pos;
            }
        }
    }

    return c;
}

std::size_t Matrix::getRows() const{
    return rows;
}

std::size_t Matrix::getCols() const{
    return cols;
}

double Matrix::det(void) const{
    double det = 0.0;
    for(std::size_t i = 0; i < rows; ++i){
        det += m[i][0] * this->cofactor(i,0);
    }

    return det;
}

double Matrix::cofactor(std::size_t r, std::size_t c) const {
    return pow((-1),(r+c)) * this->minor(r,c);
}

double Matrix::minor(std::size_t r, std::size_t c) const {
    this->minorRecursive(r,c,m);
}


double Matrix::detRecursive(const std::vector<std::vector<double> > & mat) const {
    double det = 0.0;
    for(std::size_t i = 0; i < mat.size(); ++i){
        det += mat[i][0] * this->cofactorRecursive(i,0, mat);
    }

    return det;
}

double Matrix::cofactorRecursive(std::size_t r, std::size_t c, const std::vector<std::vector<double> > & mat) const {
    return pow((-1),(r+c)) * this->minorRecursive(r,c,mat);
}

double Matrix::minorRecursive(std::size_t r, std::size_t c, const std::vector<std::vector<double> > & mat) const {
    if(mat.size() == 1)
        return mat[0][0];

    std::vector<std::vector<double> > * tmp = new std::vector<std::vector<double> >(mat.size() - 1);
    for(std::size_t i = 0; i < mat.size() - 1; ++i){
        (*tmp)[i].resize(mat[0].size() - 1);
    }

    for(std::size_t i = 0; i < mat.size() -1; ++i){
        for(std::size_t j = 0; i < mat[0].size() -1; ++i){
            (*tmp)[i][j] = mat[(i >= r) ? i+1 : i][(j >= c) ? j+1 : j];
        } 
    }

    return this->detRecursive(*tmp);
}


void Matrix::display(void) const {
    std::cout << std::endl;
    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            std::cout << m[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::string Matrix::to_str(void) const {
    std::stringstream ss;
    ss << "[";
    for(std::size_t i = 0; i < rows; ++i){
        for(std::size_t j = 0; j < cols; ++j){
            ss << m[i][j] << " ";
        }
        if(i+1 != rows){ss << ":";}
    }
    ss << "]";
    return ss.str();
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



Matrix & MatProps::divide(const double slhs, const Matrix & rhs){
    return MatProps::multiply(1.0/slhs, rhs);
}
Matrix & MatProps::divide(const Matrix & lhs, const double srhs){
    return MatProps::multiply(lhs, 1.0/srhs);
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

Matrix & MatProps::operator/(const double slhs, const Matrix & rhs){
    return MatProps::divide(slhs,rhs);
}

Matrix & MatProps::operator/(const Matrix & lhs, const double srhs){
    return MatProps::divide(lhs,srhs);
}

Matrix & MatProps::operator+(const Matrix & lhs, const Matrix & rhs){
    return MatProps::add(lhs,rhs);
}


void MatProps::display(const Matrix & matrix){
    matrix.display();
}