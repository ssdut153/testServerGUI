#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QTextEdit>
#include "myclient.h"
#include <QCloseEvent>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


private slots:
    void acceptConnection();
    void readClient(int);
    void disconnect(int);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // MAINWINDOW_H
