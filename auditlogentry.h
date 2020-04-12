#ifndef AUDITLOGENTRY_H
#define AUDITLOGENTRY_H

#include "auditlogmanager.h"
#include <QDebug>
#include <QDateTime>

#define AUDIT_INFO()        AuditLogEntry(LogMsgType::Info, QDateTime::currentDateTime()).log()
#define AUDIT_DEBUG()       AuditLogEntry(LogMsgType::Debug, QDateTime::currentDateTime()).log()
#define AUDIT_WARNING()     AuditLogEntry(LogMsgType::Warning, QDateTime::currentDateTime()).log()
#define AUDIT_CRITICAL()    AuditLogEntry(LogMsgType::Critical, QDateTime::currentDateTime()).log()
#define AUDIT_FATAL()       AuditLogEntry(LogMsgType::Fatal, QDateTime::currentDateTime()).log()

class AuditLogEntry
{
public:
    AuditLogEntry
    (
        LogMsgType msgType,
        QDateTime msgTime
    );
    ~AuditLogEntry();
    QDebug& log();

private:
    QDebug debug;
    QString buffer = "";
    LogMsgType logEntryMsgType = LogMsgType::Info;
    QDateTime logEntryTimeStamp;

    void formatBuffer();

};

#endif // AUDITLOGENTRY_H
