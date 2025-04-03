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
//#include <QtWidgets/QSlider>
#include "ControlSlider.h"
#include <QtWidgets/QMenuBar>
#include <QtCharts/QChartView>
#include <QtCharts/QPolarChart>
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
    float time_ ;
    QSize buttonsize = QSize(100, 100);
    Controller<State, Event, Transitions> ctrl;
    QPushButton *m_button;
    QWidget *centralwidget;
    QWidget *HorizontalLayoutWidget;
    QWidget *verticalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonHeat_;
    QPushButton *pushButton_IDLE;
    QPushButton *pushButton_ClearData;
    QPushButton *pushButton_6;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Cool;
    QPushButton *pushButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QChartView *m_chartView;
    QPolarChart *m_chart;
    QLineSeries *m_inTempData;
    QLineSeries *m_outTempData;
    QTimer* m_ChartUpdateTimer;
    ControlSlider* m_ModeSelector;

    void setupChart();
    void setupModeSelector();
    void addDataPoint(qreal time, qreal inTemp, qreal outTemp);
    void clearChartData();  // Add this line
public slots:
    void updateChart();
    void setIdleState();
    void setHeatingState();
    void setCoolingState();
    void heatButtonClicked();
    void idleButtonClicked();
    void coolButtonClicked();


};

#endif // MAINWINDOW_H