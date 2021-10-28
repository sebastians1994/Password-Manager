#include "dashboard.h"
#include "ui_dashboard.h"

Dashboard::Dashboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Dashboard)
{
    ui->setupUi(this);
    connect(ui->backToMain, SIGNAL(clicked()), this, SLOT(backToMain()));  //connecting the return buttons to the back to main(dashboard) function
    connect(ui->backToMain2, SIGNAL(clicked()), this, SLOT(backToMain()));
    connect(ui->backToMain3, SIGNAL(clicked()), this, SLOT(backToMain()));
    connect(ui->backToMain4, SIGNAL(clicked()), this, SLOT(backToMain()));
    connect(ui->backToMain5, SIGNAL(clicked()), this, SLOT(backToMain()));
    connect(ui->passLengthSlider, SIGNAL(valueChanged(int)), this, SLOT(passwordLength(int))); //Length slider for password generation to display numerical value
    if(ui->stackedWidget->currentWidget() != ui->dashboardPage){ //testing to ensure the main dashboard opens after login
        ui->stackedWidget->setCurrentWidget(ui->dashboardPage);
    }
}

Dashboard::~Dashboard()
{
    delete ui;
}

void Dashboard::on_addItem_clicked()
{
    /*When add item (for password accounts) is clicked, this function is called to get the text from the text fields
    it then sends the test fields to datainteraction to be added to the datainteraction, will display error or success
    message depending on the return value*/
    unsigned short folder = ui->addFolder->currentIndex();
    QString name = ui->addName->text();
    QString username = ui->addUsername->text();
    QString password = ui->addPassword->text();
    QString website = ui->addWebsite->text();
    int error = datainteraction.AddItem(folder, name, username, password, website);
    switch (error) {
    case 0:
        ui->feedbackAddLabel->setText("Please fill all the required fields!");
        ui->addName->setFocus();
        break;
    case 1:
        ui->feedbackAddLabel->setText("Please fill all the required fields!");
        ui->addUsername->setFocus();
        break;
    case 2:
        ui->feedbackAddLabel->setText("Please fill all the required fields!");
        ui->addPassword->setFocus();
        break;
    case 3:
        ui->feedbackAddLabel->setText("Item created successfully!");
        ui->addFolder->setCurrentIndex(0);
        ui->addName->setText("");
        ui->addUsername->setText("");
        ui->addPassword->setText("");
        ui->addWebsite->setText("");
        break;
    }
}

void Dashboard::on_addCard_clicked()
{
    /*when add card is clicked (for card accounts), it sends the text fields from the ui to datainteraction to be added to the datainteraction
     will output error/success message based on the result*/
    QString name = ui->addName_2->text();
    QString CardName = ui->addnameOnCard->text();
    QString CardNum = ui->addcardNumber->text();
    QDate ExpirationDate = ui->addExpirationDate->date();
    QString CvvNum = ui->addcvv->text();
    QString CType = ui ->addcType->currentText();
    int error = datainteraction.AddCard(name, CardName, CardNum, ExpirationDate, CvvNum, CType);
    switch (error) {
    case 0:
        ui->feedbackAddLabel->setText("Please fill all the required fields!");
        ui->addName_2->setFocus();
        break;
    case 1:
        ui->feedbackAddLabel->setText("Please fill all the required fields!");
        ui->addnameOnCard->setFocus();
        break;
    case 2:
        ui->feedbackAddLabel->setText("Please fill all the required fields!");
        ui->addcardNumber->setFocus();
        break;
    case 3:
        ui->feedbackAddLabel->setText("Item created successfully!");
        ui->addName_2->setText("");
        ui->addnameOnCard->setText("");
        ui->addcardNumber->setText("");
        ui->addcvv->setText("");
        ui->addcType->setCurrentIndex(0);
        break;
    }
}


void Dashboard::backToMain()  //return to the main dashboard screen in the gui app, once a back button is clicked.
{
    ui->stackedWidget->setCurrentWidget(ui->dashboardPage);
}

void Dashboard::on_settings_clicked() //go to settings page when settings button is pressed, reset success page in case it was populated
{
    ui->successLabelSettings->setText("");
    ui->stackedWidget->setCurrentWidget(ui->settingsPage);
}

void Dashboard::on_logout_clicked() //logout and return to menu dialog
{
    LoginDialog *login= new LoginDialog(this);
    login->setWindowTitle("Login");
    ui->stackedWidget->setCurrentWidget(ui->dashboardPage);
    hide();
    login->show();
}

void Dashboard::on_passwordGenerator_clicked() //go to password generator page when generator button is pressed.
{
    ui->stackedWidget->setCurrentWidget(ui->generatorPage);
}

void Dashboard::on_newItem_clicked() // go to add item page when new item button is pressed
{
    ui->feedbackAddLabel->setText("");
    ui->stackedWidget->setCurrentWidget(ui->addPage);
}

