#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QtGui>
#include <QString>
#include <QtSql>
#include "sqlite.h"
#include "helper.h"
#include <vector>
#include "common/allmessage.h"
//#include <QMessageBox>
//  TODO：增加日志写到文件的功能
QTcpServer *server;

int clientSize=0;
std::vector<MyClient> clients;
QSignalMapper *signalMapper;
//QSignalMapper *signalMapper2;

Sqlite *sqlite;

void MainWindow::acceptConnection()
{
    QString tem;
    QTextStream(&tem)<<"temp"<<clientSize;
    //ui->textEdit->append(tem);
    clients.push_back(MyClient(tem.toStdString(),server->nextPendingConnection(),clientSize++));
    //clientConnection = clients[clientSize-1].client;

    QString conne;
    QTextStream(&conne)<<"New connection: "<<clients[clientSize-1].client->peerAddress().toString()<<"\t"<<clients[clientSize-1].client->peerPort()<<" @"<<Helper::getDateTime();
    ui->textEdit->append(conne);

    connect(clients[clientSize-1].client, SIGNAL(readyRead()), signalMapper, SLOT(map()));
    signalMapper->setMapping(clients[clientSize-1].client, clientSize-1);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(readClient(int)));

    //  TODO：绑定离线事件
    //connect(clients[clientSize-1].client, SIGNAL(disConnected()), signalMapper2, SLOT(map()));
    //signalMapper2->setMapping(clients[clientSize-1].client, clientSize-1);
    //connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(disconnect(int)));
    //connect(clients[clientSize-1].client, SIGNAL(readyRead()), this, SLOT(readClient(QTcpSocket*)));
}
QString login(std::string textJson,MyClient* socket,int ind)
{
    loginMessage loginmessage;
    QString res;
    loginmessage.loadfromJson(textJson);

    if(sqlite->checkpassword(loginmessage.user.c_str(),loginmessage.pass.c_str()))
    {
        loginFeedBackMessage feedback(loginmessage.user,"true");
        socket->username=loginmessage.user;
        socket->client->write(feedback.getJsonString().c_str());
        QTextStream(&res)<<loginmessage.user.c_str()<<" log in success @"<<Helper::getDateTime()<<" &scoketName:"<<QString::fromStdString(clients[ind].username);

        //  TODO：强制已在线同一用户名登出
    }
    else
    {
        loginFeedBackMessage feedback(loginmessage.user,"false");
        socket->client->write(feedback.getJsonString().c_str());
        QTextStream(&res)<<loginmessage.user.c_str()<<" log in fail @"<<Helper::getDateTime();
    }
    return res;
}
QString regUser(std::string textJson,MyClient* socket,int ind)
{
    regUserMessage regusermessage;
    QString res;
    regusermessage.loadfromJson(textJson);

    if(sqlite->reguser(regusermessage.user.c_str(),regusermessage.pass.c_str(),"0"))
    {
        regFeedBackMessage feedback(regusermessage.user,"true");
        socket->client->write(feedback.getJsonString().c_str());
        QTextStream(&res)<<regusermessage.user.c_str()<<" reg success @"<<Helper::getDateTime();
    }
    else
    {
        loginFeedBackMessage feedback(regusermessage.user,"false");
        socket->client->write(feedback.getJsonString().c_str());
        QTextStream(&res)<<regusermessage.user.c_str()<<" reg fail @"<<Helper::getDateTime();
    }
    return res;
}
void MainWindow::disconnect(int ind)
{
    for (int i=0;i<clientSize;i++)
    {
        if(clients[i].index==ind)
        {
            clients.erase(clients.begin()+i);
            return;
        }
    }
    //clientConnection->close();
}
void offline(std::string username){}

