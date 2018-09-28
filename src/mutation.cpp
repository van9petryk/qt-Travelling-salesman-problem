#include "mutation.h"
#include <QDebug>

Mutation::Mutation()
{

}

void Mutation::inversion(QList<int> &chromosome)
{
    QPair <int, int> position = Random::random(1, chromosome.size() - 2, Random::REPEAT_NO, Random::ORDER_ASC);
    for (int i = position.first, j = position.second; i < j; i++, j--)
        chromosome.swap(i, j);
}

void Mutation::reciprocalExchange(QList<int> &chromosome)
{
    QPair <int, int> position = Random::random(0, chromosome.size() - 1, Random::REPEAT_NO);
    chromosome.swap(position.first, position.second);
}

void Mutation::insertion(QList<int> &chromosome)
{
    QPair <int, int> position = Random::random(0, chromosome.size() - 1, Random::REPEAT_NO);
    int value = chromosome.takeAt(position.first);
    chromosome.insert(position.second, value);
}
