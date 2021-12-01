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
#include <QDebug>

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
    HighscoresList &list = model->getData();
    HighscoresList::iterator record_position =
        std::find_if_not(list.begin(), list.end(),
        [score](HighscoresList::const_reference item){ return getScore(item) > score; });
    list.insert(record_position, makeScoreEntry(model->getUserName(), score, true));
    int status = exec();
    for (auto item : list) {
        qDebug() << "HighScoresTable: " << std::get<0>(item) << " : " << std::get<1>(item);
    }
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
    QString name = value.toString().trimmed();
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

void HighScoresModel::loadData() {
    QSettings load_settings(OrganizationName, ApplicationName);
    load_settings.beginGroup(SettingsGroupName);

    foreach (const QString &key, load_settings.childKeys()) {
        mData.append(makeScoreEntry(key, load_settings.value(key).toInt(), false));
    }
    std::sort(mData.begin(), mData.end(), &EntryScoreGreaterThan);

    load_settings.endGroup();
}

void HighScoresModel::saveData() const
{
    QSettings save_settings(OrganizationName, ApplicationName);
    save_settings.beginGroup(SettingsGroupName);

    int i=0;
    save_settings.remove("");
    for (const ScoreEntry &entry : mData) {
        if (save_settings.contains(getName(entry)) &&
            getScore(entry) <= save_settings.value(getName(entry)).toInt())
                continue;
        if (++i <= MAX_SAVED_HIGHSCORES)
            save_settings.setValue(getName(entry), getScore(entry));
    }
    save_settings.endGroup();
}

