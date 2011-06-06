/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of
DigiPen Institute of Technology is prohibited.

File Name: matrix.cpp
Purpose: Implementation of an arbitrary-sized numerical matrix class.
Language: C++ (MSVC, G++)
Platform: Windows, Linux
Project: marcus.meng_cs200_1
Author: Marcus Meng (marcus.meng) 80002709
Creation date: 2011-05-18
- End Header --------------------------------------------------------*/

//#include "matrix.hpp"

#include <numeric>

/*****************************************************************************
 * Cons
 */
template<int rows, int cols, typename T>
Matrix<rows, cols, T>::Matrix()
{
    for (int i = 0; i < rows * cols; ++i)
    {
        myMatrix[i] = 0;
    }
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T>::Matrix(const Matrix& rhs)
{
    fromArray(rhs.myMatrix);
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T>::Matrix(const T* array)
{
    fromArray(array);
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T>::~Matrix() throw()
{
}

template<int rows, int cols, typename T>
void Matrix<rows, cols, T>::fromArray(const T *array)
{
    for (int i = 0; i < rows * cols; ++i)
    {
        myMatrix[i] = array[i];
    }
}

/*****************************************************************************
 * Operators.
 */
template<int rows, int cols, typename T>
Matrix<rows, cols, T>& Matrix<rows, cols, T>::operator=(const Matrix<rows, cols, T> &rhs)
{
    if (&rhs == this)
        return(*this);

    fromArray(rhs.myMatrix);
    return(*this);
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T>& Matrix<rows, cols, T>::operator+=(const Matrix<rows, cols, T> &rhs)
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            (*this)(i, j) += rhs(i, j);
        }
    }

    return(*this);
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator+(const Matrix<rows, cols, T> &rhs) const
{
    Matrix to_return(*this);

    to_return += rhs;

    return(to_return);
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T>& Matrix<rows, cols, T>::operator*=(const Matrix<rows, cols, T> &rhs)
{
    (*this) = (*this) * rhs;

    return(*this);
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::operator*(const Matrix<rows, cols, T> &rhs) const
{
    Matrix<rows, cols, T> to_return;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            to_return(i, j) = std::inner_product(row_begin(i), row_end(i), rhs.col_begin(j), T(0));
        }
    }

    return(to_return);
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T> operator*(int scalar, const Matrix<rows, cols, T>& matrix)
{
    Matrix<rows, cols, T> to_return = matrix;
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            to_return(i, j) *= scalar;
        }
    }

    return(to_return);
}

template<int rows, int cols, typename T>
bool Matrix<rows, cols, T>::operator==(const Matrix& rhs) const
{
    for (int i = 0; i < rows * cols; ++i)
    {
        if (myMatrix[i] != rhs.myMatrix[i])
            return(false);
    }
    return(true);
}

template<int rows, int cols, typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<rows, cols, T> &rhs)
{
    os << '[';
    for (int i = 0; i < rhs.getRows(); ++i)
    {
        os << "[ ";
        for (int j = 0; j < rhs.getCols(); ++j)
        {
            os << rhs(i, j) << ' ';
        }
        os << "]";
    }
    os << ']';

    return(os);
}

template<int rows, int cols, typename T>
T& Matrix<rows, cols, T>::operator()(const int& row, const int& col)
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        throw(std::out_of_range("Provided row or column out of bounds."));
    }
    return(myMatrix[cols * row + col]);
}

template<int rows, int cols, typename T>
const T& Matrix<rows, cols, T>::operator()(const int& row, const int& col) const
{
    if (row < 0 || row >= rows || col < 0 || col >= cols)
    {
        throw(std::out_of_range("Provided row or column out of bounds."));
    }
    return(myMatrix[cols * row + col]);
}

/*****************************************************************************
 * Math functions.
 */

// TODO: this only works for 3x3 right now!
template<int rows, int cols, typename T>
T Matrix<rows, cols, T>::determinant() const
{
    if (rows != cols)
    {
        // Makes no sense! Abort!
        throw(std::domain_error("Determinant for nonsquare matrix is undefined."));
    }

    return((*this)(0, 0) * cofactor(0, 0) +
            (*this)(0, 1) * cofactor(0, 1) +
            (*this)(0, 2) * cofactor(0, 2));
}

// TODO: this only works for 3x3 right now!
template<int rows, int cols, typename T>
T Matrix<rows, cols, T>::cofactor(int row, int col) const
{
    int factors[4];
    int* current = factors;
    for (int i = 0; i < rows; ++i)
    {
        if (i == row)
            continue;

        for (int j = 0; j < cols; ++j)
        {
            if (j == col)
                continue;

            *current = (*this)(i, j);
            ++current;
        }
    }

    int sign;

    if ((row + col) % 2 == 0)
    {
        sign = 1;
    }
    else
    {
        sign = -1;
    }

    return(sign * (factors[0] * factors[3] - factors[2] * factors[1]));
}

/*****************************************************************************
 * Info functions.
 */
template<int rows, int cols, typename T>
int Matrix<rows, cols, T>::getRows() const
{
    return(rows);
}

