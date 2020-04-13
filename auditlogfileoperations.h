#ifndef AUDITLOGFILEOPERATIONS_H
#define AUDITLOGFILEOPERATIONS_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

class AuditLogFileOperations : public QObject
{
    Q_OBJECT

public:
    AuditLogFileOperations();
    void closeLogFile();

public slots:
    void streamToFile(const QString message);

private:
    QFile logFile;
    QTextStream stream;
    QDateTime invocationTime;
    quint32 logFileCount = 1U;

    void configureLogFile(const QString& filePath);
    void verifyLogfileSize();
    void writeLogFileHeader();
    void writeLogFileFooter();
};

#endif // AUDITLOGFILEOPERATIONS_H
