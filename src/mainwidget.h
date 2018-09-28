#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "mapframe.h"
#include "tsp_model.h"
#include "tsp_historymodel.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QRadioButton>
#include <QLabel>
#include <QHeaderView>
#include <QCheckBox>
#include <QMessageBox>
#include <QSlider>
#include <QSortFilterProxyModel>
#include <QScrollArea>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = 0);
private:
    MapFrame *mapFrame;
    TSP_Model *model;
    QTableView *view, *historyView;
    QSortFilterProxyModel *proxyModel;
    TSP_HistoryModel *historyModel;

    QLabel *lbl_tourCount, *lbl_iterationCount, *lbl_selectionType , *lbl_crossoverType, *lbl_mutationType,
    *lbl_circlePointCount, *lbl_radius, *lbl_randomPointCount;
    QPushButton *butt_createTours, *butt_reset, *butt_runEvolution, *butt_makeCirclePoints, *butt_makeRandomPoints,
    *checkAll, *uncheckAll;
    QSpinBox *tourCount, *iterationCount, *circlePointCount, *randomPointCount;
    QComboBox *selectionType, *crossoverType, *mutationType;
    QRadioButton *firstCrossover, *firstMutation;
    QCheckBox *mutationState, *checkBest, *checkMedium, *checkWorst;
    QSlider *radius;

    QVBoxLayout *layout;

    QHBoxLayout *mainLayout;
    QVBoxLayout *rightMainLayout;

    QHBoxLayout *topLayout;
    QGridLayout *sectionTopLayout;

    QScrollArea *scrollMapFrame;
    QMessageBox *error;

private slots:
    void createTours();
    void runEvolution();
    void reset();
    void drawCirclePoints();
    void drawRandomPoints();
};

#endif // MAINWIDGET_H
