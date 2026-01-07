#include "h.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

void CreateDeck(std::vector<int>& deck) {
    deck.clear();
    for (int rank = 6; rank <= 14; rank++)
        for (int i = 0; i < 4; i++)
            deck.push_back(rank);
}

void ShuffleDeck(std::vector<int>& deck) {
    std::srand(std::time(0));
    std::vector<int> shuffled;
    while (!deck.empty()) {
        int index = std::rand() % deck.size();
        shuffled.push_back(deck[index]);
        deck[index] = deck.back();
        deck.pop_back();
    }
    deck = shuffled;
}

void DealCards(const std::vector<int>& deck, Player& p1, Player& p2) {
    p1.cards.clear();
    p2.cards.clear();
    for (int i = 0; i < deck.size(); i++) {
        if (i % 2 == 0) {
            p1.cards.push_back(deck[i]); }
        else {
            p2.cards.push_back(deck[i]); }
    }
}

std::string CardToString(int card) {
    if (card <= 10) {return std::to_string(card); }
    if (card == 11) {return "J"; }
    if (card == 12) {return "Q"; }
    if (card == 13) {return "K"; }
    return "A";
}

int CompareCards(int c1, int c2) {
    if (c1 > c2) {return 1;}
    if (c2 > c1) {return 2;}
    return 0;
}

void AddLog(std::vector<std::string>& log, int round, int c1, int c2, int winner) {
    std::string entry =
        "Раунд " + std::to_string(round) + ": " +
        CardToString(c1) + " vs " + CardToString(c2);

    if (winner == 1) {
        entry += " → Победил Игрок 1"; }
    else if (winner == 2) {
        entry += " → Победил Игрок 2"; }
    else
        {entry += " → Ничья"; }

    log.push_back(entry);
}

void PrintGameWinner(const Player& p1, const Player& p2) {
    if (p1.cards.size() > p2.cards.size())
        {std::cout << "ПОБЕДИЛ ИГРОК 1\n";}
    else if (p2.cards.size() > p1.cards.size())
        {std::cout << "ПОБЕДИЛ ИГРОК 2\n";}
    else
        {std::cout << "НИЧЬЯ\n"; }
}

void PlayGame(Player& p1, Player& p2) {
    std::vector<std::string> log;
    int round = 1;
    std::cout << "\nИГРА НАЧАЛАСЬ\nНажмите Enter\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (!p1.cards.empty() && !p2.cards.empty() && round <= 1000) {
        std::vector<int> table;
        std::cout << "\n--------------------------------\n";
        std::cout << "Раунд " << round << '\n';
        std::cout << "Карты у Игрока 1: [" << p1.cards.size() << "]\n";
        std::cout << "Карты у Игрока 2: [" << p2.cards.size() << "]\n";
        std::cout << "Нажмите Enter, чтобы открыть карты\n";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        int c1 = p1.cards.front();
        int c2 = p2.cards.front();
        p1.cards.erase(p1.cards.begin());
        p2.cards.erase(p2.cards.begin());
        table.push_back(c1);
        table.push_back(c2);
        std::cout << "Игрок 1 открыл: " << CardToString(c1) << '\n';
        std::cout << "Игрок 2 открыл: " << CardToString(c2) << '\n';
        // ---------- СПОР ----------
        while (c1 == c2 && !p1.cards.empty() && !p2.cards.empty()) {
            std::cout << "СПОР! Карты равны(игра продолжится пока у одного из игркоов не окажется карта более выского ранга).\n";
            std::cout << "Каждый кладет карту рубашкой вниз(ставка)\n";
            table.push_back(p1.cards.front());
            table.push_back(p2.cards.front());
            p1.cards.erase(p1.cards.begin());
            p2.cards.erase(p2.cards.begin());
            if (p1.cards.empty() || p2.cards.empty()) {
                if (p1.cards.empty()) {
                    std::cout << "У первого игрока закончились карты во время спора.\n";
                }
                else {
                    std::cout << "У второго игрока закончились карты во время спора.\n";
                }
                break; }
            std::cout << "Нажмите Enter, чтобы открыть дополнительные карты\n";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            c1 = p1.cards.front();
            c2 = p2.cards.front();
            p1.cards.erase(p1.cards.begin());
            p2.cards.erase(p2.cards.begin());
            table.push_back(c1);
            table.push_back(c2);
            std::cout << "Дополнительно:\n";
            std::cout << "Игрок 1: " << CardToString(c1) << '\n';
            std::cout << "Игрок 2: " << CardToString(c2) << '\n';
        }
        int winner = CompareCards(c1, c2);
        if (winner == 1) {
            std::cout << "Победил Игрок 1 в этом раунде!\n";
            for (int card : table)
                p1.cards.push_back(card);
        }
        else if (winner == 2) {
            std::cout << "Победил Игрок 2 в этом раунде!\n";
            for (int card : table)
                p2.cards.push_back(card);
        }
        AddLog(log, round, c1, c2, winner);
        round++;
    }
    std::cout << "\n===== ИГРА ОКОНЧЕНА =====\n";
    PrintGameWinner(p1, p2);
    while (true) {
        std::cout << "\nЧто хотите сделать дальше?\n";
        std::cout << "1 - Вернуться в меню\n";
        std::cout << "2 - Показать лог боев\n";
        std::cout << "Выберите 1 или 2: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Введите число 1 или 2.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (choice == 1) {
            break;
        }
        else if (choice == 2) {
            std::cout << "\nЛОГ ХОДОВ:\n";
            for (const std::string& s : log)
                std::cout << s << '\n';
            std::cout << "\nНажмите Enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        else {
            std::cout << "Неверный ввод. Введите 1 или 2.\n";
        }
    }
}

