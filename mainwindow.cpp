#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QtGui>
#include <QString>
#include <QtSql>
#include "sqlite.h"
#include "helper.h"
QTcpServer *server;
QTcpSocket *clientConnection;
Sqlite *sqlite;
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
    //ui->textEdit->append(helloworld());
    sqlite=new Sqlite();
    QSqlQuery query;//以下执行相关QSL语句
    //query.exec("create table users(id integer PRIMARY KEY autoincrement,username varchar(10) not null,salt varchar(10) not null,password varchar(70) not null,regdate datetime,ip int unsigned,port int,logindate datetime,logoutdate datetime,vip int)");    //新建student表，id设置为主键，还有一个name项
//ui->textEdit->append(query.lastError().text());

    query.exec("select id,name from student where id>=1");
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString ele0=query.value(0).toString();//query.value(0)是id的值，将其转换为int型
        QString ele1=query.value(1).toString();
        ui->textEdit->append(ele0+"  "+ele1);//输出两个值
    }
    //query.exec(QObject::tr("drop student"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query;
    ui->textEdit->append("exec:"+ui->textEdit_2->toPlainText());
    ui->textEdit->append(query.exec(ui->textEdit_2->toPlainText())?"exec true":"exec false");
    ui->textEdit_2->setPlainText("");
}
/*
 * insert into users (username,password,salt,regdate) values('testuser','testpassword','testsalt','2016-6-22 9:56')
 * */
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
