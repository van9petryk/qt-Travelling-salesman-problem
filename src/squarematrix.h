#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H


class SquareMatrix
{
public:
    SquareMatrix(const int &order = 0);
    ~SquareMatrix();
    double get(const int &row, const int &column) const;
    bool set(const int &row, const int &column, const double &newValue);
    void reorder(const int &newOrder);
    double operator()(const int &row, const int &column) const;
    bool operator()(const int &row, const int &column, const double &newValue);
private:
    int _order;
    double *_array;
};

#endif // SQUAREMATRIX_H
