#include "gameboard.h"
#include "gamecontrol.h"
#include "animatediconbutton.h"
#include "cellgridcontrol.h"

CellGridControl::CellGridControl(
    QGridLayout *gridLayout,
    QObject *parent
    )
    : QObject(parent)
    , selectedCell(nullptr)
    //, gameControl(new GameControl(this, this))
{
    movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);

    movieLabel = new QLabel();
    movieLabel->setAlignment(Qt::AlignCenter);
    movieLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    movieLabel->setBackgroundRole(QPalette::Dark);
    movieLabel->setAutoFillBackground(true);
    movieLabel->setMovie(movie);

    for (BallColor::type c=BallColor::first;
        c<=BallColor::last;
        c=static_cast<BallColor::type>(c+1)) //TOFIX: define operator++?
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

//    connect(
//        this, &CellGridControl::userInput,
//        gameControl, &GameControl::handleMove); //TOFIX: temporary code

    gridLayout->update();
//    makeNextMove();
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
/*
void CellGridControl::makeNextMove()
{
    BallColor::type *spawn_begin, *spawn_end;
    std::tie(spawn_begin, spawn_end) = gameControl->getNextSpawn();

    std::vector<std::pair<int,int>> spawn_pos;
    gameControl->generateRandomSpawn(spawn_pos);

    for (std::vector<std::pair<int,int>>::iterator i = spawn_pos.begin();
        i < spawn_pos.end();
        ++i) {
        AnimatedIconButton *btn = boardCells[i->first][i->second];
        int state = *spawn_begin++;
        btn->setupAnimation("opacity", 0, 1, 600, state);
        btn->startAnimation(state);
    }
    gameControl->makeNextMove();
}

void CellGridControl::handleMove(AnimatedIconButton *btn)
{
    emit userInput(BoardInfo::cell_location(btn->getRow(),btn->getColumn()));

    std::vector<BoardInfo::cell_location> connection;
    BoardInfo bi(*this);
    bi.getStraitConnection(
        BoardInfo::cell_location(btn->getRow(), btn->getColumn()),
        connection);

    if (connection.size() > 0) {
        for (std::vector<BoardInfo::cell_location>::iterator i = connection.begin();
            i < connection.end();
            ++i) {
            startEliminationAnimation(boardCells[i->first][i->second]);
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
*/
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
                            ///this->handleMove(clickedButton);
                            emit userInput(BoardInfo::cell_location(
                                clickedButton->getRow(), clickedButton->getColumn()));
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

void CellGridControl::removeWithAnimation(
    const std::vector<BoardInfo::cell_location> &locations)
{
    if (locations.size() > 0) {
        hideAnimation();
        AnimatedIconButton *btn;
        for (std::vector<BoardInfo::cell_location>::const_iterator i = locations.begin();
            i < locations.end();
            ++i) {
            btn = boardCells[i->first][i->second];
            startEliminationAnimation(btn);
        }
        connect(
            btn, &AnimatedIconButton::animation_finished,
            this, [this] {
                emit animationFinished();
                disconnect(this, &CellGridControl::animationFinished, nullptr,nullptr);});
    } else {
        emit animationFinished();
        disconnect(this, &CellGridControl::animationFinished, nullptr,nullptr);
    }
}

void CellGridControl::putWithAnimation(
    const std::vector<BoardInfo::cell_location> &locations,
    const std::vector<BallColor::type> &colors)
{
    if (locations.size() > 0) {
        hideAnimation();
        AnimatedIconButton *btn;
//        for (std::vector<BoardInfo::cell_location>::iterator i = locations.begin();
//            i < locations.end();
        for (size_t i = 0;
            i < locations.size();
            ++i) {
            BoardInfo::cell_location loc = locations[i];
            int state = colors[i];
            btn = boardCells[loc.first][loc.second];
            btn->setupAnimation("opacity", 0, 1, 600, state);
            btn->startAnimation(state);
        }
        connect(
            btn, &AnimatedIconButton::animation_finished,
            this, [this] {
                emit animationFinished();
                disconnect(this, &CellGridControl::animationFinished, nullptr,nullptr);});
    } else {
        emit animationFinished();
        disconnect(this, &CellGridControl::animationFinished, nullptr,nullptr);
    }
}
