#include "header.h"

void erase(const card &erasing_card, std::vector<card> &changing_cards) {
    for (auto it = changing_cards.begin(); it != changing_cards.end(); ++it) { //deleting card
        if ((it->upper_right == erasing_card.upper_right) &&
            (it->upper_left == erasing_card.upper_left) &&
            (it->lower_left == erasing_card.lower_left) &&
            (it->lower_right == erasing_card.lower_right) &&
            (it->value == erasing_card.value)) {
            changing_cards.erase(it);
            break;
        }
    }

    if (erasing_card.upper_left != nullptr) {     //checking if upper cards became active
        erasing_card.upper_left->lower_right = nullptr;
        if (erasing_card.upper_left->lower_left == nullptr) {
            changing_cards.push_back(*erasing_card.upper_left);
        }
    }
    if (erasing_card.upper_right != nullptr) {
        erasing_card.upper_right->lower_left = nullptr;
        if (erasing_card.upper_right->lower_right == nullptr) {
            changing_cards.push_back(*erasing_card.upper_right);
        }
    }
}

bool is_numeric(const std::string &string_for_number) {
    for (int i = 0; i < string_for_number.size(); i++)
        if (std::isdigit(string_for_number[i]) == false)
            return false;
    return true;
}

bool is_input_correct(std::vector<std::vector<int>> &deck, std::string &value, int &int_value) {
    if (is_numeric(value)) //checking if string is numeric
        int_value = std::stoi(value);
    else if (value.size() == 1) {         //checking if user enter picture
        if ((value[0] == 'J') or (value[0] == 'j'))
            int_value = 11;
        if ((value[0] == 'Q') or (value[0] == 'q'))
            int_value = 12;
        if ((value[0] == 'K') or (value[0] == 'k'))
            int_value = 13;
        if ((value[0] == 'A') or (value[0] == 'a'))
            int_value = 1;
    } else {
        std::cout << "Error. Enter the number" << std::endl;
        return false;
    }


    if ((int_value > 13) or (int_value < 1)) {     //checking if user enter incorrect number
        std::cout << "Incorrect value. Too much or little." << std::endl;
        return false;
    } else if (deck[int_value - 1].empty()) {     //checking if user enter too much same cards
        {
            std::cout << "These cards are over" << std::endl;
            return false;
        }
    } else {                                     // if all is correct remove entered card from deck
        deck[int_value - 1].pop_back();
        return true;
    }
}

std::vector<int> shuffle(std::vector<std::vector<int>> &deck) {
    srand(time(nullptr));
    bool are_empty_deleted = false; //deleting empty values from deck
    do {
        are_empty_deleted = true;
        for (auto it = deck.begin(); it != deck.end(); ++it) {
            if (it->empty()) {
                deck.erase(it);
                are_empty_deleted = false;
                break;
            }
        }
    } while (!are_empty_deleted);

    std::vector<int> shuffled_values;
    while (!deck.empty()) {
        short int value_index = rand() % deck.size(); //getting random value
        shuffled_values.push_back(
                deck[value_index][deck[value_index].size() - 1]);  //recieving the last element in value
        deck[value_index].pop_back(); // deleting last element with this value
        if (deck[value_index].empty()) {  //checking if now all cards with this value is over
            deck.erase(deck.begin() + value_index);
        }
    }
    return shuffled_values;
}

