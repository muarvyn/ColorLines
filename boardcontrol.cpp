#include "gameboard.h"
#include "boardcontrol.h"

BoardControl::BoardControl(CellGridControl *gc, QObject *parent)
    : QObject(parent)
    , gridControl(gc)
    , selectedCell(nullptr)
{
    board = new GameBoard(gridControl->getCells(), this);
}

void BoardControl::handleCellClicked( AnimatedIconButton *clickedButton,
                                      CellButton *unused)
{
    if (clickedButton==selectedCell) {
        selectedCell=nullptr;
        gridControl->hideAnimation();
    }
    else {
        if (selectedCell != nullptr) {
            selectedCell->setState(selectedCell->getState());
        }
        if (clickedButton->getState() == CellButton::UNOCCUPIED) {
            if (selectedCell != nullptr) {
                board->makeDijkstraSearch(
                    selectedCell->getRow(),
                    selectedCell->getColumn());

                std::vector<std::pair<int,int>> path;
                Board::distance_type dist = board->getReversePathTo(
                    clickedButton->getRow(),
                    clickedButton->getColumn(),
                    path);

                if (dist < OCCUPATION_THRESHOLD) {
                    gridControl->hideAnimation();
                    int st = selectedCell->getState();
                    int delay = 0;
                    path.push_back(std::make_pair(
                        selectedCell->getRow(), selectedCell->getColumn()));
                    AnimatedIconButton *path_button = nullptr;
                    for (std::vector<std::pair<int,int>>::reverse_iterator ri = path.rbegin();
                        ri != path.rend();
                        ++ri) {
                        path_button = gridControl->getCells()[ri->first][ri->second];
                        path_button->setupAnimation("opacity", 1, 0, 1000,
                            AnimatedIconButton::UNOCCUPIED);
                        gridControl->startDelayedAnimation(path_button, st, delay);
                        delay+=100;
                    }
                    connect(path_button, &AnimatedIconButton::animation_finished,
                        this,
                        [this, clickedButton, path_button] {
                            emit moveFinished(BoardInfo::cell_location(
                                clickedButton->getRow(), clickedButton->getColumn()));
                            disconnect(path_button, &AnimatedIconButton::animation_finished, nullptr, nullptr);
                        });
                    QTimer::singleShot(
                        delay,
                        clickedButton,
                        [clickedButton, st]{ clickedButton->setState(st); });
                    selectedCell = nullptr;
                }
    //            } else {
    //                clickedButton->setState(Board::getRandom());
            }
        } else {
            gridControl->setButtonAnimation(*clickedButton);
            selectedCell=clickedButton;
        }
    }
}