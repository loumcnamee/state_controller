#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMenuBar>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QtCore/QTimer>
#include <Controller.h>

// #include "HeatingState.h"
// #include "CoolingState.h"
// #include "IdleState.h"
// #include "Event.h"



using State = variant<IdleState, HeatingState, CoolingState>;

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget* parent=0);
    ~MainWindow();
    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);

public slots:
    void storeContent();
private:
    Controller<State, Event, Transitions> ctrl;
    QPushButton *m_button;
    QWidget *centralwidget;
    QWidget *HorizontalLayoutWidget;
    QWidget *verticalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_1;
    QPushButton *pushButton_6;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QChartView *m_chartView;
    QChart *m_chart;
    QLineSeries *m_series;
    QTimer* m_ChartUpdateTimer;

    void setupChart();
    void addDataPoint(qreal time, qreal value);
public slots:
    void updateChart();
};

#endif // MAINWINDOW_H