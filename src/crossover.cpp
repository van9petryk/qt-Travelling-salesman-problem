#include "crossover.h"
#include <QDebug>
Crossover::Crossover()
{

}

QPair<QList<int>, QList<int> > Crossover::order(const QPair<QList<int>, QList<int> > &parent)
{
    int size = parent.first.size();

    QPair <int, int> crossoverPoint = Random::random(1, size - 2, Random::REPEAT_NO, Random::ORDER_ASC);
    int sizeSequence = crossoverPoint.first + size - crossoverPoint.second;
    int sizeSubSequence = crossoverPoint.second - crossoverPoint.first;

    QPair <QList <int>, QList <int> > subSequence, sequence;
    subSequence.first = parent.first.mid(crossoverPoint.first, sizeSubSequence);
    subSequence.second = parent.second.mid(crossoverPoint.first, sizeSubSequence);
    sequence.first = parent.first.mid(crossoverPoint.second) + parent.first.mid(0, crossoverPoint.second);
    sequence.second = parent.second.mid(crossoverPoint.second) + parent.second.mid(0, crossoverPoint.second);

    for (int i = 0; i < sizeSubSequence; i++){
        sequence.first.removeOne(subSequence.second.at(i));
        sequence.second.removeOne(subSequence.first.at(i));
    }

    QPair <QList <int>, QList <int> > offspring;
    int midPoint = sizeSequence - crossoverPoint.first;
    offspring.first = sequence.first.mid(midPoint) + subSequence.second + sequence.first.mid(0, midPoint);
    offspring.second = sequence.second.mid(midPoint) + subSequence.first + sequence.second.mid(0, midPoint);

    return offspring;
}

QPair<QList<int>, QList<int> > Crossover::partiallyMapped(const QPair<QList<int>, QList<int> > &parent)
{
    int size = parent.first.size();

    QPair <int, int> crossoverPoint = Random::random(1, size - 2, Random::REPEAT_NO, Random::ORDER_ASC);
    int sizeSequence = crossoverPoint.first + size - crossoverPoint.second;
    int sizeSubSequence = crossoverPoint.second - crossoverPoint.first;

    QPair <QList <int>, QList <int> > subSequence, sequence;
    subSequence.first = parent.first.mid(crossoverPoint.first, sizeSubSequence);
    subSequence.second = parent.second.mid(crossoverPoint.first, sizeSubSequence);
    sequence.first = parent.first.mid(0, crossoverPoint.first) + parent.first.mid(crossoverPoint.second);
    sequence.second = parent.second.mid(0, crossoverPoint.first) + parent.second.mid(crossoverPoint.second);

    if (sizeSequence > sizeSubSequence){
        for (int i = 0, idxReplace, idxRepeat, valueToReplace; i < sizeSubSequence; i++){
            if ((idxReplace = sequence.first.indexOf(subSequence.second.at(i))) != -1){
                valueToReplace = subSequence.first.at(i);
                sequence.first.replace(idxReplace, valueToReplace);
                while ((idxRepeat = subSequence.second.indexOf(valueToReplace)) != -1){
                    valueToReplace = subSequence.first.at(idxRepeat);
                    sequence.first.replace(idxReplace, valueToReplace);
                }
            }

            if ((idxReplace = sequence.second.indexOf(subSequence.first.at(i))) != -1){
                valueToReplace = subSequence.second.at(i);
                sequence.second.replace(idxReplace, valueToReplace);
                while ((idxRepeat = subSequence.first.indexOf(valueToReplace)) != -1){
                    valueToReplace = subSequence.second.at(idxRepeat);
                    sequence.second.replace(idxReplace, valueToReplace);
                }
            }
        }
    }
    else {
        for (int i = 0, idxValue, valueToReplace; i < sizeSequence; i++){
            while ((idxValue = subSequence.second.indexOf(sequence.first.at(i))) != -1){
                valueToReplace = subSequence.first.at(idxValue);
                sequence.first.replace(i, valueToReplace);
            }
            while ((idxValue = subSequence.first.indexOf(sequence.second.at(i))) != -1){
                valueToReplace = subSequence.second.at(idxValue);
                sequence.second.replace(i, valueToReplace);
            }
        }
    }

    QPair <QList <int>, QList <int> > offspring;
    int midPoint = crossoverPoint.first;
    offspring.first = sequence.first.mid(0, midPoint) + subSequence.second + sequence.first.mid(midPoint);
    offspring.second = sequence.second.mid(0, midPoint) + subSequence.first + sequence.second.mid(midPoint);

    return offspring;
}