void ShowMenu() {
    std::cout << "\nСИМУЛЯТОР КАРТОЧНОЙ ИГРЫ \"ПЬЯНИЦА\"\n";
    std::cout << "\n1. Начать игру\n";
    std::cout << "2. Правила\n";
    std::cout << "3. Выход\n";
    std::cout << "Выбор: ";
}

int GetMenuChoice() {
    int choice;
    while (!(std::cin >> choice) || choice < 1 || choice > 3) {
        std::cout << "Ошибка. Введите 1-3: ";
        std::cin.clear(); // сбрасывает фалг ошибки cin
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore(); // В буфере остаётся символ Enter ('\n') удаляем его
    return choice;
}

void ShowRules() {
    std::cout << "\nПРАВИЛА ИГРЫ \"ПЬЯНИЦА\"\n\n";
    std::cout << "1. Игроки и колода:\n";
    std::cout << "   - Два игрока.\n";
    std::cout << "   - Колода из 36 карт (6, 7, 8, 9, 10, J, Q, K, A, 4 масти).\n";
    std::cout << "   - Колода перемешивается и раздаётся поровну.\n\n";
    std::cout << "2. Ход игры:\n";
    std::cout << "   - Каждый раунд оба игрока открывают верхнюю карту.\n";
    std::cout << "   - Карты сравниваются по номиналу (масть не учитывается).\n";
    std::cout << "   - Старшая карта выигрывает, игрок забирает все карты раунда.\n";
    std::cout << "   - При равенстве карт начинается спор (война).\n\n";
    std::cout << "3. Спор (война):\n";
    std::cout << "   - Каждый игрок кладёт одну карту рубашкой вниз.\n";
    std::cout << "   - Затем открывают следующую верхнюю карту для сравнения.\n";
    std::cout << "   - Повторяется, пока не выявится победитель раунда или не закончатся карты.\n";
    std::cout << "   - Победитель забирает все карты на столе, включая карты рубашкой вниз.\n\n";
    std::cout << "4. Окончание игры:\n";
    std::cout << "   - Игра продолжается до полного сбора карт одним игроком или 1000 раундов.\n";
    std::cout << "   - Побеждает игрок с большим количеством карт.\n";
    std::cout << "   - При равенстве карт объявляется ничья.\n\n";
    std::cout << "5. Лог раундов:\n";
    std::cout << "   - Программа ведёт журнал ходов (открытые карты и победитель раунда).\n";
    std::cout << "   - В конце игры можно вывести лог или вернуться в меню.\n\n";
    std::cout << "6. Управление:\n";
    std::cout << "   - Нажимайте Enter для подтверждения действий (открытие карт, продолжение спора, просмотр логов).\n\n";
    std::cout << "Нажмите Enter для возврата в меню";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


