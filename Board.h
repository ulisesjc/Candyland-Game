#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#define RED "\033[;41m"     /* Red */
#define GREEN "\033[;42m"   /* Green */
#define BLUE "\033[;44m"    /* Blue */
#define MAGENTA "\033[;45m" /* Magenta */
#define CYAN "\033[;46m"    /* Cyan */
#define ORANGE "\033[48;2;230;115;0m"  /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

struct Candy
{
    string name;
    string description;
    string effect_type;
    string effect_value;
    string candy_type;
    double price;
};

struct Riddle
{
    string question;
    string answer;
};

struct Tile
{
    string color;
    string type;
};

struct Card
{
    string color;
    int advance;
    bool is_double;
};



class Board
{
private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;

    int _player_positions[2];
    int _hidden_treasures[3];

public:
    Board();

    void resetBoard();
    void displayTile(int);
    void displayBoard();
    void drawCard(int playerIndex);
    int calculateMove(string& color, int currentPosition); 



    bool playRockPaperScissors();
    void handleCalamity(int playerIndex);
    void movePlayerToClosestColor(const string& color, bool isDouble);
    int findNextColorTile(int start, const string& color);
    void handleTreasureTile(int playerIndex);
    bool marshmallowHailstorm();
    bool checkRiddleSolution();
    Riddle getRandomRiddle();


    bool setPlayerPositions(int playerIndex, int newPosition);
    int getPlayerPositions(int playerIndex) const;

    int getBoardSize() const;
    int getCandyStoreCount() const;


    bool addCandyStore(int);
    bool isPositionCandyStore(int); 
    bool getColorTile();


    bool movePlayers(int playerIndex, int tile_to_move_forward);
};



#endif