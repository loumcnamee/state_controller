#include "MainWindow.h"

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDir>

//#include "HomeHeatModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    
    setupUi(this);
    
    
}

MainWindow::~MainWindow()
{

}

void MainWindow::setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
       
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        

        MainWindow->resize(800, 800);
       
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

        pushButton_5 = new QPushButton();
        pushButton_5->setObjectName(QString::fromUtf8("5"));
        pushButton_5->setText(QString::fromUtf8("PB 5"));
        verticalLayout->addWidget(pushButton_5);
        //verticalLayout->addWidget(pushButton_5);

        pushButton_3 = new QPushButton();
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setText(QString::fromUtf8("PB 5"));
        verticalLayout->addWidget(pushButton_3);
        

        //verticalLayout->addWidget(pushButton_3);

        pushButton_1 = new QPushButton(verticalLayoutWidget);
        pushButton_1->setObjectName(QString::fromUtf8("PB 1"));

        verticalLayout->addWidget(pushButton_1);

        pushButton_6 = new QPushButton(verticalLayoutWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));

        verticalLayout->addWidget(pushButton_6);
        
        horizontalSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);

        
        
        setupChart();
        horizontalLayout->addWidget(m_chartView);
        horizontalLayout->addItem(horizontalSpacer);
        

        pushButton_4 = new QPushButton();
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(320, 80, 81, 81));
        verticalLayout->addWidget(pushButton_4);
       
        pushButton_4->setSizePolicy(sizePolicy);

        pushButton_2 = new QPushButton();
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 180, 158, 23));
        verticalLayout->addWidget(pushButton_2);

        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setFlat(false);

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
        retranslateUi(MainWindow);
        
        //setCentralWidget(m_button);
        connect(m_button, &QPushButton::clicked, this, &MainWindow::storeContent);

        // Set up the chart update timer
        m_ChartUpdateTimer = new QTimer(this);
        m_ChartUpdateTimer->setInterval(100);
        //connect(m_ChartUpdateTimer, SIGNAL(timeout()), this, SLOT(MainWindow::updateChart()));
        connect(m_ChartUpdateTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::updateChart));
        
        QMetaObject::connectSlotsByName(MainWindow);
        m_ChartUpdateTimer->start();
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
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "PB 5", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PB 3", nullptr));
        pushButton_1->setText(QCoreApplication::translate("MainWindow", "PB 1", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "PB 6", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "PB 4", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "PB 2", nullptr));
    } // retranslateUi

void MainWindow::setupChart()
{
    // Create series
    m_series = new QLineSeries();
    m_series->setName("Time Series Data");

    // Create chart and take ownership of series
    m_chart = new QChart();
    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();
    m_chart->setTitle("Data Over Time");



    // Create X axis (time)
    /**
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("HH:mm:ss");
    axisX->setTitleText("Time");
    m_chart->addAxis(axisX, Qt::AlignBottom);
    m_series->attachAxis(axisX);

    // Create Y axis (values)
    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("Value");
    m_chart->addAxis(axisY, Qt::AlignLeft);
    m_series->attachAxis(axisY);
    */

    // Create chart view
    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    sizePolicy.setHorizontalStretch(1);
    sizePolicy.setVerticalStretch(1);
    m_chartView->setSizePolicy(sizePolicy);
        

    // Add chart to main window
    //setCentralWidget(m_chartView);
}

void MainWindow::addDataPoint(qreal time, qreal value)
{
    m_series->append(time, value);
    
    //Auto-scroll the view if needed
    QValueAxis *axisX = qobject_cast<QValueAxis*>(m_chart->axes(Qt::Horizontal).first());
    if (axisX) {
       axisX->setRange(m_series->at(0).x(), m_series->at(m_series->count()-1).x());
   }
    
    // Auto-scale Y axis
    
    QValueAxis *axisY = qobject_cast<QValueAxis*>(m_chart->axes(Qt::Vertical).first());
    if (axisY) {
        qreal minY = m_series->at(0).y();
        qreal maxY = m_series->at(0).y();
        for (int i = 1; i < m_series->count(); ++i) {
            minY = qMin(minY, m_series->at(i).y());
            maxY = qMax(maxY, m_series->at(i).y());
        }
        axisY->setRange(minY, maxY);
    
    }
    
}

void MainWindow::updateChart()
{
    static qreal time = 0;
    static qreal value = 0;
    qDebug() << "... update charts";
    addDataPoint(time, value);
    time += 1;
    value = 5+5*qSin(time);
}