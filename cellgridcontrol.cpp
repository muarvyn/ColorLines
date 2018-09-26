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
    //QString fn = QString("/home/vlad/images/green-anim.gif");
    //movie->stop();
    movieLabel->setMovie(movie);
    //movie->setFileName(fn);
    //movie->isValid();
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
    if (btn.getState() == -1) return;
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
    CellButton *clickedButton = qobject_cast<CellButton *>(sender());
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
                    int delay = 0;
                    for (std::vector<std::pair<int,int>>::iterator i = path.begin();
                        i != path.end();
                        ++i) {
                        //boardCells[i->first][i->second]->setState(selectedCell->getState());
                        boardCells[i->first][i->second]->startDelayed(delay);
                        delay+=100;
                    }
                    clickedButton->setState(selectedCell->getState());

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
