#include "tsp_model.h"
#include <QDebug>

TSP_Model::TSP_Model(const QList<QVector2D> &cityLocation) : cityLocation(cityLocation)
{
    selectionType = TSP_Model::TOURNAMENT;
    crossoverType = TSP_Model::PARTIALLY_MAPPED;
    mutationType = TSP_Model::INVERSION;
    operatorOrder = TSP_Model::FIRST_CROSSOVER;
    mutationIncluded = true;
}

int TSP_Model::rowCount(const QModelIndex &parent) const
{
    return tourLength.size();
}

int TSP_Model::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant TSP_Model::data(const QModelIndex &index, int role) const
{
    switch (index.column()) {
    case 0:
        switch (role){
        case Qt::DisplayRole:
            return index.row();
        case Qt::CheckStateRole:
            return checkedTour.contains(index.row()) ? Qt::Checked : Qt::Unchecked;
        case Qt::BackgroundRole:
            if (tourLength.at(index.row()) < midMinMidLength)
                return QBrush(QColor(0, 255, 0, 127));
            else if (tourLength.at(index.row()) > midMaxMidLength)
                return QBrush(QColor(255, 0, 0, 127));
            else if (tourLength.at(index.row()) > midMinMidLength && tourLength.at(index.row()) < midMaxMidLength)
                return QBrush(QColor(255, 255, 0, 127));
            else
                return QBrush(QColor(0, 0, 255, 127));
        default:
            return QVariant();
        }
    case 1:
        switch (role){
        case Qt::DisplayRole:
            return tourLength.at(index.row());
        case Qt::BackgroundRole:
            if (tourLength.at(index.row()) < midMinMidLength)
                return QBrush(QColor(0, 255, 0, 127));
            else if (tourLength.at(index.row()) > midMaxMidLength)
                return QBrush(QColor(255, 0, 0, 127));
            else if (tourLength.at(index.row()) > midMinMidLength && tourLength.at(index.row()) < midMaxMidLength)
                return QBrush(QColor(255, 255, 0, 127));
            else
                return QBrush(QColor(0, 0, 255, 127));
        default:
            return QVariant();
        }
    default:
        return QVariant();
    }
}

bool TSP_Model::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role == Qt::CheckStateRole){
        if (checkedTour.contains(index.row())){
            checkedTour.removeOne(index.row());
            emit unchecked(index.row());
        }
        else {
            checkedTour.append(index.row());
            emit checked(index.row());
        }
        emit dataChanged(index, index);
        return true;
    }
    else
        return false;
}

Qt::ItemFlags TSP_Model::flags(const QModelIndex &index) const
{
    if (index.column() == 0)
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | Qt::ItemIsSelectable;
    if (index.column() == 1)
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    else return Qt::NoItemFlags;
}

QVariant TSP_Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (orientation) {
    case Qt::Vertical:
        if (role == Qt::DisplayRole)
            return section;
        else
            return QVariant();
    case Qt::Horizontal:
        if (role == Qt::DisplayRole){
            if (section == 0)
                return "№ тура";
            else if (section == 1)
                return "Длина";
            else
                return QVariant();
        }
        else
            return QVariant();
    default:
        return QVariant();
    }
}

void TSP_Model::addTour(const int &numberCities)
{
    if (numberCities < 4) //если городов < 4, нету смысла
        return;
    QList <int> cityTourOrder;
    for (int i = 0; i < numberCities; i++)
        cityTourOrder << i;
    for (int i = 0, j, temp; i < numberCities; i++){
        j = Random::random(i, numberCities - 1);
        temp = cityTourOrder.at(i);
        cityTourOrder[i] = cityTourOrder.at(j);
        cityTourOrder[j] = temp;
    }
    tour << cityTourOrder;
}

bool TSP_Model::createTours(const int &size)
{
    deleteTours();
    int numberTours = size;
    if (numberTours < 1)
        return false;
    int numberCities = cityLocation.size();
    if (numberCities < 4)
        return false;
    cityDistance.updateBy(cityLocation);
    for (int i = 0; i < numberTours; i++)
        addTour(numberCities);
    calcLengthTours();
    beginInsertRows(QModelIndex(), 0, tour.size() - 1);
    endInsertRows();
    emit toursReady(tour);
    emit toursInfoReady(toursInfo, true);
    return true;
}

