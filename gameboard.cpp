#include <vector>
#include <QRandomGenerator>

#include "gameboard.h"
#include "animatediconbutton.h"

constexpr GameBoard::Direction GameBoard::orig_dirs[];

GameBoard::GameBoard(
    AnimatedIconButton *(&board)[BoardDim::ROWS_NUM][BoardDim::COLUMNS_NUM]
    , QObject *parent)
    : Board (board, parent)
{

}

int GameBoard::getUnoccupied(std::vector<const AnimatedIconButton*> &unoccupied)
{
    for (int r = 0; r < BoardDim::ROWS_NUM; ++r) {
        for (int c = 0; c < BoardDim::COLUMNS_NUM; ++c) {
            if (board[r][c]->getState() == CellButton::UNOCCUPIED) {
                unoccupied.push_back(board[r][c]);
            }
        }
    }
    return static_cast<int>(unoccupied.size());
}

bool GameBoard::getRandomVacantDoze(const AnimatedIconButton* vacant[doze_size]) {
    std::vector<const AnimatedIconButton*> unoccupied;
    this->getUnoccupied(unoccupied);
    if (unoccupied.size() < doze_size) return false;
    std::vector<const AnimatedIconButton*>::size_type random_values[doze_size];
    for (int i=0; i<doze_size; ++i) {
        random_values[i] = static_cast<std::vector<const AnimatedIconButton*>::size_type>
            (QRandomGenerator::global()->bounded(static_cast<int>(unoccupied.size())-i));
    }
    vacant[0] = unoccupied[random_values[0]];
    std::vector<const AnimatedIconButton*>::size_type
        disp = random_values[1] < random_values[0] ? 0 : 1;
    vacant[1] = unoccupied[random_values[1]+disp];
    disp = random_values[2] < random_values[0] ? 0 : 1;
    disp += random_values[2] < random_values[1] ? 0 : 1;
    vacant[2] = unoccupied[random_values[2]+disp];
    // TOFIX: returns 3 vacant cells, not 'doze_size' as designed
    return true;
}

void GameBoard::getElimination(int r, int c, std::vector<AnimatedIconButton*> &connection)
{
    connection.empty();
    int state = board[r][c]->getState();
    if (state == CellButton::UNOCCUPIED) return;

    for (const Direction *dir = &orig_dirs[0];
        dir < &orig_dirs[ORIG_DIRECTIONS_NUM];
        ++dir) {
        int row=r, column=c;
        std::vector<AnimatedIconButton*> line;

        while (true) {
            row += dir->first;
            column += dir->second;
            if (!isInRange(row,column)) break;
            AnimatedIconButton *btn = board[row][column];
            if (btn->getState() != state) break;
            line.push_back(btn);
        }
        row=r; column=c;
        while (true) {
            row -= dir->first;
            column -= dir->second;
            if (!isInRange(row,column)) break;
            AnimatedIconButton *btn = board[row][column];
            if (btn->getState() != state) break;
            line.push_back(btn);
        }
        if (line.size() >= MIN_LINE_ELIMINATION_SIZE-1) {
            std::copy(line.begin(), line.end(), std::back_inserter(connection));
        }
        line.empty();
    }
}
