#include "mainwindow_test.h"

#include <tuple>
#include <QApplication>
#include <QRandomGenerator>
#include <QStringList>

#include "../app_defs.h"
#include "../highscorestable.h"

const QString Names[8] = {"John", "Michael", "Maria", "Isaac", "Christopher", "Jack", "Isabella", "Carolina"};
const QString Surnames[7] = {"Silver", "Black", "Brown", "Lee", "Carpenter", "Smith", "Woods"};

void populate() {

    QSettings save_settings(OrganizationName, ApplicationName);
    save_settings.beginGroup(SettingsGroupName);
    if (save_settings.childKeys().size() >= MAX_SAVED_HIGHSCORES)
        return;

    QString key_1(Names[QRandomGenerator::global()->bounded(int(sizeof(Names)/sizeof(*Names)))]+" "+
        Surnames[QRandomGenerator::global()->bounded(int(sizeof(Surnames)/sizeof(*Surnames)))]);
    int val_1 = QRandomGenerator::global()->bounded(500+1);
    save_settings.setValue(key_1, val_1);

    HighscoresList data;
    for (const QString &key : save_settings.childKeys()) {
        data.append(makeScoreEntry(key, save_settings.value(key).toInt(),false));
    }

    std::sort(data.begin(), data.end(),
              [](HighscoresList::const_reference a, HighscoresList::const_reference b)
              { return std::get<1>(a) < std::get<1>(b); });
    save_settings.remove("");
    for (const ScoreEntry &entry : data) {
        save_settings.setValue(std::get<0>(entry), std::get<1>(entry));
    }
    save_settings.endGroup();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    populate();
    const QStringList &list = a.arguments();

    HighScoresTable w;
    int score = list.size() > 1 ?
                list[1].toInt() :
                QRandomGenerator::global()->bounded(1000);
    w.newScore(score);
    return 0;
}
