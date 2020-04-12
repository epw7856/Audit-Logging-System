#include "auditlogfileoperations.h"
#include <QDir>
#include <QStandardPaths>
#include <QDebug>
#include <QThread>

AuditLogFileOperations::AuditLogFileOperations()
{
    invocationTime = QDateTime::currentDateTime();
    const QString auditLogsPath = QString("%1").arg(QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + "/.AuditLogs/");
    QDir dir(auditLogsPath);

    if(!dir.exists())
    {
        dir.mkpath(dir.absolutePath());
    }

    const QString& logFilePath = QString("%1").arg(auditLogsPath +
                                                   "AuditLog_" +
                                                   invocationTime.toString("yyyy-MM-dd_HH-mm-ss") +
                                                   "_1.log");

    configureLogFile(logFilePath);
}

void AuditLogFileOperations::streamToFile(const QString message)
{
    if(logFile.isOpen())
    {
        verifyLogfileSize();

        stream << message << endl;
        stream.flush();
    }
}

void AuditLogFileOperations::closeLogFile()
{
    if(logFile.isOpen())
    {
        writeLogFileFooter();
        logFile.close();
    }

    thread()->quit();
    thread()->wait(2000);
}

void AuditLogFileOperations::configureLogFile(const QString &filePath)
{
    if(logFile.isOpen())
    {
        logFile.close();
    }

    logFile.setFileName(filePath);

    if (!logFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        return;
    }

    logFileCount++;
    stream.setDevice(&logFile);

    writeLogFileHeader();
}

void AuditLogFileOperations::verifyLogfileSize()
{
    // The max log file size is defined as 5MB but 1kB of this limit is reserved for the footer information
    const quint32 LogFileMaxSize = 4999000U;

    if(logFile.size() >= LogFileMaxSize)
    {
        writeLogFileFooter();
        QString nextLogFilePath = logFile.fileName();
        nextLogFilePath.truncate(nextLogFilePath.lastIndexOf("_") + 1);
        nextLogFilePath += QString::number(logFileCount+1) + ".log";

        configureLogFile(nextLogFilePath);
    }
}

void AuditLogFileOperations::writeLogFileHeader()
{
    const quint32 timeStampFieldWidth = 32U;
    const quint32 logMsgTypeFieldWidth = 16U;

    stream << QString("%1").arg("Audit Log Report").rightJustified(58, QChar(' ')) << endl;
    stream << endl;
    stream << "Application Launch Time: " << invocationTime.toString("yyyy-MM-dd HH:mm:ss") << endl;
    stream << "Current Log File Number: " << QString::number(logFileCount) << endl;
    stream << QString("%1").arg("").rightJustified(100, QChar('=')) << endl;

    QString columnHeaders = QString("%1").arg("TimeStamp").leftJustified(timeStampFieldWidth, QChar(' '));
    columnHeaders += QString("%1").arg("Entry Type").leftJustified(logMsgTypeFieldWidth, QChar(' '));
    columnHeaders += QString("%1").arg("Message");

    stream << columnHeaders << endl;
    stream << QString("%1").arg("").rightJustified(100, QChar('=')) << endl;
    stream << endl;

    stream.flush();
}

void AuditLogFileOperations::writeLogFileFooter()
{
    stream << endl;
    stream << QString("%1").arg("").rightJustified(100, QChar('=')) << endl;
    stream << QString("%1").arg("End of Audit Log Report").rightJustified(61, QChar(' ')) << endl;

    stream.flush();
}
