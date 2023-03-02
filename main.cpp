#include <time.h>
#include "./Game.h"

int main(void)
{
    srand(time(NULL));

    Game jeu;
    jeu.run();
    return 0;
}
