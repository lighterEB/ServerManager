#include "server.h"

Server::Server() : m_port(0) {}

Server::Server(const QString &name, const QString &username, const QString &password,
               const QString &ip, int port)
    : m_name(name), m_username(username), m_password(password), m_ip(ip), m_port(port)
{}

QString Server::getName() const { return m_name; }
void Server::setName(const QString &name) { m_name = name; }

QString Server::getUsername() const { return m_username; }
void Server::setUsername(const QString &username) { m_username = username; }

QString Server::getPassword() const { return m_password; }
void Server::setPassword(const QString &password) { m_password = password; }

QString Server::getIp() const { return m_ip; }
void Server::setIp(const QString &ip) { m_ip = ip; }

int Server::getPort() const { return m_port; }
void Server::setPort(int port) { m_port = port; }
