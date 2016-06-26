/*****************************************************************************************
 *  Copyright(c) 2016 Yang Zhizhuang (Software School of Dalian University of Technology)
 *  All rights reserved.
 *
 *  文件名称: mainwindow.cpp
 *  简要描述:
 *
 *  创建日期: 2016-6-21
 *  作者: Yang Zhizhuang
 *  说明: 收到logout消息时没有断开并移除相应的连接
 *
 *  修改日期:
 *  作者:
 *  说明:
 ****************************************************************************************/
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
#include "common/allmessage.h"

//#include <QMessageBox>
//  TODO：增加日志写到文件的功能
char* logpath;
QTcpServer *server;

int clientSize=0;
std::vector<MyClient> clients;
QSignalMapper *signalMapper;
//QSignalMapper *signalMapper2;

Sqlite *sqlite;
/**
 * @brief MainWindow::acceptConnection
 * SLOT:建立新TCP连接
 */
void MainWindow::acceptConnection()
{
    QString tem;
    QTextStream(&tem)<<"temp"<<clientSize;
    clients.push_back(MyClient(tem.toStdString(),server->nextPendingConnection(),clientSize++));

    QString conne;
    QTextStream(&conne)<<"New connection: "<<clients[clientSize-1].client->peerAddress().toString()<<"\t"<<clients[clientSize-1].client->peerPort()<<" @"<<Helper::getDateTime();
    if(Helper::log(conne.toStdString().c_str(),logpath))
        ui->textEdit->append(conne);
    else
    {
        QTextStream(&conne)<<" log failed";
        ui->textEdit->append(conne);
    }

    connect(clients[clientSize-1].client, SIGNAL(readyRead()), signalMapper, SLOT(map()));
    signalMapper->setMapping(clients[clientSize-1].client, clientSize-1);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(readClient(int)));

    //  TODO：绑定离线事件
    //connect(clients[clientSize-1].client, SIGNAL(disConnected()), signalMapper2, SLOT(map()));
    //signalMapper2->setMapping(clients[clientSize-1].client, clientSize-1);
    //connect(signalMapper2, SIGNAL(mapped(int)), this, SLOT(disconnect(int)));
    //connect(clients[clientSize-1].client, SIGNAL(readyRead()), this, SLOT(readClient(QTcpSocket*)));
}
/**
 * @brief login
 * @param textJson Json字符串
 * @param socket MyClient类
 * @param ind Index
 * @return QString log
 */
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
/**
 * @brief regUser
 * @param textJson Json字符串
 * @param socket MyClient类
 * @param ind Index
 * @return  QString log
 */
QString regUser(std::string textJson,MyClient* socket)
{
    regUserMessage regusermessage;
    QString res;
    regusermessage.loadfromJson(textJson);

    if(sqlite->reguser(regusermessage.user.c_str(),regusermessage.pass.c_str(),"0"))
    {
        regFeedBackMessage feedback(regusermessage.user, "true");
        socket->client->write(feedback.getJsonString().c_str());
        QTextStream(&res)<<regusermessage.user.c_str()<<" reg success @"<<Helper::getDateTime();
    }
    else
    {
        regFeedBackMessage feedback(regusermessage.user,"false");
        socket->client->write(feedback.getJsonString().c_str());
        QTextStream(&res)<<regusermessage.user.c_str()<<" reg fail @"<<Helper::getDateTime();
    }
    return res;
}
/**
 * @brief getFriendList
 * @param textJson Json字符串
 * @param socket MyClient类
 * @param ind Index
 * @return  QString log
 */
QString getFriendList(std::string textJson,MyClient* socket)
{
    getFriendListMessage getfriendlistmessage;
    QString res;
    getfriendlistmessage.loadfromJson(textJson);

    if(sqlite->sendfriendlist(getfriendlistmessage.user.c_str(),socket->client))
    {
        QTextStream(&res)<<getfriendlistmessage.user.c_str()<<" send friend list success @"<<Helper::getDateTime();
    }
    else
    {
        QTextStream(&res)<<getfriendlistmessage.user.c_str()<<" send friend list fail @"<<Helper::getDateTime();
    }
    return res;
}
/**
 * @brief offline
 * @param username 用户名
 */
std::string offline(std::string username){return username;}
/**
 * @brief MainWindow::readClient
 * SLOT:读取数据
 * @param ind Index
 */
