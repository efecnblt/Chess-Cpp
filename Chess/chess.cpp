#include "chess.h"
#include <string>
#include <random>
#include <fstream>
Cell Board::cell[8][8];
Cell Board::tempBoard[8][8];

bool rookMove1 = false;
bool rookMove2 = false;
bool rookMove3 = false;
bool rookMove4 = false;
bool kingMove1 = false;
bool kingMove2 = false;
std::vector<char> WhiteEaten{};
std::vector<char> BlackEaten{};

std::vector<std::string> Piece{"KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK", "PAWN", "EMPTY"};
std::vector<std::string> Color{"WHITE", "BLACK", "NONE"};

std::vector<int> x_knightMoves{
    2,
    2,
    -2,
    -2,
    1,
    1,
    -1,
    -1,
};

std::vector<int> y_knightMoves{
    -1,
    1,
    1,
    -1,
    2,
    -2,
    -2,
    2,
};

std::vector<int> x_kingMoves{
    1,
    1,
    1,
    -1,
    -1,
    -1,
    0,
    0

};

std::vector<int> y_kingMoves{
    1,
    -1,
    0,
    1,
    -1,
    0,
    1,
    -1,
};

// OK
std::string Cell::getColor()
{
    return _color;
}
// OK
std::string Cell::getType()
{
    return _piece;
}
// OK
Cell::Cell()
{
    _piece = getType();
    _color = getColor();
}
// OK
Cell::Cell(std::string piece, std::string color)
{
    piece = getType();
    color = getColor();
}
// OK
std::vector<Cell> Board::GetAllPossibleMoves(Cell *selectedCell)
{
    std::vector<Cell> PossibleMoves{};
    int currentX = selectedCell->getXCoordinate();
    int currentY = selectedCell->getYCoordinate();
    int nextPos_x;
    int nextPos_y;
    switch (selectedCell->getType()[2])
    {
    case 'N':
        for (size_t i = 0; i < x_kingMoves.size(); i++)
        {

            if (isOutOfBounds(currentX + x_kingMoves.at(i), currentY + y_kingMoves.at(i)))
                continue;

            if (isEmpty(currentX + x_kingMoves.at(i), currentY + y_kingMoves.at(i)))
            {
                PossibleMoves.push_back(cell[currentX + x_kingMoves.at(i)][currentY + y_kingMoves.at(i)]);
            }
            else
            {
                if (!isSameColor(currentX + x_kingMoves.at(i), currentY + y_kingMoves.at(i), selectedCell))
                {
                    PossibleMoves.push_back(cell[currentX + x_kingMoves.at(i)][currentY + y_kingMoves.at(i)]);
                }
                continue;
            }
        }
        if (selectedCell->getColor() == Color.at(0))
        {
            if (!isThreatenedByBishop(Board::getCell(7, 2)) && !isThreatenedByRook(Board::getCell(7, 2)) && !isThreatenedByKnight(Board::getCell(7, 2)))
                if (!isThreatenedByBishop(Board::getCell(7, 3)) && !isThreatenedByRook(Board::getCell(7, 3)) && !isThreatenedByKnight(Board::getCell(7, 3)))
                    if (!isThreatenedByBishop(Board::getCell(7, 4)) && !isThreatenedByRook(Board::getCell(7, 4)) && !isThreatenedByKnight(Board::getCell(7, 4)))
                        if (canMakeCastling(selectedCell, Board::getCell(7, 2)))
                        {
                            PossibleMoves.push_back(cell[7][2]);
                            if (player_order == Color.at(0))
                                kingMove1 = true;
                            else
                                kingMove2 = true;
                        }
        }
        else
        {
            if (!isThreatenedByBishop(Board::getCell(7, 4)) && !isThreatenedByRook(Board::getCell(7, 4)) && !isThreatenedByKnight(Board::getCell(7, 4)))
                if (!isThreatenedByBishop(Board::getCell(7, 5)) && !isThreatenedByRook(Board::getCell(7, 5)) && !isThreatenedByKnight(Board::getCell(7, 5)))
                    if (!isThreatenedByBishop(Board::getCell(7, 6)) && !isThreatenedByRook(Board::getCell(7, 6)) && !isThreatenedByKnight(Board::getCell(7, 6)))
                        if (canMakeCastling(selectedCell, Board::getCell(7, 6)))
                        {
                            PossibleMoves.push_back(cell[7][6]);
                            if (player_order == Color.at(0))
                                kingMove1 = true;
                            else
                                kingMove2 = true;
                        }
        }

        break;
    case 'E':
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x--;
            nextPos_y--;

            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x--;
            nextPos_y++;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x++;
            nextPos_y--;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_y++;
            nextPos_x++;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x++;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x--;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_y++;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_y--;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        break;
    case 'S':
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x--;
            nextPos_y--;

            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x--;
            nextPos_y++;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x++;
            nextPos_y--;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_y++;
            nextPos_x++;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        break;
    case 'I':

        for (size_t i = 0; i < x_knightMoves.size(); i++)
        {

            if (!isOutOfBounds(currentX + x_knightMoves.at(i), currentY + y_knightMoves.at(i)))
            {

                if ((isEmpty(currentX + x_knightMoves.at(i), currentY + y_knightMoves.at(i))) || (!isEmpty(currentX + x_knightMoves.at(i), currentY + y_knightMoves.at(i)) && !isSameColor(currentX + x_knightMoves.at(i), currentY + y_knightMoves.at(i), selectedCell)))
                {

                    PossibleMoves.push_back(cell[currentX + x_knightMoves.at(i)][currentY + y_knightMoves.at(i)]);
                }
            }
        }

        break;

    case 'O':

        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x++;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_x--;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_y++;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }
        nextPos_x = currentX;
        nextPos_y = currentY;
        while (true)
        {
            nextPos_y--;
            if (isOutOfBounds(nextPos_x, nextPos_y))
                break;
            if (isEmpty(nextPos_x, nextPos_y))
            {
                PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
            }
            else
            {
                if (!isSameColor(nextPos_x, nextPos_y, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x][nextPos_y]);
                }
                break;
            }
        }

        break;

    case 'W':
        nextPos_x = currentX;
        nextPos_y = currentY;
        if (selectedCell->getColor() == Color.at(0))
        {
            if (currentX == 6)
            {
                if (isEmpty(nextPos_x - 1, nextPos_y))
                {
                    PossibleMoves.push_back(cell[nextPos_x - 1][nextPos_y]);
                    if (isEmpty(nextPos_x - 2, nextPos_y))
                    {
                        PossibleMoves.push_back(cell[nextPos_x - 2][nextPos_y]);
                    }
                }

                if (!isEmpty(nextPos_x - 1, nextPos_y + 1) && !isSameColor(nextPos_x - 1, nextPos_y + 1, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x - 1][nextPos_y + 1]);
                }
                if (!isEmpty(nextPos_x - 1, nextPos_y - 1) && !isSameColor(nextPos_x - 1, nextPos_y - 1, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x - 1][nextPos_y - 1]);
                }
            }
            else
            {
                if (isEmpty(nextPos_x - 1, nextPos_y))
                {
                    PossibleMoves.push_back(cell[nextPos_x - 1][nextPos_y]);
                }
                if (!isEmpty(nextPos_x - 1, nextPos_y + 1) && !isSameColor(nextPos_x - 1, nextPos_y + 1, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x - 1][nextPos_y + 1]);
                }
                if (!isEmpty(nextPos_x - 1, nextPos_y - 1) && !isSameColor(nextPos_x - 1, nextPos_y - 1, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x - 1][nextPos_y - 1]);
                }
            }
        }
        else
        {
            if (currentX == 1)
            {
                if (isEmpty(nextPos_x + 1, nextPos_y))
                {
                    PossibleMoves.push_back(cell[nextPos_x + 1][nextPos_y]);
                    if (isEmpty(nextPos_x + 2, nextPos_y))
                    {
                        PossibleMoves.push_back(cell[nextPos_x + 2][nextPos_y]);
                    }
                }

                if (!isEmpty(nextPos_x + 1, nextPos_y + 1) && !isSameColor(nextPos_x + 1, nextPos_y + 1, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x + 1][nextPos_y + 1]);
                }
                if (!isEmpty(nextPos_x + 1, nextPos_y - 1) && !isSameColor(nextPos_x + 1, nextPos_y - 1, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x + 1][nextPos_y - 1]);
                }
            }
            else
            {
                if (isEmpty(nextPos_x + 1, nextPos_y))
                {
                    PossibleMoves.push_back(cell[nextPos_x + 1][nextPos_y]);
                }
                if (!isEmpty(nextPos_x + 1, nextPos_y + 1) && !isSameColor(nextPos_x + 1, nextPos_y + 1, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x + 1][nextPos_y + 1]);
                }
                if (!isEmpty(nextPos_x + 1, nextPos_y - 1) && !isSameColor(nextPos_x + 1, nextPos_y - 1, selectedCell))
                {
                    PossibleMoves.push_back(cell[nextPos_x + 1][nextPos_y - 1]);
                }
            }
        }

    default:
        break;
    }
    return PossibleMoves;
}

