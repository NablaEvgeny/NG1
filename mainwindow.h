#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <QPlainTextEdit>
#include <QtCore/QtGlobal>
#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QLayout>
#include <QPushButton>


namespace Ui {
class MainWindow;
}

class SettingsDialog;

class SimplePlot;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openSerialPort();
    void closeSerialPort();
    void showPlot();
    void handlePlotTimer();

    void handleError(QSerialPort::SerialPortError error);

private:
    void initActionsConnections();

private:
    Ui::MainWindow *ui;
    SettingsDialog *settings;

    QSerialPort *serial;
    QGridLayout *layout;
    QTimer *timer;


    void createCentralWidget();

    QMenu *helpMenu;
    QPlainTextEdit *textEdit;

    SimplePlot *plot0;
    SimplePlot *plot1;
    QPushButton *rec0;
    QPushButton *rec1;

};

#endif // MAINWINDOW_H
