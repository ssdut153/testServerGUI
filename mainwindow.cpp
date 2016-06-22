#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QtGui>
#include <QString>
#include <QtSql>
#include "sqlite.h"
#include "helper.h"
#include "myclient.h"
#include <vector>
QTcpSocket *client;
QTcpServer *server;
std::vector<MyClient> clients;
QSignalMapper *signalMapper;
Sqlite *sqlite;
int clientSize=0;
void MainWindow::acceptConnection()
{
    QString tem;
    QTextStream(&tem)<<"test"<<clientSize;
    ui->textEdit->append(tem);
    clients.push_back(MyClient(tem.toStdString(),server->nextPendingConnection(),clientSize++));

    //clientConnection = clients[clientSize-1].client;

    QString conne;
    QTextStream(&conne)<<"New connection:"<<clients[clientSize-1].client->peerName()<<"\t"<<clients[clientSize-1].client->peerAddress().toString()<<"\t"<<clients[clientSize-1].client->peerPort();
    ui->textEdit->append(conne);

    connect(clients[clientSize-1].client, SIGNAL(readyRead()), signalMapper, SLOT(map()));
    signalMapper->setMapping(clients[clientSize-1].client, clientSize-1);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(readClient(int)));

    //connect(clients[clientSize-1].client, SIGNAL(readyRead()), this, SLOT(readClient(QTcpSocket*)));
}

void MainWindow::readClient(int ind)
{
    QTcpSocket* tempSocket;
    for (int i=0;i<clientSize;i++)
    {
        if(clients[i].index==ind)
        {
            tempSocket=clients[i].client;
            break;
        }
    }
    QString str = tempSocket->readAll();
    //下列代码实现read会乱码不论中英文
    //char buf[1024];
    //clientConnection->read(buf,1024);

    if(!str.isEmpty())
    {
        ui->textEdit->append(str);
        tempSocket->write("I received your message:");
        tempSocket->write(str.toStdString().c_str());
    }
    //clientConnection->close();
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();
    server->listen(QHostAddress::Any, 6665);
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
    signalMapper = new QSignalMapper(this);
    //  初始化Sqlite类
    sqlite=new Sqlite();
    QSqlQuery query;//以下执行相关QSL语句


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    QTcpSocket* tempSocket;
    for (int i=0;i<clientSize;i++)
    {
        if(clients[i].username==ui->textEdit_3->toPlainText().toStdString())
        {
            tempSocket=clients[i].client;
            break;
        }
    }
    std::string str = ui->textEdit_2->toPlainText().toStdString();
    const char* ch = str.c_str();
    tempSocket->write(ch);
    ui->textEdit_2->setPlainText("");
}

void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query;
    ui->textEdit->append(query.exec("select * from users")?"select true":"select error");
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString ele0=query.value(0).toString();//query.value(0)是id的值，将其转换为int型
        QString ele1=query.value(1).toString();
        QString ele2=query.value(2).toString();//query.value(0)是id的值，将其转换为int型
        QString ele3=query.value(3).toString();
        QString ele4=query.value(4).toString();//query.value(0)是id的值，将其转换为int型
        QString ele5=query.value(5).toString();
        QString ele6=query.value(6).toString();//query.value(0)是id的值，将其转换为int型
        QString ele7=query.value(7).toString();
        QString ele8=query.value(8).toString();//query.value(0)是id的值，将其转换为int型
        QString ele9=query.value(9).toString();
        ui->textEdit->append(ele0+"  "+ele1+"  "+ele2+"  "+ele3+"  "+ele4+"  "+ele5+"  "+ele6+"  "+ele7+"  "+ele8+"  "+ele9);//输出两个值
    }

}



void MainWindow::on_pushButton_3_clicked()
{
    //char temp[3];
    //itoa(Helper::lenofchararrau("123"),temp,10);
    //ui->textEdit->append(temp);
    //sqlite->reguser("testuser3","testuser","0");
    ui->textEdit->append(sqlite->checkpassword("testuser3","testuser")?"check true":"check false");
    ui->textEdit->append(sqlite->checkpassword("testuser4","testuser3")?"check true":"check false");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->append(Helper::getsalt(8));
}
