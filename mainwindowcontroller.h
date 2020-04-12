#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

#include <QObject>

class MainWindowController : public QObject
{
    Q_OBJECT

public:
    MainWindowController();
    void logDebugMsg();
    void logInfoMsg();
    void logWarningMsg();
    void logCriticalMsg();
    void logFatalMsg();

signals:
    void sendStatusUpdate(QString);
};

#endif // MAINWINDOWCONTROLLER_H
