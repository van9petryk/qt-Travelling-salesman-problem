#ifndef TSP_HISTORYMODEL_H
#define TSP_HISTORYMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include "toursinfo.h"

class TSP_HistoryModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    TSP_HistoryModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
public slots:
    void addToursInfo(const ToursInfo &toursInfo, bool newStage = false);
private:
    QList <ToursInfo> toursInfo;
    void clearToursInfo();
};

#endif // TSP_HISTORYMODEL_H
