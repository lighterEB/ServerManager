#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include "databasemanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addServer();
    void editServer();
    void deleteServer();
    void searchServers();
    void refreshServerList();

private:
    QListWidget *serverList;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QLineEdit *searchBox;
    DatabaseManager dbManager;

    void setupUi();
    void connectSlots();
};

#endif // MAINWINDOW_H
