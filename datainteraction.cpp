#include "datainteraction.h"

DataInteraction::DataInteraction() {
    /*Creates a new window, QWidgets, applies appropriate style and size settings.
    Also creates all the fields in the window; search bar, button, table, model, proxymodel.
    Puts everything into the correct size, placement, and layout, names appropriates fields*/
    accountsWindow = new QWidget;
    searchBar = new QLineEdit();
    topHorizontalLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();
    modelPasswords = new QStandardItemModel;
    passwordsTable = new QTableView();
    saveChangesPasswords = new QPushButton;
    proxyModelPassword = new QSortFilterProxyModel;
    feedbackLabel = new QLabel;
    modelCards = new QStandardItemModel;//cards
    proxyModelCards = new QSortFilterProxyModel; //cards
    searchBar->setStyleSheet("max-width:250px");
    searchBar->setPlaceholderText("Search...");
    topHorizontalLayout->addWidget(searchBar,0,  Qt::AlignLeft);
    mainLayout->addLayout(topHorizontalLayout);
    accountsWindow->setLayout(mainLayout);
    topHorizontalLayout->addWidget(feedbackLabel, 0, Qt::AlignRight);
    topHorizontalLayout->addWidget(saveChangesPasswords, 0, Qt::AlignRight);
    saveChangesPasswords->setText("Save New Changes");
    saveChangesPasswords->setStyleSheet("max-width:200px");
    accountsWindow->setStyleSheet("background-color:rgb(48, 48, 48);" "color: rgb(240, 240, 240);");
    modelPasswords->setHorizontalHeaderLabels({"Name", "Username", "Password", "Website" });
    proxyModelPassword->setSourceModel(modelPasswords);
    proxyModelPassword->setFilterKeyColumn(0);
    proxyModelPassword->setFilterCaseSensitivity(Qt::CaseInsensitive);
    passwordsTable->setModel(proxyModelPassword);
    mainLayout->addWidget(passwordsTable);
    passwordsTable->verticalHeader()->hide();
    passwordsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    passwordsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    passwordsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    passwordsTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    passwordsTable->setStyleSheet("QHeaderView::section { background-color:black }");
    QDesktopWidget userWindow;
    int x=userWindow.width()*0.40;
    int y=userWindow.height()*0.28;
    accountsWindow->setMinimumSize(x,y);

}

void DataInteraction::DisplayFolder(int whichFolder){
    /*Called from dashboard class once a folder is pressed, based on the folder sets appropriate window
    names, and puts appropriate data from database class into a model for the table view*/
    if (!accountsWindow->isActiveWindow()) feedbackLabel->setText("");
    QList <Password> passList = database.getPasswordList(whichFolder);
    modelPasswords->removeRows(0,modelPasswords->rowCount());
    modelPasswords->setVerticalHeaderLabels({QString::number(whichFolder)});
    accountsWindow->setWindowTitle(folderNames[whichFolder]);
    int i = 0;
    for (auto dataBlock : passList) {
            modelPasswords->setItem(i, 0, new QStandardItem(dataBlock.getName()));
            modelPasswords->setItem(i, 1, new QStandardItem(dataBlock.getUsername()));
            modelPasswords->setItem(i, 2, new QStandardItem(dataBlock.getPassword()));
            modelPasswords->setItem(i, 3, new QStandardItem(dataBlock.getWesbite()));
            i++;
    }
    /*whenever any change is detected in the search textfield,
        calls function to display appropriate results*/
    connect(searchBar, SIGNAL(textChanged(QString)), proxyModelPassword, SLOT(setFilterRegExp(QString)));
    QObject::connect(saveChangesPasswords, SIGNAL(clicked()), this, SLOT(SavePassChanges()));
    accountsWindow->show();
}

void DataInteraction::SavePassChanges(){
    /*Called from dashboard class when save password changes button is pressed.
    gets the data that is in the model and sends it to the database class to be saved.*/
    int whichFolder = proxyModelPassword->headerData(0, Qt::Vertical).toInt();
    QList<Password> passList = database.getPasswordList(whichFolder);
    for (int i  = 0;i < passList.size() ;i++ ) {
        passList[i].setName(proxyModelPassword->data(proxyModelPassword->index(i,0)).toString());
        passList[i].setUsername(proxyModelPassword->data(proxyModelPassword->index(i,1)).toString());
        passList[i].setPassword(proxyModelPassword->data(proxyModelPassword->index(i,2)).toString());
        passList[i].setWebsite(proxyModelPassword->data(proxyModelPassword->index(i,3)).toString());
    }
    database.setPasswordList(passList);
    database.writeToFileP();
    feedbackLabel->setText("Changes saved successfully!");
    DisplayFolder(whichFolder);
}

