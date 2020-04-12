#include "mainwindowcontroller.h"
#include "auditlogentry.h"

MainWindowController::MainWindowController()
{
    AuditLogManager::setLoggingEnvironment(LogEnvironment::Development);
}

void MainWindowController::logDebugMsg()
{
    AUDIT_DEBUG() << "This is a debug log message.";
}

void MainWindowController::logInfoMsg()
{
    AUDIT_INFO() << "This is a info log message.";
}

void MainWindowController::logWarningMsg()
{
    AUDIT_WARNING() << "This is a warning log message.";
}

void MainWindowController::logCriticalMsg()
{
    AUDIT_CRITICAL() << "This is a critical log message.";
}

void MainWindowController::logFatalMsg()
{
    AUDIT_FATAL() << "This is a fatal log message.";
}
