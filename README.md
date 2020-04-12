# Audit-Logging-System
This repo contains a lightweight logging module for Qt-based C++ projects. The logging system utilizes a Meyers Singleton design pattern.
It is thread-safe and cross-platform compatible. The following macros are used to log messages directly to files:

* AUDIT_INFO()
* AUDIT_DEBUG()
* AUDIT_WARNING()
* AUDIT_CRITICAL()
* AUDIT_FATAL()

The log files are saved to the following locations:

Windows: C:/Users/\<USER\>/.AuditLogs/
Linux: ~/.AuditLogs/
