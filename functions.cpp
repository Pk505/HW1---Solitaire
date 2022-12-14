#include "header.h"
void erase(const card &erasing_card, std::vector<card> &changing_cards){
    for (auto it = changing_cards.begin(); it != changing_cards.end(); ++it){ //deleting card
        if ((it->upper_right == erasing_card.upper_right) &&
            (it->upper_left == erasing_card.upper_left) &&
            (it->lower_left == erasing_card.lower_left) &&
            (it->lower_right == erasing_card.lower_right) &&
            (it->value == erasing_card.value)){
            changing_cards.erase(it);
            break;
        }
    }

    if (erasing_card.upper_left != nullptr){     //checking if upper cards became active
        erasing_card.upper_left->lower_right = nullptr;
        if (erasing_card.upper_left->lower_left == nullptr){
            changing_cards.push_back(*erasing_card.upper_left);
        }
    }
    if (erasing_card.upper_right != nullptr){
        erasing_card.upper_right->lower_left = nullptr;
        if (erasing_card.upper_right->lower_right == nullptr){
            changing_cards.push_back(*erasing_card.upper_right);
        }
    }
}