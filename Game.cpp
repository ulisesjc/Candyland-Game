#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Candystore.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>



Game::Game() 
{
    // Initialize game components
    // Initialize calamities
    _calamities.push_back("Candy Bandits");
    _calamities.push_back("Lost in a Lollipop Labyrinth");
    _calamities.push_back("Candy Avalanche");
    _calamities.push_back("Sticky Taffy Trap");

}


void Game::setupGame()
{

    

    Candystore candyStore; // Create an instance of the Candystore class
    vector<Candy> candies = candyStore.loadCandies();
    vector<Character> characters = loadCharacters("character.txt");

    


    int num_players;
    cout << "Welcome to Candyland!!!(Or at least a game that supposed to be kinda like that)" << endl;
    cout << "Enter The Number of Participants: " << endl;
    cin >> num_players;


    vector<Player> players(num_players);

    for(int i = 0; i < num_players; i++)
    {
        string player_name;
        cout << "Enter player name: " << endl;
        cin >> player_name; 
        players.at(i).setName(player_name);

        cout << "Great! Here's a list of Characters that you can choose from: " << endl;
        cout << "--------------------------" << endl;

        for (int i = 0; i < characters.size(); i++)
        {
            cout << "CHARACTER " << (i + 1) << endl;
            cout << "Name: " << characters.at(i).name << endl;
            cout << "Stamina: " << characters.at(i).stamina << endl;
            cout << "Gold: " << characters.at(i).gold << endl;
            cout << "Candies:" << endl;

            int numCandies = characters.at(i).candies.size();
            for (int j = 0; j < numCandies; j++)
            {
                cout << "[" << characters.at(i).candies.at(j).name << "]" << endl;
            }
            cout << "--------------------------" << endl;
        }


        int character_choice;
        cout << "Enter the number corresponding to the character you want to choose: " << endl;
        cin >> character_choice;
        //players.at(i).setName(characters.at(character_choice - 1));

        if(character_choice >= 1 && character_choice <= characters.size())
        {
            Character chosenCharacter = characters.at(character_choice - 1);
            cout << "The Selected Character is " << chosenCharacter.name << endl;
            
            players.at(i).setStamina(chosenCharacter.stamina);
            players.at(i).setGold(chosenCharacter.gold);
            //players.at(i).setCandies(chosenCharacter.candies);
        }
        else
        {
            cout << "Invalid character choice." << endl;
        }
            char storechoice;
            cout << "Would you like to visit the CandyStore? Enter (y/n)" << endl;
            cin >> storechoice;

            if(storechoice == 'y')
            {
                candyStore.displayCandies();
                //cout << "call candystore function" << endl;
            }
            else
            {
                continue;
            }
    }

    

    Board board;
    
    srand(time(0));
    int choice;
    bool gameRunning = true;


    cout << "Lets begin the game. Here is the board: " << endl;
    board.displayBoard();

    while (gameRunning)
    {
        
        for(int i = 0; i < num_players; i++)
        {
            bool turn = false;

            while(!turn)
            {
                //board.displayBoard();
                cout << "It's " << players.at(i).getName() << "'s turn" << endl;
                cout << "Please select a menu option:" << endl;
                cout << "1. Draw a card"<< endl;
                cout << "2. Use candy"<< endl;
                cout << "3. Show player stats"<< endl;
                cout << "4. Quit game" << endl; // Option to quit game

                char d;
                int numCandies = characters.at(i).candies.size();
                cin >> choice;

                

                switch(choice) 
                {


                    case 1:
                    cout << "Press d to draw a card" << endl;
                    cin >> d;
                    if(d == 'd')
                    {
                        board.drawCard(i);
                        board.displayBoard();
                        turn = true;
                    }
                    else
                    {
                        cout << "Invalid input" << endl;
                    }
                    // board.drawCard(i);
                    // board.displayBoard();
                    //turn = true;

                    if (board.getPlayerPositions(i) == 82) 
                    {
                        // Game ends when a player reaches the castle
                        cout << "CONGRATULATIONS, " << players.at(i).getName() << " HAS REACHED THE CASTLE AND WON THE GAME!!!!" << endl;
                        cout << "Here are your Final Stats: " << endl;
                        cout << "Player name: " << players.at(i).getName() << endl;
                        cout << "Character: " << characters.at(i).name << endl;
                        cout << "Stamina: " << characters.at(i).stamina << endl;
                        cout << "Gold: " << characters.at(i).gold << endl;
                        cout << "Candies: " << endl;
                        int numCandies = characters.at(i).candies.size();

                        for (int j = 0; j < numCandies; j++)
                        {
                            //cout << "[" << characters.at(i).candies.at(j).name << "]" << endl;
                            if(!characters.at(i).candies.at(j).name.empty())
                            {
                                cout << "[" <<  characters.at(i).candies.at(j).name << "]";
                            }
                            else
                            {
                                cout << "[Empty]";
                            }
                            cout << " " << endl;
                        }
                        

                        ofstream file_out("player_stats.txt"); // Open a file for writing
                        if (!file_out.is_open()) 
                            {
                                cout << "Failed to open file for writing stats." << endl;
                                return;
                            }

                        for (int i = 0; i < num_players; i++) 
                        {
                            file_out << "Player name: " << players.at(i).getName() << endl;
                            file_out << "Character: " << characters.at(i).name << endl;
                            file_out << "Stamina: " << characters.at(i).stamina << endl;
                            file_out << "Gold: " << characters.at(i).gold << endl;
                            file_out << "Candies: " << endl;
                            for (int j = 0; j < num_players; j++) 
                            {
                                file_out << characters.at(i).candies.at(j).name << endl;
                            }
                            file_out << "--------------------------" << endl;
                        }

                        file_out.close();

                        exit(0);
                    }
                    break;

                    case 2:
                    cout << "placeholder for use candy" << endl;
                    //useCandy();
                    turn = true;
                    break;

                    case 3:
                    cout << "Here are your stats: " << endl;
                    cout << "Player name: " << players.at(i).getName() << endl;
                    cout << "Character: " << characters.at(i).name << endl;
                    cout << "Stamina: " << characters.at(i).stamina << endl;
                    cout << "Gold: " << characters.at(i).gold << endl;
                    cout << "Candies: " << endl;

                    for (int j = 0; j < numCandies; j++)
                    {
                        //cout << " " << "[" <<  characters.at(i).candies.at(j).name << "]" << endl;
                        if(!characters.at(i).candies.at(j).name.empty())
                        {
                            cout << " " << "[" <<  characters.at(i).candies.at(j).name << "]";
                        }
                        else
                        {
                            cout << "[Empty]";
                        }
                        if (j % 4 == 1) // Start a new line after every two items
                        {
                            cout << "" << endl;
                        }
                    }
                    cout << " " << endl;
                    break;


                    case 4:
                    cout << "Exiting game..." << endl;;
                    gameRunning = false; // Set the flag to false to exit the loop
                    turn = true;
                    break;
                
                    default:
                    cout << "Invalid option. Please try again.\n";
                    break;
                }
            }
        }
    }
    //setup the board
    //place special tiles
    //place candy stores

}






