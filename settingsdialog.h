#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>


namespace Ui {
class SettingsDialog;
}

class QIntValidator;


class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    struct Settings {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };

    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();

    Settings settings () const;

private slots:
    void apply ();
    void showPortInfo( int);
    void checkCustomBaudRatePolicy( int);

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

private:
    Ui::SettingsDialog *ui;
    QIntValidator *intValidator;
    Settings currentSettings;
};

#endif // SETTINGSDIALOG_H
