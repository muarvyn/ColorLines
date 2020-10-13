#include "gameboard.h"
#include "boardcontrol.h"

BoardControl::BoardControl(CellGridControl *gc, QObject *parent)
    : QObject(parent)
    , gridControl(gc)
    , selectedCell(nullptr)
{
    board = new GameBoard(gridControl->getCells(), this);
}

bool BoardControl::selectCell(BoardInfo::cell_location loc)
{
    selectCell(board->getCell(loc));
}

bool BoardControl::selectCell(AnimatedIconButton *cell)
{
    if (cell == selectedCell || cell->getState() == CellButton::UNOCCUPIED) {
        return false;
    }
    //TODO: does it stop selectedCell animation?
    if (selectedCell != nullptr) {
        selectedCell->setState(selectedCell->getState());
    }

    gridControl->setButtonAnimation(*cell);
    selectedCell = cell;
}

bool BoardControl::deselect() {
    if (selectedCell == nullptr)
        return false;
    selectedCell=nullptr;
    gridControl->hideAnimation();
    return true;
}

void BoardControl::animatePath(std::vector<BoardInfo::cell_location> &path,
                                AnimatedIconButton *lastButton) {

    int delay = 0;
    AnimatedIconButton *path_button = nullptr;
    int st = selectedCell->getState();

    for (std::vector<BoardInfo::cell_location>::reverse_iterator ri = path.rbegin();
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
        [this, lastButton, path_button] {
            emit moveFinished(BoardInfo::cell_location(
                lastButton->getRow(), lastButton->getColumn()));
            disconnect(path_button, &AnimatedIconButton::animation_finished, nullptr, nullptr);
        });
    QTimer::singleShot(
        delay,
        lastButton,
        [lastButton, st]{ lastButton->setState(st); });
    selectedCell = nullptr;
}

void BoardControl::animateSpawn(
    const std::vector<BoardInfo::cell_location> &locations,
    const std::vector<BallColor::type> &colors)
{
    if (locations.size() > 0) {
        gridControl->hideAnimation();
        AnimatedIconButton *btn;
//        for (std::vector<BoardInfo::cell_location>::iterator i = locations.begin();
//            i < locations.end();
        for (size_t i = 0;
            i < locations.size();
            ++i) {
            BoardInfo::cell_location loc = locations[i];
            int state = colors[i];
            btn = gridControl->getCells()[loc.first][loc.second];
            btn->setupAnimation("opacity", 0, 1, 600, state);
            btn->startAnimation(state);
        }
        connect(
            btn, &AnimatedIconButton::animation_finished,
            this, [this] {
                emit gridControl->animationFinished();
                //disconnect(gridControl, &CellGridControl::animationFinished, nullptr,nullptr);
                });
    } else {
        emit gridControl->animationFinished();
        //disconnect(gridControl, &CellGridControl::animationFinished, nullptr,nullptr);
    }
}

void BoardControl::animateDisappear(
    const std::vector<BoardInfo::cell_location> &locations)
{
    if (locations.size() > 0) {
        gridControl->hideAnimation();
        AnimatedIconButton *btn;
        for (std::vector<BoardInfo::cell_location>::const_iterator i = locations.begin();
            i < locations.end();
            ++i) {
            btn = gridControl->getCells()[i->first][i->second];
            gridControl->startEliminationAnimation(btn);
        }
        connect(
            btn, &AnimatedIconButton::animation_finished,
            this, [this] {
                emit gridControl->animationFinished();
                disconnect(gridControl, &CellGridControl::animationFinished, nullptr,nullptr);});
    } else {
        emit gridControl->animationFinished();
        disconnect(gridControl, &CellGridControl::animationFinished, nullptr,nullptr);
    }

}

void BoardControl::handleClicked( AnimatedIconButton *clickedButton) {
    if (clickedButton==selectedCell) {
        deselect();
        return;
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
                animatePath(path, clickedButton);
            }
        }
    } else {
        gridControl->setButtonAnimation(*clickedButton);
        selectedCell=clickedButton;
    }
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
