#include <iostream>
#include <vector>
#include <string>

class Cell
{

private:
    int x, y; // Represent the coordinates of each part
    std::string _piece;
    std::string _color;

public:
    std::string getColor();
    std::string getType();
    Cell();

    Cell(std::string piece, std::string color);
    void setType(std::string type);
    void fillBlank(Cell *);
    void setToEmpty();
    void setTypeAndColor(std::string pice, std::string color);
    void setXCoordinate(int new_x) { x = new_x; };
    void setYCoordinate(int new_y) { y = new_y; };
    int getXCoordinate() const { return x; }
    int getYCoordinate() const { return y; }
};

class Board
{

private:
    // Each element in this array represents a square on a chessboard
    static Cell cell[8][8];
    static Cell tempBoard[8][8];

    std::string player_order = "WHITE";
    std::vector<Cell> GetAllPossibleMoves(Cell *selectedCell);

    bool playKing(Cell *king, Cell *space);
    bool playQueen(Cell *queen, Cell *space);
    bool playRook(Cell *rook, Cell *space);
    bool playKnight(Cell *knight, Cell *space);
    bool playBishop(Cell *bishop, Cell *space);
    bool playPawn(Cell *pawn, Cell *space);
    bool makeMove(int x1, int y1, int x2, int y2);
    bool isEmpty(int x, int y);
    bool isSameColor(int x, int y, Cell *selectedCell);
    bool isOutOfBounds(int x2, int y2);
    bool isThreatenedByRook(Cell *cell);
    bool isThreatenedByBishop(Cell *type);
    bool isThreatenedByKnight(Cell *type);
    bool isThreatendByPawn(Cell *type);
    bool canMakeCastling(Cell *king, Cell *space);
    void printBoard();
    bool checkKing();
    void copyBoard(Cell originalBoard[8][8], Cell copy[8][8]);
    void saveToFile();
    void restoreOriginalBoard(Cell original[8][8], Cell copy[8][8]);
    int getPieceValue(Cell *type);
    float evaluateBoard(std::string color);

public:
    // Allows access to every element of the called cell.
    static Cell *getCell(int x, int y)
    {
        return &cell[x][y];
    }

    Board(){};
    bool canMove();
    bool startGame();
    void setBoard();
    int convertCharToInt(char ch);
    bool loadTheFile();
    char convertIntToChar(int x1);
};