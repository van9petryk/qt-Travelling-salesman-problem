#include "mapframe.h"
#include <QDebug>
MapFrame::MapFrame(QWidget * parent, Qt::WindowFlags f) : QFrame(parent, f)
{
    setFixedSize(800, 600);
    setFrameShadow(QFrame::Sunken);
    setFrameShape(QFrame::WinPanel);
    setLineWidth(3);
    setAutoFillBackground(true);
    setStyleSheet("background-color:white;");
}

const QList<QVector2D> &MapFrame::getPoints() const
{
    return point;
}

void MapFrame::resetMap()
{
    tourMapShowed.clear();
    tourMap.clear();
    point.clear();
    update();
}

void MapFrame::makeCirclePoints(const int &numberPoints, const int &radius)
{
    QPoint _center(width()/2, height()/2);
    double x, y, angle = (2 * M_PI)/numberPoints;
    for (int i = 0; i < numberPoints; i++){
        x = radius * cos(angle * i) + _center.x();
        y = radius * sin(angle * i) + _center.y();
        point << QVector2D(x, y);
    }
    update();
}

void MapFrame::makeRandomPoints(const int &numberPoints)
{
    int x, y;
    for (int i = 0; i < numberPoints; i++){
        x = Random::random(5, width() - 6);
        y = Random::random(5, height() - 6);
        point << QVector2D(x, y);
    }
    update();
}

void MapFrame::clearTourMapShowed()
{
    tourMapShowed.clear();
    update();
}

void MapFrame::showTourMap(const int &numberTourMap)
{
    tourMapShowed << numberTourMap;
    update();
}

void MapFrame::hideTourMap(const int &numberTourMap)
{
    tourMapShowed.removeOne(numberTourMap);
    update();
}

void MapFrame::updateToursMap(const QList<QList<int> > &tour)
{
    tourMap.clear();
    for (int i = 0; i < tour.size(); i++){
        const QList <int> &cityTourOrder = tour.at(i);
        QPicture map;
        QPainter painter(&map);
        QBrush brush("black");
        QPen pen(brush, 1);
        painter.setPen(pen);
        for (int j = 0; j < cityTourOrder.size() - 1; j++){
            QPoint from = point.at(cityTourOrder.at(j)).toPoint();
            QPoint to = point.at(cityTourOrder.at(j + 1)).toPoint();
            painter.drawLine(from, to);
        }
        painter.drawLine(point.at(cityTourOrder.last()).toPoint(), point.at(cityTourOrder.first()).toPoint());
        tourMap << map;
    }
}

void MapFrame::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QBrush brush("black");
    QPen pen(brush, 5);
    painter.setPen(pen);
    for (int i = 0; i < point.size(); i++){
        painter.drawPoint(point.at(i).toPoint());
    }
    for (int i = 0; i < tourMapShowed.size(); i++)
        painter.drawPicture(e->rect().topLeft(), tourMap.at(tourMapShowed.at(i)));
    QFrame::paintEvent(e);
}

void MapFrame::mousePressEvent(QMouseEvent *e)
{
    point << QVector2D(e->pos());
    update();
}

