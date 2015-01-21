#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>
#include <math.h>

#undef minor

class Matrix {

    public:
        explicit Matrix(std::size_t r = 0, std::size_t c = 0);
        explicit Matrix(std::string matrix);
        explicit Matrix(const std::vector<std::vector<double> > & mrhs);

        explicit Matrix(const Matrix & rhs);
        ~Matrix(void);

        Matrix & operator=(const Matrix & rhs);

        std::size_t getRows(void) const;
        std::size_t getCols(void) const;

        double det(void) const;

        double cofactor(std::size_t r, std::size_t c) const;
        double minor(std::size_t r, std::size_t c) const;
        Matrix & adj(const Matrix & rhs) const;

        Matrix & inv(const Matrix & rhs) const;
        
    
        void display(void) const;
        std::string to_str(void) const;

        const std::vector<double> & operator[](std::size_t index) const;
        std::vector<double> & operator[](std::size_t index);

        bool operator==(const Matrix & rhs) const;

        bool operator!=(const Matrix & rhs) const;

        void swap(Matrix & new_matrix);

    private:

        std::vector<std::vector<double> > parseMatrix(const std::string & input) const;
        std::size_t countRows(const std::string & input) const;
        std::size_t countCols(const std::string & input) const;
        double minorRecursive(std::size_t r, std::size_t c, const std::vector<std::vector<double> > & mat) const;
        double cofactorRecursive(std::size_t r, std::size_t c, const std::vector<std::vector<double> > & mat) const;
        double detRecursive(const std::vector<std::vector<double> > & mat) const;

        bool in_range(std::size_t index) const;

        std::size_t rows,cols;
        std::vector<std::vector<double> > m;

};

namespace MatProps {

    Matrix & multiply(const Matrix & lhs, const Matrix & rhs);
    Matrix & multiply(const double slhs, const Matrix & rhs);
    Matrix & multiply(const Matrix & lhs, const double srhs);

    Matrix & divide(const double slhs, const Matrix & rhs);
    Matrix & divide(const Matrix & lhs, const double srhs);

    Matrix & add(const Matrix & lhs, const Matrix & rhs);

    Matrix & operator*(const Matrix & lhs, const Matrix & rhs);
    Matrix & operator*(const double slhs, const Matrix & rhs);
    Matrix & operator*(const Matrix & lhs, const double srhs);

    Matrix & operator/(const double slhs, const Matrix & rhs);
    Matrix & operator/(const Matrix & lhs, const double srhs);

    Matrix & operator+(const Matrix & lhs, const Matrix & rhs);

    void display(const Matrix & matrix);

}

#endif
