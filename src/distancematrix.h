#ifndef DISTANCEMATRIX_H
#define DISTANCEMATRIX_H

#include "squarematrix.h"
#include <QList>
#include <QVector2D>

class DistanceMatrix : private SquareMatrix
{
public:
    DistanceMatrix(const QList <QVector2D> &cityLocation = QList <QVector2D> ());
    void updateBy(const QList <QVector2D> &cityLocation);
    double operator()(const int &row, const int &column) const;
};

#endif // DISTANCEMATRIX_H
