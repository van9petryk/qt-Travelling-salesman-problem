#include "mainwidget.h"
#include <QDebug>
MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    mapFrame = new MapFrame;

    scrollMapFrame = new QScrollArea;
    scrollMapFrame->setWidget(mapFrame);
    scrollMapFrame->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    model = new TSP_Model(mapFrame->getPoints());
    proxyModel = new QSortFilterProxyModel();
    proxyModel->setSourceModel(model);
    historyModel = new TSP_HistoryModel();

    view = new QTableView;
    view->setModel(proxyModel);
    view->setSelectionMode(QTableView::ExtendedSelection);
    view->setSelectionBehavior(QTableView::SelectRows);
    view->verticalHeader()->hide();
    view->setColumnWidth(0, 50);
    view->setColumnWidth(1, 70);
    view->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    view->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    view->setSortingEnabled(true);

    historyView = new QTableView;
    historyView->setModel(historyModel);
    historyView->setColumnWidth(0, 30);
    historyView->setColumnWidth(1, 60);
    historyView->setColumnWidth(2, 60);
    historyView->setColumnWidth(3, 60);
    historyView->verticalHeader()->hide();
    historyView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    historyView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

    butt_createTours = new QPushButton("Сгенерировать \nНачальные Маршруты");
    butt_reset = new QPushButton("Сброс");
    butt_runEvolution = new QPushButton("Запустить Еволюцию");
    butt_makeCirclePoints = new QPushButton("Нарисовать точки кольцом");
    butt_makeRandomPoints = new QPushButton("Нарисовать\nрандомные точки");

    tourCount = new QSpinBox;
    tourCount->setRange(2, 1000000);
    tourCount->setSingleStep(2);

    iterationCount = new QSpinBox;
    iterationCount->setRange(1, 1000000);

    circlePointCount = new QSpinBox;
    circlePointCount->setRange(4, 1000);

    randomPointCount = new QSpinBox;
    randomPointCount->setRange(1, 1000);

    lbl_tourCount = new QLabel("Кол-во маршрутов:");
    lbl_iterationCount = new QLabel("Кол-во итераций:");
    lbl_selectionType = new QLabel("Тип селекции:");
    lbl_crossoverType = new QLabel("Тип кроссовера:");
    lbl_mutationType = new QLabel("Тип мутации:");
    lbl_circlePointCount = new QLabel("Кол-во точек");
    lbl_radius = new QLabel("Радиус");
    lbl_randomPointCount = new QLabel("Кол-во точек:");

    selectionType = new QComboBox();
    selectionType->addItem("Турнирный отбор");
    crossoverType = new QComboBox();
    crossoverType->addItem("Partially-Mapped");
    crossoverType->addItem("Order");
    crossoverType->addItem("Cycle");
    crossoverType->addItem("Edge Recombination");
    mutationType = new QComboBox();
    mutationType->addItem("Inversion");
    mutationType->addItem("Insertion");
    mutationType->addItem("ReciprocalExchange");

    firstCrossover = new QRadioButton("Сначала кроссовер");
    firstMutation = new QRadioButton("Сначала мутация");
    firstCrossover->setChecked(true);

    mutationState = new QCheckBox("Мутация");
    mutationState->setChecked(true);

    radius = new QSlider(Qt::Horizontal);
    radius->setRange(5, mapFrame->height()/2 - 25);

    checkAll = new QPushButton("Выбрать все");
    uncheckAll = new QPushButton("Снять все");
    checkBest = new QCheckBox("Лучшие");
    checkMedium = new QCheckBox("Средние");
    checkWorst = new QCheckBox("Худшие");

    sectionTopLayout = new QGridLayout[6];

    sectionTopLayout[0].addWidget(lbl_circlePointCount, 0, 0);
    sectionTopLayout[0].addWidget(circlePointCount, 1, 0);
    sectionTopLayout[0].addWidget(lbl_radius, 0, 1);
    sectionTopLayout[0].addWidget(radius, 1, 1);
    sectionTopLayout[0].addWidget(butt_makeCirclePoints, 2, 0, 1, 2);

    sectionTopLayout[1].addWidget(lbl_randomPointCount, 0, 0);
    sectionTopLayout[1].addWidget(randomPointCount, 0, 1);
    sectionTopLayout[1].addWidget(butt_makeRandomPoints, 1, 0, 2, 2);

    sectionTopLayout[2].addWidget(lbl_tourCount, 0, 0);
    sectionTopLayout[2].addWidget(tourCount, 0, 1);
    sectionTopLayout[2].addWidget(butt_createTours, 1, 0, 2, 2);

    sectionTopLayout[3].addWidget(lbl_selectionType, 0, 0);
    sectionTopLayout[3].addWidget(lbl_crossoverType, 1, 0);
    sectionTopLayout[3].addWidget(lbl_mutationType, 2, 0);
    sectionTopLayout[3].addWidget(selectionType, 0, 1);
    sectionTopLayout[3].addWidget(crossoverType, 1, 1);
    sectionTopLayout[3].addWidget(mutationType, 2, 1);

    sectionTopLayout[4].addWidget(mutationState, 0, 0);
    sectionTopLayout[4].addWidget(firstCrossover, 1, 0);
    sectionTopLayout[4].addWidget(firstMutation, 2, 0);

    sectionTopLayout[5].addWidget(lbl_iterationCount, 0, 0);
    sectionTopLayout[5].addWidget(iterationCount, 0, 1);
    sectionTopLayout[5].addWidget(butt_runEvolution, 1, 0, 1, 2);
    sectionTopLayout[5].addWidget(butt_reset, 2, 0, 1, 2);

    topLayout = new QHBoxLayout;
    topLayout->addLayout(sectionTopLayout);
    topLayout->addStretch(1);
    topLayout->addLayout(sectionTopLayout + 1);
    topLayout->addStretch(1);
    topLayout->addLayout(sectionTopLayout + 2);
    topLayout->addStretch(1);
    topLayout->addLayout(sectionTopLayout + 3);
    topLayout->addStretch(1);
    topLayout->addLayout(sectionTopLayout + 4);
    topLayout->addStretch(1);
    topLayout->addLayout(sectionTopLayout + 5);

    rightMainLayout = new QVBoxLayout;
    rightMainLayout->addWidget(view);
    rightMainLayout->addWidget(checkBest);
    rightMainLayout->addWidget(checkMedium);
    rightMainLayout->addWidget(checkWorst);
    rightMainLayout->addWidget(checkAll);
    rightMainLayout->addWidget(uncheckAll);

    mainLayout = new QHBoxLayout;
    mainLayout->addWidget(historyView);
    mainLayout->addWidget(scrollMapFrame);
    mainLayout->addLayout(rightMainLayout);

    layout = new QVBoxLayout;
    layout->addLayout(topLayout);
    layout->addLayout(mainLayout);
    setLayout(layout);

    error = new QMessageBox(this);
    error->setText("Недостаточо городов! Как минимум нужно 4 города");

    connect(butt_createTours, SIGNAL(clicked(bool)), this, SLOT(createTours()));
    connect(butt_reset, SIGNAL(clicked(bool)), this, SLOT(reset()) );
    connect(butt_runEvolution, SIGNAL(clicked(bool)), this, SLOT(runEvolution()));
    connect(model, SIGNAL(toursReady(QList<QList<int> >)), mapFrame, SLOT(updateToursMap(QList<QList<int> >)));
    connect(model, SIGNAL(checked(int)), mapFrame, SLOT(showTourMap(int)));
    connect(model, SIGNAL(unchecked(int)), mapFrame, SLOT(hideTourMap(int)));
    connect(mutationState, SIGNAL(clicked(bool)), mutationType, SLOT(setEnabled(bool)));
    connect(mutationState, SIGNAL(clicked(bool)), firstCrossover, SLOT(setEnabled(bool)));
    connect(mutationState, SIGNAL(clicked(bool)), firstMutation, SLOT(setEnabled(bool)));
    connect(butt_makeCirclePoints, SIGNAL(clicked(bool)), this, SLOT(drawCirclePoints()));
    connect(butt_makeRandomPoints, SIGNAL(clicked(bool)), this, SLOT(drawRandomPoints()));
    connect(checkAll, SIGNAL(clicked(bool)), model, SLOT(checkAll()));
    connect(checkBest, SIGNAL(stateChanged(int)), model, SLOT(checkBest(int)));
    connect(checkMedium, SIGNAL(stateChanged(int)), model, SLOT(checkMedium(int)));
    connect(checkWorst, SIGNAL(stateChanged(int)), model, SLOT(checkWorst(int)));
    connect(uncheckAll, SIGNAL(clicked(bool)), model, SLOT(uncheckAll()));
    connect(uncheckAll, SIGNAL(clicked(bool)), mapFrame, SLOT(clearTourMapShowed()));
    connect(model, SIGNAL(toursInfoReady(ToursInfo,bool)), historyModel, SLOT(addToursInfo(ToursInfo,bool)));
}

