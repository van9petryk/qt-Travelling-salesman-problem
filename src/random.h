#ifndef RANDOM_H
#define RANDOM_H

#include <QTime>
#include <QPair>

class Random
{
public:
    enum Repeat {REPEAT_YES, REPEAT_NO};
    enum Order {ORDER_NO, ORDER_ASC, ORDER_DESC};
    static bool isInit();
    static int getSeed();
    static int random(int from, int to);
    static QPair <int, int> random(int from, int to, Repeat repeat, Order order = Random::ORDER_NO);

private:
    Random();
    Random(const Random &);
    Random &operator=(Random &);
    static bool init;
    static int seed;
    static void setSeed();
    static void swap(int &left, int &right);
};

#endif // RANDOM_H
