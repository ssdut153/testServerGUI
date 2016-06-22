#ifndef SQLITE_H
#define SQLITE_H

#include <QtSql>
#include <QString>
class Sqlite
{
public:
    Sqlite();
    ~Sqlite();
    bool checkpassword(char* username,char* password);
    bool reguser(char* username,char* password,char* vip);//salt,regdate,sha-256
    bool queryexec(char* sqltext);
    char* select1(char* selecttext);
private:
    QSqlDatabase dbconn;
    QString regusersql="insert into users (username,password,salt,regdate,vip) values('?','?','?','?',?)";
    QString checkpasswordsql="select password,salt from users where username=':user'";
};

#endif // SQLITE_H