// fillBlank-> Fill the cell to be paved with the existing stone.
void Cell::fillBlank(Cell *blank)
{
    _color = blank->getColor();
    _piece = blank->getType();
}
// setToEmpty-> The movement empties the previous position of the stone.
void Cell::setToEmpty()
{
    _piece = Piece.at(6); // assign EMPTY
    _color = Color.at(2); // assign NONE
}
// setTypeAndColor-> It sets the color and type of the stone in the cell.
void Cell::setTypeAndColor(std::string piece, std::string color)
{

    _piece = piece;
    _color = color;
}
// setBoard-> It sets the initial state of the board.
void Board::setBoard()
{

    /*  std::vector<std::string> Piece{"KING", "QUEEN", "BISHOP", "KNIGHT", "ROOK", "PAWN", "EMPTY"};
     std::vector<std::string> Color{"WHITE", "BLACK", "NONE"}; */
    player_order = Color.at(0);
    cell[7][0].setTypeAndColor(Piece.at(4), Color.at(0)); // Rook-WHITE
    cell[7][1].setTypeAndColor(Piece.at(3), Color.at(0)); // Knight-WHITE
    cell[7][2].setTypeAndColor(Piece.at(2), Color.at(0)); // Bishop-WHITE
    cell[7][3].setTypeAndColor(Piece.at(1), Color.at(0)); // Queen-WHITE
    cell[7][4].setTypeAndColor(Piece.at(0), Color.at(0)); // King-WHITE
    cell[7][5].setTypeAndColor(Piece.at(2), Color.at(0)); // Bishop-WHITE
    cell[7][6].setTypeAndColor(Piece.at(3), Color.at(0)); // Knight-WHITE
    cell[7][7].setTypeAndColor(Piece.at(4), Color.at(0)); // Rook-WHITE

    cell[0][0].setTypeAndColor(Piece.at(4), Color.at(1)); // Rook-BLACK
    cell[0][1].setTypeAndColor(Piece.at(3), Color.at(1)); // Knight-BLACK
    cell[0][2].setTypeAndColor(Piece.at(2), Color.at(1)); // Bishop-BLACK
    cell[0][3].setTypeAndColor(Piece.at(1), Color.at(1)); // Queen-BLACK
    cell[0][4].setTypeAndColor(Piece.at(0), Color.at(1)); // King-BLACK
    cell[0][5].setTypeAndColor(Piece.at(2), Color.at(1)); // Bishop-BLACK
    cell[0][6].setTypeAndColor(Piece.at(3), Color.at(1)); // Knight-BLACK
    cell[0][7].setTypeAndColor(Piece.at(4), Color.at(1)); // Rook-BLACK

    for (int i = 0; i < 8; i++)
    {
        cell[6][i].setTypeAndColor(Piece.at(5), Color.at(0));
        cell[1][i].setTypeAndColor(Piece.at(5), Color.at(1));
    }

    for (int i = 2; i < 6; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cell[i][j].setTypeAndColor(Piece.at(6), Color.at(2));
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            cell[i][j].setXCoordinate(i);
            cell[i][j].setYCoordinate(j);
        }
    }
}
// OK
void Board::printBoard()
{

    std::cout << "Exit game with (exit/close/save)!" << std::endl;
    printAllEaten();
    std::cout << std::endl;
    int flag = 9;
    for (size_t i = 0; i < 8; i++)
    {
        flag -= 1;
        std::cout << " " << flag << " | ";
        for (size_t j = 0; j < 8; j++)
        {
            std::string p = cell[i][j].getType();
            std::string c = cell[i][j].getColor();
            switch (p[2])
            {
            case 'N': // KING
                if (c == Color.at(0) ? std::cout << " K " : std::cout << " k ")
                    ;
                break;
            case 'E':
                if (c == Color.at(0) ? std::cout << " Q " : std::cout << " q ")
                    ;
                break;
            case 'S':
                if (c == Color.at(0) ? std::cout << " B " : std::cout << " b ")
                    ;
                break;
            case 'I':
                if (c == Color.at(0) ? std::cout << " N " : std::cout << " n ")
                    ;
                break;
            case 'O':
                if (c == Color.at(0) ? std::cout << " R " : std::cout << " r ")
                    ;
                break;
            case 'W':
                if (c == Color.at(0) ? std::cout << " P " : std::cout << " p ")
                    ;
                break;
            case 'P':
                std::cout << " . ";
                ;
                break;
            default:

                break;
            }
        }
        std::cout << std::endl;
    }
    std::cout << "      -----------------------" << std::endl;
    std::cout << "      a  b  c  d  e  f  g  h " << std::endl;
    saveToFile();
}
/*copyBoard-> To enable evaluating all possible scenarios before making an automatic move, we
create a copy of the board to perform reassignment by duplicating the board.*/
void Board::copyBoard(Cell originalBoard[8][8], Cell copy[8][8])
{

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {

            copy[i][j] = originalBoard[i][j];
        }
    }
}
// OK
void Board::restoreOriginalBoard(Cell original[8][8], Cell copy[8][8])
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            original[i][j] = copy[i][j];
        }
    }
}
// setType-> When a pawn reaches the opposite side, manually assigning the piece to transform it into the chosen piece
void Cell::setType(std::string type)
{
    _piece = type;
}
// canMove -> Checking the validity of moves and providing users with information based on valid or invalid conditions; the brain of the game.
bool Board::canMove()
{

    std::string make_move;
    int x1, y1, x2, y2;
    char ch;
    bool _end = false;

    while (!_end)
    {

        if (player_order == Color.at(0) ? std::cout << "[White's Turn]" << std::endl : std::cout << "[Black's Turn]" << std::endl)
            ;

        std::cout << "Enter Your Move: ";
        std::cin >> make_move;

        if (make_move == "suggest")
        {

            std::vector<Cell> Cells{};
            bool endLoop = false;

            for (size_t i = 0; i < 8 && !endLoop; i++)
            {

                for (size_t j = 0; j < 8; j++)
                {
                    if (Board::getCell(i, j)->getType() != "EMPTY" && Board::getCell(i, j)->getColor() == player_order)
                    {
                        Cells.push_back(cell[i][j]);
                    }
                    else if (Board::getCell(i, j)->getType() == "EMPTY")
                    {
                        continue;
                    }
                }
            }

            std::vector<float> score;
            std::vector<std::vector<int>> Moves;

            for (size_t i = 0; i < Cells.size(); i++)
            {
                x1 = Cells.at(i).getXCoordinate();
                y1 = Cells.at(i).getYCoordinate();

                std::vector<Cell> PossibleMoves = GetAllPossibleMoves(Board::getCell(x1, y1));

                if ((PossibleMoves.size() > 0))
                {
                    for (size_t j = 0; j < PossibleMoves.size(); j++)
                    {
                        copyBoard(cell, tempBoard);
                        x2 = PossibleMoves.at(j).getXCoordinate();
                        y2 = PossibleMoves.at(j).getYCoordinate();

                        std::vector<int> move;
                        move.push_back(x1);
                        move.push_back(y1);
                        move.push_back(x2);
                        move.push_back(y2);
                        Moves.push_back(move);

                        cell[x2][y2].setTypeAndColor(Board::getCell(x1, y1)->getType(), Board::getCell(x1, y1)->getColor());
                        cell[x1][y1].setTypeAndColor(Piece.at(6), Color.at(2));

                        score.push_back(evaluateBoard(player_order));
                        restoreOriginalBoard(cell, tempBoard);
                    }
                }
                else
                    continue;
            }

            std::vector<int> for_x1;
            std::vector<int> for_y1;
            std::vector<int> for_x2;
            std::vector<int> for_y2;

            int max = score.at(0);
            for (size_t i = 1; i < score.size(); i++)
            {
                if (score.at(i) == max)
                {
                    for_x1.push_back(Moves.at(i).at(0));
                    for_y1.push_back(Moves.at(i).at(1));
                    for_x2.push_back(Moves.at(i).at(2));
                    for_y2.push_back(Moves.at(i).at(3));
                }

                else if (score.at(i) > max)
                {
                    max = score.at(i);
                    for_x1.clear();
                    for_y1.clear();
                    for_x2.clear();
                    for_y2.clear();
                    for_x1.push_back(Moves.at(i).at(0));
                    for_y1.push_back(Moves.at(i).at(1));
                    for_x2.push_back(Moves.at(i).at(2));
                    for_y2.push_back(Moves.at(i).at(3));
                }
            }

            if (for_x1.size() == 0)
            {
                for_x1.push_back(Moves.at(0).at(0));
                for_y1.push_back(Moves.at(0).at(1));
                for_x2.push_back(Moves.at(0).at(2));
                for_y2.push_back(Moves.at(0).at(3));
                x1 = for_x1.at(0);
                y1 = for_y1.at(0);
                x2 = for_x2.at(0);
                y2 = for_y2.at(0);
            }
            else
            {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, for_x1.size() - 1);

                int randomNumber = dis(gen);
                x1 = for_x1.at(randomNumber);
                y1 = for_y1.at(randomNumber);
                x2 = for_x2.at(randomNumber);
                y2 = for_y2.at(randomNumber);
            }

            std::cout << "Suggestion is: [" << convertIntToChar(y1) << abs(x1 - 8) << convertIntToChar(y2) << abs(x2 - 8) << "](Press enter!)";
            std::string ch;
            std::cin.ignore();
            getline(std::cin, ch);
        }
        else if (make_move == "exit" || make_move == "close" || make_move == "save")
        {
            std::cout << "Game moves are saved to the file... The game has been terminated. See you :)" << std::endl;

            return false;
        }
        else if (make_move.length() == 4 && !isalpha(make_move[0]) || !isdigit(make_move[1]) || !isalpha(make_move[2]) || !isdigit(make_move[3]) || make_move[0] > 'h' || make_move[2] > 'h')
        {
            system("clear");
            printBoard();
            std::cout << "Invalid input. Please enter valid limits.[a-h, 1-8]" << std::endl;
            continue;
        }

        else
        {
            x1 = abs((make_move[1] - 48) - 8);
            y1 = convertCharToInt(make_move[0]);
            x2 = abs((make_move[3] - 48) - 8);
            y2 = convertCharToInt(make_move[2]);
        }

        // Check the correctness of the player_order. If the player_order is correct,
        // make the move. If the player_order is wrong, give a warning. (Player_order = WHITE or BLACK)

        if (getCell(x1, y1)->getColor() == player_order)
        {
            if (makeMove(x1, y1, x2, y2) == false)
            {
                std::cout << "Invalid move, try again." << std::endl;
            }
            else
            {

                _end = true;
            }
        }
        else
        {
            std::cout << "It's not your turn. It's the turn of the [" << player_order << "] stones. Try again." << std::endl;
        }
    }

    if (player_order == Color.at(1))
        player_order = Color.at(0);
    else
        player_order = Color.at(1);
    if (!checkKing())
    {
        if (player_order == Color.at(1))
            std::cout << "WHITE WINS" << std::endl;
        else
            std::cout << "BLACK WINS!" << std::endl;
        return false;
    }

    return true;
}

