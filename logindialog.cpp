#include "logindialog.h"
#include "ui_logindialog.h"
#include "dashboard.h"
#include "qmessagebox.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(this, &LoginDialog::login, this, &LoginDialog::loginSlot);
    connect(this, &LoginDialog::clear, this, &LoginDialog::clearSlot);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btnLogin_clicked()
{
    //Gets the textfields from the login dialog when login button is pressed, and sends them to loginSlot via "connect"
    QString username = ui->edtUsername->text();
    QString password = ui->edtPassword->text();
    emit login(username, password);
}

void LoginDialog::on_btnClear_clicked()
{
    //Calls clearSlot when clear button is pressed
    emit clear();
}

void LoginDialog::loginSlot(QString username, QString password)
{
    /*Calls on the user class for login verification, appropriate message if necessary,
    or opens main window if credentials are correct.*/
    User login(username, password);
    if (username.trimmed().length() == 0) {
                 QMessageBox::information(this, "Prompt", "User name cannot be empty!");
        ui->edtUsername->setFocus();
        return;
    }
    if (password.trimmed().length() == 0) {
                 QMessageBox::information(this, "Prompt", "Password cannot be empty!");
        ui->edtPassword->setFocus();
        return;
    }
    if (login.validCredentials()) {
        parentWidget()->show();
        this->hide();
    } else {
        QMessageBox::information(this, "Prompt", "Unfortunately, login failed!");
    }
}

void LoginDialog::clearSlot()
{
    //clears fields
    ui->edtUsername->setText("");
    ui->edtPassword->setText("");
    ui->edtUsername->setFocus();
}
