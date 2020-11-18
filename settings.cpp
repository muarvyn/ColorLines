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

#include "settings.h"
#include "basic_defs.hpp"
#include "app_defs.h"

const QString SavedGameSettingsGroupName("saved game");
const QString ScoreSavedSetting("score");

Settings::Settings(QObject *parent) : QObject(parent)
{

}

std::size_t Settings::loadGame(BoardInterface &board, int &score)
{
    board.clear();
    QSettings load_settings(OrganizationName, ApplicationName);
    load_settings.beginGroup(SavedGameSettingsGroupName);
    bool is_number;
    std::size_t count = 0;

    foreach (const QString &key, load_settings.childKeys()) {
        key.toInt(&is_number);
        if (is_number) {
            QString ball(load_settings.value(key).toString());
            QStringList list = ball.split(" ");
            if (list.size() < 3) {
                continue;
            }
            int row = list[0].toInt(&is_number);
            if (!is_number) continue;
            int column = list[1].toInt(&is_number);
            if (!is_number) continue;
            int color = list[2].toInt(&is_number);
            if (!is_number) continue;
            board.setColorAt(row, column, BallColor::type(color));
            ++count;
        } else {
            score = load_settings.value(key).toInt();
        }
    }
    load_settings.endGroup();
    return count;
}

void Settings::saveGame(const BoardInterface &board, int score)
{
    QSettings save_settings(OrganizationName, ApplicationName);
    save_settings.beginGroup(SavedGameSettingsGroupName);
    save_settings.remove("");

    int count = 1;
    QString format("%1 %2 %3");
    for (int r = 0; r < BoardDim::ROWS_NUM; ++r) {
        for (int c = 0; c < BoardDim::COLUMNS_NUM; ++c) {
            BallColor::type color = board.getColorAt(r,c);
            if (color != BallColor::none) {
                save_settings.setValue(QString::number(count++), format.arg(r).arg(c).arg(color));
            }
        }
    }
    save_settings.setValue(ScoreSavedSetting, score);
    save_settings.endGroup();
}
