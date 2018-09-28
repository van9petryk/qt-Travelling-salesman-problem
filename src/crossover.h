#ifndef CROSSOVER_H
#define CROSSOVER_H

#include <QList>
#include <QPair>
#include <QMap>
#include "random.h"
class Crossover
{
public:
    Crossover();
    QPair <QList <int>, QList <int> > order(const QPair <QList <int>, QList <int> > &parent);
    QPair <QList <int>, QList <int> > partiallyMapped(const QPair <QList <int>, QList <int> > &parent);
    QPair <QList <int>, QList <int> > cycle(const QPair <QList <int>, QList <int> > &parent);
    QPair <QList <int>, QList <int> > edgeRecombination(const QPair <QList <int>, QList <int> > &parent);
private:
    QSet <int> findNeighbors(const int &neighborsOf, const QList <int> &chromosome);
    QList <int> childEdgeRecombination(const QMap <int, QSet <int> > &neighbors, const int &firstNode);
};

#endif // CROSSOVER_H
