#include "ConsoleGameService.h"

#ifdef _WIN32
#include <windows.h>

static void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hOut, &mode);
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
}

void ConsoleGameService::hideCursor()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

void ConsoleGameService::init() {
    enableANSI();
    hideCursor();
}

void ConsoleGameService::resetGame(DisplayShelf& shelf, Robot& r1, Robot& r2)
{
    shelf.reset();
    r1.reset();
    r2.reset();
}

void ConsoleGameService::clear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
#endif