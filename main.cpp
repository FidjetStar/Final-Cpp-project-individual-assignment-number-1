#include <iostream>
#include "h.h"
#ifdef _WIN64
#include <windows.h>
#endif

int main() {
    using namespace std;
    #ifdef _WIN64
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    #endif
    vector<int> deck;
    Player player1, player2;
    while (true) {
        ShowMenu();
        int choice = GetMenuChoice();
        if (choice == 1) {
            CreateDeck(deck);
            ShuffleDeck(deck);
            DealCards(deck, player1, player2);
            PlayGame(player1, player2);
        }
        else if (choice == 2) {
            ShowRules();
        }
        else {
            cout << "Программа завершена.\n";
            break;
        }
    }
    return 0;
}


