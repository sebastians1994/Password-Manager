#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QPixmap>


LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    //QPixmap pix(":/resources/img/login-icon.png");
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_pushButton_Login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();

    if((username ==  "test" && password == "test") || (username ==  "admin" && password == "password")) {
        //QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        dashboard = new Dashboard(this);
        dashboard->show();
    }
    else {
        QMessageBox::warning(this,"Login", "Username and password is not correct");
    }
}