void MainWindow::readClient(int ind)
{
    QTcpSocket* tempSocket=NULL;
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
        {
            QString log=login(str.toStdString(),&clients[i],i);
            if(Helper::log(log.toStdString().c_str(),logpath))
                ui->textEdit->append(log);
            else
            {
                QTextStream(&log)<<" log failed";
                ui->textEdit->append(log);
            }
            return;
        }
        else if(head=="logout")
        {
            logoutMessage logoutmessage;
            logoutmessage.loadfromJson(str.toStdString());
            QString log;
            QTextStream(&log)<<QString::fromStdString(logoutmessage.user)<<" log out @"<<Helper::getDateTime();
            offline(logoutmessage.user);
            //移除前要disconnect
            //clients[i].client=NULL;
            //clients[i].username="~logout";
            //clients.erase(clients.begin()+i);
            //clientSize--;
            if(Helper::log(log.toStdString().c_str(),logpath))
                ui->textEdit->append(log);
            else
            {
                QTextStream(&log)<<" log failed";
                ui->textEdit->append(log);
            }
            return;
        }
        else if(head=="regUser")
        {
            QString log=regUser(str.toStdString(),&clients[i]);
            if(Helper::log(log.toStdString().c_str(),logpath))
                ui->textEdit->append(log);
            else
            {
                QTextStream(&log)<<" log failed";
                ui->textEdit->append(log);
            }
            return;
        }
        else if(head=="getFriendList")
        {
            QString log=getFriendList(str.toStdString(),&clients[i]);
            if(Helper::log(log.toStdString().c_str(),logpath))
                ui->textEdit->append(log);
            else
            {
                QTextStream(&log)<<" log failed";
                ui->textEdit->append(log);
            }
            return;
        }
        else if(head=="p2p")
        {
            QString log;
            p2pMessage p2pmessage;
            p2pmessage.loadfromJson(str.toStdString());
            if(clients[i].username!=p2pmessage.FromUserName)
            {
                feedBackMessage sendfailmessage(p2pmessage.ToUserName,"sendfail");
                tempSocket->write(sendfailmessage.getJsonString().c_str());
                QTextStream(&log)<<p2pmessage.FromUserName.c_str()<<" to "<<p2pmessage.ToUserName.c_str()<<" not same user @"<<p2pmessage.CreateTime.c_str();
                if(Helper::log(log.toStdString().c_str(),logpath))
                    ui->textEdit->append(log);
                else
                {
                    QTextStream(&log)<<" log failed";
                    ui->textEdit->append(log);
                }
                return;
            }
            if(!sqlite->isfriend(p2pmessage.ToUserName.c_str(),p2pmessage.FromUserName.c_str()))
            {
                feedBackMessage sendfailmessage(p2pmessage.ToUserName,"sendfail");
                tempSocket->write(sendfailmessage.getJsonString().c_str());
                QTextStream(&log)<<p2pmessage.FromUserName.c_str()<<" to "<<p2pmessage.ToUserName.c_str()<<" not friend @"<<p2pmessage.CreateTime.c_str();
                if(Helper::log(log.toStdString().c_str(),logpath))
                    ui->textEdit->append(log);
                else
                {
                    QTextStream(&log)<<" log failed";
                    ui->textEdit->append(log);
                }
                return;
            }
            QTcpSocket* tempSocket2=NULL;
            bool flag=false;
            for (int i=0;i<clientSize;i++)
            {
                if(clients[i].username==p2pmessage.ToUserName)
                {
                    tempSocket2=clients[i].client;
                    flag=true;
                    break;
                }
            }
            if(flag)
            {
                tempSocket2->write(p2pmessage.getJsonString().c_str());
                feedBackMessage sendsuccessmessage(p2pmessage.ToUserName,"sendsuccess");
                tempSocket->write(sendsuccessmessage.getJsonString().c_str());
                QTextStream(&log)<<p2pmessage.FromUserName.c_str()<<" to "<<p2pmessage.ToUserName.c_str()<<" send success @"<<p2pmessage.CreateTime.c_str();
            }
            else
            {
                feedBackMessage sendfailmessage(p2pmessage.ToUserName,"sendfail");
                tempSocket->write(sendfailmessage.getJsonString().c_str());
                QTextStream(&log)<<p2pmessage.FromUserName.c_str()<<" to "<<p2pmessage.ToUserName.c_str()<<" send fail @"<<p2pmessage.CreateTime.c_str();
            }
            if(Helper::log(log.toStdString().c_str(),logpath))
                ui->textEdit->append(log);
            else
            {
                QTextStream(&log)<<" log failed";
                ui->textEdit->append(log);
            }
            return;
        }
        else
        {
            QString log;
            QTextStream(&log)<<str<<" @"<<Helper::getDateTime();
            tempSocket->write("I received your message:");
            tempSocket->write(str.toStdString().c_str());
            if(Helper::log(log.toStdString().c_str(),logpath))
                ui->textEdit->append(log);
            else
            {
                QTextStream(&log)<<" log failed";
                ui->textEdit->append(log);
            }
            return;
        }
    }
    //clientConnection->close();
}
//{"head":"login","username":"testuser88","password":"testuser"}
//{"head":"logout","username":"testuser88"}
//{"head":"regUser","username":"testuser","password":"testuser"}
//{"head":"p2p","fromusername":"testuser1","tousername":"testuser2","createtime":"2016-6-26 20:9:35","content":"hello"}

