#include "animatediconbutton.h"
#include "cellgridcontrol.h"
#include "gameboard.h"

CellGridControl::CellGridControl(QGridLayout *gridLayout, QObject *parent)
    : QObject(parent)
    , selectedCell(nullptr)
{
    movie = new QMovie(this);
    movie->setCacheMode(QMovie::CacheAll);

    movieLabel = new QLabel(tr("nothing"));
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
    this->fitAnimationSize(QSize(40,40)); // TODO: fix "magic numbers"

    board = new GameBoard(boardCells, this);
    this->makeNextMove();
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
    movieLabel->show();
    movie->start();
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
            boardCells[first_doze[i]->getRow()][first_doze[i]->getColumn()]->
                setDelayed(Board::getRandom(),i*200+1);
        }
    }
}

void CellGridControl::handleMove(AnimatedIconButton *btn, int state)
{
    btn->setState(state);
    std::vector<AnimatedIconButton*> connection;
    this->board->getElimination(btn->getRow(), btn->getColumn(), connection);

    if (connection.size() > 0) {
        for (std::vector<AnimatedIconButton*>::iterator i = connection.begin();
            i < connection.end();
            ++i) {
            (*i)->setDelayed(CellButton::UNOCCUPIED,400);
        }
        btn->setDelayed(CellButton::UNOCCUPIED, 400);
    }
    this->makeNextMove();
}

void CellGridControl::handleCellClicked()
{
    AnimatedIconButton *clickedButton = qobject_cast<AnimatedIconButton *>(sender());
    if (clickedButton==selectedCell) {
        selectedCell=nullptr;
        hideAnimation();
        clickedButton->setState(CellButton::UNOCCUPIED);
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
                /*Board::distance_type dist = board->getDistance(
                    clickedButton->getRow(),
                    clickedButton->getColumn());*/
                Board::distance_type dist = board->getReversePathTo(
                    clickedButton->getRow(),
                    clickedButton->getColumn(),
                    path);

                if (dist < OCCUPATION_THRESHOLD) {
                    hideAnimation();
                    int st = selectedCell->getState();
                    int delay = 0;
                    for (std::vector<std::pair<int,int>>::reverse_iterator ri = path.rbegin();
                        ri != path.rend();
                        ++ri) {
                        AnimatedIconButton *path_button = boardCells[ri->first][ri->second];
                        path_button->startDelayed(st, delay);
                        delay+=100;
                    }
                    //clickedButton->setDelayed(st, delay);
                    QTimer::singleShot(
                        delay,
                        this,
                        [this, clickedButton, st] () { handleMove(clickedButton, st); });
                    //selectedCell->setState(CellButton::UNOCCUPIED);
                    selectedCell = nullptr;
                }
            } else {
                clickedButton->setState(Board::getRandom());
            }
        } else {
            setButtonAnimation(*clickedButton); // remove icon, if any?
            selectedCell=clickedButton;
        }
    }
}
