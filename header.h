#ifndef HW1_HEADER_H
#define HW1_HEADER_H

#include <iostream>
#include <vector>
#include <ctime>

struct card {
    card *upper_left = nullptr;
    card *upper_right = nullptr;
    card *lower_left = nullptr;
    card *lower_right = nullptr;
    int value;
};
struct row {
    card *cards;
};
struct layout {
    row *rows;
};

void erase(const card erasing_card, std::vector<card> &changing_cards);

bool is_numeric(const std::string &string_for_number);

bool is_input_correct(std::vector<std::vector<int>> &deck, std::string &value, int &int_value);

std::vector<int> shuffle(std::vector<std::vector<int>> deck);

bool try_delete(std::vector<card> &cards);

bool try_delete_with_top_card(std::vector<card> &cards, int& top_card, std::vector<int> &fall_cards,
                              std::vector<int>& remaining_deck);
bool retake_deck(std::vector<int> &remaining_deck, std::vector<int> &fall_cards);

#endif //HW1_HEADER_H
