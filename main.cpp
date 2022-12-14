#include <iostream>
#include <vector>
#include "header.h"


int main() {
    layout user_layout;
    user_layout.rows = new row[7];

    //filling the layout with user's values
    for (int i = 0; i < 7; i++) {
        user_layout.rows[i].cards = new card[i + 1];
        for (int j = 0; j <= i; j++) {
            std::cout << "Enter the " << j + 1 << " value for the " << i + 1 << " row:" << std::endl;
            std::cin >> user_layout.rows[i].cards[j].value;
            if ((j != 0) && (i != 0)) {
                user_layout.rows[i].cards[j].upper_left = &user_layout.rows[i - 1].cards[j - 1];
                user_layout.rows[i - 1].cards[j - 1].lower_right = &user_layout.rows[i].cards[j];
            }
            if (j != i) {
                user_layout.rows[i].cards[j].upper_right = &user_layout.rows[i - 1].cards[j];
                user_layout.rows[i - 1].cards[j].lower_left = &user_layout.rows[i].cards[j];
            }
        }
    }

    std::vector<card> active_cards = {user_layout.rows[6].cards[0], user_layout.rows[6].cards[1],
                                      user_layout.rows[6].cards[2], user_layout.rows[6].cards[3],
                                      user_layout.rows[6].cards[4], user_layout.rows[6].cards[5],
                                      user_layout.rows[6].cards[6],};


    erase(active_cards[6], active_cards);
    erase(active_cards[5], active_cards);


    for (int i = 0; i < 7; i++)
        delete[] user_layout.rows[i].cards;
    delete[] user_layout.rows;

    return 0;
}

