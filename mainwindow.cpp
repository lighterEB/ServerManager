#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include "serverdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connectSlots();
    refreshServerList();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUi()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    searchBox = new QLineEdit(this);
    searchBox->setPlaceholderText("搜索服务器...");
    mainLayout->addWidget(searchBox);

    serverList = new QListWidget(this);
    mainLayout->addWidget(serverList);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("添加", this);
    editButton = new QPushButton("编辑", this);
    deleteButton = new QPushButton("删除", this);
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);

    setCentralWidget(centralWidget);
}

void MainWindow::connectSlots()
{
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addServer);
    connect(editButton, &QPushButton::clicked, this, &MainWindow::editServer);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteServer);
    connect(searchBox, &QLineEdit::textChanged, this, &MainWindow::searchServers);
}

void MainWindow::addServer()
{
    ServerDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Server newServer = dialog.getServer();
        if (dbManager.addServer(newServer)) {
            refreshServerList();
            QMessageBox::information(this, "成功", "服务器添加成功");
        } else {
            QMessageBox::warning(this, "错误", "添加服务器失败");
        }
    }
}

void MainWindow::editServer()
{
    QListWidgetItem *currentItem = serverList->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "警告", "请先选择一个服务器");
        return;
    }

    QString name = currentItem->text();
    QVector<Server> servers = dbManager.searchServers(name);
    if (servers.isEmpty()) return;

    Server server = servers.first();
    ServerDialog dialog(this, &server);
    if (dialog.exec() == QDialog::Accepted) {
        Server updatedServer = dialog.getServer();
        if (dbManager.updateServer(updatedServer)) {
            refreshServerList();
            QMessageBox::information(this, "成功", "服务器更新成功");
        } else {
            QMessageBox::warning(this, "错误", "更新服务器失败");
        }
    }
}

void MainWindow::deleteServer()
{
    QListWidgetItem *currentItem = serverList->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "警告", "请先选择一个服务器");
        return;
    }

    QString name = currentItem->text();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "确认删除", "确定要删除服务器 " + name + " 吗？",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if (dbManager.deleteServer(name)) {
            refreshServerList();
        } else {
            QMessageBox::warning(this, "错误", "删除服务器失败");
        }
    }
}

void MainWindow::searchServers()
{
    QString keyword = searchBox->text();
    QVector<Server> servers = dbManager.searchServers(keyword);
    serverList->clear();
    for (const Server &server : servers) {
        serverList->addItem(server.getName());
    }
}

void MainWindow::refreshServerList()
{
    QVector<Server> servers = dbManager.getAllServers();
    serverList->clear();
    for (const Server &server : servers) {
        serverList->addItem(server.getName());
    }
}
