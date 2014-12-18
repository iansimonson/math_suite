#ifndef MATRIX_CLASS_H
#define MATRIX_CLASS_H
#include <iostream>
#include <string>
#include <vector>



class Matrix {

    public:
        explicit Matrix(std::size_t r = 0, std::size_t c = 0);
        explicit Matrix(std::string matrix);
        explicit Matrix(const Matrix & rhs);
        ~Matrix(void);

        Matrix & operator=(const Matrix & rhs);

        std::size_t getRows(void) const;
        std::size_t getCols(void) const;

        double det(const Matrix & rhs) const;

        const Matrix & cofactor(int r, int c);
        const Matrix & minor(int r, int c);
        const Matrix & adj(const Matrix & rhs);

        const Matrix & inv(const Matrix & rhs);
        
    
        void display(void) const;

        const std::vector<double> & operator[](std::size_t index) const;
        std::vector<double> & operator[](std::size_t index);

        bool operator==(const Matrix & rhs) const;

        bool operator!=(const Matrix & rhs) const;

        void swap(Matrix & new_matrix);

    private:

        bool in_range(std::size_t index) const;

        std::size_t rows,cols;
        std::vector<std::vector<double> > m;

};

namespace MatProps {

    Matrix & multiply(const Matrix & lhs, const Matrix & rhs);
    Matrix & multiply(const double slhs, const Matrix & rhs);
    Matrix & multiply(const Matrix & lhs, const double srhs);

    Matrix & add(const Matrix & lhs, const Matrix & rhs);

    Matrix & operator*(const Matrix & lhs, const Matrix & rhs);
    Matrix & operator*(const double slhs, const Matrix & rhs);
    Matrix & operator*(const Matrix & lhs, const double srhs);

    Matrix & operator+(const Matrix & lhs, const Matrix & rhs);

}

#endif
