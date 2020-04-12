#include "mainwindowcontroller.h"
#include "auditlogentry.h"

MainWindowController::MainWindowController()
{
    AuditLogManager::setLoggingEnvironment(LogEnvironment::Development);
}

void MainWindowController::logDebugMsg()
{
    AUDIT_DEBUG() << "This is a debug log message.";
    emit sendStatusUpdate("Debug message written to log!");
}

void MainWindowController::logInfoMsg()
{
    AUDIT_INFO() << "This is a info log message.";
    emit sendStatusUpdate("Info message written to log!");
}

void MainWindowController::logWarningMsg()
{
    AUDIT_WARNING() << "This is a warning log message.";
    emit sendStatusUpdate("Warning message written to log!");
}

void MainWindowController::logCriticalMsg()
{
    AUDIT_CRITICAL() << "This is a critical log message.";
    emit sendStatusUpdate("Critical message written to log!");
}

void MainWindowController::logFatalMsg()
{
    AUDIT_FATAL() << "This is a fatal log message.";
    emit sendStatusUpdate("Fatal message written to log!");
}
