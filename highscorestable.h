#ifndef HIGHSCORESTABLE_H
#define HIGHSCORESTABLE_H

#include <QDialog>

#include "qabstractitemmodel.h"

typedef QPair<QString, int> ScoreEntry;
typedef QList<ScoreEntry> HighscoresList;

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
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    void populate();

    void loadData();

private:
    HighscoresList mData;

};

namespace Ui {
class HighScoresTable;
}

class HighScoresTable : public QDialog
{
    Q_OBJECT

public:
    explicit HighScoresTable(QWidget *parent = nullptr);
    ~HighScoresTable();

private:
    Ui::HighScoresTable *ui;

private slots:
    //void showEvent(QShowEvent *event);
};

#endif // HIGHSCORESTABLE_H
