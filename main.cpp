#include <iostream>
#include <vector>
#include "header.h"
#include <string>

//
int main() {
    int converge_count = 0;
    int divergence_count = 0;
    for (int k = 0; k < 100000; k++) {
        layout layout;
        layout.rows = new row[7];

        std::vector<std::vector<int>> deck;     //making full deck, elements of vectors are suits,
                                                // each suit includes 4 cards
        for (int i = 0; i < 13; i++) {
            std::vector<int> suit;
            for (int j = 0; j < 4; j++) {
                suit.push_back(i + 1);
            }
            deck.push_back(suit);
        }
        std::vector<int> remaining_deck = shuffle(deck);
        for (int i = 0; i < 7; i++) {
            layout.rows[i].cards = new card[i + 1];
            for (int j = 0; j <= i; j++) {
                int position = rand() % remaining_deck.size();
                layout.rows[i].cards[j].value = remaining_deck[position];
                remaining_deck.erase(remaining_deck.begin() + position);
                if ((j != 0) && (i != 0)) {              //making connections with upper cards
                    layout.rows[i].cards[j].upper_left = &layout.rows[i - 1].cards[j - 1];
                    layout.rows[i - 1].cards[j - 1].lower_right = &layout.rows[i].cards[j];
                }
                if (j != i) {
                    layout.rows[i].cards[j].upper_right = &layout.rows[i - 1].cards[j];
                    layout.rows[i - 1].cards[j].lower_left = &layout.rows[i].cards[j];
                }
            }
        }

        std::vector<card> active_cards = {layout.rows[6].cards[0],
                                          layout.rows[6].cards[1],  //making active cards
                                          layout.rows[6].cards[2],
                                          layout.rows[6].cards[3],  //filling it with
                                          layout.rows[6].cards[4],
                                          layout.rows[6].cards[5],  //lowest row
                                          layout.rows[6].cards[6]};


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
            delete[] layout.rows[i].cards;
        delete[] layout.rows;
    }
    float convergence = float(converge_count) / (converge_count + divergence_count) * 100;
    std::cout << "Convergence: " << convergence << "%"  << std::endl;
    return 0;
}

