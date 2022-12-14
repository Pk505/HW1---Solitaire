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

int main() {
    layout user_layout;
    user_layout.rows = new row[7];

    //filling the layout with user's values
    for (int i = 0; i < 7; i++) {
        user_layout.rows[i].cards = new card[i+1];
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
    
    for (int i = 0; i < 7; i++)
        delete[] user_layout.rows[i].cards;
    delete[] user_layout.rows;

    return 0;
}

