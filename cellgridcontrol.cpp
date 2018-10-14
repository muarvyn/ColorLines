#include "gameboard.h"
#include "gamecontrol.h"
#include "animatediconbutton.h"
#include "cellgridcontrol.h"

CellGridControl::CellGridControl(
    QGridLayout *gridLayout,
    QLabel *nextLabels[SPAWN_BALLS_NUM],
    QObject *parent
    )
    : QObject(parent)
    , selectedCell(nullptr)
    , gameControl(new GameControl(this, this))
{
    movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);

    movieLabel = new QLabel();
    movieLabel->setAlignment(Qt::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);
    movieLabel->setAutoFillBackground(true);
    movieLabel->setMovie(movie);

    std::copy(&nextLabels[0], &nextLabels[SPAWN_BALLS_NUM], nextMoveLabels);

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
    for (QLabel **nextLab=&nextMoveLabels[0];
        nextLab < nextMoveLabels+SPAWN_BALLS_NUM;
        ++nextLab) {
        (*nextLab)->setMinimumSize(QSize(40,40)); //TOFIX: magic numbers
    }

    board = new GameBoard(boardCells, this);

    gridLayout->update();
    makeNextMove();
}

BallColor::type CellGridControl::getColorAt(int r, int c) const
{
    return static_cast<BallColor::type>(boardCells[r][c]->getState());
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
    BallColor::type *spawn_begin, *spawn_end;
    std::tie(spawn_begin, spawn_end) = gameControl->getNextSpawn();
    const AnimatedIconButton *first_doze[SPAWN_BALLS_NUM];
    if (board->getRandomVacantDoze(first_doze)) {
        for (int i=0; i<SPAWN_BALLS_NUM; ++i) {
            AnimatedIconButton *btn =
                boardCells[first_doze[i]->getRow()][first_doze[i]->getColumn()];
            int state = *spawn_begin++;
            btn->setupAnimation("opacity", 0, 1, 600, state);
            btn->startAnimation(state);
        }
    }
    gameControl->makeNextMove();
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
            ] {
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
                        ] {
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
