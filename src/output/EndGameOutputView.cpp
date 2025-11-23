#include "EndGameOutputView.h"
#include <iostream>

void EndGameOutputView::printResult(int score1, int score2)
{
    std::cout << "\n===== GAME OVER =====\n";
    std::cout << "Player1 Score: " << score1 << "\n";
    std::cout << "Player2 Score: " << score2 << "\n";

    if (score1 > score2)      std::cout << "Winner: Player 1!\n";
    else if (score2 > score1) std::cout << "Winner: Player 2!\n";
    else                      std::cout << "Draw!\n";
}