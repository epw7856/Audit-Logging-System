#ifndef AUDITLOGMANAGER_H
#define AUDITLOGMANAGER_H

#include <QThread>
#include <QMutex>

class AuditLogFileOperations;

enum class LogEnvironment
{
    Disabled,
    Production,
    Development
};

enum class LogMsgType
{
    Info,
    Debug,
    Warning,
    Critical,
    Fatal
};

class AuditLogManager : public QObject
{
    Q_OBJECT

public:
    static AuditLogManager& getInstance();
    static void setLoggingEnvironment(LogEnvironment env);
    static QString logMsgTypeToString(LogMsgType type);
    bool isLogMsgTypeEnabled(LogMsgType type) const;
    void processLogEntry(const QString message) const;

signals:
    void logRequest(QString message);

private:
    AuditLogManager();
    ~AuditLogManager();
    AuditLogManager(const AuditLogManager&) = delete;
    AuditLogManager& operator=(const AuditLogManager&) = delete;

    static QMutex lock;
    static LogEnvironment environment;
    std::shared_ptr<AuditLogFileOperations> fileOperations = nullptr;
    QThread fileOperationsThread;
    std::vector<LogMsgType> enabledMsgTypes = {};

    void setEnabledLogMsgTypes();

};

#endif // AUDITLOGMANAGER_H
