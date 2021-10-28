#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "user.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

signals:
    void login(QString username, QString password);
    void clear();

private slots:
    void on_btnLogin_clicked();
    void on_btnClear_clicked();
    void loginSlot(QString username, QString password);
    void clearSlot();

private:
    Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
