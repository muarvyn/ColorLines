#include "animatediconbutton.h"
#include "cellgridcontrol.h"

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
    board = new Board(boardCells, this);
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
                    clickedButton->setDelayed(st, delay);

                    selectedCell->setState(CellButton::UNOCCUPIED);
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
