#ifndef H_H
#define H_H

#include <vector>
#include <string>

struct Player {
    std::vector<int> cards;
};

// Колода
void CreateDeck(std::vector<int>& deck);
void ShuffleDeck(std::vector<int>& deck);
void DealCards(const std::vector<int>& deck, Player& p1, Player& p2);

// Игра
void PlayGame(Player& p1, Player& p2);

// Вспомогательные функции
std::string CardToString(int card);
int CompareCards(int c1, int c2);
void AddLog(std::vector<std::string>& log, int round, int c1, int c2, int winner);
void PrintGameWinner(const Player& p1, const Player& p2);

// Меню
void ShowMenu();
void ShowRules();
int GetMenuChoice();

#endif