void Dashboard::on_passwords_clicked() // displays the folders when passwords button is pressed
{
    ui->stackedWidget->setCurrentWidget(ui->passwordsPage);
}

void Dashboard::on_paymentCards_clicked()
{
    /*goes to the card table page when payment cards button is pressed.
    creates a proxy model pointer to be used for the search functionality,
    gets the pointer from the datainteraction class.
    Also sets settings and stylesheet for the table*/
    QSortFilterProxyModel *proxyModel = datainteraction.DisplayCards();
    ui->cardsTable->setModel(proxyModel);
    connect(ui->cardsSearch, SIGNAL(textChanged(QString)), proxyModel, SLOT(setFilterRegExp(QString)));
    ui->cardsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->cardsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->cardsTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::ResizeToContents);
    ui->cardsTable->horizontalHeader()->setSectionResizeMode(5, QHeaderView::ResizeToContents);
    ui->cardsTable->setStyleSheet("QHeaderView::section { background-color:black; color:white;} QTableView { background-color: rgb(65, 65, 65);color:white; }");
    ui->feedbackCardsLabel->setText("");
    ui->stackedWidget->setCurrentWidget(ui->cardsPage);
}

void Dashboard::passwordLength(int length){ //when slider is moved this function is called to display numerical value
    ui->passwordLengthLabel->setText(QString("Length: %1").arg(length));
}

void Dashboard::on_generate_clicked()
{
    /*When the user press generate button in the password generration page, this function is called
    and it gets the textboxes fields as bools, along with the length desired, and passes all the fields
    to the RNG class, which returns a string which is then display.
    Also checks for at least one checked box*/
    QClipboard* clipboard = QGuiApplication::clipboard();
    int password_length = ui->passLengthSlider->value();
    bool upper = ui->checkUpper-> QAbstractButton::isChecked();
    bool lower = ui->checkLower->QAbstractButton::isChecked();
    bool digits = ui->checkNum->QAbstractButton::isChecked();
    bool special = ui->checkSpecial->QAbstractButton::isChecked();
    if(upper == false && lower == false && digits == false && special == false){
        QMessageBox::warning(this,"Error", "Must check at least one box!");
    }
    else{
    RNG temp;
    QString password = temp.passwordGen(password_length,upper,lower,digits,special);
    ui->generatedPassword->setText(password);
    ui->addPassword->setText(password);
    clipboard->setText(password);
    }
}
/*Folder functions below are called when any folder is pressed, depending on which folder
 it will pass the folder index and call on DisplayFolder which is in data interaction*/
void Dashboard::on_businessFolder_clicked()
{

    datainteraction.DisplayFolder(0);
}

void Dashboard::on_educationFolder_clicked()
{
    datainteraction.DisplayFolder(1);
}

void Dashboard::on_emailFolder_clicked()
{
    datainteraction.DisplayFolder(2);
}

void Dashboard::on_entertainmentFolder_clicked()
{
    datainteraction.DisplayFolder(3);
}

void Dashboard::on_financeFolder_clicked()
{
    datainteraction.DisplayFolder(4);
}

void Dashboard::on_gamesFolder_clicked()
{
    datainteraction.DisplayFolder(5);
}

void Dashboard::on_newsFolder_clicked()
{
    datainteraction.DisplayFolder(6);
}

void Dashboard::on_productivityFolder_clicked()
{
    datainteraction.DisplayFolder(7);
}

void Dashboard::on_shoppingFolder_clicked()
{
    datainteraction.DisplayFolder(8);
}

void Dashboard::on_socialFolder_clicked()
{
    datainteraction.DisplayFolder(9);
}

/*change username/password, in the settings menu when either button is pressed, the respective function is called
    and it takes the text fields, sends them to the login class for validation,
    displays appropriate message according to the boolean returned.*/
void Dashboard::on_changeUsername_clicked()
{
    QString oldUser = ui->oldUsername->text();
    QString newUser = ui->newUsername->text();
    if (user.changeUsername(oldUser, newUser)){
        ui->successLabelSettings->setText("Username changed successfully!");
        ui->oldUsername->setText("");
        ui->newUsername->setText("");
        return;
    }
    else {
        ui->successLabelSettings->setText("Username is not correct!");
        ui->oldUsername->setFocus();
        return;
    }
}

void Dashboard::on_changePassword_clicked()
{
    QString oldPass = ui->oldPassword->text();
    QString newPass = ui->newPassword->text();
    if (user.changePassword(oldPass, newPass)){
        ui->successLabelSettings->setText("Password changed successfully!");
        ui->oldPassword->setText("");
        ui->newPassword->setText("");
        return;
    }
    else {
        ui->successLabelSettings->setText("Password is not correct!");
        ui->oldPassword->setFocus();
        return;
    }
}
//when save changes in the cards table view is pressed, it calles a function from datainteraction to save the new changes
void Dashboard::on_saveChangesCard_clicked()
{
    datainteraction.SaveCardChanges();
    ui->feedbackCardsLabel->setText("Changes saved successfully!");
}