void MainWidget::createTours()
{
    if(!model->createTours(tourCount->value()))
        error->show();
    mapFrame->clearTourMapShowed();
    if (checkBest->isChecked())
        model->checkBest(1);
    else
        model->checkBest(0);
    if (checkMedium->isChecked())
        model->checkMedium(1);
    else
        model->checkMedium(0);
    if (checkWorst->isChecked())
        model->checkWorst(1);
    else
        model->checkWorst(0);
}

void MainWidget::runEvolution()
{
    model->setSelectionType(TSP_Model::SelectionType(selectionType->currentIndex()));
    model->setCrossoverType(TSP_Model::CrossoverType(crossoverType->currentIndex()));
    model->setMutationType(TSP_Model::MutationType(mutationType->currentIndex()));
    firstCrossover->isChecked() ? model->setOperatorOrder(TSP_Model::FIRST_CROSSOVER) :
                                  model->setOperatorOrder(TSP_Model::FIRST_MUTATION);
    model->setMutationIncluded(mutationState->isChecked());
    model->evolution(iterationCount->value());
    mapFrame->clearTourMapShowed();

    model->uncheckAll();
    if (checkBest->isChecked())
        model->checkBest(1);
    else
        model->checkBest(0);
    if (checkMedium->isChecked())
        model->checkMedium(1);
    else
        model->checkMedium(0);
    if (checkWorst->isChecked())
        model->checkWorst(1);
    else
        model->checkWorst(0);
}

void MainWidget::reset()
{
    mapFrame->resetMap();
    model->deleteTours();

}

void MainWidget::drawCirclePoints()
{
    mapFrame->makeCirclePoints(circlePointCount->value(), radius->value());
}

void MainWidget::drawRandomPoints()
{
    mapFrame->makeRandomPoints(randomPointCount->value());
}
