#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "settingsdialog.h"
#include "geologyplot.h"

#include <QMessageBox>
#include <QtSerialPort/QSerialPort>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort( this);
    settings = new SettingsDialog;

    createCentralWidget();
    //setCentralWidget(plot);

    ui->actionConfigure->setEnabled(true);
    ui->actionDraw_Plot->setEnabled(true);

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
            SLOT(handleError(QSerialPort::SerialPortError)));

   initActionsConnections();
}

MainWindow::~MainWindow()
{
    delete settings;
    delete ui;
}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = settings->settings();
    serial->setPortName(p.name);
    if (serial->open(QIODevice::ReadWrite)) {
        if (serial->setBaudRate(p.baudRate)
                && serial->setDataBits(p.dataBits)
                && serial->setParity(p.parity)
                && serial->setStopBits(p.stopBits)
                && serial->setFlowControl(p.flowControl)) {

            ui->actionConnect->setEnabled(false);
            ui->actionDisconnect->setEnabled(true);
            ui->actionConfigure->setEnabled(false);
            ui->statusBar->showMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                                       .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                       .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));

        } else {
            serial->close();
            QMessageBox::critical(this, tr("Error"), serial->errorString());

            ui->statusBar->showMessage(tr("Open error"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());

        ui->statusBar->showMessage(tr("Configure error"));
    }
}

void MainWindow::closeSerialPort()
{
    serial->close();
    ui->actionConnect->setEnabled(true);
    ui->actionDisconnect->setEnabled(false);
    ui->actionConfigure->setEnabled(true);
    ui->statusBar->showMessage(tr("Disconnected"));
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::showPlot()
{
    timer->start(25);
}

void MainWindow::handlePlotTimer()
{
    plot0->timerHandle();
}

void MainWindow::initActionsConnections()
{
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(openSerialPort()));
    connect(ui->actionDisconnect, SIGNAL(triggered()), this, SLOT(closeSerialPort()));
    connect(ui->actionConfigure, SIGNAL(triggered()), settings, SLOT(show()));
    connect(ui->actionDraw_Plot, SIGNAL(triggered()), this, SLOT(showPlot()));
    connect(timer, SIGNAL( timeout() ), this, SLOT( handlePlotTimer() ) );
}

void MainWindow::createCentralWidget()
 {
    setWindowTitle(tr("Nabla geology 1"));

    textEdit = new QPlainTextEdit;
    textEdit->setSizePolicy(QSizePolicy::Expanding,
          QSizePolicy::Expanding);

    plot0 = new GeologyPlot(this);
    QString f0 = "tmpfile0.dat";
    plot0->SetTmpfile(f0);

    rec0 = new QPushButton(this);
    rec0 ->setText("Rec");

    layout = new QGridLayout();
    layout->addWidget(plot0, 0, 0);
    layout->addWidget(rec0, 1, 0);
    layout->addWidget(textEdit, 0, 1, 0, 1);
    centralWidget()->setLayout(layout);


    timer = new QTimer(this);

 }

