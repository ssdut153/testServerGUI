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
QTcpSocket *client;
QTcpServer *server;
std::vector<MyClient> clients;
QSignalMapper *signalMapper;
Sqlite *sqlite;
int clientSize=0;
void MainWindow::acceptConnection()
{
    QString tem;
    QTextStream(&tem)<<"temp"<<clientSize;
    //ui->textEdit->append(tem);
    clients.push_back(MyClient(tem.toStdString(),server->nextPendingConnection(),clientSize++));
    //clientConnection = clients[clientSize-1].client;

    QString conne;
    QTextStream(&conne)<<"New connection:"<<clients[clientSize-1].client->peerName()<<"\t"<<clients[clientSize-1].client->peerAddress().toString()<<"\t"<<clients[clientSize-1].client->peerPort()<<" @"<<Helper::getDateTime();
    ui->textEdit->append(conne);

    connect(clients[clientSize-1].client, SIGNAL(readyRead()), signalMapper, SLOT(map()));
    signalMapper->setMapping(clients[clientSize-1].client, clientSize-1);
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(readClient(int)));

    //connect(clients[clientSize-1].client, SIGNAL(readyRead()), this, SLOT(readClient(QTcpSocket*)));
}
QString MainWindow::login(std::string textJson,MyClient* socket,int ind)
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
        /*
        for (int i=0;i<clientSize;i++)
        {
            if(clients[i].index!=ind&&clients[i].username==loginmessage.user)
            {
                clients[i].client->write("{\"head\":\"forceLogOut\"}");
                break;
            }
        }
        */
    }
    else
    {
        loginFeedBackMessage feedback(loginmessage.user,"false");
        socket->client->write(feedback.getJsonString().c_str());
        QTextStream(&res)<<loginmessage.user.c_str()<<" log in fail @"<<Helper::getDateTime();
    }
    return res;
}

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
    //下列代码实现read会乱码不论中英文
    //char buf[1024];
    //clientConnection->read(buf,1024);

    if(!str.isEmpty())
    {
        QString log;
        QTextStream(&log)<<str<<" @"<<Helper::getDateTime();
        ui->textEdit->append(log);

        //std::string head="login";
        std::string head=Helper::getHeadfromJson(str.toStdString());
        if(head=="login")
            ui->textEdit->append(login(str.toStdString(),&clients[i],i));
        else
        {
            tempSocket->write("I received your message:");
            tempSocket->write(str.toStdString().c_str());
        }
    }



    //clientConnection->close();
}
//{"head":"login","username":"testuser88","password":"testuser"}

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
   */
    /*
    loginFeedBackMessage test("testuser","true");
    std::string tempjson=test.getJsonString();
    ui->textEdit->append(QString::fromStdString(tempjson));

    loginFeedBackMessage testload;
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

    sqlite->reguser(ui->textEdit_3->toPlainText().toStdString().c_str(),ui->textEdit_2->toPlainText().toStdString().c_str(),"0");
    ui->textEdit_2->setPlainText("");
    ui->textEdit_3->setPlainText("");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->textEdit->append(Helper::getsalt(8));
}
