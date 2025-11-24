#include <iomanip>
#include <iostream>
#include <sstream>
#include "Ui.h"

void renderUI(const DisplayShelf& shelf, int pos1, int pos2, int score1, int score2, int timeLeft)
{
    std::cout << "\033[H";

    std::cout << "================= CONSOLE GAME =================\n\n";
    std::cout << "Time Left: " << timeLeft << "sec   \n";
    std::cout << "Global Lock: " << (shelf.isGlobalLocked() ? "ACTIVE\n" : "OFF\n");

    constexpr int leftCol = 12;
    constexpr int shelfCol = 25;
    constexpr int rightCol = 14;

    constexpr int ARM_LEN = 10;

    std::string lockOwner = shelf.getLockOwner();

    constexpr const char* leftArmPadding = "      ";
    constexpr const char* rightArmPadding = "";

    std::string armLColored;
    std::string armRColored;

    if (lockOwner == "Player1") {
        armLColored = std::string(leftArmPadding) + "<==|";
        armRColored = std::string(rightArmPadding) + "\033[31m|==>\033[0m";
    }
    else if (lockOwner == "Player2") {
        armLColored = std::string(leftArmPadding) + "\033[31m<==|\033[0m";
        armRColored = std::string(rightArmPadding) + "|==>";
    }
    else {
        armLColored = std::string(leftArmPadding) + "<==|";
        armRColored = std::string(rightArmPadding) + "|==>";
    }

    std::cout
        << std::left << std::setw(leftCol) << "   [Player1]"
        << std::left << std::setw(shelfCol) << "   [Display Shelf]"
        << std::left << std::setw(rightCol) << "[Player2]"
        << "\n";

    std::cout << std::string(leftCol + shelfCol + rightCol, '-') << "\n";

    const char* armL = "        <==|";
    const char* armR = "|==>";

    int size = shelf.getSize();

    for (int i = 0; i < size; i++) {
        if (pos1 == i)
            std::cout << std::setw(leftCol - ARM_LEN) << "" << armLColored;
        else
            std::cout << std::setw(leftCol) << "";

        const Item& item = shelf.peek(i);
        std::ostringstream itemText;
        if (item.name.empty())
        {
            itemText << "   [" << i << "] empty";
        }
        else
        {
            itemText << "   [" << i << "] " << item.name;

            if (!item.isDoubleScore && !item.isGlobalLock)
            {
                itemText << " (+" << item.value << ")";
            }
        }

        std::cout << std::left << std::setw(shelfCol) << itemText.str();

        if (pos2 == i)
            std::cout << std::left << std::setw(rightCol) << armRColored;
        else
            std::cout << std::left << std::setw(rightCol) << "";

        std::cout << "\n";
    }

    std::cout << std::string(leftCol + shelfCol + rightCol, '-') << "\n\n";

    std::cout << "Player1 Score: " << score1 << "\n";
    std::cout << "Player2 Score: " << score2 << "\n\n";

    std::cout << "[Controls]\n"
        << " Player1: W/S = Move, D = Select\n"
        << " Player2: I/K = Move, L = Select\n";
}