// makeMove ->Determining which piece will be played based on the given coordinates.
bool Board::makeMove(int x1, int y1, int x2, int y2)
{

    if (x1 < 0 || x1 > 7 || y1 < 0 || y1 > 7 || x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7)
    {
        std::cout << "Please enter valid limits.[a-h, 1-8]" << std::endl;
        return false;
    }
    Cell *current_location = Board::getCell(x1, y1);
    Cell *request_location = Board::getCell(x2, y2);

    if (current_location->getColor() == request_location->getColor() && request_location->getColor() != Color.at(2))
    {
        std::cout << "Invalid move: You cannot put stone upon stone. Try again" << std::endl;
        return false;
    }

    switch (current_location->getType()[2])
    {

    case 'N':
        return playKing(current_location, request_location);
        break;
    case 'E':
        return playQueen(current_location, request_location);
        break;
    case 'S':
        return playBishop(current_location, request_location);
        break;
    case 'I':
        return playKnight(current_location, request_location);
        break;
    case 'O':
        return playRook(current_location, request_location);
        break;
    case 'W':
        return playPawn(current_location, request_location);
        break;
    case 'P':
        std::cout << "You don't have any stones there. Try again" << std::endl;
        return false;
        break;
    default:
        std::cout << "ERROR";
        break;
    }
    return false;
}
// isOutOfBounds ->Indicating whether the piece is crossing the boundaries of the 8x8 board
bool Board::isOutOfBounds(int x2, int y2)
{
    return (x2 < 0 || x2 > 7 || y2 < 0 || y2 > 7);
}

