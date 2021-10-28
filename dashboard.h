#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QtWidgets>
#include "datainteraction.h"
#include "rng.h"
#include "user.h"
#include "logindialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dashboard; }
QT_END_NAMESPACE

class Dashboard : public QMainWindow
{
   Q_OBJECT

private:
    DataInteraction datainteraction;
    User user;

public:
    explicit Dashboard(QWidget *parent = nullptr);
    ~Dashboard();   

private slots: 
    void on_settings_clicked();
    void on_newItem_clicked();
    void on_passwordGenerator_clicked();
    void on_passwords_clicked();
    void on_paymentCards_clicked();
    void backToMain();
    void on_generate_clicked();
    void on_addItem_clicked();
    void on_changeUsername_clicked();
    void on_changePassword_clicked();
    void on_businessFolder_clicked();
    void on_educationFolder_clicked();
    void on_emailFolder_clicked();
    void on_entertainmentFolder_clicked();
    void on_financeFolder_clicked();
    void on_gamesFolder_clicked();
    void on_newsFolder_clicked();
    void on_productivityFolder_clicked();
    void on_shoppingFolder_clicked();
    void on_socialFolder_clicked();
    void on_saveChangesCard_clicked();
    void passwordLength(int length);
    void on_addCard_clicked();
    void on_logout_clicked();
private:
    Ui::Dashboard *ui;
};

#endif // DASHBOARD_H
