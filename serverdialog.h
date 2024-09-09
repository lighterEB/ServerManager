#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include "server.h"

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = nullptr, const Server *server = nullptr);
    Server getServer() const;
    bool isValid() const;

private:
    QLineEdit *nameEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *ipEdit;
    QSpinBox *portSpinBox;
    bool isValidIpFormat(const QString &ip) const;
};

#endif // SERVERDIALOG_H
