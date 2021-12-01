#ifndef HIGHSCORESTABLE_H
#define HIGHSCORESTABLE_H

#include <tuple>
#include <QDialog>

#include "qabstractitemmodel.h"


typedef std::tuple<QString, int, bool> ScoreEntry;
typedef QList<ScoreEntry> HighscoresList;
ScoreEntry makeScoreEntry(QString name, int score, bool editable);

class HighScoresModel : public QAbstractTableModel
{
    Q_OBJECT
public :
    HighScoresModel(QObject * parent = nullptr);

    int rowCount(const QModelIndex&) const override
    { return mData.size(); }

    int columnCount(const QModelIndex&) const override
    { return 2; }

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    HighscoresList &getData() { return mData; }

    void loadData();
    void saveData() const;
    const QString &getUserName() { return user_name; }

private:
    HighscoresList mData;
    QString user_name;

};

namespace Ui {
class HighScoresTable;
}

class HighScoresTable : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoresTable(QWidget *parent = nullptr);
    int newScore(int score);
    ~HighScoresTable();

private:
    Ui::HighScoresTable *ui;

private slots:
};

#endif // HIGHSCORESTABLE_H