bool TSP_Model::evolution(const int &numberIterations)
{
    if (tour.size() < 4)
        return false;
    if (mutationIncluded){
        if (operatorOrder == TSP_Model::FIRST_CROSSOVER){
            for (int i = 0; i < numberIterations; i++){
                selection();
                crossover();
                mutation();
                updateTours();
            }
        }
        else {
            for (int i = 0; i < numberIterations; i++){
                selection();
                mutation();
                crossover();
                updateTours();
            }
        }
    }
    else {
        for (int i = 0; i < numberIterations; i++){
            selection();
            crossover();
            updateTours();
        }
    }
    emit toursReady(tour);
    emit dataChanged(index(0, 0), index(tour.size() - 1, 1));
    return true;
}

void TSP_Model::deleteTours()
{
    if (rowCount() > 0){
        beginRemoveRows(QModelIndex(), 0, rowCount() - 1);
        endRemoveRows();
    }
    tour.clear();
    checkedTour.clear();
    tourLength.clear();
}

void TSP_Model::setSelectionType(TSP_Model::SelectionType selectionType)
{
    this->selectionType = selectionType;
}

void TSP_Model::setCrossoverType(TSP_Model::CrossoverType crossoverType)
{
    this->crossoverType = crossoverType;
}

void TSP_Model::setMutationType(TSP_Model::MutationType mutationType)
{
    this->mutationType = mutationType;
}

void TSP_Model::setOperatorOrder(TSP_Model::OperatorOrder operatorOrder)
{
    this->operatorOrder = operatorOrder;
}

void TSP_Model::setMutationIncluded(const bool &on)
{
    mutationIncluded = on ? true : false;
}

void TSP_Model::selection()
{
    switch (selectionType) {
    case TSP_Model::TOURNAMENT:
        selectionTournament();
        break;
    default:
        break;
    }
}

void TSP_Model::crossover()
{
    offspring.clear();
    QList <QPair <QList <int>, QList <int> > > pairParents;
    while(matingPool.size() != 0)
        pairParents << qMakePair(matingPool.takeAt(Random::random(0, matingPool.size() - 1)),
                                 matingPool.takeAt(Random::random(0, matingPool.size() - 1)));

    QPair <QList <int>, QList <int> > (Crossover::*funcPtr)(const QPair <QList <int>, QList <int> > &);
    switch (crossoverType) {
    case TSP_Model::PARTIALLY_MAPPED:
        funcPtr = &Crossover::partiallyMapped;
        break;
    case TSP_Model::ORDER:
        funcPtr = &Crossover::order;
        break;
    case TSP_Model::CYCLE:
        funcPtr = &Crossover::cycle;
        break;
    case TSP_Model::EDGE_RECOMBINATION:
        funcPtr = &Crossover::edgeRecombination;
        break;
    default:
        break;
    }
    QPair <QList <int>, QList <int> > pairOffspring;
    for (int i = 0; i < pairParents.size(); i++){
        pairOffspring = (_crossover.*funcPtr)(pairParents.at(i));
        offspring << pairOffspring.first << pairOffspring.second;
    }
}

void TSP_Model::mutation()
{
    QList <QList <int> > *tourToMutate;
    tourToMutate = operatorOrder == TSP_Model::FIRST_CROSSOVER ? &matingPool : &offspring;
    void (Mutation::*funcPtr)(QList <int> &);
    switch (mutationType) {
    case TSP_Model::INVERSION:
        funcPtr = &Mutation::inversion;
        break;
    case TSP_Model::INSERTION:
        funcPtr = &Mutation::insertion;
        break;
    case TSP_Model::RECIPROCAL_EXCHANGE:
        funcPtr = &Mutation::reciprocalExchange;
        break;
    default:
        break;
    }

    for (int i = 0; i < tourToMutate->size(); i++){
        (_mutation.*funcPtr)((*tourToMutate)[i]);
    }
}

bool TSP_Model::updateTours()
{
    if(offspring.size() == tour.size()){
        tour = offspring;
        calcLengthTours();
        emit toursInfoReady(toursInfo);
        return true;
    }
    else return false;
}

void TSP_Model::calcLengthTours()
{
    tourLength.clear();
    double maxLength = lengthOf(0);
    double minLength = maxLength;
    double midLength = 0;
    double temp;
    for (int i = 0; i < tour.size(); i++){
        temp = lengthOf(i);
        tourLength << temp;
        if (maxLength < temp)
            maxLength = temp;
        else if (minLength > temp)
            minLength = temp;
        midLength += temp;
    }
    totalLength = midLength;
    midLength /= tour.size();
    toursInfo.maxLength = maxLength;
    toursInfo.midLength = midLength;
    toursInfo.minLength = minLength;
    midMaxMidLength = (maxLength + midLength)/2;
    midMinMidLength = (midLength + minLength)/2;
}

