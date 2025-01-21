#include "Candystore.h"
#include "Player.h" // added this in
#include <vector>
#include <fstream>
#include <sstream>


Candystore::Candystore()
{
    _store_name = "";
    _candy_count = 0;
}

Candystore::Candystore(string store_name)
{
    _store_name = store_name;
    _candy_count = 0;

}


vector<Candy> Candystore::loadCandies()
{
    vector<Candy> candies;
    ifstream file("candies.txt");

    if (!file.is_open())
    {
        cout << "Failed to open file" << endl;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }
        stringstream ss(line);
        Candy candy;
        getline(ss, candy.name, '|');
        getline(ss, candy.description, '|');
        getline(ss, candy.effect_type, '|');
        getline(ss, candy.effect_value, '|');
        getline(ss, candy.candy_type, '|');
        ss >> candy.price;
        candies.push_back(candy);
    }

    _loadedCandies = candies;  // store the loaded candies

    return candies;
}




bool Candystore::addCandy(Candy candy)
{
    if(_candy_count == _MAX_CANDIES)
    {
        cout << "Store has max candies. Unable to add more" << endl;
        return false;
    }
    _candies[_candy_count] = candy;
    _candy_count++;
    return true;
}

bool Candystore::removeCandy(string candy_name)
{
    bool removedCandy = false;
    for(int i = 0; i < _candy_count; i++)
    {
        if(_candies[i].name == candy_name)
        {
            for(int j = i +1; j < _candy_count -1; j++)
            {
                _candies[j-1] = _candies[j];
            }
            _candy_count--;
            removedCandy = true;
            break;
        }
    }
    return removedCandy;
}


void Candystore::displayCandies() const 
{
    if (_loadedCandies.empty()) 
    {
        cout << "No candies are present in the Costco" << endl;
    } 
    else 
    {
        cout << "Candies present in Costco" << endl;
        for (int i = 0; i < 3; i++) 
        {
            int random_index = rand() % _loadedCandies.size();
            Candy candy = _loadedCandies.at(random_index);
            cout << "Name: " << candy.name << endl;
            cout << "Description: " << candy.description << endl;
            cout << "Effect: " << candy.effect_type << endl;
            cout << "Effect value: " << candy.effect_value << endl;
            cout << "Candy type: " << candy.candy_type << endl;
            cout << "Price: " << candy.price << endl;
            cout << "-----------------------" << endl;
        }
    }
}







