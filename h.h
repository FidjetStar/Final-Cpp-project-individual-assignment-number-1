#ifndef H_H
#define H_H

#include <vector>
#include <string>

struct Player {
    std::vector<int> cards;
};


void CreateDeck(std::vector<int>& deck);
void ShuffleDeck(std::vector<int>& deck);
void DealCards(const std::vector<int>& deck, Player& p1, Player& p2);


void PlayGame(Player& p1, Player& p2);


std::string CardToString(int card);


void ShowMenu();
void ShowRules();
int GetMenuChoice();

#endif
