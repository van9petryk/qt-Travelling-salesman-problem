#ifndef TSP_MODEL_H
#define TSP_MODEL_H

#include <QDebug>
#include <QAbstractTableModel>
#include <QVariant>
#include <QVector2D>
#include <QBrush>
#include "distancematrix.h"
#include "crossover.h"
#include "mutation.h"
#include "toursinfo.h"
#include "random.h"

class TSP_Model : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum SelectionType {TOURNAMENT};
    enum CrossoverType {PARTIALLY_MAPPED, ORDER, CYCLE, EDGE_RECOMBINATION};
    enum MutationType {INVERSION, INSERTION, RECIPROCAL_EXCHANGE};
    enum OperatorOrder {FIRST_CROSSOVER, FIRST_MUTATION};
    TSP_Model(const QList <QVector2D> &cityLocation);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    bool createTours(const int &size);
    bool evolution(const int &numberIterations);
    void deleteTours();

    void setSelectionType(TSP_Model::SelectionType selectionType);
    void setCrossoverType(TSP_Model::CrossoverType crossoverType);
    void setMutationType(TSP_Model::MutationType mutationType);
    void setOperatorOrder(TSP_Model::OperatorOrder operatorOrder);
    void setMutationIncluded(const bool &on);
private:
    const QList <QVector2D> &cityLocation;
    DistanceMatrix cityDistance;
    QList <QList <int> > tour;
    QList <double> tourLength;
    QList <QList <int> > matingPool;
    QList <QList <int> > offspring;
    QList <int> checkedTour;

    double lengthOf(const int &numberTour) const;
    double fitnessOf(const int &numberTour) const;
    void addTour(const int &numberCities);
    void selectionTournament();

    Crossover _crossover;
    Mutation _mutation;

    SelectionType selectionType;
    CrossoverType crossoverType;
    MutationType mutationType;
    OperatorOrder operatorOrder;
    bool mutationIncluded;

    void selection();
    void crossover();
    void mutation();
    bool updateTours();

    ToursInfo toursInfo;
    double midMaxMidLength;
    double midMinMidLength;
    double totalLength;

    void calcLengthTours();
signals:
    void checked(const int &numberTour);
    void unchecked(const int &numberTour);
    void toursReady(const QList <QList <int> > &tour);
    void toursInfoReady(const ToursInfo &toursInfo, bool newStage = false);
public slots:
    void checkAll();
    void uncheckAll();
    void checkBest(int state);
    void checkMedium(int state);
    void checkWorst(int state);
};

#endif // TSP_MODEL_H
