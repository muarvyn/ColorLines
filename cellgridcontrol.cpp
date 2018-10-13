#include "animatediconbutton.h"
#include "cellgridcontrol.h"
#include "gameboard.h"

CellGridControl::CellGridControl(QGridLayout *gridLayout, QObject *parent)
    : QObject(parent)
    , selectedCell(nullptr)
{
    movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);

    movieLabel = new QLabel();
    movieLabel->setAlignment(Qt::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);
    movieLabel->setAutoFillBackground(true);
    movieLabel->setMovie(movie);
    for (BallColor::type c=BallColor::brown; c<=BallColor::yellow; c=static_cast<BallColor::type>(c+1))
    {
        ballIcons[c] = QIcon(QString(":/images/ball")+QString::number(c)+".gif");
    }
    for (int r = 0; r < BoardDim::ROWS_NUM; ++r) {
        for (int c = 0; c < BoardDim::COLUMNS_NUM; ++c) {
            boardCells[r][c] = createCell(r,c);
            gridLayout->addWidget(boardCells[r][c], r, c);
        }
    }

    board = new GameBoard(boardCells, this);
    gridLayout->update();
    makeNextMove();
}

AnimatedIconButton *CellGridControl::createCell(int r, int c)
{
    AnimatedIconButton * cell = new AnimatedIconButton(r,c,ballIcons);
    connect(cell, SIGNAL(clicked()), this, SLOT(handleCellClicked()));
    return cell;
}

void CellGridControl::setButtonAnimation(CellButton &btn)
{
    movie->stop();
    if (btn.getState() == CellButton::UNOCCUPIED) return;
    movie->setFileName(QString(":/images/ball")+QString::number(btn.getState())+".gif");
    movieLabel->setParent(&btn);
    fitAnimationSize(btn.size());
    connect(&btn, &CellButton::resized, this, [this,&btn] { this->movieResized(&btn);} );
    movieLabel->show();
    movie->start();
}

void CellGridControl::movieResized(CellButton *btn)
{
    // just drop selection
    hideAnimation();
    disconnect(btn, &CellButton::resized,nullptr, nullptr);
    selectedCell=nullptr;
    //fitAnimationSize(btn->size());
}

void CellGridControl::hideAnimation()
{
    movie->stop();
    movieLabel->setParent(nullptr);
}

void CellGridControl::fitAnimationSize(QSize size)
{
    movieLabel->resize(size);
    movieLabel->setAutoFillBackground(false);
    movie->setScaledSize( movieLabel->frameSize()/movieScale);
}

void CellGridControl::makeNextMove()
{
    const AnimatedIconButton *first_doze[GameBoard::doze_size];
    if (board->getRandomVacantDoze(first_doze)) {
        for (int i=0; i<GameBoard::doze_size; ++i) {
            AnimatedIconButton *btn =
                boardCells[first_doze[i]->getRow()][first_doze[i]->getColumn()];
            int state = Board::getRandom();
            btn->setupAnimation("opacity", 0, 1, 600, state);
            btn->startAnimation(state);
        }
    }
}

void CellGridControl::handleMove(AnimatedIconButton *btn)
{
    std::vector<AnimatedIconButton*> connection;
    board->getElimination(btn->getRow(), btn->getColumn(), connection);

    if (connection.size() > 0) {
        for (std::vector<AnimatedIconButton*>::iterator i = connection.begin();
            i < connection.end();
            ++i) {
            startEliminationAnimation(*i);
        }
        connect(btn, &AnimatedIconButton::animation_finished, this,
            [this
//            , btn
            ] {
//                disconnect(btn, &AnimatedIconButton::animation_finished, nullptr, nullptr);
                this->makeNextMove();
            });
        startEliminationAnimation(btn);
    } else {
        this->makeNextMove();
    }
}

void CellGridControl::startEliminationAnimation(AnimatedIconButton *btn)
{
    btn->setupAnimation("iconSize", btn->size(), QSize(5,5),
        600, AnimatedIconButton::UNOCCUPIED);
    btn->startAnimation(btn->getState());
}

void CellGridControl::handleCellClicked()
{
    AnimatedIconButton *clickedButton = qobject_cast<AnimatedIconButton *>(sender());
    if (clickedButton==selectedCell) {
        selectedCell=nullptr;
        hideAnimation();
//        clickedButton->setState(CellButton::UNOCCUPIED);
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
                    hideAnimation();
                    int st = selectedCell->getState();
                    int delay = 0;
                    path.push_back(std::make_pair(
                        selectedCell->getRow(), selectedCell->getColumn()));
                    AnimatedIconButton *path_button = nullptr;
                    for (std::vector<std::pair<int,int>>::reverse_iterator ri = path.rbegin();
                        ri != path.rend();
                        ++ri) {
                        path_button = boardCells[ri->first][ri->second];
                        path_button->setupAnimation("opacity", 1, 0, 1000,
                            AnimatedIconButton::UNOCCUPIED);
                        startDelayedAnimation(path_button, st, delay);
                        delay+=100;
                    }
                    connect(path_button, &AnimatedIconButton::animation_finished,
                        this,
                        [this
                        , clickedButton
//                        , path_button
                        ] {
//                            disconnect(path_button, &AnimatedIconButton::animation_finished,
//                                nullptr, nullptr);
                            this->handleMove(clickedButton);
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
            setButtonAnimation(*clickedButton);
            selectedCell=clickedButton;
        }
    }
}

void CellGridControl::startDelayedAnimation(
    AnimatedIconButton *btn, int animated_state, int delay)
{
    QTimer::singleShot(delay, btn,
        [btn, animated_state]{ btn->startAnimation(animated_state); });
}
