#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlError>
#include <QSqlDatabase>

DatabaseManager::DatabaseManager()
{
    initDatabase();
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isOpen())
        m_db.close();
}

bool DatabaseManager::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("servers.db");

    if (!m_db.open()) {
        qDebug() << "Error: connection with database failed";
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS servers "
               "(name TEXT PRIMARY KEY, "
               "username TEXT, "
               "password TEXT, "
               "ip TEXT, "
               "port INTEGER)");

    return true;
}

bool DatabaseManager::addServer(const Server &server)
{
    QSqlQuery query;
    query.prepare("INSERT INTO servers (name, username, password, ip, port) "
                  "VALUES (:name, :username, :password, :ip, :port)");
    query.bindValue(":name", server.getName());
    query.bindValue(":username", server.getUsername());
    query.bindValue(":password", server.getPassword());
    query.bindValue(":ip", server.getIp());
    query.bindValue(":port", server.getPort());

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "addServer error:" << query.lastError();
        return false;
    }
}

bool DatabaseManager::updateServer(const Server &server)
{
    QSqlQuery query;
    query.prepare("UPDATE servers SET username=:username, password=:password, "
                  "ip=:ip, port=:port WHERE name=:name");
    query.bindValue(":name", server.getName());
    query.bindValue(":username", server.getUsername());
    query.bindValue(":password", server.getPassword());
    query.bindValue(":ip", server.getIp());
    query.bindValue(":port", server.getPort());

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "updateServer error:" << query.lastError();
        return false;
    }
}

bool DatabaseManager::deleteServer(const QString &name)
{
    QSqlQuery query;
    query.prepare("DELETE FROM servers WHERE name = :name");
    query.bindValue(":name", name);

    if (query.exec()) {
        return true;
    } else {
        qDebug() << "deleteServer error:" << query.lastError();
        return false;
    }
}

QVector<Server> DatabaseManager::getAllServers()
{
    QVector<Server> servers;
    QSqlQuery query("SELECT * FROM servers");
    while (query.next()) {
        Server server(
            query.value("name").toString(),
            query.value("username").toString(),
            query.value("password").toString(),
            query.value("ip").toString(),
            query.value("port").toInt()
            );
        servers.push_back(server);
    }
    return servers;
}

QVector<Server> DatabaseManager::searchServers(const QString &keyword)
{
    QVector<Server> servers;
    QSqlQuery query;
    query.prepare("SELECT * FROM servers WHERE name LIKE :keyword OR ip LIKE :keyword");
    query.bindValue(":keyword", "%" + keyword + "%");

    if (query.exec()) {
        while (query.next()) {
            Server server(
                query.value("name").toString(),
                query.value("username").toString(),
                query.value("password").toString(),
                query.value("ip").toString(),
                query.value("port").toInt()
                );
            servers.push_back(server);
        }
    } else {
        qDebug() << "searchServers error:" << query.lastError();
    }
    return servers;
}

// 实现其他方法 (updateServer, deleteServer, getAllServers, searchServers)...