//create table users(uid integer primary key autoincrement,username varchar(20) UNIQUE,salt varchar(10),password varchar(70),regdate datetime,ip varchar(20),logindate datetime,vip int)
/**
 * @brief MainWindow::MainWindow
 * 窗口主程序
 * @param parent
 */
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
*
    regFeedBackMessage test("testuser","true");
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));

    regFeedBackMessage testload;
    testload.loadfromJson(tempjson);
    ui->textEdit->append(QString::fromStdString(testload.user));
    ui->textEdit->append(QString::fromStdString(testload.stat));
*//*
    getFriendListMessage test;
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));

    getFriendListMessage testload;
    testload.loadfromJson(tempjson);
    ui->textEdit->append(QString::fromStdString(testload.head));
*//*{"head":"getFriendList","username":"testuser1"}
    std::string tempjson("[{\"username\":\"testuser3\"},{\"username\":\"testuser2\"},{\"username\":\"testuser4\"}]");

    friendListMessage testload;
    testload.loadfromJson(tempjson);
    for(int i=0;i<testload.size;i++)
        ui->textEdit->append(QString::fromStdString(testload.user[i]));
*/
    //  UUID
    //ui->textEdit->append(Helper::newuuid());
    /*
    p2pMessage test("testuser1","testuser2","hello");
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));

    p2pMessage testload;
    testload.loadfromJson(tempjson);
    ui->textEdit->append(QString::fromStdString(testload.head));
    ui->textEdit->append(QString::fromStdString(testload.FromUserName));
    ui->textEdit->append(QString::fromStdString(testload.ToUserName));
    ui->textEdit->append(QString::fromStdString(testload.CreateTime));
    ui->textEdit->append(QString::fromStdString(testload.Content));
    */
    //************************************************************

    logpath=(char*)malloc(sizeof(char)*1024);
    Helper::getLogPath(logpath);
    QString log;
    QTextStream(&log)<<"Server start @"<<Helper::getDateTime();
    if(Helper::log(log.toStdString().c_str(),logpath))
        ui->textEdit->append(log);
    else
    {
        QTextStream(&log)<<" log failed";
        ui->textEdit->append(log);
    }
}
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::on_pushButton_clicked
 */
void MainWindow::on_pushButton_clicked()
{

    QTcpSocket* tempSocket=NULL;
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
/**
 * @brief MainWindow::on_pushButton_2_clicked
 */
void MainWindow::on_pushButton_2_clicked()
{
    QSqlQuery query;
    ui->textEdit->append(query.exec("select * from users")?"select true":"select error");
    while(query.next())//query.next()指向查找到的第一条记录，然后每次后移一条记录
    {
        QString ele0=query.value(0).toString();
        QString ele1=query.value(1).toString();
        QString ele2=query.value(2).toString();
        QString ele3=query.value(3).toString();
        QString ele4=query.value(4).toString();
        QString ele5=query.value(5).toString();
        QString ele6=query.value(6).toString();
        QString ele7=query.value(7).toString();
        QString ele8=query.value(8).toString();
        QString ele9=query.value(9).toString();
        ui->textEdit->append(ele0+"  "+ele1+"  "+ele2+"  "+ele3+"  "+ele4+"  "+ele5+"  "+ele6+"  "+ele7+"  "+ele8+"  "+ele9);//输出两个值
    }
}
/**
 * @brief MainWindow::on_pushButton_3_clicked
 */
void MainWindow::on_pushButton_3_clicked()
{

    QString res;
    if(sqlite->queryexec(ui->textEdit_2->toPlainText().toStdString().c_str()))
        QTextStream(&res)<<"sql:"<<ui->textEdit_2->toPlainText()<<"\texec true";
    else
        QTextStream(&res)<<"sql:"<<ui->textEdit_2->toPlainText()<<"\texec false";
    if(Helper::log(res.toStdString().c_str(),logpath))
        ui->textEdit->append(res);
    else
    {
        QTextStream(&res)<<" log failed";
        ui->textEdit->append(res);
    }
    // sqlite->reguser(ui->textEdit_3->toPlainText().toStdString().c_str(),ui->textEdit_2->toPlainText().toStdString().c_str(),"0");
    // ui->textEdit_2->setPlainText("");
    //ui->textEdit_3->setPlainText("");
}
/**
 * @brief MainWindow::on_pushButton_4_clicked
 */
void MainWindow::on_pushButton_4_clicked()
{
    //ui->textEdit->append(Helper::getsalt(8));
    //  TODO：输出所有在线用户的ip、port、socket名
    ui->textEdit->append("Output start");
    for (int i=0;i<clientSize;i++)
    {
        QString output;
        QTextStream(&output)
                <<QString::fromStdString(clients[i].username)
               <<"\t"<<clients[i].client->peerAddress().toString()
              <<"\t"<<clients[i].client->peerPort();
        ui->textEdit->append(output);
    }
    ui->textEdit->append("Output end");
}
/**
 * @brief MainWindow::closeEvent
 * @param event
 */
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
    QString log;
    QTextStream(&log)<<"Server stop @"<<Helper::getDateTime();
    Helper::log(log.toStdString().c_str(),logpath);
    event->accept();
}
