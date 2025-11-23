#include "GameController.h"
#include "ConsoleGameService.h"

int main()
{
    ConsoleGameService service;

    GameController controller(service);
    controller.run();

    return 0;
}