void TSP_Model::checkAll()
{
    for (int i = 0; i < tour.size(); i++){
        if(!checkedTour.contains(i)){
            checkedTour << i;
            emit checked(i);
            emit dataChanged(index(i,0), index(i,0));
        }
    }
}

void TSP_Model::uncheckAll()
{
    checkedTour.clear();
    if (rowCount() > 0)
        emit dataChanged(index(0,0), index(rowCount() - 1,0));
}

void TSP_Model::checkBest(int state)
{
    if (state){
        for (int i = 0; i < tour.size(); i++){
            if(tourLength.at(i) < midMinMidLength && !checkedTour.contains(i)){
                checkedTour << i;
                emit checked(i);
                emit dataChanged(index(i, 0), index(i, 0));
            }
        }
    }
    else {
        for (int i = 0; i < tour.size(); i++){
            if(tourLength.at(i) < midMinMidLength && checkedTour.contains(i)){
                checkedTour.removeOne(i);
                emit unchecked(i);
                emit dataChanged(index(i, 0), index(i, 0));
            }
        }
    }
}

void TSP_Model::checkMedium(int state)
{
    if (state){
        for (int i = 0; i < tour.size(); i++)
            if(tourLength.at(i) < midMaxMidLength && tourLength.at(i) > midMinMidLength && !checkedTour.contains(i)){
                checkedTour << i;
                emit checked(i);
                emit dataChanged(index(i, 0), index(i, 0));
            }

    }
    else {
        for (int i = 0; i < tour.size(); i++)
            if (tourLength.at(i) < midMaxMidLength && tourLength.at(i) > midMinMidLength && checkedTour.contains(i)){
                checkedTour.removeOne(i);
                emit unchecked(i);
                emit dataChanged(index(i, 0), index(i, 0));
            }
    }
}

void TSP_Model::checkWorst(int state)
{
    if (state){
        for (int i = 0; i < tour.size(); i++)
            if(tourLength.at(i) > midMaxMidLength && !checkedTour.contains(i)){
                checkedTour << i;
                emit checked(i);
                emit dataChanged(index(i, 0), index(i, 0));
            }
    }
    else {
        for (int i = 0; i < tour.size(); i++)
            if (tourLength.at(i) > midMaxMidLength && checkedTour.contains(i)){
                checkedTour.removeOne(i);
                emit unchecked(i);
                emit dataChanged(index(i, 0), index(i, 0));
            }
    }
}

double TSP_Model::lengthOf(const int &numberTour) const
{
    if(numberTour >= tour.size() || numberTour < 0)
        return -1.0;
    const QList <int> &cityTourOrder = tour.at(numberTour);
    double length = 0;
    for (int i = 0, fromCity, toCity; i < cityTourOrder.size() - 1; i++){
        fromCity = cityTourOrder.at(i);
        toCity = cityTourOrder.at(i + 1);
        length += cityDistance(fromCity, toCity);
    }
    length += cityDistance(cityTourOrder.last(), cityTourOrder.first());
    return length;
}

double TSP_Model::fitnessOf(const int &numberTour) const
{
    if(numberTour >= tour.size() || numberTour < 0)
        return -1.0;
    return totalLength/tourLength.at(numberTour);
}

//турнирный отбор (2 существа)
void TSP_Model::selectionTournament()
{
    matingPool.clear();
    QPair <int, int> numberTour;
    for (int i = 0; i < tour.size(); i++){
        numberTour.first = Random::random(0, tour.size() - 1);
        numberTour.second = Random::random(0, tour.size() - 1);
        tourLength.at(numberTour.first) < tourLength.at(numberTour.second)
                ? matingPool << tour.at(numberTour.first)
                                : matingPool << tour.at(numberTour.second);
    }
}

///roulette selection
//void CommisVoyageur::rouletteSelection()
//{
//    QList <double> fitness;
//    double rouletteSum = 0;
//    for (int i = 0; i < tour.size(); i++){
//        fitness << fitnessOf(i);
//        rouletteSum += fitness.last();
//    }
//    QList <double> roulette;
//    for (int i = 0; i < tour.size(); i++)
//        roulette << fitness.at(i)/rouletteSum;
//    for (int i = 0; i < population.size(); i++){
//        int number = rand()%101;
//        for (int j = 0; j < roulette.size(); j++){
//            number < roulette
//        }
//    }
//}

