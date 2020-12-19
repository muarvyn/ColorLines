#include "cellgridcontrol.h"
#include "animatediconbutton.h"
#include "editmodecontrol.h"

EditModeControl::EditModeControl(CellGridControl *board,
                                 CellGridControl *toolbar,
                                 ColorCell::LineIterator line,
                                 QObject *parent)
    : QObject(parent)
    , board(board)
    , toolbar(toolbar)
{
    for (BallColor::type c=BallColor::first; c<=BallColor::last; ++c, ++line) {
        toolbar->setColorAt(line.row, line.column, c);
    }
    board->hideAnimation();
    CellButton *selectedCell = toolbar->getCells()[0][0];
    selectedColor = selectedCell->getColor();
    toolbar->setButtonAnimation(*selectedCell);
    connect(board, &CellGridControl::userInput, this, &EditModeControl::handleBoardInput);
    connect(toolbar, &CellGridControl::userInput, this, &EditModeControl::handleToolbarInput);
}

EditModeControl::~EditModeControl()
{
    toolbar->hideAnimation();
    disconnect(this, nullptr, nullptr, nullptr);
}

void EditModeControl::handleBoardInput( AnimatedIconButton *clickedButton)
{
    if (clickedButton->getState() == CellButton::UNOCCUPIED) {
        board->setColorAt(clickedButton->getRow(),
                        clickedButton->getColumn(),
                        selectedColor);
    }
    else {
        board->setColorAt(clickedButton->getRow(),
                        clickedButton->getColumn(),
                        BallColor::none);
    }
}

void EditModeControl::handleToolbarInput( AnimatedIconButton *clickedButton)
{
    toolbar->hideAnimation();
    toolbar->setButtonAnimation(*clickedButton);
    selectedColor=clickedButton->getColor();
}

