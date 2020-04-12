#include "auditlogmanager.h"
#include "auditlogfileoperations.h"

QMutex AuditLogManager::lock(QMutex::Recursive);
LogEnvironment AuditLogManager::environment = LogEnvironment::Disabled;

AuditLogManager::AuditLogManager()
{
    if(environment != LogEnvironment::Disabled)
    {
        fileOperations = std::make_shared<AuditLogFileOperations>();

        fileOperationsThread.start();
        fileOperations->moveToThread(&fileOperationsThread);

        connect(this, &AuditLogManager::logRequest, fileOperations.get(), &AuditLogFileOperations::streamToFile);
    }
    setEnabledLogMsgTypes();
}

AuditLogManager& AuditLogManager::getInstance()
{
    static AuditLogManager instance;
    return instance;
}

void AuditLogManager::setLoggingEnvironment(LogEnvironment env)
{
    QMutexLocker locker(&lock);

    environment = env;
}

QString AuditLogManager::logMsgTypeToString(LogMsgType type)
{
    switch(type)
    {
        case (LogMsgType::Info) :
            return "Info";

        case (LogMsgType::Debug) :
            return "Debug";

        case (LogMsgType::Warning) :
            return "Warning";

        case (LogMsgType::Critical) :
            return "Critical";

        case (LogMsgType::Fatal) :
            return "Fatal";
    }
    return "Unknown";
}

bool AuditLogManager::isLogMsgTypeEnabled(LogMsgType type) const
{
    return (std::find(enabledMsgTypes.begin(), enabledMsgTypes.end(), type) != enabledMsgTypes.end());
}

void AuditLogManager::processLogEntry(const QString message) const
{
    emit getInstance().logRequest(message);
}

AuditLogManager::~AuditLogManager()
{
    if(fileOperations != nullptr)
    {
        fileOperations->closeLogFile();
    }
}

void AuditLogManager::setEnabledLogMsgTypes()
{
    switch(environment)
    {
        case (LogEnvironment::Production):

            enabledMsgTypes = {LogMsgType::Info,
                               LogMsgType::Warning,
                               LogMsgType::Critical,
                               LogMsgType::Fatal};
            break;

        case (LogEnvironment::Development):

            enabledMsgTypes = {LogMsgType::Info,
                               LogMsgType::Debug,
                               LogMsgType::Warning,
                               LogMsgType::Critical,
                               LogMsgType::Fatal};
            break;

        default:
            enabledMsgTypes = {};
            break;
    }
}
