#include <iostream>
#include <vector>
#include "header.h"
#include <string>
#include <ctime>

int main() {
    layout user_layout;
    user_layout.rows = new row[7];

    std::vector<std::vector<int>> deck; //deck of cards, filling it
    for (int i = 0; i < 13; i++) {
        std::vector<int> suit;
        for (int j = 0; j < 4; j++) {
            suit.push_back(i + 1);
        }
        deck.push_back(suit);
    }

    //filling the layout with user's values
    for (int i = 0; i < 7; i++) {
        user_layout.rows[i].cards = new card[i + 1];
        for (int j = 0; j <= i; j++) {
            std::string user_value;
            std::cout << "Enter the " << j + 1 << " value for the " << i + 1 << " row:" << std::endl;
            std::cin >> user_value;


            if (is_input_correct(deck, user_value, user_layout.rows[i].cards[j].value)) {
                if ((j != 0) && (i != 0)) {              //making connections with upper cards
                    user_layout.rows[i].cards[j].upper_left = &user_layout.rows[i - 1].cards[j - 1];
                    user_layout.rows[i - 1].cards[j - 1].lower_right = &user_layout.rows[i].cards[j];
                }
                if (j != i) {
                    user_layout.rows[i].cards[j].upper_right = &user_layout.rows[i - 1].cards[j];
                    user_layout.rows[i - 1].cards[j].lower_left = &user_layout.rows[i].cards[j];
                }
            } else j--;  //if input is incorrect prog request a new value for same pos
        }
    }

    std::vector<card> active_cards = {user_layout.rows[6].cards[0], user_layout.rows[6].cards[1],  //making active cards
                                      user_layout.rows[6].cards[2], user_layout.rows[6].cards[3],  //filling it with
                                      user_layout.rows[6].cards[4], user_layout.rows[6].cards[5],  //lowest row
                                      user_layout.rows[6].cards[6],};


    std::vector<int> remaining_deck = shuffle(deck);

    for (int i = 0; i < 7; i++)
        delete[] user_layout.rows[i].cards;
    delete[] user_layout.rows;

    return 0;
}