//setup the board
//place special tiles
//place candy stores







vector<Character> Game::loadCharacters(string filename)
{
    vector<Character> characters;
    ifstream file_in("character.txt");
    string temp1, temp2;
    
    if(!file_in.is_open())
    {
        
        cout << "Failed to open file" << endl;
        return characters;
        
    }

    string temp;
    getline(file_in, temp);
    string line;

    while(getline(file_in, line))
    {
        if (line.empty()) 
        {
            continue;
        }
        else
        {
            Character character;
            
            stringstream ss(line);

            getline(ss, character.name, '|');
            getline(ss, temp1, '|');
            character.stamina = stoi(temp1);

            getline(ss, temp2, '|');
            character.gold = stoi(temp2);
            
            getline(ss, line, '\n');
            stringstream candiesStream(line);
            string candyName;
            while(getline(candiesStream, candyName, ','))
            {
                Candy candies;
                candies.name = candyName;
                character.candies.push_back(candies);
            }

            characters.push_back(character);

        }
    }
    file_in.close();
    return characters;

 }








// void Game::useCandy() 
// {
//     // Implement the logic for using candy here
//     // Prompt the user to select a candy from their inventory
//     // Modify the player attributes according to the selected candy's effect
//     // Print a message to the user
//     // Example:
//    // _player.useCandy(_candystore.selectCandy());  // Assuming Player and Candystore have appropriate methods
//     cout << "You used a candy with an effect." << endl;
// }


// void Game::handleCalamity()
// {
//     // Check if a calamity occurs (40% chance)
//     if (rand() % 100 < 40) 
//     {
//         // Choose a random calamity event
//         int eventIndex = rand() % _calamities.size();
//         string calamity = _calamities[eventIndex];

//         // Handle different calamity events here
//         if (calamity == "Candy Bandits") 
//         {
//             // Handle Candy Bandits event
//         } else if (calamity == "Lost in a Lollipop Labyrinth") 
//         {
//             // Handle Lost in a Lollipop Labyrinth event
//         } else if (calamity == "Candy Avalanche") 
//         {
//             // Handle Candy Avalanche event
//         } else if (calamity == "Sticky Taffy Trap") 
//         {
//             // Handle Sticky Taffy Trap event
//         }
//     }
// }

void Game::playRockPaperScissors() 
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

    // Determining the winner without using ||
    if (p1choice == 'r') 
    {

        if (p2choice == 's') 
        {

            cout << "Player wins!" << endl;

        } 
        else 
        {

            cout << "Computer wins!" << endl;
        }
    }
    if (p1choice == 'p') 
    {

        if (p2choice == 'r') 
        {

            cout << "Player wins!" << endl;

        } 
        else 
        {

            cout << "Computer wins!" << endl;

        }
    }
    if (p1choice == 's') 
    {

        if (p2choice == 'p') 
        {

            cout << "Player wins!" << endl;

        } 
        else 
        {

            cout << "Computer wins!" << endl;

        }
    }
}