// The sequence of functions that determine valid moves based on the pieces.
bool Board::playKing(Cell *king, Cell *space)
{
    int current_X1 = king->getXCoordinate();
    int current_Y1 = king->getYCoordinate();
    int request_x1 = space->getXCoordinate();
    int request_y1 = space->getYCoordinate();

    if (current_X1 == request_x1 && current_Y1 == 4 && (request_y1 == 2 || request_y1 == 6))
    {

        if (request_y1 == 2)
        {
            if (!isThreatenedByBishop(Board::getCell(7, 2)) && !isThreatenedByRook(Board::getCell(7, 2)) && !isThreatenedByKnight(Board::getCell(7, 2)))
                if (!isThreatenedByBishop(Board::getCell(7, 3)) && !isThreatenedByRook(Board::getCell(7, 3)) && !isThreatenedByKnight(Board::getCell(7, 3)))
                    if (!isThreatenedByBishop(Board::getCell(7, 4)) && !isThreatenedByRook(Board::getCell(7, 4)) && !isThreatenedByKnight(Board::getCell(7, 4)))
                        if (canMakeCastling(king, space))
                        {

                            space->fillBlank(king);
                            king->setToEmpty();

                            if (player_order == Color.at(0))
                                kingMove1 = true;
                            else
                                kingMove2 = true;

                            return true;
                        }
                        else

                            return false;

                    else

                        return false;

                else

                    return false;

            else

                return false;
        }

        else if (request_y1 == 6)
        {
            if (!isThreatenedByBishop(Board::getCell(7, 2)) && !isThreatenedByRook(Board::getCell(7, 2)) && !isThreatenedByKnight(Board::getCell(7, 2)))
                if (!isThreatenedByBishop(Board::getCell(7, 3)) && !isThreatenedByRook(Board::getCell(7, 3)) && !isThreatenedByKnight(Board::getCell(7, 3)))
                    if (!isThreatenedByBishop(Board::getCell(7, 4)) && !isThreatenedByRook(Board::getCell(7, 4)) && !isThreatenedByKnight(Board::getCell(7, 4)))
                        if (canMakeCastling(king, space))
                        {
                            space->fillBlank(king);
                            king->setToEmpty();
                            if (player_order == Color.at(0))
                                kingMove1 = true;
                            else
                                kingMove2 = true;

                            return true;
                        }
                        else
                            return false;
                    else
                        return false;
                else
                    return false;
            else
                return false;
        }

        else
            return false;
    }
    // yukarı
    else if (current_X1 - request_x1 == 1 && current_Y1 == request_y1)
    {
        if (cell[request_x1][current_Y1].getColor() != Color.at(2) && cell[request_x1][request_y1].getColor() == player_order)
        {

            return false;
        }

        else
        {
            if (space->getType() != "EMPTY")
            {
                eaten(space);
            }

            space->fillBlank(king);
            king->setToEmpty();
            if (player_order == Color.at(0))
                kingMove1 = true;
            else
                kingMove2 = true;
            return true;
        }
    }
    // aşşağı
    else if (current_X1 - request_x1 == -1 && current_Y1 == request_y1)
    {
        if (cell[request_x1][current_Y1].getColor() != Color.at(2) && cell[request_x1][request_y1].getColor() == player_order)
        {

            return false;
        }

        else
        {
            if (space->getType() != "EMPTY")
            {
                eaten(space);
            }
            space->fillBlank(king);
            king->setToEmpty();
            if (player_order == Color.at(0))
                kingMove1 = true;
            else
                kingMove2 = true;
            return true;
        }
    }
    // sağa
    else if (request_y1 - current_Y1 == 1 && current_X1 == request_x1)
    {
        if (cell[current_X1][request_y1].getColor() != Color.at(2) && cell[request_x1][request_y1].getColor() == player_order)
        {
            return false;
        }
        else
        {
            if (space->getType() != "EMPTY")
            {
                eaten(space);
            }
            space->fillBlank(king);
            king->setToEmpty();
            if (player_order == Color.at(0))
                kingMove1 = true;
            else
                kingMove2 = true;
            return true;
        }
    }
    // sola
    else if (request_y1 - current_Y1 == -1 && current_X1 == request_x1)
    {
        if (cell[current_X1][request_y1].getColor() != Color.at(2) && cell[request_x1][request_y1].getColor() == player_order)
        {
            return false;
        }
        else
        {
            if (space->getType() != "EMPTY")
            {
                eaten(space);
            }
            space->fillBlank(king);
            king->setToEmpty();
            if (player_order == Color.at(0))
                kingMove1 = true;
            else
                kingMove2 = true;
            return true;
        }
    }

    else if (abs(current_Y1 - request_y1 > 1) || abs(current_X1 - request_x1 > 1))
    {
        return false;
    }
    // sol yukarı çapraz
    else if (current_X1 - request_x1 == 1 && current_Y1 - request_y1 == 1)
    {
        if (cell[request_x1][request_y1].getColor() != Color.at(2) && cell[request_x1][request_y1].getType() == player_order)
        {
            return false;
        }
        else
        {
            if (space->getType() != "EMPTY")
            {
                eaten(space);
            }
            space->fillBlank(king);
            king->setToEmpty();
            if (player_order == Color.at(0))
                kingMove1 = true;
            else
                kingMove2 = true;
            return true;
        }
    }
    // sağ yukarı çapraz
    else if (current_X1 - request_x1 == 1 && current_Y1 - request_y1 == -1)
    {
        if (cell[request_x1][request_y1].getColor() != Color.at(2) && cell[request_x1][request_y1].getType() == player_order)
        {
            return false;
        }
        else
        {
            if (space->getType() != "EMPTY")
            {
                eaten(space);
            }
            space->fillBlank(king);
            king->setToEmpty();
            if (player_order == Color.at(0))
                kingMove1 = true;
            else
                kingMove2 = true;
            return true;
        }
    }

    else if (current_X1 - request_x1 == -1 && current_Y1 - request_y1 == 1)
    {

        if (cell[request_x1][request_y1].getColor() != Color.at(2) && cell[request_x1][request_y1].getType() == player_order)
        {

            return false;
        }
        else
        {
            if (space->getType() != "EMPTY")
            {
                eaten(space);
            }
            space->fillBlank(king);
            king->setToEmpty();
            if (player_order == Color.at(0))
                kingMove1 = true;
            else
                kingMove2 = true;
            return true;
        }
    }

    else if (current_X1 - request_x1 == -1 && current_Y1 - request_y1 == -1)
    {
        if (cell[request_x1][request_y1].getColor() != Color.at(2) && cell[request_x1][request_y1].getType() == player_order)
        {
            return false;
        }
        else
        {
            if (space->getType() != "EMPTY")
            {
                eaten(space);
            }
            space->fillBlank(king);
            king->setToEmpty();
            if (player_order == Color.at(0))
                kingMove1 = true;
            else
                kingMove2 = true;
            return true;
        }
    }

    return false;
}
// OK
bool Board::playQueen(Cell *queen, Cell *space)
{

    int current_X1 = queen->getXCoordinate();
    int current_Y1 = queen->getYCoordinate();
    int request_x1 = space->getXCoordinate();
    int request_y1 = space->getYCoordinate();

    bool check = false;
    /* if (current_X1 != request_x1 || current_Y1 != request_y1)
    {
        // If I'm only moving in a horizontal line, my x value is constant.
        if (current_X1 == request_x1)
        {
            if (current_Y1 - request_y1 < 0)
            {
                for (size_t i = current_Y1 + 1; i != request_y1; i++)
                {
                    if (cell[current_X1][i].getColor() != Color.at(2) && cell[current_X1][i - 1].getType() != "EMPTY")
                    {
                        return false;
                    }
                }
            }
            else if (current_Y1 - request_y1 > 0)
            {
                for (size_t i = current_Y1 - 1; i != request_y1; i--)
                {
                    if (cell[current_X1][i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }

        else if (current_Y1 == request_y1)
        {
            if (current_X1 - request_x1 < 0)
            {
                for (size_t i = current_X1 + 1; i != request_x1; i++)
                {
                    if (cell[i][current_Y1].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            else if (current_X1 - request_x1 > 0)
            {
                for (size_t i = current_X1 - 1; i != request_x1; i--)
                {
                    if (cell[i][current_X1].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }

        else if (abs(current_X1 - request_x1) == abs(current_Y1 - request_y1))
        {
            if (request_x1 - current_X1 > 0)
            {
                // aşşağı iner buda x in arttığını gösterir
                if (current_Y1 - request_y1 < 0)
                {
                    for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                    {

                        if (cell[current_X1 + 1 * i][current_Y1 + 1 * i].getColor() != Color.at(2))
                            return false;
                    }
                }
                else if (current_Y1 - request_y1 > 0)
                {
                    for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                    {

                        if (cell[current_X1 + 1 * i][current_Y1 - 1 * i].getColor() != Color.at(2))
                            return false;
                    }
                }
            }
            else if (request_x1 - current_X1 < 0)
            {
                if (current_Y1 - request_y1 < 0)
                {
                    for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                    {

                        if (cell[current_X1 - 1 * i][current_Y1 + 1 * i].getColor() != Color.at(2))
                            return false;
                    }
                }
                else if (current_Y1 - request_y1 > 0)
                {
                    for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                    {

                        if (cell[current_X1 - 1 * i][current_Y1 - 1 * i].getColor() != Color.at(2))
                            return false;
                    }
                }
                // yukarı çıkar  buda x in azaldığını gösterir
            }
        }

        else
            return false;
    }
    else
    {
        return false;
    } */

    if (current_X1 == request_x1 || current_Y1 == request_y1)
    {
        if (current_X1 == request_x1)
        {
            // SAĞA GİDİŞ
            if (current_Y1 - request_y1 < 0)
            {
                for (size_t i = current_Y1 + 1; i != request_y1; i++)
                {
                    if (cell[current_X1][i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            // SOLA GİDİŞ
            else if (current_Y1 - request_y1 > 0)
            {
                for (size_t i = current_Y1 - 1; i != request_y1; i--)
                {
                    if (cell[current_X1][i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }

        else if (current_Y1 == request_y1)
        {
            //  AŞŞAĞI GİDİŞ
            if (current_X1 - request_x1 < 0)
            {
                for (size_t i = current_X1 + 1; i != request_x1; i++)
                {

                    if (cell[i][current_Y1].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            // YUKARI GİDİŞ
            else if (current_X1 - request_x1 > 0)
            {
                for (size_t i = current_X1 - 1; i != request_x1; i--)
                {
                    if (cell[i][current_Y1].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }
    }
    else if (abs(current_X1 - request_x1) == abs(current_Y1 - request_y1))
    {
        // SOL YUKARI ÇAPRAZ - SAĞ YUKARI ÇAPRAZ
        if (current_X1 - request_x1 > 0)
        {
            // SOL YUKARI GİDİŞ
            if (current_Y1 - request_y1 > 0)
            {
                for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                {
                    if (cell[current_X1 - 1 * i][current_Y1 - 1 * i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            // SAĞ YUKARI GİDİŞ
            else if (current_Y1 - request_y1 < 0)
            {
                for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                {
                    if (cell[current_X1 - 1 * i][current_Y1 + 1 * i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }
        else if (current_X1 - request_x1 < 0)
        {
            // SOL AŞŞAĞI GİDİŞ
            if (current_Y1 - request_y1 > 0)
            {
                for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                {
                    if (cell[current_X1 + 1 * i][current_Y1 - 1 * i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            // SAĞ AŞŞAĞI GİDİŞ
            else if (current_Y1 - request_y1 < 0)
            {
                for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                {
                    if (cell[current_X1 + 1 * i][current_Y1 + 1 * i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        return false;
    }
    if (!check)
    {
        if (space->getType() != "EMPTY")
        {
            eaten(space);
        }
        space->fillBlank(queen);
        queen->setToEmpty();
        return true;
    }

    else
        return false;
}
// OK
bool Board::playBishop(Cell *bishop, Cell *space)
{

    int current_X1 = bishop->getXCoordinate();
    int current_Y1 = bishop->getYCoordinate();

    int request_x1 = space->getXCoordinate();
    int request_y1 = space->getYCoordinate();
    bool check = false;
    if (abs(current_X1 - request_x1) == abs(current_Y1 - request_y1))
    {
        // SOL YUKARI ÇAPRAZ - SAĞ YUKARI ÇAPRAZ
        if (current_X1 - request_x1 > 0)
        {
            // SOL YUKARI GİDİŞ
            if (current_Y1 - request_y1 > 0)
            {
                for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                {
                    if (cell[current_X1 - 1 * i][current_Y1 - 1 * i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            // SAĞ YUKARI GİDİŞ
            else if (current_Y1 - request_y1 < 0)
            {
                for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                {
                    if (cell[current_X1 - 1 * i][current_Y1 + 1 * i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }
        else if (current_X1 - request_x1 < 0)
        {
            // SOL AŞŞAĞI GİDİŞ
            if (current_Y1 - request_y1 > 0)
            {
                for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                {
                    if (cell[current_X1 + 1 * i][current_Y1 - 1 * i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            // SAĞ AŞŞAĞI GİDİŞ
            else if (current_Y1 - request_y1 < 0)
            {
                for (size_t i = 1; i < abs(current_X1 - request_x1); i++)
                {
                    if (cell[current_X1 + 1 * i][current_Y1 + 1 * i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        return false;
    }

    if (!check)
    {
        if (space->getType() != "EMPTY")
        {
            eaten(space);
        }
        space->fillBlank(bishop);
        bishop->setToEmpty();
        return true;
    }
    else
        return false;
}
// OK
bool Board::playKnight(Cell *knight, Cell *space)
{

    int current_X1 = knight->getXCoordinate();
    int current_Y1 = knight->getYCoordinate();

    int request_x1 = space->getXCoordinate();
    int request_y1 = space->getYCoordinate();

    if ((abs(current_X1 - request_x1) == 2 && abs(current_Y1 - request_y1) == 1) || (abs(current_X1 - request_x1) == 1 && abs(current_Y1 - request_y1) == 2))
    {
        if (space->getType() != "EMPTY")
        {
            eaten(space);
        }

        space->fillBlank(knight);
        knight->setToEmpty();
        return true;
    }
    else
    {
        return false;
    }
}
// OK
bool Board::playRook(Cell *rook, Cell *space)
{

    int current_X1 = rook->getXCoordinate();
    int current_Y1 = rook->getYCoordinate();

    int request_x1 = space->getXCoordinate();
    int request_y1 = space->getYCoordinate();

    bool check = false;
    if (current_X1 == request_x1 || current_Y1 == request_y1)
    {
        if (current_X1 == request_x1)
        {
            // SAĞA GİDİŞ
            if (current_Y1 - request_y1 < 0)
            {
                for (size_t i = current_Y1 + 1; i != request_y1; i++)
                {
                    if (cell[current_X1][i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            // SOLA GİDİŞ
            else if (current_Y1 - request_y1 > 0)
            {
                for (size_t i = current_Y1 - 1; i != request_y1; i--)
                {
                    if (cell[current_X1][i].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }

        else if (current_Y1 == request_y1)
        {
            //  AŞŞAĞI GİDİŞ
            if (current_X1 - request_x1 < 0)
            {
                for (size_t i = current_X1 + 1; i != request_x1; i++)
                {

                    if (cell[i][current_Y1].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
            // YUKARI GİDİŞ
            else if (current_X1 - request_x1 > 0)
            {
                for (size_t i = current_X1 - 1; i != request_x1; i--)
                {
                    if (cell[i][current_Y1].getColor() != Color.at(2))
                    {
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        return false;
    }

    if (!check)
    {
        if (rook->getXCoordinate() == 0 && rook->getYCoordinate() == 0)
        {
            rookMove1 = true;
        }
        if (rook->getXCoordinate() == 0 && rook->getYCoordinate() == 7)
        {
            rookMove2 = true;
        }
        if (rook->getXCoordinate() == 7 && rook->getYCoordinate() == 0)
        {
            rookMove3 = true;
        }
        if (rook->getXCoordinate() == 0 && rook->getYCoordinate() == 7)
        {
            rookMove4 = true;
        }
        if (space->getType() != "EMPTY")
        {
            eaten(space);
        }
        space->fillBlank(rook);
        rook->setToEmpty();

        return true;
    }
    else
    {

        return false;
    }
}
// OK
bool Board::playPawn(Cell *pawn, Cell *space)
{

    int current_X1 = pawn->getXCoordinate();
    int current_Y1 = pawn->getYCoordinate();

    int request_x1 = space->getXCoordinate();
    int request_y1 = space->getYCoordinate();

    bool check = false;

    if (pawn->getColor() == Color.at(0))
    {
        if (((current_Y1 == request_y1) && (current_X1 == request_x1 + 1) && (space->getColor() == Color.at(2))) || (current_X1 == 6 && request_x1 == 4 && current_Y1 == request_y1 && space->getColor() == Color.at(2)))
        {
            if (current_X1 == request_x1 + 1 && current_X1 == 1 && space->getColor() == Color.at(2))
            {
                char myType;
                std::cout << "Which Piece do you chose [R-N-B-Q]: ";
                std::cin >> myType;
                std::string setType;
                switch (myType)
                {
                case 'R':
                    setType = Piece.at(4);
                    break;
                case 'N':
                    setType = Piece.at(3);
                    break;
                case 'B':
                    setType = Piece.at(2);
                    break;
                case 'Q':
                    setType = Piece.at(1);
                    break;
                default:

                    break;
                }
                pawn->setType(setType);
                space->fillBlank(pawn);
                pawn->setToEmpty();
                return true;
            }

            else if (Board::getCell(current_X1 - 1, current_Y1)->getType() == "EMPTY")
            {
                space->fillBlank(pawn);
                pawn->setToEmpty();
                return true;
            }
            else
                return false;
        }
        else if ((current_X1 == request_x1 + 1) && (current_Y1 == request_y1 - 1 || current_Y1 == request_y1 + 1) && space->getColor() == Color.at(1))
        {
            if ((current_X1 == request_x1 + 1) && current_X1 == 1 && space->getColor() == Color.at(1))
            {
                char myType;
                std::cout << "Which Piece do you chose [R-N-B-Q]: ";
                std::cin >> myType;
                std::string setType;
                switch (myType)
                {
                case 'R':
                    setType = Piece.at(4);
                    break;
                case 'N':
                    setType = Piece.at(3);
                    break;
                case 'B':
                    setType = Piece.at(2);
                    break;
                case 'Q':
                    setType = Piece.at(1);
                    break;
                default:
                    setType = Piece.at(1);
                    break;
                }
                eaten(space);
                pawn->setType(setType);
                space->fillBlank(pawn);
                pawn->setToEmpty();
                return true;
            }
            eaten(space);
            space->fillBlank(pawn);
            pawn->setToEmpty();
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (pawn->getColor() == Color.at(1))
    {
        if (((current_Y1 == request_y1) && (current_X1 == request_x1 - 1) && (space->getColor() == Color.at(2))) || current_X1 == 1 && request_x1 == 3 && space->getColor() == Color.at(2))
        {
            if (current_X1 == request_x1 - 1 && current_X1 == 6 && space->getColor() == Color.at(2))
            {
                char myType;
                std::cout << "Which Piece do you chose [R-N-B-Q]: ";
                std::cin >> myType;
                std::string setType;
                switch (myType)
                {
                case 'R':
                    setType = Piece.at(4);
                    break;
                case 'N':
                    setType = Piece.at(3);
                    break;
                case 'B':
                    setType = Piece.at(2);
                    break;
                case 'Q':
                    setType = Piece.at(1);
                    break;
                default:

                    break;
                }
                pawn->setType(setType);
                space->fillBlank(pawn);
                pawn->setToEmpty();
                return true;
            }

            else if (Board::getCell(current_X1 + 1, current_Y1)->getType() == "EMPTY")
            {
                space->fillBlank(pawn);
                pawn->setToEmpty();
                return true;
            }
            else
                return false;
        }
        else if ((current_X1 == request_x1 - 1) && (current_Y1 == request_y1 - 1 || current_Y1 == request_y1 + 1) && space->getColor() == Color.at(0))
        {
            if (current_X1 == request_x1 - 1 && current_X1 == 6 && space->getColor() == Color.at(0))
            {

                char myType;
                std::cout << "Which Piece do you chose [R-N-B-Q]: ";
                std::cin >> myType;
                std::string setType;
                switch (myType)
                {
                case 'R':
                    setType = Piece.at(4);
                    break;
                case 'N':
                    setType = Piece.at(3);
                    break;
                case 'B':
                    setType = Piece.at(2);
                    break;
                case 'Q':
                    setType = Piece.at(1);
                    break;
                default:

                    break;
                }
                eaten(space);
                pawn->setType(setType);
                space->fillBlank(pawn);
                pawn->setToEmpty();
                return true;
            }
            eaten(space);
            space->fillBlank(pawn);
            pawn->setToEmpty();
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
// OK

bool Board::startGame()
{

    system("clear");
    printBoard();
    return canMove();
}
// OK

// isEmpty ->The function that checks whether the destination area is empty or not
bool Board::isEmpty(int x, int y)
{
    return cell[x][y].getType() == "EMPTY";
}
// isSameColor-> The function that checks if the piece at the destination area is of the same color as the moving piece
bool Board::isSameColor(int x, int y, Cell *selectedCell)
{
    return selectedCell->getColor() == cell[x][y].getColor();
}
// The functions that check whether the pieces are under threat by opposing pieces
bool Board::isThreatenedByRook(Cell *type)
{
    int currentX = type->getXCoordinate();
    int currentY = type->getYCoordinate();
    int nextPos_x;
    int nextPos_y;

    Cell *request;

    nextPos_x = currentX;
    nextPos_y = currentY;
    while (true)
    {
        nextPos_x++;
        if (isOutOfBounds(nextPos_x, nextPos_y))
            break;
        if (isEmpty(nextPos_x, nextPos_y))
        {
            ;
        }
        else
        {
            request = Board::getCell(nextPos_x, nextPos_y);
            if ((request->getType() == Piece.at(4) || request->getType() == Piece.at(1)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() != player_order)

                return true;

            break;
        }
    }

    nextPos_x = currentX;
    nextPos_y = currentY;
    while (true)
    {

        nextPos_x--;
        if (isOutOfBounds(nextPos_x, nextPos_y))
            break;
        if (isEmpty(nextPos_x, nextPos_y))
        {
            ;
        }

        else
        {
            request = Board::getCell(nextPos_x, nextPos_y);
            if ((request->getType() == Piece.at(4) || request->getType() == Piece.at(1)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() != player_order)

                return true;

            break;
        }
    }
    nextPos_x = currentX;
    nextPos_y = currentY;
    while (true)
    {

        nextPos_y++;
        if (isOutOfBounds(nextPos_x, nextPos_y))
            break;
        if (isEmpty(nextPos_x, nextPos_y))
        {
            ;
        }
        else
        {
            request = Board::getCell(nextPos_x, nextPos_y);
            if ((request->getType() == Piece.at(4) || request->getType() == Piece.at(1)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() != player_order)

                return true;

            break;
        }
    }
    nextPos_x = currentX;
    nextPos_y = currentY;
    while (true)
    {

        nextPos_y--;
        if (isOutOfBounds(nextPos_x, nextPos_y))
            break;
        if (isEmpty(nextPos_x, nextPos_y))
        {
            ;
        }
        else
        {
            request = Board::getCell(nextPos_x, nextPos_y);
            if ((request->getType() == Piece.at(4) || request->getType() == Piece.at(1)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() != player_order)

                return true;

            break;
        }
    }

    return false;
}
// OK
bool Board::isThreatenedByBishop(Cell *type)
{
    int currentX = type->getXCoordinate();
    int currentY = type->getYCoordinate();
    int nextPos_x;
    int nextPos_y;

    Cell *request;

    nextPos_x = currentX;
    nextPos_y = currentY;
    while (true)
    {
        nextPos_x--;
        nextPos_y--;

        if (isOutOfBounds(nextPos_x, nextPos_y))
            break;
        if (isEmpty(nextPos_x, nextPos_y))
        {
            ;
        }
        else
        {
            request = Board::getCell(nextPos_x, nextPos_y);
            if ((request->getType() == Piece.at(1) || request->getType() == Piece.at(2)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() != player_order)

                return true;

            break;
        }
    }
    nextPos_x = currentX;
    nextPos_y = currentY;
    while (true)
    {
        nextPos_x--;
        nextPos_y++;
        if (isOutOfBounds(nextPos_x, nextPos_y))
            break;
        if (isEmpty(nextPos_x, nextPos_y))
        {
            ;
        }
        else
        {
            request = Board::getCell(nextPos_x, nextPos_y);
            if ((request->getType() == Piece.at(1) || request->getType() == Piece.at(2)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() != player_order)

                return true;

            break;
        }
    }
    nextPos_x = currentX;
    nextPos_y = currentY;
    while (true)
    {
        nextPos_x++;
        nextPos_y--;
        if (isOutOfBounds(nextPos_x, nextPos_y))
            break;
        if (isEmpty(nextPos_x, nextPos_y))
        {
            ;
        }
        else
        {
            request = Board::getCell(nextPos_x, nextPos_y);
            if ((request->getType() == Piece.at(1) || request->getType() == Piece.at(2)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() != player_order)

                return true;

            break;
        }
    }
    nextPos_x = currentX;
    nextPos_y = currentY;
    while (true)
    {
        nextPos_y++;
        nextPos_x++;
        if (isOutOfBounds(nextPos_x, nextPos_y))
            break;
        if (isEmpty(nextPos_x, nextPos_y))
        {
            ;
        }
        else
        {
            request = Board::getCell(nextPos_x, nextPos_y);
            if ((request->getType() == Piece.at(1) || request->getType() == Piece.at(2)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() != player_order)

                return true;

            break;
        }
    }
    return false;
}
// OK
bool Board::isThreatenedByKnight(Cell *type)
{
    int currentX = type->getXCoordinate();
    int currentY = type->getYCoordinate();
    int nextPos_x;
    int nextPos_y;

    nextPos_x = currentX;
    nextPos_y = currentY;

    nextPos_x = currentX + 2;
    nextPos_y = currentY - 1;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
    {
        if (Board::getCell(nextPos_x, nextPos_y)->getType() == Piece.at(3) && Board::getCell(nextPos_x, nextPos_y)->getColor() != Board::getCell(currentX, currentY)->getColor() && Board::getCell(nextPos_x, nextPos_y)->getColor() != player_order)
        {

            return true;
        }
    }

    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX + 2;
    nextPos_y = currentY + 1;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
    {

        if (Board::getCell(nextPos_x, nextPos_y)->getType() == Piece.at(3) && Board::getCell(nextPos_x, nextPos_y)->getColor() != Board::getCell(currentX, currentY)->getColor() && Board::getCell(nextPos_x, nextPos_y)->getColor() != player_order)
        {

            return true;
        }
    }

    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX - 2;
    nextPos_y = currentY + 1;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
    {
        if (Board::getCell(nextPos_x, nextPos_y)->getType() == Piece.at(3) && Board::getCell(nextPos_x, nextPos_y)->getColor() != Board::getCell(currentX, currentY)->getColor() && Board::getCell(nextPos_x, nextPos_y)->getColor() != player_order)
        {

            return true;
        }
    }

    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX - 2;
    nextPos_y = currentY - 1;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
    {
        if (Board::getCell(nextPos_x, nextPos_y)->getType() == Piece.at(3) && Board::getCell(nextPos_x, nextPos_y)->getColor() != Board::getCell(currentX, currentY)->getColor() && Board::getCell(nextPos_x, nextPos_y)->getColor() != player_order)
        {

            return true;
        }
    }

    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX - 1;
    nextPos_y = currentY + 2;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
    {
        if (Board::getCell(nextPos_x, nextPos_y)->getType() == Piece.at(3) && Board::getCell(nextPos_x, nextPos_y)->getColor() != Board::getCell(currentX, currentY)->getColor() && Board::getCell(nextPos_x, nextPos_y)->getColor() != player_order)
        {

            return true;
        }
    }

    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX + 1;
    nextPos_y = currentY + 2;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
    {
        if (Board::getCell(nextPos_x, nextPos_y)->getType() == Piece.at(3) && Board::getCell(nextPos_x, nextPos_y)->getColor() != Board::getCell(currentX, currentY)->getColor() && Board::getCell(nextPos_x, nextPos_y)->getColor() != player_order)
        {
            return true;
        }
    }

    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX + 1;
    nextPos_y = currentY - 2;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
    {
        if (Board::getCell(nextPos_x, nextPos_y)->getType() == Piece.at(3) && Board::getCell(nextPos_x, nextPos_y)->getColor() != Board::getCell(currentX, currentY)->getColor() && Board::getCell(nextPos_x, nextPos_y)->getColor() != player_order)
        {
            return true;
        }
    }

    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX - 1;
    nextPos_y = currentY - 2;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
    {
        if (Board::getCell(nextPos_x, nextPos_y)->getType() == Piece.at(3) && Board::getCell(nextPos_x, nextPos_y)->getColor() != Board::getCell(currentX, currentY)->getColor() && Board::getCell(nextPos_x, nextPos_y)->getColor() != player_order)
        {
            return true;
        }
    }

    return false;
}
// OK
bool Board::isThreatendByPawn(Cell *type)
{
    int currentX = type->getXCoordinate();
    int currentY = type->getYCoordinate();
    int nextPos_x;
    int nextPos_y;

    Cell *request;

    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX - 1;
    nextPos_y = currentY - 1;

    request = Board::getCell(nextPos_x, nextPos_y);
    if (!isOutOfBounds(nextPos_x, nextPos_y))
        if ((request->getType() == Piece.at(5) || request->getType() == Piece.at(0)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() == Color.at(1))
            return true;
    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX - 1;
    nextPos_y = currentY + 1;
    request = Board::getCell(nextPos_x, nextPos_y);
    if (!isOutOfBounds(nextPos_x, nextPos_y))
        if ((request->getType() == Piece.at(5) || request->getType() == Piece.at(0)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() == Color.at(1))
            return true;
    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX + 1;
    nextPos_y = currentY - 1;
    request = Board::getCell(nextPos_x, nextPos_y);
    if (!isOutOfBounds(nextPos_x, nextPos_y))
        if ((request->getType() == Piece.at(5) || request->getType() == Piece.at(0)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() == Color.at(0))
            return true;
    nextPos_x = currentX;
    nextPos_y = currentY;
    nextPos_x = currentX + 1;
    nextPos_y = currentY + 1;
    if (!isOutOfBounds(nextPos_x, nextPos_y))
        if ((request->getType() == Piece.at(5) || request->getType() == Piece.at(0)) && request->getColor() != Board::getCell(currentX, currentY)->getColor() && request->getColor() == Color.at(0))
            return true;

    return false;
}
// canMakeCastling-> The function that checks whether the king can perform castling in the current state.
bool Board::canMakeCastling(Cell *king, Cell *space)
{

    int current_location_X1 = king->getXCoordinate();
    int current_location_Y1 = king->getYCoordinate();

    int request_location_x1 = space->getXCoordinate();
    int request_location_y1 = space->getYCoordinate();

    if (player_order == Color.at(0) && current_location_X1 == 7 && current_location_Y1 == 4 && kingMove1 == false)
    {
        if (cell[current_location_X1][current_location_Y1 - 1].getType() == Piece.at(6) && cell[current_location_X1][current_location_Y1 - 2].getType() == Piece.at(6) && cell[current_location_X1][current_location_Y1 - 3].getType() == Piece.at(6) && (current_location_Y1 - request_location_y1 > 0) && rookMove3 == false)
        {

            cell[7][0].setTypeAndColor(Piece.at(6), Color.at(2));
            cell[7][3].setTypeAndColor(Piece.at(4), Color.at(0));

            return true;
        }
        else if (cell[current_location_X1][current_location_Y1 + 1].getType() == Piece.at(6) && cell[current_location_X1][current_location_Y1 + 2].getType() == Piece.at(6) && (current_location_Y1 - request_location_y1 < 0) && rookMove4 == false)
        {
            cell[7][7].setTypeAndColor(Piece.at(6), Color.at(2));
            cell[7][5].setTypeAndColor(Piece.at(4), Color.at(0));
            return true;
        }
        else
        {
            return false;
        }
    }
    else if (player_order == Color.at(1) && current_location_X1 == 0 && current_location_Y1 == 4 && kingMove2 == false)
    {
        if (cell[current_location_X1][current_location_Y1 - 1].getType() == Piece.at(6) && cell[current_location_X1][current_location_Y1 - 2].getType() == Piece.at(6) && cell[current_location_X1][current_location_Y1 - 3].getType() == Piece.at(6) && (current_location_Y1 - request_location_y1 > 0) && rookMove1 == false)
        {
            playRook(Board::getCell(0, 0), Board::getCell(0, 3));
            return true;
        }
        else if (cell[current_location_X1][current_location_Y1 + 1].getType() == Piece.at(6) && cell[current_location_X1][current_location_Y1 + 2].getType() == Piece.at(6) && (current_location_Y1 - request_location_y1 < 0) && rookMove2 == false)
        {
            playRook(Board::getCell(0, 7), Board::getCell(0, 5));
            return true;
        }
        else
        {
            return false;
        }
    }
    else
        return false;
}

// evaluateBoard-> The function that calculates the current score of the board.
float Board::evaluateBoard(std::string color)
{

    float whiteScore = 0;
    float blackScore = 0;
    std::vector<Cell> Whites;
    std::vector<Cell> Blacks;
    Cell request;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            request = cell[i][j];
            if (request.getColor() == Color.at(0))
            {
                Whites.push_back(request);
            }
            else if (request.getColor() == Color.at(1))
            {
                Blacks.push_back(request);
            }
        }
    }

    if (color == Color.at(0))
    {

        for (size_t i = 0; i < Whites.size(); i++)
        {
            bool end = false;
            for (size_t j = 0; j < Blacks.size() && !end; j++)
            {

                std::vector<Cell> PossibleMove = GetAllPossibleMoves(&Blacks.at(j));

                for (size_t k = 0; k < PossibleMove.size() && !end; k++)
                {

                    if (Whites.at(i).getXCoordinate() == PossibleMove.at(k).getXCoordinate() && Whites.at(i).getYCoordinate() == PossibleMove.at(k).getYCoordinate())
                    {

                        int pieceValue = getPieceValue(&Whites.at(i));

                        switch (Whites.at(i).getType()[2])
                        {
                        case 'N':
                            whiteScore -= pieceValue / 2.0f;

                            break;
                        case 'E':
                            whiteScore -= pieceValue / 2.0f;

                            break;
                        case 'S':
                            whiteScore -= pieceValue / 2.0f;

                            break;
                        case 'I':
                            whiteScore -= pieceValue / 2.0f;

                            break;
                        case 'O':
                            whiteScore -= pieceValue / 2.0f;

                            break;
                        case 'W':
                            whiteScore -= pieceValue / 2.0f;

                            break;

                        default:

                            break;
                        }
                        end = true;
                    }
                }
            }
        }
    }
    else
    {
        for (size_t i = 0; i < Blacks.size(); i++)
        {
            bool end = false;
            for (size_t j = 0; j < Whites.size() && !end; j++)
            {

                std::vector<Cell> PossibleMove = GetAllPossibleMoves(&Whites.at(j));
                for (size_t k = 0; k < PossibleMove.size() && !end; k++)
                {
                    if (PossibleMove.at(k).getXCoordinate() == Blacks.at(i).getXCoordinate() && PossibleMove.at(k).getYCoordinate() == Blacks.at(i).getYCoordinate())
                    {

                        int pieceValue = getPieceValue(&Blacks.at(i));

                        switch (Blacks.at(i).getType()[2])
                        {
                        case 'N':
                            blackScore -= pieceValue / 2.0f;

                            break;
                        case 'E':
                            blackScore -= pieceValue / 2.0f;

                            break;
                        case 'S':
                            blackScore -= pieceValue / 2.0f;

                            break;
                        case 'I':
                            blackScore -= pieceValue / 2.0f;

                            break;
                        case 'O':
                            blackScore -= pieceValue / 2.0f;

                            break;
                        case 'W':
                            blackScore -= pieceValue / 2.0f;

                            break;

                        default:

                            break;
                        }
                        end = true;
                    }
                }
            }
        }
    }

    if (color == Color.at(0))
    {
        return whiteScore - blackScore;
    }
    else
        return blackScore - whiteScore;
}
// getPieceValue-> The function that returns the value of the desired piece.
int Board::getPieceValue(Cell *type)
{
    std::vector<int> Points{1 /*Pawn*/, 3 /*Knight*/, 3 /*Bishop*/, 5 /*Rook*/, 9 /*Queen*/, 900};
    switch (type->getType()[2])
    {
    case 'N': // KING
        return 900;
        break;
    case 'E':
        return 9;
        break;
    case 'S':
        return 3;
        break;
    case 'I':
        return 3;
        break;
    case 'O':
        return 5;
        break;
    case 'W':
        return 1;
        break;

    default:

        break;
    }
    return 0;
}
// convertCharToInt-> Converting letters from user input into coordinates according to the coordinate system
int Board::convertCharToInt(char ch)
{
    ch = std::tolower(ch);
    switch (ch)
    {
    case 'a':
        return 0;
        break;
    case 'b':
        return 1;
        break;
    case 'c':
        return 2;
        break;
    case 'd':
        return 3;
        break;
    case 'e':
        return 4;
        break;
    case 'f':
        return 5;
        break;
    case 'g':
        return 6;
        break;
    case 'h':
        return 7;
        break;
    default:
        return -1;
        break;
    }
}
// OK
char Board::convertIntToChar(int x1)
{

    switch (x1)
    {
    case 0:
        return 'a';
        break;
    case 1:
        return 'b';
        break;
    case 2:
        return 'c';
        break;
    case 3:
        return 'd';
        break;
    case 4:
        return 'e';
        break;
    case 5:
        return 'f';
        break;
    case 6:
        return 'g';
        break;
    case 7:
        return 'h';
        break;
    }
    return '0';
}

bool Board::checkKing()
{

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            if (Board::getCell(i, j)->getType() == "KING" && Board::getCell(i, j)->getColor() == player_order)
            {
                return true;
            }
        }
    }

    return false;
}

void Board::saveToFile()
{

    std::ofstream last_board("board.txt");
    std::ofstream last_player("player.txt");
    std::ofstream last_WhiteEaten("white_eaten.txt");
    std::ofstream last_BlackEaten("black_eaten.txt");
    if (last_board.is_open())
    {
        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                switch (getCell(i, j)->getType()[2])
                {
                case 'N': // KING
                    if (getCell(i, j)->getColor() == Color.at(0) ? last_board << " K " : last_board << " k ")
                        ;
                    break;
                case 'E':
                    if (getCell(i, j)->getColor() == Color.at(0) ? last_board << " Q " : last_board << " q ")
                        ;
                    break;
                case 'S':
                    if (getCell(i, j)->getColor() == Color.at(0) ? last_board << " B " : last_board << " b ")
                        ;
                    break;
                case 'I':
                    if (getCell(i, j)->getColor() == Color.at(0) ? last_board << " N " : last_board << " n ")
                        ;
                    break;
                case 'O':
                    if (getCell(i, j)->getColor() == Color.at(0) ? last_board << " R " : last_board << " r ")
                        ;
                    break;
                case 'W':
                    if (getCell(i, j)->getColor() == Color.at(0) ? last_board << " P " : last_board << " p ")
                        ;
                    break;
                case 'P':
                    last_board << " . ";
                    ;
                    break;
                default:

                    break;
                }
            }
            last_board << std::endl;
        }

        last_player << player_order << std::endl;
        if (last_WhiteEaten.is_open())
        {
            for (size_t i = 0; i < WhiteEaten.size(); i++)
            {
                last_WhiteEaten << WhiteEaten.at(i);
            }
        }
        if (last_BlackEaten.is_open())
        {
            for (size_t i = 0; i < BlackEaten.size(); i++)
            {
                last_BlackEaten << BlackEaten.at(i);
            }
        }
        last_BlackEaten.close();
        last_WhiteEaten.close();
        last_board.close();
        last_player.close();
    }
}

bool Board::loadTheFile()
{
    std::ifstream dosya("board.txt");
    std::ifstream player_turn("player.txt");
    std::ifstream white_eaten("white_eaten.txt");
    std::ifstream black_eaten("black_eaten.txt");
    char satir;
    if (dosya.is_open() && player_turn.is_open())
    {
        std::string playerOrder;
        player_turn >> playerOrder;
        player_order = playerOrder;

        for (size_t i = 0; i < 8; i++)
        {
            for (size_t j = 0; j < 8; j++)
            {
                dosya >> satir;
                switch (satir)
                {

                case 'r':
                    cell[i][j].setTypeAndColor(Piece.at(4), Color.at(1));
                    break;
                case 'n':
                    cell[i][j].setTypeAndColor(Piece.at(3), Color.at(1));

                    break;
                case 'b':
                    cell[i][j].setTypeAndColor(Piece.at(2), Color.at(1));

                    break;
                case 'q':
                    cell[i][j].setTypeAndColor(Piece.at(1), Color.at(1));

                    break;
                case 'k':
                    cell[i][j].setTypeAndColor(Piece.at(0), Color.at(1));

                    break;
                case 'p':
                    cell[i][j].setTypeAndColor(Piece.at(5), Color.at(1));

                    break;
                case '.':
                    cell[i][j].setTypeAndColor(Piece.at(6), Color.at(2));

                    break;
                case 'R':
                    cell[i][j].setTypeAndColor(Piece.at(4), Color.at(0));

                    break;
                case 'N':
                    cell[i][j].setTypeAndColor(Piece.at(3), Color.at(0));

                    break;
                case 'B':
                    cell[i][j].setTypeAndColor(Piece.at(2), Color.at(0));

                    break;
                case 'Q':
                    cell[i][j].setTypeAndColor(Piece.at(1), Color.at(0));

                    break;
                case 'K':
                    cell[i][j].setTypeAndColor(Piece.at(0), Color.at(0));

                    break;
                case 'P':
                    cell[i][j].setTypeAndColor(Piece.at(5), Color.at(0));

                    break;
                }
            }
        }
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                cell[i][j].setXCoordinate(i);
                cell[i][j].setYCoordinate(j);
            }
        }

        dosya.close();
        char c;
        while (white_eaten.get(c))
        {

            WhiteEaten.push_back(c);
        }
        char k;
        while (black_eaten.get(k))
        {

            BlackEaten.push_back(k);
        }
        white_eaten.close();
        black_eaten.close();
        return true;
    }

    return false;
}

void Board::eaten(Cell *piece)
{

    if (piece->getColor() == "BLACK")
    {
        if (piece->getType() == "KNIGHT")
        {
            WhiteEaten.push_back(tolower(piece->getType()[1]));
        }
        else
        {
            WhiteEaten.push_back(tolower(piece->getType()[0]));
        }
    }
    else if (piece->getColor() == "WHITE")
    {
        if (piece->getType() == "KNIGHT")
        {
            BlackEaten.push_back(piece->getType()[1]);
        }
        else
        {
            BlackEaten.push_back(piece->getType()[0]);
        }
    }
    else
    {
    }
}

void Board::printAllEaten()
{

    std::cout << " WHITE    BLACK" << std::endl;
    std::cout << "|--------------|" << std::endl;

    int p = characterCount(WhiteEaten, 'p');
    int n = characterCount(WhiteEaten, 'n');
    int b = characterCount(WhiteEaten, 'b');
    int q = characterCount(WhiteEaten, 'q');
    int k = characterCount(WhiteEaten, 'k');
    int r = characterCount(WhiteEaten, 'r');
    int p1 = characterCount(BlackEaten, 'P');
    int n1 = characterCount(BlackEaten, 'N');
    int b1 = characterCount(BlackEaten, 'B');
    int q1 = characterCount(BlackEaten, 'Q');
    int k1 = characterCount(BlackEaten, 'K');
    int r1 = characterCount(BlackEaten, 'R');
    if (p != 0)
    {
        std::cout << "|p x " << p << " ";
        if (p1 != 0)
        {
            std::cout << "| P x " << p1 << " |" << std::endl;
        }
        else
            std::cout << std::endl;
    }

    if (n != 0)
    {
        std::cout << "|n x " << n << " ";
        if (n1 != 0)
        {
            std::cout << "| N x " << n1 << " |" << std::endl;
        }
        else
            std::cout << std::endl;
    }

    if (b != 0)
    {
        std::cout << "|b x " << b << " ";
        if (b1 != 0)
        {
            std::cout << "| B x " << b1 << " |" << std::endl;
        }
        else
            std::cout << std::endl;
    }

    if (q != 0)
    {
        std::cout << "|q x " << q << " ";
        if (q1 != 0)
        {
            std::cout << "| Q x " << q1 << " |" << std::endl;
        }
        else
            std::cout << std::endl;
    }

    if (k != 0)
    {
        std::cout << "|k x " << k << " ";
        if (k1 != 0)
        {
            std::cout << "| K x " << k1 << " |" << std::endl;
        }
        else
            std::cout << std::endl;
    }

    if (r != 0)
    {
        std::cout << "|r x " << r << " ";
        if (r1 != 0)
        {
            std::cout << "| R x " << r1 << " |" << std::endl;
        }
        else
            std::cout << std::endl;
    }

    std::cout << "|--------------|" << std::endl;
}

int Board::characterCount(const std::vector<char> &vec, char karakter)
{
    int sayac = 0;
    for (char c : vec)
    {
        if (c == karakter)
        {
            sayac++;
        }
    }
    return sayac;
}