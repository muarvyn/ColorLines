/*

Copyright (C) 2020 Volodymyr Kryachko

This file is part of ColorLines.

ColorLines is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

ColorLines is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with ColorLines; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/

#include <QSettings>

#include "app_defs.h"
#include "highscorestable.h"
#include "ui_highscorestable.h"

#define getName std::get<0>
#define getScore std::get<1>
#define getIsEditable std::get<2>


ScoreEntry makeScoreEntry(QString name, int score, bool editable) {
    return std::make_tuple(name, score, editable);
}

bool EntryScoreGreaterThan(HighscoresList::const_reference a, HighscoresList::const_reference b)
{ return getScore(a) > getScore(b); };

HighScoresTable::HighScoresTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HighScoresTable)
{
    ui->setupUi(this);
    QTableView *tableView = ui->highScoresView;
    HighScoresModel *tableModel = new HighScoresModel(this);
    tableModel->loadData();
    tableView->setModel(tableModel);
    tableView->resizeColumnsToContents();
}

int HighScoresTable::newScore(int score)
{
    HighScoresModel *model = qobject_cast<HighScoresModel *>(ui->highScoresView->model());
    HighscoresList &list = model->getData(); // TOFIX: use HighScoresModel::data
    HighscoresList::const_iterator record_it =
        std::find_if_not(list.begin(), list.end(),
        [score](HighscoresList::const_reference item){ return getScore(item) > score; });
    int row = record_it - list.cbegin();
    model->insertRows(row, 1);
    getScore(list[row]) = score;
    QModelIndex selection = model->index(row,0);
    ui->highScoresView->selectionModel()->select(selection, QItemSelectionModel::ClearAndSelect);
    int status = exec();
    model->saveData();
    return status;
}

HighScoresTable::~HighScoresTable()
{
    delete ui;
}

HighScoresModel::HighScoresModel(QObject * parent)
    : QAbstractTableModel(parent)
    , mData()
    , user_name(qgetenv("USER"))
{

}

QVariant HighScoresModel::data(const QModelIndex & index, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (index.row() < 0 || index.row() >= mData.count())
        return QVariant();

    const ScoreEntry &entry = mData[index.row()];

    if (index.column() == 0) {
        return getName(entry);
    }
    else {
        return getScore(entry);
    }
}

bool HighScoresModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    QString name = value.toString().trimmed().remove('\'');
    if (name.isEmpty()) return false;
    ScoreEntry &entry = mData[index.row()];
    getName(entry) = name;
    emit dataChanged(index, index);
    return true;
}


Qt::ItemFlags HighScoresModel::flags(const QModelIndex &index) const {
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemNeverHasChildren | Qt::ItemIsSelectable;
    if (getIsEditable(mData[index.row()])) {
        flags |= Qt::ItemIsEditable;
    }
    return flags;
}

bool HighScoresModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (count <= 0) {
        return false;
    }
    beginInsertRows(parent, row, row+count-1);
    for(int i=0; i<count; ++i) {
        mData.insert(row, makeScoreEntry(getUserName(), 0, true));
    }
    endInsertRows();
    return true;
}


void HighScoresModel::loadData() {
    QSettings load_settings(OrganizationName, ApplicationName);
    load_settings.beginGroup(HighscoresSettingsGroupName);

    foreach (const QString &key, load_settings.childKeys()) {
        QString entry_str(load_settings.value(key).toString());
        QStringList list = entry_str.split('\'');
            if (list.size() < 2) {
                continue;
            }
        mData.append(makeScoreEntry(list[0], list[1].toInt(), false));
    }
    std::sort(mData.begin(), mData.end(), &EntryScoreGreaterThan);

    load_settings.endGroup();
}

void HighScoresModel::saveData() const
{
    QSettings save_settings(OrganizationName, ApplicationName);
    save_settings.beginGroup(HighscoresSettingsGroupName);

    int i=0;
    save_settings.remove("");
    QString format("%1'%2");
    foreach (const ScoreEntry &entry, mData) {
        save_settings.setValue(QString::number(i), format.arg(getName(entry)).arg(int(getScore(entry))));
        if (++i >= MAX_SAVED_HIGHSCORES) {
            break;
        }
    }
    save_settings.endGroup();
}

