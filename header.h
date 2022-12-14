#ifndef HW1_HEADER_H
#define HW1_HEADER_H
#include <iostream>
#include <vector>
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
void erase(const card &erasing_card, std::vector<card> &changing_cards);
#endif //HW1_HEADER_H
