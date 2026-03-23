#ifndef CS2SX_COUNTER_H
#define CS2SX_COUNTER_H

#pragma once
#include "_forward.h"

struct Counter
{
    int value;
    int f_ticks;
};

Counter* Counter_New();
void Counter_Increment(Counter* self);
void Counter_Decrement(Counter* self);
void Counter_Reset(Counter* self);
void Counter_Tick(Counter* self);
int Counter_GetValue(Counter* self);
int Counter_GetTicks(Counter* self);
bool Counter_IsZero(Counter* self);



#endif
