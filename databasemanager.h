#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QVector>
#include "server.h"

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    bool addServer(const Server &server);
    bool updateServer(const Server &server);
    bool deleteServer(const QString &name);
    QVector<Server> getAllServers();
    QVector<Server> searchServers(const QString &keyword);

private:
    QSqlDatabase m_db;
    bool initDatabase();
};

#endif // DATABASEMANAGER_H
