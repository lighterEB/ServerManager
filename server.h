#ifndef SERVER_H
#define SERVER_H

#include <QString>

class Server
{
public:
    Server();
    Server(const QString &name, const QString &username, const QString &password,
           const QString &ip, int port);

    QString getName() const;
    void setName(const QString &name);

    QString getUsername() const;
    void setUsername(const QString &username);

    QString getPassword() const;
    void setPassword(const QString &password);

    QString getIp() const;
    void setIp(const QString &ip);

    int getPort() const;
    void setPort(int port);

private:
    QString m_name;
    QString m_username;
    QString m_password;
    QString m_ip;
    int m_port;
};

#endif // SERVER_H
