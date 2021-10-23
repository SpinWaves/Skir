#ifndef __FPS__
#define __FPS__

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    unsigned int fps;
    unsigned int out_fps;
    unsigned int ticks;
    unsigned int out_ticks;
    double ns;
    uint32_t timer;
    unsigned long long before;
    unsigned long long now;
    bool make_update;
} FPS_counter;

void initFPS(FPS_counter *counter);
unsigned long getFPS(FPS_counter *counter);
unsigned long getUPS(FPS_counter *counter);
void updateFPS(FPS_counter *counter);

#endif // __FPS__
