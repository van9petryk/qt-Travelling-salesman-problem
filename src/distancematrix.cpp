#include "distancematrix.h"

DistanceMatrix::DistanceMatrix(const QList<QVector2D> &cityLocation) : SquareMatrix(cityLocation.size())
{
    int numberCities = cityLocation.size();
    for (int i = 0; i < numberCities; i++)
        for (int j = 0; j < numberCities; j++)
            set(i, j, cityLocation.at(i).distanceToPoint(cityLocation.at(j)));
}

void DistanceMatrix::updateBy(const QList<QVector2D> &cityLocation)
{
    int numberCities = cityLocation.size();
    reorder(numberCities);
    for (int i = 0; i < numberCities; i++)
        for (int j = 0; j < numberCities; j++)
            set(i, j, cityLocation.at(i).distanceToPoint(cityLocation.at(j)));
}

double DistanceMatrix::operator()(const int &row, const int &column) const
{
    return get(row, column);
}
