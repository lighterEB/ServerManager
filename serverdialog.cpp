#include "serverdialog.h"
#include <QFormLayout>
#include <QPushButton>
#include <QDialogButtonBox>

ServerDialog::ServerDialog(QWidget *parent, const Server *server)
    : QDialog(parent)
{
    setWindowTitle(server ? "编辑服务器" : "添加服务器");

    nameEdit = new QLineEdit(this);
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    ipEdit = new QLineEdit(this);
    portSpinBox = new QSpinBox(this);
    portSpinBox->setRange(1, 65535);
    portSpinBox->setValue(22);

    if (server) {
        nameEdit->setText(server->getName());
        usernameEdit->setText(server->getUsername());
        passwordEdit->setText(server->getPassword());
        ipEdit->setText(server->getIp());
        portSpinBox->setValue(server->getPort());
    }

    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("名称:", nameEdit);
    formLayout->addRow("用户名:", usernameEdit);
    formLayout->addRow("密码:", passwordEdit);
    formLayout->addRow("IP地址:", ipEdit);
    formLayout->addRow("端口:", portSpinBox);


    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    // 创建自定义按钮并设置中文文本
    QPushButton *okButton = buttonBox->button(QDialogButtonBox::Ok);
    QPushButton *cancelButton = buttonBox->button(QDialogButtonBox::Cancel);
    okButton->setText("确定");
    cancelButton->setText("取消");

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);
}

bool ServerDialog::isValid() const
{
    return !nameEdit->text().isEmpty() &&
           !usernameEdit->text().isEmpty() &&
           !passwordEdit->text().isEmpty() &&
           !ipEdit->text().isEmpty();
}

Server ServerDialog::getServer() const
{
    if (!isValid()) {
        throw std::runtime_error("无效的服务器信息");
    }
    return Server(nameEdit->text(), usernameEdit->text(), passwordEdit->text(),
                  ipEdit->text(), portSpinBox->value());
}
