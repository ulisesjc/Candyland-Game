#include "Board.h"
#include <fstream>
#include <sstream>
#include <vector>

Board::Board()
{
    resetBoard();
}


void Board::resetBoard() {

    const int COLOR_COUNT = 3;
    const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
    Tile new_tile;
    string current_color;

    srand(time(0)); // Initialize random seed

    // Make an array of tile types
    vector<string> tileTypes(_BOARD_SIZE - 1, "regular tile");
    tileTypes[0] = "Shortcut Tile";
    tileTypes[1] = "Ice Cream Stop Tile";
    tileTypes[2] = "Gumdrop Forest Tile";
    tileTypes[3] = "Gingerbread House Tile";
    tileTypes[4] = "Hidden Treasure";


    // Shuffle the array of tile types manually
    for (int i = _BOARD_SIZE - 2; i > 0; --i) 
    {
        int j = rand() % (i + 1);

        // Manual swapping
        string temp = tileTypes[i];
        tileTypes[i] = tileTypes[j];
        tileTypes[j] = temp;

    }

    for (int i = 0; i < 3; i++) 
    {
    int treasurePosition;
    bool isUnique;
    do
    {
        isUnique = true;
        treasurePosition = rand() % _BOARD_SIZE;

        // Check if this position is already used for a hidden treasure
        for (int j = 0; j < i; j++) 
        {
            if (_hidden_treasures[j] == treasurePosition) 
            {
                isUnique = false;
                break;
            }
        }
    } 
    while (!isUnique);

    _hidden_treasures[i] = treasurePosition;
    // Replace the placeholder with actual hidden treasure
    tileTypes[treasurePosition] = "Hidden Treasure Tile";
    }

    for (int i = 0; i < _BOARD_SIZE - 1; i++) 
    {

        current_color = COLORS[i % COLOR_COUNT];

        new_tile = {current_color, tileTypes[i]};

        _tiles[i] = new_tile;

    }

    new_tile = {ORANGE, "regular tile"};

    _tiles[_BOARD_SIZE - 1] = new_tile;

    _candy_store_count = 0;

    for (int i = 0; i < _MAX_CANDY_STORE; i++) 
    {

        _candy_store_position[i] = -1;

    }

    _player_positions[0] = 0;
    _player_positions[1] = 0;

}


void Board::displayTile(int position) 
{
    if (position < 0 || position >= _BOARD_SIZE) 
    {
        return;
    }

    Tile target = _tiles[position];
    //cout << target.color << " ";
    
    // For regular tile, just display the color
    if (target.type == "regular tile") 
    {

        cout << target.color << " ";

    } 
    else 
    {

        // Display the color and an emoji for special tile types
        string tileEmoji;
        if (target.type == "Shortcut Tile") 
        {

            tileEmoji = "⚡"; // Lightning bolt for shortcut tile

        } 
        else if (target.type == "Ice Cream Stop Tile") 
        {

            tileEmoji = "🍦"; // Ice cream for ice cream stop tile

        } 
        else if (target.type == "Gumdrop Forest Tile") 
        {

            tileEmoji = "🌳"; // Tree for gumdrop forest tile

        } 
        else if (target.type == "Gingerbread House Tile") 
        {

            tileEmoji = "🏠"; // House for gingerbread house tile

        }

        cout << target.color << tileEmoji << " ";
    }

    // Displaying player positions
    if (position == _player_positions[0]) 
    {

        cout << "1";

    } 
    if (position == _player_positions[1]) 
    {

        cout << "2";

    } 
    else {

        cout << " ";

    }

    cout << " " << RESET;
}







void Board::displayBoard()
{
    // First horizontal segment
    for (int i = 0; i <= 23; i++)
    {
        displayTile(i);
    }
    cout << endl;
    // First vertical segment
    for (int i = 24; i <= 28; i++)
    {
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        displayTile(i);
        cout << endl;
    }
    // Second horizontal segment
    for (int i = 52; i > 28; i--)
    {
        displayTile(i);
    }
    cout << endl;
    // Second vertical segment
    for (int i = 53; i <= 57; i++)
    {
        displayTile(i);
        for (int j = 0; j < 23; j++)
        {
            cout << "   ";
        }
        cout << endl;
    }
    // Third horizontal segment
    for (int i = 58; i < _BOARD_SIZE; i++)
    {
        displayTile(i);
    }
    cout << ORANGE << "Castle" << RESET << endl;
}