template<int rows, int cols, typename T>
int Matrix<rows, cols, T>::getCols() const
{
    return(cols);
}

/*****************************************************************************
 * Static functions.
 */
template<int rows, int cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::Identity()
{
    Matrix to_return;
    for (int i = 0; i < rows; ++i)
    {
        to_return(i, i) = 1;
    }

    return(to_return);
}

template<int rows, int cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::Zero()
{
    // Default constructor creates zero matrix.
    return(Matrix());
}

/*****************************************************************************
 * Iterators.
 *
 * For now, we are treating "ending iterator" as "end of entire array",
 * instead of just the individual row or column, hmm.
 */

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::iterator Matrix<rows, cols, T>::begin()
{
    return(iterator(myMatrix, 1, rows * cols, 0));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::iterator Matrix<rows, cols, T>::end()
{
    return(iterator(myMatrix, 1, rows * cols, rows * cols));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::const_iterator Matrix<rows, cols, T>::begin() const
{
    return(const_iterator(myMatrix, 1, rows * cols, 0));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::const_iterator Matrix<rows, cols, T>::end() const
{
    return(const_iterator(myMatrix, 1, rows * cols, rows * cols));
}

// Normal iterator.
template<int rows, int cols, typename T>
Matrix<rows, cols, T>::iterator::iterator(T* array, int stride, int end, int start_index)
    :myArray(array), myStride(stride), myEnd(end), myIndex(start_index)
{
}

template<int rows, int cols, typename T>
bool Matrix<rows, cols, T>::iterator::operator==(const iterator &rhs) const
{
    if (myArray == rhs.myArray && myIndex == rhs.myIndex && myStride == rhs.myStride)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

template<int rows, int cols, typename T>
bool Matrix<rows, cols, T>::iterator::operator!=(const iterator &rhs) const
{
    return(!((*this) == rhs));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::iterator& Matrix<rows, cols, T>::iterator::operator++()
{
    myIndex += myStride;

    if (myIndex > myEnd)
    {
        myIndex = myEnd;
    }

    return(*this);
}

template<int rows, int cols, typename T>
T& Matrix<rows, cols, T>::iterator::operator*()
{
    return(myArray[myIndex]);
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::iterator Matrix<rows, cols, T>::row_begin(int index)
{
    return(Matrix<rows, cols, T>::iterator(myMatrix, 1, (index + 1) * cols, index * cols));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::iterator Matrix<rows, cols, T>::row_end(int index)
{
    return(Matrix<rows, cols, T>::iterator(myMatrix, 1, (index + 1) * cols, (index + 1) * cols));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::iterator Matrix<rows, cols, T>::col_begin(int index)
{
    return(Matrix<rows, cols, T>::iterator(myMatrix, cols, index + ((rows - 1) * cols), index));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::iterator Matrix<rows, cols, T>::col_end(int index)
{
    return(Matrix<rows, cols, T>::iterator(myMatrix, cols, index + ((rows - 1) * cols), index + ((rows - 1) * cols)));
}

// Const iterator.
template<int rows, int cols, typename T>
Matrix<rows, cols, T>::const_iterator::const_iterator(const T* array, int stride, int end, int start_index)
    :myArray(array), myStride(stride), myEnd(end), myIndex(start_index)
{
}

template<int rows, int cols, typename T>
bool Matrix<rows, cols, T>::const_iterator::operator==(const const_iterator &rhs) const
{
    if (myArray == rhs.myArray && myIndex == rhs.myIndex && myStride == rhs.myStride)
    {
        return(true);
    }
    else
    {
        return(false);
    }
}

template<int rows, int cols, typename T>
bool Matrix<rows, cols, T>::const_iterator::operator!=(const const_iterator &rhs) const
{
    return(!((*this) == rhs));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::const_iterator& Matrix<rows, cols, T>::const_iterator::operator++()
{
    myIndex += myStride;

    if (myIndex > myEnd)
    {
        myIndex = myEnd;
    }

    return(*this);
}

template<int rows, int cols, typename T>
const T& Matrix<rows, cols, T>::const_iterator::operator*() const
{
    return(myArray[myIndex]);
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::const_iterator Matrix<rows, cols, T>::row_begin(int index) const
{
    return(Matrix<rows, cols, T>::const_iterator(myMatrix, 1, (index + 1) * cols, index * cols));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::const_iterator Matrix<rows, cols, T>::row_end(int index) const
{
    return(Matrix<rows, cols, T>::const_iterator(myMatrix, 1, (index + 1) * cols, (index + 1) * cols));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::const_iterator Matrix<rows, cols, T>::col_begin(int index) const
{
    return(Matrix<rows, cols, T>::const_iterator(myMatrix, cols, index + ((rows - 1) * cols), index));
}

template<int rows, int cols, typename T>
typename Matrix<rows, cols, T>::const_iterator Matrix<rows, cols, T>::col_end(int index) const
{
    return(Matrix<rows, cols, T>::const_iterator(myMatrix, cols, index + ((rows - 1) * cols), index + ((rows - 1) * cols)));
}