QPair<QList<int>, QList<int> > Crossover::cycle(const QPair<QList<int>, QList<int> > &parent)
{
    int size = parent.first.size();
    QList <int> cyclePosition;
    int idx = 0;
    do {
        cyclePosition << idx;
        int value = parent.first.at(idx);
        idx = parent.second.indexOf(value);
    } while(idx != 0);

    QPair <QList <int>, QList <int> > offspring;
    for (int i = 0; i < size; i++){
        if (cyclePosition.contains(i)){
            offspring.first << parent.first.at(i);
            offspring.second << parent.second.at(i);
        }
        else {
            offspring.first << parent.second.at(i);
            offspring.second << parent.first.at(i);
        }
    }

    return offspring;
}

QPair<QList<int>, QList<int> > Crossover::edgeRecombination(const QPair<QList<int>, QList<int> > &parent)
{
    int size = parent.first.size();
    QMap <int, QSet <int> > neighbors;

    QSet <int> neighbor;
    int key;

    key = parent.first.first();
    neighbor = findNeighbors(key, parent.second);
    neighbor << parent.first.last() << parent.first.at(1);
    neighbors.insert(key, neighbor);
    for (int i = 1; i < size - 1; i++){
        key = parent.first.at(i);
        neighbor = findNeighbors(key, parent.second);
        neighbor << parent.first.at(i - 1) << parent.first.at(i + 1);
        neighbors.insert(key, neighbor);
    }

    key = parent.first.last();
    neighbor = findNeighbors(key, parent.second);
    neighbor << parent.first.at(size - 2) << parent.first.first();
    neighbors.insert(key, neighbor);

    QPair <QList <int>, QList <int> > offspring;
    offspring.first = childEdgeRecombination(neighbors, parent.first.first());
    offspring.second = childEdgeRecombination(neighbors, parent.second.first());

    return offspring;
}

QSet<int> Crossover::findNeighbors(const int &neighborsOf, const QList<int> &chromosome)
{
    QSet <int> neighbor;
    int idx = chromosome.indexOf(neighborsOf);
    if (idx == -1)
        return neighbor;
    if (idx != 0 && idx != chromosome.size() - 1){
        neighbor << chromosome.at(idx - 1);
        neighbor << chromosome.at(idx + 1);
    }
    else if (idx == 0){
        neighbor << chromosome.last();
        neighbor << chromosome.at(1);
    }
    else {
        neighbor << chromosome.first();
        neighbor << chromosome.at(chromosome.size() - 2);
    }
    return neighbor;
}

QList<int> Crossover::childEdgeRecombination(const QMap<int, QSet<int> > &neighbors, const int &firstNode)
{
    int size = neighbors.size();
    QMap <int, QSet <int> > _neighbors = neighbors;
    QList <int> child;
    int node = firstNode;
    child << node;
    while (child.size() < size){
        const QSet <int> &neighbor = _neighbors.value(node);
        for (QSet <int>::const_iterator it = neighbor.constBegin(); it != neighbor.constEnd(); it++)
            _neighbors[*it].remove(node);
        if (neighbor.size() > 0){
            QList <int> fewestNeighbors;
            fewestNeighbors << *neighbor.constBegin();
            for (QSet <int>::const_iterator it = neighbor.constBegin() + 1; it != neighbor.constEnd(); it++){
                int _last = fewestNeighbors.last();
                int _lastSize = _neighbors.value(_last).size();
                int _nextSize = _neighbors.value(*it).size();
                if (_lastSize > _nextSize){
                    fewestNeighbors.removeLast();
                    fewestNeighbors << *it;
                }
                else if (_lastSize == _nextSize)
                    fewestNeighbors << *it;
            }
            _neighbors.remove(node); //after this line, ref(neighbor) mustn't be called
            if (fewestNeighbors.size() == 1)
                node = fewestNeighbors.first();
            else {
                int idxNode = Random::random(0, fewestNeighbors.size() - 1);
                node = fewestNeighbors.at(idxNode);
            }
            child << node;
        }
        else {
            _neighbors.remove(node); //after this line, ref(neighbor) mustn't be called
            int offset = Random::random(0, _neighbors.size() - 1);
            node = _neighbors.key(*(_neighbors.constBegin() + offset));
            child << node;
        }
    }
    return child;
}
