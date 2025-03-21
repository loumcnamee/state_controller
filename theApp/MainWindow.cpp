#include "MainWindow.h"

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDir>
#include <QLabel>

//#include "HomeHeatModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    time_ = 0.0;
    setupUi(this);
    
    
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));

               
        QSizePolicy btnsizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        btnsizePolicy.setHorizontalStretch(1);
        btnsizePolicy.setVerticalStretch(1);
        

        MainWindow->resize(1024, 1024);
       
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        
        
        
        HorizontalLayoutWidget = new QWidget(centralwidget);
        HorizontalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        HorizontalLayoutWidget->setGeometry(QRect(10, 10, 700, 700));

        horizontalLayout = new QHBoxLayout(HorizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        
        
        verticalLayoutWidget = new QWidget();
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 160, 700));
        horizontalLayout->addWidget(verticalLayoutWidget);

        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        
        m_button = new QPushButton("Store Content", this);
        verticalLayout->addWidget(m_button);

        pushButtonHeat_ = new QPushButton();
        pushButtonHeat_->setObjectName(QString::fromUtf8("Heat"));
        pushButtonHeat_->setText(QString::fromUtf8("HEAT"));
        pushButtonHeat_->setSizePolicy(btnsizePolicy);
        pushButtonHeat_->setGeometry(QRect(QPoint(0,0),buttonsize));
        
        verticalLayout->addWidget(pushButtonHeat_);
        

        pushButton_IDLE = new QPushButton();
        pushButton_IDLE->setObjectName(QString::fromUtf8("pushButton_IDLE"));
        pushButton_IDLE->setText(QString::fromUtf8("IDLE"));
        verticalLayout->addWidget(pushButton_IDLE);
        

        

        QHBoxLayout *mainLayout = new QHBoxLayout();
        
        verticalLayout->addLayout(mainLayout);
        
        horizontalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
        
        setupChart();
        horizontalLayout->addWidget(m_chartView);
        horizontalLayout->addItem(horizontalSpacer);
        

        pushButton_Cool = new QPushButton();
        pushButton_Cool->setObjectName(QString::fromUtf8("pushButton_Cool"));
        pushButton_Cool->setGeometry(QRect(QPoint(100, 100), QSize(200, 50)));
        pushButton_Cool->setSizePolicy(btnsizePolicy);
        verticalLayout->addWidget(pushButton_Cool);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
        verticalLayout->addItem(verticalSpacer);
        
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);

        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        
        MainWindow->setCentralWidget(centralwidget);
                
        //setCentralWidget(m_button);
        connect(m_button, &QPushButton::clicked, this, &MainWindow::storeContent);
        connect(pushButtonHeat_, &QPushButton::clicked, this, &MainWindow::heatButtonClicked);
        connect(pushButton_IDLE, &QPushButton::clicked, this, &MainWindow::idleButtonClicked);


        // Set up the chart update timer
        m_ChartUpdateTimer = new QTimer(this);
        m_ChartUpdateTimer->setInterval(100);
        //connect(m_ChartUpdateTimer, SIGNAL(timeout()), this, SLOT(MainWindow::updateChart()));
        connect(m_ChartUpdateTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::updateChart));
        
        QMetaObject::connectSlotsByName(MainWindow);
        ctrl.setOutsideTemperature(0.0f);
        m_ChartUpdateTimer->start();
        
        retranslateUi(MainWindow);
    } // setupUi

void MainWindow::storeContent()
{
    qDebug() << "... store content";
    QString message("Hello World!");
    QFile file(QDir::home().absoluteFilePath("out.txt"));
    if(!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Can not open file with write access";
        return;
    }
    QTextStream stream(&file);
    stream << message;
}

 void MainWindow::retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        
        // pushButtonHeat_->setText(QCoreApplication::translate("MainWindow", "PB 5", nullptr));
        // pushButton_IDLE->setText(QCoreApplication::translate("MainWindow", "PB 3", nullptr));
        // pushButton_1->setText(QCoreApplication::translate("MainWindow", "PB 1", nullptr));
        // pushButton_6->setText(QCoreApplication::translate("MainWindow", "PB 6", nullptr));
        // pushButton_Cool->setText(QCoreApplication::translate("MainWindow", "PB 4", nullptr));
        // pushButton_2->setText(QCoreApplication::translate("MainWindow", "PB 2", nullptr));

        qDebug() << "... retranslateUi";

    } // retranslateUi

