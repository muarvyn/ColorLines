#include <QSettings>
#include <QShowEvent>

#include "app_defs.h"
#include "highscorestable.h"
#include "ui_highscorestable.h"


HighScoresTable::HighScoresTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighScoresTable)
{
    ui->setupUi(this);
    QTableView *tableView = ui->highScoresView;
    HighScoresModel *tableModel = new HighScoresModel(this);
    //tableModel->populate();
    tableModel->loadData();
    tableView->setModel(tableModel);
    tableView->resizeColumnsToContents();
}

HighScoresTable::~HighScoresTable()
{
    delete ui;
}

//void HighScoresTable::showEvent(QShowEvent *event) {
//    QDialog::showEvent(event);
//    if (!event->spontaneous()){
//        ui->highScoresView->resizeColumnsToContents();
//    }

//}

HighScoresModel::HighScoresModel(QObject * parent)
    : QAbstractTableModel(parent)
    , mData()
{
    //loadData();
}

QVariant HighScoresModel::data(const QModelIndex & index, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (index.row() < 0 || index.row() >= mData.count())
        return QVariant();

    const ScoreEntry &entry = mData[index.row()];

    if (index.column() == 0) {
        return entry.first;
    }
    else {
        return entry.second;
    }
}

Qt::ItemFlags HighScoresModel::flags(const QModelIndex &index) const {
    Q_UNUSED(index)
    return Qt::ItemIsEnabled;
}

void HighScoresModel::loadData() {
    QSettings load_settings(OrganizationName, ApplicationName);
    load_settings.beginGroup(SettingsGnoupName);

    foreach (const QString &key, load_settings.childKeys()) {
        mData.append(QPair<QString, int>(key, load_settings.value(key).toInt()));
    }
    std::sort(mData.begin(), mData.end(),
        [](HighscoresList::const_reference a, HighscoresList::const_reference b)
            { return a.second > b.second; });

    load_settings.endGroup();
}

//******************** For testing ********************
#include <QRandomGenerator>
const QString Names[8] = {"John", "Michael", "Maria", "Isaac", "Christopher", "Jack", "Isabella", "Carolina"};
const QString Surnames[7] = {"Silver", "Black", "Brown", "Lee", "Carpenter", "Smith", "Woods"};

void HighScoresModel::populate() {
    QString key_1(Names[QRandomGenerator::global()->bounded(int(sizeof(Names)/sizeof(*Names)))]+" "+
        Surnames[QRandomGenerator::global()->bounded(int(sizeof(Surnames)/sizeof(*Surnames)))]);
    int val_1 = QRandomGenerator::global()->bounded(500+1);
    QSettings save_settings(OrganizationName, ApplicationName);
    save_settings.beginGroup(SettingsGnoupName);

    save_settings.setValue(key_1, val_1);
    HighscoresList data;
    foreach (const QString &key, save_settings.childKeys()) {
        data.append(QPair<QString, int>(key, save_settings.value(key).toInt()));
    }

    std::sort(data.begin(), data.end(),
        [](HighscoresList::const_reference a, HighscoresList::const_reference b)
            { return a.second > b.second; });
    int i=0;
    save_settings.remove("");
    foreach (const ScoreEntry &entry, data) {
        if (++i <= MAX_SAVED_HIGHSCORES)
            save_settings.setValue(entry.first, entry.second);
    }
    save_settings.endGroup();

}
