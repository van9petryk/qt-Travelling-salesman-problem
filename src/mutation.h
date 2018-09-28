#ifndef MUTATION_H
#define MUTATION_H

#include <QList>
#include <QPair>
#include "random.h"
class Mutation
{
public:
    Mutation();
    void inversion(QList <int> &chromosome);
    void reciprocalExchange(QList <int> &chromosome);
    void insertion(QList <int> &chromosome);
};

#endif // MUTATION_H