//array
bool Board::setPlayerPositions(int playerIndex, int newPosition)
{
    if (playerIndex >= 0 && playerIndex < 2 && newPosition >= 0 && newPosition < _BOARD_SIZE)
    {
        _player_positions[playerIndex] = newPosition;
        return true;
    }
    return false;
}


//array
int Board::getPlayerPositions(int playerIndex) const
{
    if(playerIndex >= 0 && playerIndex < 2)
    {
        return _player_positions[playerIndex];
    }
    return -1;
}



bool Board::movePlayers(int playerIndex, int tile_to_move_forward) 
{
    

    int currentPlayerPosition = _player_positions[playerIndex];
    int newPlayerPosition = currentPlayerPosition + tile_to_move_forward;

    // Ensure the new position is within board bounds
    if (newPlayerPosition >= _BOARD_SIZE) 
    {
        newPlayerPosition = _BOARD_SIZE - 1;
    }

    // Update player position
    _player_positions[playerIndex] = newPlayerPosition;

    // Check the type of tile at the new position
    Tile currentTile = _tiles[newPlayerPosition];


    bool foundTreasure = false;
    for (int i = 0; i < 2; i++) 
    {
        if (_hidden_treasures[i] == newPlayerPosition) 
        {
            foundTreasure = true;
            break; // Break the loop if the treasure is found
        }
    }

    if(rand() % 100 < 40)
    {
        handleCalamity(playerIndex);
    }
    
    if (rand() % 100 < 5) 
    {   // 5% chance
        marshmallowHailstorm();
    }

    if (foundTreasure) 
    {
        cout << "You landed on a Hidden Treasure!" << endl;
        handleTreasureTile(playerIndex);
    }

    if (currentTile.type == "Shortcut Tile") 
    {

        // Move forward by 4 tiles or to the final tile
        newPlayerPosition = min(newPlayerPosition + 4, _BOARD_SIZE - 1);
        cout << "You landed on the Shortcut Tile! You will advance a whole 4 tiles!!" << endl;

    }
    else if (currentTile.type == "Ice Cream Stop Tile") 
    {

        drawCard(playerIndex);
        cout << "You landed on the Ice Cream Stop Tile" << endl;

    } 
    else if (currentTile.type == "Gumdrop Forest Tile") 
    {

        // Move back by 4 tiles or to the start of the game
        newPlayerPosition = max(newPlayerPosition - 4, 0);
        cout << "You landed on the Gumdrop Forest Tile. You will go beack 4 tiles!!" << endl;

    } 
    else if (currentTile.type == "Gingerbread House Tile") 
    {

        // Move back to the previous position and lose an immunity candy
        newPlayerPosition = currentPlayerPosition; // Revert to previous position
        // Logic to lose an immunity candy

    }

    // Update the player's position after handling special tiles
    _player_positions[playerIndex] = newPlayerPosition;

    return true; // Assuming the move is always successful

}


int Board::getBoardSize() const
{
    return _BOARD_SIZE;
}

int Board::getCandyStoreCount() const
{
    return _candy_store_count;
}


bool Board::addCandyStore(int position)
{
    if (_candy_store_count >= _MAX_CANDY_STORE)
    {
        return false;
    }
    _candy_store_position[_candy_store_count] = position;
    _candy_store_count++;
    return true;
}

bool Board::isPositionCandyStore(int board_position)
{
    for (int i = 0; i < _candy_store_count; i++)
    {
        if(_candy_store_position[i] == board_position)
        {
            return true;
        }
    }
    return false;
}


