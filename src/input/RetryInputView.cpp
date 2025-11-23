#include "RetryInputView.h"
#include <iostream>

bool RetryInputView::askRetry()
{
    std::cout << "\nRetry? (Y/N): ";

    char c;
    while (true)
    {
        std::cin >> c;
        c = toupper(c);

        if (c == 'Y') return true;
        if (c == 'N') return false;

        std::cout << "Invalid input. Enter Y or N: ";
    }
}