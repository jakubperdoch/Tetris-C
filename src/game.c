#include "game.h"
#include "constants.h"

int delay_calcular(int lines_cleared)
{
    int delay = FALL_DELAY - (lines_cleared / 5) * FALL_SPEED_MULTIPLIER;
    return delay > MIN_DELAY ? delay : MIN_DELAY;
}
