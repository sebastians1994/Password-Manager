#include "dashboard.h"
#include <QApplication>
#include <logindialog.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dashboard w;
    w.setWindowTitle("Password Manager");
    LoginDialog login(&w);
    login.setWindowTitle("Login");
    login.show();
    return a.exec();
}