int DataInteraction::AddItem(unsigned short folder, QString name, QString username, QString password, QString website){
    /*Called from dashboard class when an item is added.
    checks for empty fields and returns appropriate result.
    if all check passed, send data to database class to be saved to file*/
    Password temp;
    QStringList nameList= name.split(' ', Qt::SkipEmptyParts);
    name = QString();
    if (nameList.isEmpty()) return 0;
    else{
        QString space = " ";
        for(auto i: nameList) name = name + space + i;
    }
    nameList= username.split(' ', Qt::SkipEmptyParts);
    username = QString();
    if (nameList.isEmpty()) return 1;
    else{
        QString space = " ";
        for(auto i: nameList) username = username + space + i;
    }
    nameList= password.split(' ', Qt::SkipEmptyParts);
    password = QString();
    if (nameList.isEmpty()) return 2;
    else{
        QString space = " ";
        for(auto i: nameList) password = password + space + i;
    }
    temp.setFolder(folder);
    temp.setName(name);
    temp.setUsername(username);
    temp.setPassword(password);
    temp.setWebsite(website);
    database.addToPassList(temp);
    database.writeToFileP();
    return 3;
}

QSortFilterProxyModel* DataInteraction::DisplayCards(){
    /*Called from dashboard class when useer navigates to cards page.
    gets data from database class and puts the data into a model from table display*/
    QList <Card> cardList = database.getCardList();
    modelCards->removeRows(0,modelCards->rowCount());
    modelCards->setHorizontalHeaderLabels({"Name", "Name on card", "Card Number", "Type", "Expiration", "CVV" });
    modelCards->setVerticalHeaderLabels({"cards"});
    int i = 0;
    for (auto dataBlock : cardList) {
        modelCards->setItem(i, 0, new QStandardItem(dataBlock.getName()));
        modelCards->setItem(i, 1, new QStandardItem(dataBlock.getNameOnCard()));
        modelCards->setItem(i, 2, new QStandardItem(dataBlock.getCardNum()));
        modelCards->setItem(i, 3, new QStandardItem(dataBlock.getCardType()));
        modelCards->setItem(i, 4, new QStandardItem(dataBlock.getexpirationDate().toString("MM/yy")));
        modelCards->setItem(i, 5, new QStandardItem(dataBlock.getCVV()));
        i++;
    }
    proxyModelCards->setSourceModel(modelCards);
    proxyModelCards->setFilterKeyColumn(0);
    proxyModelCards->setFilterCaseSensitivity(Qt::CaseInsensitive);
    return proxyModelCards;
}

void DataInteraction::SaveCardChanges(){
    /*Function is called from dashboard class when user presses button to save card changes.
    Gets the data from the model and sends it to database class to be saved to file.*/
    QList <Card> cardList = database.getCardList();
    for (int i  = 0;i < cardList.size() ;i++ ) {
        cardList[i].setName(proxyModelCards->data(proxyModelCards->index(i,0)).toString());
        cardList[i].setCardName(proxyModelCards->data(proxyModelCards->index(i,1)).toString());
        cardList[i].setCardNum(proxyModelCards->data(proxyModelCards->index(i,2)).toString());
        cardList[i].setCardType(proxyModelCards->data(proxyModelCards->index(i,3)).toString());
        cardList[i].setExpirationDate(QDate::fromString(proxyModelCards->data(proxyModelCards->index(i,4)).toString(), "MM/yy").addYears(100));
        cardList[i].setCvvNum(proxyModelCards->data(proxyModelCards->index(i,5)).toString());
    }
    database.setCardList(cardList);
    database.writeToFileC();
    DisplayCards();
}

int DataInteraction::AddCard(QString name, QString CardName, QString CardNum, QDate ExpirationDate, QString CvvNum, QString CType){
    /*Function is called from dashboard class when user adds a card,
    checks for empty fields and returns appropriate result.
    If all checks pass, calls from data to be saved to database and then written to file.*/
    Card temp(CType, name, CardName, CardNum, ExpirationDate, CvvNum);
    QStringList nameList= name.split(' ', Qt::SkipEmptyParts);
    name = QString();
    if (nameList.isEmpty()) return 0;
    else{
        QString space = " ";
        for(auto i: nameList) name = name + space + i;
    }
    nameList= CardName.split(' ', Qt::SkipEmptyParts);
    CardName = QString();
    if (nameList.isEmpty()) return 1;
    else{
        QString space = " ";
        for(auto i: nameList) CardName = CardName + space + i;
    }
    nameList= CardNum.split(' ', Qt::SkipEmptyParts);
    CardNum = QString();
    if (nameList.isEmpty()) return 2;
    else{
        QString space = " ";
        for(auto i: nameList) CardNum = CardNum + space + i;
    }
    database.addCardToList(temp);
    database.writeToFileC();
    return 3;
}

