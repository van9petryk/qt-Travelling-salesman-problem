#ifndef MAPFRAME_H
#define MAPFRAME_H

#include <QFrame>
#include <QList>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPicture>
#include <cmath>
#include "random.h"

class MapFrame : public QFrame
{
    Q_OBJECT
public:
    MapFrame(QWidget * parent = 0, Qt::WindowFlags f = 0);
    const QList <QVector2D> &getPoints() const;
    void resetMap();
    void makeCirclePoints(const int &numberPoints, const int &radius);
    void makeRandomPoints(const int &numberPoints);
public slots:
    void clearTourMapShowed();
    void showTourMap(const int &numberTourMap);
    void hideTourMap(const int &numberTourMap);
    void updateToursMap(const QList <QList <int> > &tour);
protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
private:
    QList <QVector2D> point;
    QList <QPicture> tourMap;
    QList <int> tourMapShowed;
};

#endif // MAPFRAME_H
