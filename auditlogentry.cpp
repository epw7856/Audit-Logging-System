#include "auditlogentry.h"

AuditLogEntry::AuditLogEntry(LogMsgType msgType, QDateTime msgTime)
    :
      debug(&buffer),
      logEntryMsgType(msgType),
      logEntryTimeStamp(msgTime)
{

}

AuditLogEntry::~AuditLogEntry()
{
    if(AuditLogManager::getInstance().isLogMsgTypeEnabled(logEntryMsgType))
    {
        formatBuffer();
        AuditLogManager::getInstance().processLogEntry(buffer);
    }
}

QDebug& AuditLogEntry::log()
{
    return debug.nospace();
}

void AuditLogEntry::formatBuffer()
{
    const quint32 timeStampFieldWidth = 32U;
    const quint32 logMsgTypeFieldWidth = 16U;

    // Remove whitespace and new line characters before or after the message string
    buffer = buffer.trimmed();

    // Add the timestamp of the log entry
    const QString date = QString("%1").arg(logEntryTimeStamp.toString("yyyy/MM/dd HH:mm:ss.z"))
                                      .leftJustified(timeStampFieldWidth, QChar(' '));
    buffer.insert(0, date);

    // Add the log message type
    const QString type = QString("%1").arg(AuditLogManager::logMsgTypeToString(logEntryMsgType))
                                      .leftJustified(logMsgTypeFieldWidth, QChar(' '));
    buffer.insert(timeStampFieldWidth, type);

    // If the buffer contains any new line characters, add the proper indenting
    buffer.replace(QString("\n"), QString("\n")
          .leftJustified(timeStampFieldWidth + logMsgTypeFieldWidth + 1, QChar(' ')));
}
