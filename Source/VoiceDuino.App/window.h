#ifndef WINDOW_H
#define WINDOW_H

#include <QSettings>
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QAudioDeviceInfo>
#include <QtConcurrent/QtConcurrent>
#include <QUdpSocket>
#include <QHostAddress>
#include <QDataStream>
#include "recognition.h"
#include "string2number.h"

namespace Ui
{
    class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget* = 0);
    virtual ~Window();

public slots:
    void OnExplore();
    void OnDestroy();
    void OnRecognite();
    void OnRecognized();
    void OnInitialize();
    void OnInitialized();
    void OnDeviceChanged();


private:
    void enumMicrophones(int = 0);
    void readSettings();
    void writeSettings();
    void closeEvent(QCloseEvent*);

private:
    Ui::Window* ui;
    Recognition recognition;
    QFutureWatcher<bool> initWatcher;
    QFutureWatcher<QString> recognizeWatcher;
    QUdpSocket udpSocket;

    quint8 direction;
    quint32 value;
    String2Number str2num;
};

#endif
