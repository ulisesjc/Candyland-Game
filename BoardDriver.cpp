#include "Board.h"
#include "Candystore.h"
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main()
{
    string temp;
    Board board;
    Candystore store;
    // board.displayBoard();
    // board.movePlayers(0, 23);
    // board.displayBoard();

    // board.movePlayers(1, 30);
    // board.displayBoard();

   
    
    board.isPositionCandyStore(25);
    board.addCandyStore(25);

    if(board.isPositionCandyStore(25))
    {
        cout << "yes";
    }
    else
    {
        cout << "nah";
    }
   store.displayCandies();

    return 0;
}