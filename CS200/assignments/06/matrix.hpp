/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: matrix.hpp
Purpose: Prototypes for an arbitrary-sized numerical matrix class.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-18
- End Header --------------------------------------------------------*/

/*
 * The matrix is laid out as a flat single-dimensional array in memory.
 *
 * The data type that goes into the matrix must be a numeric type.
 */
#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <iostream>
#include <iterator>

template <int rows = 3, int cols = 3, typename T=int>
class Matrix
{
    public:
        class iterator : public std::iterator<std::forward_iterator_tag, T>
        {
            T* myArray;
            int myStride;
            int myEnd;
            int myIndex;

            public:
                iterator(T* array, int stride, int end, int start_index);
                iterator& operator++();
                T& operator*();
                bool operator==(const iterator &rhs) const;
                bool operator!=(const iterator &rhs) const;
        };

        class const_iterator : public std::iterator<std::forward_iterator_tag, T>
        {
            const T* myArray;
            int myStride;
            int myEnd;
            int myIndex;

            public:
                const_iterator(const T* array, int stride, int end, int start_index);
                const_iterator& operator++();
                const T& operator*() const;
                bool operator==(const const_iterator &rhs) const;
                bool operator!=(const const_iterator &rhs) const;
        };

        // Cons
        Matrix();
        Matrix(const Matrix& rhs);
        Matrix(const T* array);

        ~Matrix() throw();

        void fromArray(const T *array);

        // Operators.
        Matrix& operator=(const Matrix &rhs);

        Matrix& operator+=(const Matrix &rhs);
        Matrix operator+(const Matrix &rhs) const;

        template<int rhs_rows, int rhs_cols>
            Matrix<rows, rhs_cols, T>& operator*=(const Matrix<rhs_rows, rhs_cols, T> &rhs);
        template<int rhs_rows, int rhs_cols>
            Matrix<rows, rhs_cols, T> operator*(const Matrix<rhs_rows, rhs_cols, T> &rhs) const;

        bool operator==(const Matrix &rhs) const;

        //friend std::ostream& operator<<(std::ostream& os, const Matrix &rhs);

        T& operator()(const int& row, const int& col);
        const T& operator()(const int& row, const int& col) const;

        // Iterator stuff.
        iterator begin();
        iterator end();

        const_iterator begin() const;
        const_iterator end() const;

        iterator row_begin(int index);
        iterator row_end(int index);
        iterator col_begin(int index);
        iterator col_end(int index);

        const_iterator row_begin(int index) const;
        const_iterator row_end(int index) const;
        const_iterator col_begin(int index) const;
        const_iterator col_end(int index) const;

        // Math funs.
        T determinant() const;
        T cofactor(int row, int col) const;

        // Information retrieval.
        int getRows() const;
        int getCols() const;

        // Various useful static functions.
        static Matrix Identity();
        static Matrix Zero();

    protected:
        T myMatrix[rows * cols];

    private:
};

template<typename number_type, int rows, int cols, typename T>
Matrix<rows, cols, T> operator*(number_type scalar, const Matrix<rows, cols, T>& matrix);

#include "matrix.cpp"

typedef Matrix<2, 2, float> Mat2;
typedef Matrix<3, 3, float> Mat3;
typedef Matrix<4, 4, float> Mat4;
typedef Matrix<5, 5, float> Mat5;

typedef Matrix<3, 1, float> Vec3;

#endif // MATRIX_H

