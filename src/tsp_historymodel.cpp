#include "tsp_historymodel.h"

TSP_HistoryModel::TSP_HistoryModel()
{

}

int TSP_HistoryModel::rowCount(const QModelIndex &parent) const
{
    return toursInfo.size();
}

int TSP_HistoryModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant TSP_HistoryModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole){
        switch (index.column()) {
        case 0:
            return index.row();
        case 1:
            return toursInfo.at(index.row()).minLength;
        case 2:
            return toursInfo.at(index.row()).midLength;
        case 3:
            return toursInfo.at(index.row()).maxLength;
        default:
            return QVariant();
        }
    }
    else
        return QVariant();
}

QVariant TSP_HistoryModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (orientation) {
    case Qt::Vertical:
        if (role == Qt::DisplayRole)
            return section;
        else
            return QVariant();
    case Qt::Horizontal:
        if (role == Qt::DisplayRole){
            switch (section) {
            case 0:
                return "№";
            case 1:
                return "MinLen";
            case 2:
                return "MidLen";
            case 3:
                return "MaxLen";
            default:
                return QVariant();
            }
        }
        else
            return QVariant();
    default:
        return QVariant();
    }
}

void TSP_HistoryModel::addToursInfo(const ToursInfo &toursInfo, bool newStage)
{
    if (newStage == true)
        clearToursInfo();
    this->toursInfo << toursInfo;
    beginInsertRows(QModelIndex(), this->toursInfo.size(), this->toursInfo.size());
    endInsertRows();
}

void TSP_HistoryModel::clearToursInfo()
{
    if (rowCount() > 0){
        beginRemoveRows(QModelIndex(), 0, this->toursInfo.size() - 1);
        endRemoveRows();
    }
    toursInfo.clear();

}

