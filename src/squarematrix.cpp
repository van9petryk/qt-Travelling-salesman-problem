#include "squarematrix.h"

SquareMatrix::SquareMatrix(const int &order)
{
    _order = order;
    if (_order < 1)
        _array = 0;
    else
        _array = new double[order * order];
}

SquareMatrix::~SquareMatrix()
{
    delete [] _array;
}

double SquareMatrix::get(const int &row, const int &column) const
{
    if (row < 0 || column < 0 || row >= _order || column >= _order)
        return -1.0;
    return _array[row * _order + column];
}

bool SquareMatrix::set(const int &row, const int &column, const double &newValue)
{
    if (row < 0 || column < 0 || row >= _order || column >= _order)
        return false;
    _array[row * _order + column] = newValue;
    return true;
}

void SquareMatrix::reorder(const int &newOrder)
{
    delete [] _array;
    _order = newOrder;
    if (_order < 1)
        _array = 0;
    else
        _array = new double[newOrder * newOrder];
}

double SquareMatrix::operator()(const int &row, const int &column) const
{
    return get(row, column);
}

bool SquareMatrix::operator()(const int &row, const int &column, const double &newValue)
{
    return set(row, column, newValue);
}