void MainWindow::readClient(int ind)
{
    QTcpSocket* tempSocket;
    int i=0;
    for (;i<clientSize;i++)
    {
        if(clients[i].index==ind)
        {
            tempSocket=clients[i].client;
            break;
        }
    }
    QString str = tempSocket->readAll();

    //  解析消息类型
    if(!str.isEmpty())
    {
        //std::string head="login";
        std::string head=Helper::getHeadfromJson(str.toStdString());
        if(head=="login")
            ui->textEdit->append(login(str.toStdString(),&clients[i],i));
        else if(head=="logout")
        {
            QString log;
            QTextStream(&log)<<QString::fromStdString(clients[i].username)<<" log out @"<<Helper::getDateTime();
            offline(clients[i].username);
            clientSize--;
            clients.erase(clients.begin()+i);
            ui->textEdit->append(log);
        }
        else if(head=="regUser")
            ui->textEdit->append(regUser(str.toStdString(),&clients[i],i));
        else
        {
            QString log;
            QTextStream(&log)<<str<<" @"<<Helper::getDateTime();
            ui->textEdit->append(log);
            tempSocket->write("I received your message:");
            tempSocket->write(str.toStdString().c_str());
        }
    }
    //clientConnection->close();
}
//{"head":"login","username":"testuser88","password":"testuser"}
//{"head":"logout","username":"testuser88"}
//{"head":"regUser","username":"testuser","password":"testuser"}

//create table users(uid integer primary key autoincrement,username varchar(20) UNIQUE,salt varchar(10),password varchar(70),regdate datetime,ip varchar(20),logindate datetime,vip int)
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
/*
    loginMessage test("testuser","testpassword");
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));
    loginMessage testload;
    testload.loadfromJson(tempjson);
    ui->textEdit->append(QString::fromStdString(testload.user));
    ui->textEdit->append(QString::fromStdString(testload.pass));
*//*
    loginFeedBackMessage test("testuser","true");
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));

    loginFeedBackMessage testload;
    testload.loadfromJson(tempjson);
    ui->textEdit->append(QString::fromStdString(testload.user));
    ui->textEdit->append(QString::fromStdString(testload.stat));
*//*
    logoutMessage test("testuser");
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));

    logoutMessage testload;
    testload.loadfromJson(tempjson);
    ui->textEdit->append(QString::fromStdString(testload.user));
*//*
    regUserMessage test("testuser","testpassword");
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));
    regUserMessage testload;
    testload.loadfromJson(tempjson);
    ui->textEdit->append(QString::fromStdString(testload.user));
    ui->textEdit->append(QString::fromStdString(testload.pass));
*//*
    regFeedBackMessage test("testuser","true");
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));

    regFeedBackMessage testload;
    testload.loadfromJson(tempjson);
    ui->textEdit->append(QString::fromStdString(testload.user));
    ui->textEdit->append(QString::fromStdString(testload.stat));
*/
    ui->textEdit->append(Helper::getDateTime());
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

    QString res;
    if(sqlite->queryexec(ui->textEdit_2->toPlainText().toStdString().c_str()))
        QTextStream(&res)<<"sql:"<<ui->textEdit_2->toPlainText()<<"\texec true";
    else
        QTextStream(&res)<<"sql:"<<ui->textEdit_2->toPlainText()<<"\texec false";
    ui->textEdit->append(res);
   // sqlite->reguser(ui->textEdit_3->toPlainText().toStdString().c_str(),ui->textEdit_2->toPlainText().toStdString().c_str(),"0");
   // ui->textEdit_2->setPlainText("");
    //ui->textEdit_3->setPlainText("");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->append(Helper::getsalt(8));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    //QMessageBox msg(QMessageBox::Warning, "警告", "您真的要退出吗?", 0, 0);
    //msg.setWindowFlags(Qt::WindowStaysOnTopHint| (this->windowFlags() &~ (Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)));
    //msg.addButton("是", QMessageBox::AcceptRole);
    //msg.addButton("否", QMessageBox::RejectRole);
    //if (msg.exec() == QMessageBox::RejectRole)
    //{
    //    event->ignore();
    //}
}