void MainWindow::setupChart()
{
    
    // Create chart and take ownership of series
    m_chart = new QPolarChart();
    
    m_chart->createDefaultAxes();
    m_chart->setTitle("Data Over Time");

    auto angularAxis = new QValueAxis;
    angularAxis->setMin(0);
    angularAxis->setMax(24);
    angularAxis->setTickCount(24); // First and last ticks are co-located on 0/360 angle.
    m_chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);   
    
    
    auto radialAxis = new QValueAxis;
    radialAxis->setTickCount(9);
    radialAxis->setMin(-50);
    radialAxis->setMax(+50);
    m_chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);
        
    // Create chart view
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalStretch(1);
    m_chartView->setSizePolicy(sizePolicy);
    
    // Create series
    m_inTempData = new QLineSeries();
    m_inTempData->setName("Inside Temp [C]");

    m_outTempData = new QLineSeries();
    m_outTempData->setName("Outside Temp [C]");

    m_chart->addSeries(m_inTempData);
    m_chart->addSeries(m_outTempData);

    m_inTempData->attachAxis(angularAxis);
    m_outTempData->attachAxis(angularAxis);
    
    m_inTempData->attachAxis(radialAxis);
    m_outTempData->attachAxis(radialAxis);



    // Create X axis (time)
    /**
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("HH:mm:ss");
    axisX->setTitleText("Time");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_inTempData->attachAxis(axisX);

    // Create Y axis (values)
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Value");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    */

    


    
    // Add chart to main window
    //setCentralWidget(m_chartView);
}

void MainWindow::addDataPoint(qreal time, qreal inTemp, qreal outTemp)
{
    m_inTempData->append(time, inTemp);
    m_outTempData->append(time, outTemp);
    

    
//     // Auto-scale Y axis
    
//     QValueAxis *axisY = qobject_cast<QValueAxis*>(m_chart->axes(Qt::Vertical).first());
//     qreal minY = -40.0f; //m_series->at(0).y();
//     qreal maxY = +40.f; // m_series->at(0).y();
//     axisY->setRange(minY, maxY);
    
    // if (axisY) {
    //     qreal minY = -40.0f; //m_series->at(0).y();
    //     qreal maxY = +40.f; // m_series->at(0).y();
    //     for (int i = 1; i < m_series->count(); ++i) {
    //         minY = qMin(minY, m_series->at(i).y());
    //         maxY = qMax(maxY, m_series->at(i).y());
    //     }
    //     axisY->setRange(minY, maxY);
    
    // }
    
}

void MainWindow::updateChart()
{
    float delta_t = 60.0f;
    float time_scale = (24*60*60)/delta_t;
    // 86,400 sec in a day
    time_ += delta_t;
    ctrl.updateModel(delta_t, time_/time_scale);
    qreal in = ctrl.getBuildingTemperature();
    qreal out = ctrl.getOutsideTemperature();
    //qDebug() << "... update charts";
    
    addDataPoint(fmodf(time_/time_scale, 24.0f), in, out);
    
}

void MainWindow::heatButtonClicked() {
    
   
    ctrl.process(EventTooCold{});
}

void MainWindow::idleButtonClicked() {
    ctrl.process(EventStop{});
}

void MainWindow::coolButtonClicked() {
    ctrl.process(EventTooHot{});
}


void MainWindow::setupModeSelector() {
        m_ModeSelector = new ControlSlider(verticalLayoutWidget);
        m_ModeSelector->setOrientation(Qt::Vertical);
        //m_ModeSelector->setGeometry(QRect(0, 0, 400, 100));
        m_ModeSelector->setMinimumWidth(50);
        m_ModeSelector->setTickPosition(QSlider::TicksLeft);
        m_ModeSelector->setTickInterval(1);
        m_ModeSelector->setRange(0, 2); // 0: HeatingState, 1: IdleState, 2: CoolingState
        m_ModeSelector->setValue(1); // Start in Idle state

        // Create labels for the notches
        QLabel *heatingLabel = new QLabel("Heating", this);
        QLabel *idleLabel = new QLabel("Idle", this);
        QLabel *coolingLabel = new QLabel("Cooling", this);

        QVBoxLayout *modeLayout = new QVBoxLayout();
        modeLayout->addWidget(heatingLabel);
        modeLayout->addWidget(idleLabel);
        modeLayout->addWidget(coolingLabel);
        //mainLayout->addLayout(modeLayout);
}