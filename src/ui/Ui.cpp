#include <iostream>
#include "Ui.h"

void renderUI(const DisplayShelf& shelf, int pos1, int pos2, int score1, int score2, int timeLeft)
{
    std::cout << "\033[H";

    std::cout << "================= CONSOLE GAME =================\n\n";

    std::cout << "Time Left: " << timeLeft << "sec\n";
    std::cout << "Global Lock: "
        << (shelf.isGlobalLocked() ? "ACTIVE\n" : "OFF\n");

    std::cout << " Player1              Display Shelf             Player2\n";
    std::cout << "-------------------------------------------------------------\n";

    const char* armL = "<==|";
    const char* armR = "|==>";

    int size = shelf.getSize();

    for (int i = 0; i < size; i++) {
        if (pos1 == i) std::cout << "  " << armL << "   ";
        else           std::cout << "        ";

        const Item& item = shelf.peek(i);
        if (item.name.empty())
            std::cout << "[" << i << "] empty            ";
        else
            std::cout << "[" << i << "] " << item.name << "(+" << item.value << ") ";

        if (pos2 == i) std::cout << "   " << armR;
        else           std::cout << "        ";

        std::cout << "\n";
    }

    std::cout << "-------------------------------------------------------------\n\n";
    std::cout << "Player1 Score: " << score1 << "\n";
    std::cout << "Player2 Score: " << score2 << "\n\n";

    std::cout << "[Controls]\n"
        << " Player1: W/S = Move, D = Select\n"
        << " Player2: I/K = Move, L = Select\n";
}