void Board::drawCard(int playerIndex) 
{

    const int CARD_COLOR_COUNT = 3;
    const string CARD_COLORS[CARD_COLOR_COUNT] = {"MAGENTA", "GREEN", "BLUE"};
    const int DOUBLE_CARD_CHANCE = 10; // 10% chance for a double card

    // Randomly draw a color
    int colorIndex = rand() % CARD_COLOR_COUNT;
    string drawnColor = CARD_COLORS[colorIndex];

    // Determine if it's a double card
    bool isDoubleCard = (rand() % 100) < DOUBLE_CARD_CHANCE;
    string result = drawnColor;

    if (isDoubleCard)
    {

        result += " (Double)";

    }

    cout << "You drew a " << result << " card." << " Your game piece advances to the " << result << " tile. Here's the updated trail:" << endl;

    string cardColor = drawnColor;

    // Handle player movement based on drawn card
    int currentPosition = getPlayerPositions(playerIndex);
    int moveForward = calculateMove(drawnColor, currentPosition);
    movePlayers(playerIndex, moveForward);

    if (isDoubleCard) 
    {
        currentPosition = getPlayerPositions(playerIndex);
        moveForward = calculateMove(drawnColor, currentPosition);
        movePlayers(playerIndex, moveForward);
    }
}

int Board::calculateMove(string& color, int currentPosition) 
{

    Board board;
    int n = currentPosition % 3;
    int moveForward = 0;

    if (color == "GREEN") 
    {
        switch (n) 
        {
            case 0: 
            moveForward = 1; 
            break;

            case 1: 
            moveForward = 3; 
            break;

            case 2: 
            moveForward = 2; 
            break;
        }
    } 
    else if (color == "MAGENTA") 
    {
        switch (n) 
        {
            case 0: 
            moveForward = 3; 
            break;

            case 1: 
            moveForward = 2; 
            break;

            case 2: 
            moveForward = 1; 
            break;
        }
    } 
    else if (color == "BLUE") 
    {
        switch (n) 
        {
            case 0: 
            moveForward = 2;
            break;

            case 1: 
            moveForward = 1; 
            break;

            case 2: 
            moveForward = 3; 
            break;
        }
    }

    return moveForward;
}



void Board::handleTreasureTile(int playerIndex) 
{
    // Logic to present a riddle to the player

    // Assuming you have a method to check if the player solved the riddle
    bool riddleSolved = checkRiddleSolution();

    if (riddleSolved) 
    {
        // Determine the reward
        int rewardType = rand() % 100; // Random number between 0-99
        if (rewardType < 30) 
        {

            cout << "You won a Stamina Refill!" << endl;
            // Stamina Refill
            // Code to add 10 to 30 stamina, capped at 100

        } 
        else if (rewardType >= 30 && rewardType < 40) 
        {

            cout << "You won a Gold Winfall!" << endl;    
            // Gold Windfall
            // Code to add 20 to 40 gold, capped at 100

        } 
        else if (rewardType >= 40 && rewardType < 70) 
        {
            cout << "You won a Robber's Repel!" << endl;
            // Robber's Repel
            // Code to give Robber's Repel candy

        } 
        else 
        {
            // Candy Acquisition
            int candyType = rand() % 100; // Random number between 0-99
            if (candyType < 70) 
            {
                cout << "You won a Jellybean of Vigor!" << endl;
                // Jellybean of Vigor
                // Code to add Jellybean of Vigor

            } 
            else 
            {
                cout << "You won a Treasure Hunter's Truffle!" << endl;
                // Treasure Hunter's Truffle
                // Code to add Treasure Hunter's Truffle

            }
        }
    }
}

Riddle Board::getRandomRiddle() 
{

    vector<Riddle> riddles;
    ifstream file("riddles.txt");
    string line;

    while (getline(file, line)) 
    {
        stringstream ss(line);
        Riddle riddle;
        getline(ss, riddle.question, '|');
        getline(ss, riddle.answer);
        riddles.push_back(riddle);
    }

    file.close();

    // Randomly select a riddle
    int index = rand() % riddles.size();
    return riddles[index];

}

