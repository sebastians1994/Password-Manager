#ifndef DATAINTERACTION_H
#define DATAINTERACTION_H

#include <QtWidgets>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DataInteraction; }
QT_END_NAMESPACE

class DataInteraction : public QObject
{
 Q_OBJECT
public:
    DataInteraction();
    void DisplayFolder(int whichFolder);
    void SaveCardChanges();
    QSortFilterProxyModel* DisplayCards();
    int AddCard(QString name, QString CardName, QString CardNum, QDate ExpirationDate, QString CvvNum, QString CType);
    int AddItem(unsigned short folder, QString name, QString username, QString password, QString website);

private slots:
    void SavePassChanges();

private:
    Database database;
    QWidget *accountsWindow;
    QLineEdit *searchBar;
    QHBoxLayout *topHorizontalLayout;
    QVBoxLayout *mainLayout;
    QStandardItemModel *modelPasswords;
    QTableView *passwordsTable;
    QLabel *feedbackLabel;
    QSortFilterProxyModel *proxyModelPassword;
    QPushButton *saveChangesPasswords;
    QStandardItemModel *modelCards;
    QSortFilterProxyModel *proxyModelCards;
    const QStringList folderNames = {"Business", "Education", "Email", "Entertainment", "Finance", "Games", "News", "Productivity", "Shopping", "Social"};
};

#endif // DATAINTERACTION_H
