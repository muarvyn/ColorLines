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
    save_settings.beginGroup(HighscoresSettingsGroupName);
    if (save_settings.childKeys().size() >= MAX_SAVED_HIGHSCORES)
        return;

    QString val_1(Names[QRandomGenerator::global()->bounded(int(sizeof(Names)/sizeof(*Names)))]+" "+
        Surnames[QRandomGenerator::global()->bounded(int(sizeof(Surnames)/sizeof(*Surnames)))]+"\'"+
        QString::number(QRandomGenerator::global()->bounded(500+1)));
    save_settings.setValue(QString::number(save_settings.childKeys().size()),
                           val_1);

    const QString format("%1'%2");
    HighscoresList data;
    for (const QString &key : save_settings.childKeys()) {
        QString entry_str(save_settings.value(key).toString());
        QStringList list = entry_str.split('\'');
            if (list.size() < 2) {
                continue;
            }
        data.append(makeScoreEntry(list[0], list[1].toInt(), false));
    }

    std::sort(data.begin(), data.end(),
              [](HighscoresList::const_reference a, HighscoresList::const_reference b)
              { return std::get<1>(a) < std::get<1>(b); });
    save_settings.remove("");
    int i=0;
    for (const ScoreEntry &entry : data) {
        save_settings.setValue(QString::number(i),
                               format.arg(std::get<0>(entry))
                                     .arg(int(std::get<1>(entry)))
                               );
        ++i;
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