void Board::handleCalamity(int playerIndex) 
{

    int calamityType = rand() % 100; // Random number between 0-99

    if (calamityType < 30)
    {

        // Candy Bandits (30% chance)
        int lostCoins = rand() % 10 + 1; // Random amount of lost gold coins (1-10 coins)
        cout << "Oh no! Candy Bandits have swiped your " << lostCoins << " gold coins!" << endl;
        // Deduct the lost coins from the player's gold

    } 
    else if (calamityType < 65) 
    {

        // Lost in a Lollipop Labyrinth (35% chance)
        cout << "Oh dear! You got lost in the lollipop labyrinth!" << endl;
        // Implement logic for losing a turn

    } 
    else if (calamityType < 80) 
    {

        int lostStamina = rand() % 6 + 5; // Random amount of lost stamina (5-10 units)
        cout << "Watch out! A candy avalanche has struck! You lost " << lostStamina << " stamina!" << endl;
        // Deduct the lost stamina from the player's stamina
        // Implement logic for skipping the next turn

        // Play Rock, Paper, Scissors to determine if the player gets the lost resources back
        if (playRockPaperScissors()) 
        {

            cout << "You won in Rock, Paper, Scissors! You regained your lost resources!" << endl;
            // Implement logic to add back the lost resources

        } 
        else 
        {

            cout << "You lost in Rock, Paper, Scissors! You couldn't regain your lost resources." << endl;

        }


    } 
    else 
    {

        // Sticky Taffy Trap (20% chance)
        cout << "Oops! You are stuck in a sticky taffy trap!" << endl;
        // Implement logic for immobilizing the player for the next turn
        // Check if the player has a Magical Candy to regain the lost turn
        // If they do, deduct one Magical Candy from their inventory and regain the turn

    }
}

bool Board::playRockPaperScissors() 
{

    char p1choice;
    char p2choice;

    // Player 1 input
    cout << "Player 1: Enter r, p, or s" << endl;

    cin >> p1choice;

    while (p1choice != 'r' && p1choice != 'p' && p1choice != 's') 
    {

        cout << "Invalid selection!" << endl;

        cin >> p1choice;

    }

    // Player 2 (Computer) input
    srand(time(0));  // Seed for random number generation

    p2choice = "rps"[rand() % 3];  // Computer's choice: 'r', 'p', or 's'

    cout << "Computer's choice: " << p2choice << endl;

    // Repeat if it's a tie
    while (p1choice == p2choice) 
    {

        cout << "Tie! Play again" << endl;

        // Player 1 input
        cout << "Player 1: Enter r, p, or s" << endl;

        cin >> p1choice;

        while (p1choice != 'r' && p1choice != 'p' && p1choice != 's') 
        {

            cout << "Invalid selection!" << endl;

            cin >> p1choice;
        }

        // Player 2 (Computer) input
        p2choice = "rps"[rand() % 3];  // Computer's choice: 'r', 'p', or 's'
        cout << "Computer's choice: " << p2choice << endl;

    }

    // Determine the winner using || for simplicity
    if ((p1choice == 'r' && p2choice == 's') || (p1choice == 'p' && p2choice == 'r') ||(p1choice == 's' && p2choice == 'p')) 
    {
        cout << "Player wins!" << endl;
        return true;
    } 
    else 
    {

        cout << "Computer wins!" << endl;
        return false;

    }
}



bool Board::checkRiddleSolution() 
{
    Riddle riddle = getRandomRiddle(); // Get a random riddle

    // Present the riddle to the player
    cout << "Riddle: " << riddle.question << endl;
    cout << "Enter your answer: ";
    cin.ignore(1000000, '\n');

    string playerAnswer;
    getline(cin, playerAnswer);

    // Convert playerAnswer to lowercase
    for (int i = 0; i < playerAnswer.length(); i++) 
    {
        playerAnswer[i] = tolower(playerAnswer[i]);
    }

    // Convert riddle answer to lowercase
    for (int i = 0; i < riddle.answer.length(); ++i) 
    {
        riddle.answer[i] = tolower(riddle.answer[i]);
    }

    // Check if the player's answer matches the riddle's answer
    if (playerAnswer == riddle.answer) 
    {
        return true;
    }

    cout << "Incorrect Answer! No reward this time." << endl;
    return false;
}

bool Board::marshmallowHailstorm() 
{
    cout << "A Marshmallow Hailstorm has struck! All players are pushed back." << endl;
    for (int i = 0; i < _player_positions[i]; i++) 
    { 
        int stepsBack = rand() % 6 + 1; // Random steps back, 1 to 6
        _player_positions[i] -= stepsBack; // Move the player back

        // Ensure the player's position does not go below 0
        if (_player_positions[i] < 0) 
        {
            _player_positions[i] = 0;
        }

        cout << "Player " << i + 1 << " is pushed back " << stepsBack << " steps." << endl;
    }
    return true;
}

