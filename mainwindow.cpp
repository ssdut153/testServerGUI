#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
QTcpServer *server;
QTcpSocket *clientConnection;

void MainWindow::acceptConnection()
{
    clientConnection = server->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));
}

void MainWindow::readClient()
{
    QString str = clientConnection->readAll();
    //下列代码实现read会乱码不论中英文
    //char buf[1024];
    //clientConnection->read(buf,1024);
    ui->textEdit->append(str);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();
    server->listen(QHostAddress::Any, 6665);
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
