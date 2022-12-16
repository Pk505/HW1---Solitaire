#include <iostream>
#include <vector>
#include "header.h"
#include <string>

//
int main() {
    int converge_count = 0;
    int divergence_count = 0;
    layout user_layout;
    user_layout.rows = new row[7];

    std::vector<std::vector<int>> deck;     //making full deck, elements of vectors are suits,
    // each suit includes 4 cards
    for (int i = 0; i < 13; i++) {
        std::vector<int> suit;
        for (int j = 0; j < 4; j++) {
            suit.push_back(i + 1);
        }
        deck.push_back(suit);
    }
    for (int i = 0; i < 7; i++) {
        user_layout.rows[i].cards = new card[i + 1];
        for (int j = 0; j <= i; j++) {
            std::string user_value;
            std::cout << "Enter the value for the " << i + 1 << " row, " << j + 1 << " card" << std::endl;
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
            } else {
                j--;
            }
        }
    }

    for (int k = 0; k < 100000; k++) {
        layout layout_cycle;
        layout_cycle.rows = new row[7];
        for (int i = 0; i < 7; i++) {
            layout_cycle.rows[i].cards = new card[i + 1];
            for (int j = 0; j <= i; j++) {
                layout_cycle.rows[i].cards[j].value = user_layout.rows[i].cards[j].value;
                if ((j != 0) && (i != 0)) {              //making connections with upper cards
                    layout_cycle.rows[i].cards[j].upper_left = &layout_cycle.rows[i - 1].cards[j - 1];
                    layout_cycle.rows[i - 1].cards[j - 1].lower_right = &layout_cycle.rows[i].cards[j];
                }
                if (j != i) {
                    layout_cycle.rows[i].cards[j].upper_right = &layout_cycle.rows[i - 1].cards[j];
                    layout_cycle.rows[i - 1].cards[j].lower_left = &layout_cycle.rows[i].cards[j];
                }
            }
        }

        std::vector<card> active_cards = {layout_cycle.rows[6].cards[0],
                                          layout_cycle.rows[6].cards[1],  //making active cards
                                          layout_cycle.rows[6].cards[2],
                                          layout_cycle.rows[6].cards[3],  //filling it with
                                          layout_cycle.rows[6].cards[4],
                                          layout_cycle.rows[6].cards[5],  //lowest row
                                          layout_cycle.rows[6].cards[6]};


        std::vector<int> remaining_deck = shuffle(deck);
        int top_card = remaining_deck[remaining_deck.size() - 1];
        remaining_deck.pop_back();
        std::vector<int> fall_cards;

        int retake_count = 0;
        while (true) {
            while (true) {
                if (!try_delete(active_cards)) {
                    break;
                }
            }
            if (!try_delete_with_top_card(active_cards, top_card, fall_cards,
                                          remaining_deck)) {
                fall_cards.push_back(top_card);
                if (!remaining_deck.empty()) {
                    top_card = remaining_deck[remaining_deck.size() - 1];
                    remaining_deck.pop_back();
                }
            }
            if ((remaining_deck.empty()) and (top_card == 0)) {
                if (retake_count != 3) {
                    retake_deck(remaining_deck, fall_cards);
                    top_card = remaining_deck[remaining_deck.size() - 1];
                    remaining_deck.pop_back();
                    retake_count++;
                } else {
                    divergence_count++;
                    break;
                }
            }
            if (active_cards.empty()) {
                converge_count++;
                break;
            }
        }


        for (int i = 0; i < 7; i++)
            delete[] layout_cycle.rows[i].cards;
        delete[] layout_cycle.rows;
    }
    for (int i = 0; i < 7; i++)
        delete[] user_layout.rows[i].cards;
    delete[] user_layout.rows;

    float convergence = float(converge_count) / (converge_count + divergence_count) * 100;
    std::cout << "Convergence: " << convergence << "%" << std::endl;
    system("pause");
    return 0;
}

