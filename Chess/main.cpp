#include <iostream>
#include <string>
#include "chess.h"

using namespace std;

int main()
{

    string s;
    bool newgame = true;
    Board board;
    while (newgame)
    {

        system("clear");
        std::cout << "********* Welcome to Chess Game! *********" << std::endl;
        std::string select;

        while (true)
        {

            std::cout << std::endl;

            std::cout << "1. Start New Game" << std::endl;
            std::cout << "2. Load Game from the file." << std::endl;
            std::cout << std::endl;
            std::cout << "--> ";
            std::cin >> select;
            if (select[0] == '1')
            {
                board.setBoard();
                break;
            }
            else if (select[0] == '2')
            {
                if (!board.loadTheFile())
                {
                    std::cout << "There is no existing txt file." << std::endl;
                    continue;
                }
                else
                {

                    break;
                }
            }
            else
                std::cout << "Please enter valid input.[1-2]" << std::endl;
            continue;
        }
        while (board.startGame())
            ;
        cout << "Do you want to play again? (y for yes, anything else for no) ";
        cin >> s;
        if (s != "y")
            newgame = false;
    }

    return 0;
}