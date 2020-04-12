#ifndef MAINWINDOWCONTROLLER_H
#define MAINWINDOWCONTROLLER_H

class MainWindowController
{
public:
    MainWindowController();
    void logDebugMsg();
    void logInfoMsg();
    void logWarningMsg();
    void logCriticalMsg();
    void logFatalMsg();
};

#endif // MAINWINDOWCONTROLLER_H
