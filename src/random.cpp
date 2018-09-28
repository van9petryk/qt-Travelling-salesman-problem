#include "random.h"
#include <QDebug>

void Random::setSeed()
{
    QTime midnight(0, 0, 0);
    seed = midnight.secsTo(QTime::currentTime());
    qsrand(seed);
    init = true;
}

void Random::swap(int &left, int &right)
{
    int temp = left;
    left = right;
    right = temp;
}

bool Random::isInit()
{
    if (init)
        return true;
    else
        return false;
}

int Random::getSeed()
{
    return seed;
}

int Random::random(int from, int to)
{
    if (!isInit())
        setSeed();
    if (from < to)
        return from + qrand()%(to + 1 - from);
    else if (from > to)
        return to + qrand()%(from + 1 - to);
    else
        return from;
}

QPair<int, int> Random::random(int from, int to, Random::Repeat repeat, Random::Order order)
{
    QPair <int, int> pair;
    pair.first = random(from, to);
    pair.second = random(from, to);
    if (repeat == Random::REPEAT_NO && pair.second == pair.first)
        if ((to - from) != 0)
            while (pair.second == pair.first)
                pair.second = random(from, to);
    if (order == Random::ORDER_ASC && pair.first > pair.second)
        swap(pair.first, pair.second);
    else if (order == Random::ORDER_DESC && pair.first < pair.second)
        swap(pair.first, pair.second);
    return pair;
}

bool Random::init = false;
int Random::seed = 0;
