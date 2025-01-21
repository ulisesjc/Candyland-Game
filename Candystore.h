#ifndef CANDYSTORE_H
#define CANDYSTORE_H
#include <vector>
#include <iostream>
#include "Board.h"
using namespace std;


// struct Candy
// {
//     string name;
//     string description;
//     string effect_type;
//     int effect_value;
//     string candy_type;
//     double price;
// };

class Candystore
{

    private:
    string _store_name;
    const static int _MAX_CANDIES = 3;
    Candy _candies[_MAX_CANDIES];
    int _candy_count;
    vector<Candy> _loadedCandies;



    public:
    Candystore();
    Candystore(string store_name);
    bool addCandy(Candy candy);
    bool removeCandy(string candy_name);
    void displayCandies()const;
    void displayInventory(vector <Candy> _candies);
    vector<Candy> loadCandies();
    


};
#endif
